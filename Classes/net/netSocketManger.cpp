//
//  netSocketManger.cpp
//  sockettest
//
//  Created by 俊盟科技1 on 11/14/14.
//
//

#include "netSocketManger.h"
#include "netConfig.h"
#include "ODSocket.h"
#include "Queue.h"
#include <thread>
//#include <endian.h>
#include "zlib.h"
#include<netinet/in.h>


static ODSocket cSocket;
bool isConnect = false;

using namespace cocos2d;
typedef std::map<uint64_t, SendDataDelegate*> SendDelegateMap;

SendDelegateMap m_sendDelegateList;             //向服务器发送消息代理

PushDataDelegate *m_pushDelegate = NULL;        //接收服务器消息代理

SocketStatusDelegate *m_statusDelegate = NULL;  //网络状态代理

CQueue<SocketData>  m_sendQueue;//发送连表
CQueue<SocketData>  m_mainQueue;//接收连表
CEvent *m_sendEvent = NULL;
uint64_t m_sn = 0;
bool m_isFirst;
//std::thread::id m_sendNtid;
//std::thread::id m_recvNtid;
std::mutex m_mutexx;

static netSocketManger *s_sharednetSocketManger = nullptr;

netSocketManger *netSocketManger::sharednetSocketManger()
{
    m_mutexx.lock();
    if (s_sharednetSocketManger == nullptr)
    {
        s_sharednetSocketManger = new netSocketManger();
        if (!s_sharednetSocketManger || !s_sharednetSocketManger->init())
        {
            CC_SAFE_DELETE(s_sharednetSocketManger);
        }
    }
    m_mutexx.unlock();
    return s_sharednetSocketManger;
}

void netSocketManger::destroyInstance()
{
    
    CC_SAFE_RELEASE_NULL(s_sharednetSocketManger);
}

netSocketManger::netSocketManger(void)
{
  m_isFirst = true;
}

netSocketManger::~netSocketManger(void)
{
   
}

bool netSocketManger::init()
{
    bool bRet = false;
    do
    {
        
        
        
        
        
        //查看服务器反回数据方法
        Director::getInstance()->getScheduler()->scheduleUpdate(this, -1, false);
        
        
        //threadSend.detach();
        //threadRecive.detach();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

int netSocketManger::send(NetWorkCommandStruct module, std::string &body, SendDataDelegate *delegate)
{
    if (!delegate ||  !isConnect) {
        return -1;
    }
    
    m_sn++;
    
    m_sendDelegateList[m_sn] = delegate;
    
    SocketData *data = newSocketData();
    data->sn = m_sn;
    
    if (body.empty()) {
        data->body = "";
        data->bodyLen = 0;
    }else {
        int bodyStrLen = (int)body.size();
        //data->body = (char*)malloc(bodyStrLen);
        const char* tmp = body.data();
        data->sendData = (char*)malloc(bodyStrLen);
        memcpy(data->sendData, tmp, bodyStrLen);
        data->bodyLen = bodyStrLen;
    }
    
    data->module.cmd = module.cmd;
    
    m_sendQueue.Push(data);
    
    m_sendEvent->Post();
    
    return (int)m_sn;
}

void netSocketManger::removeSendDelegate(SendDataDelegate *delegate)
{
    SendDelegateMap::iterator it = m_sendDelegateList.begin();
    while (it != m_sendDelegateList.end()) {
        if (it->second == delegate)
            m_sendDelegateList.erase(it++);
        else
            ++it;
    }
}

void netSocketManger::setPushDelegate(PushDataDelegate *delegate)
{
    m_pushDelegate = delegate;
}
PushDataDelegate* getPushDelegate()
{
    return m_pushDelegate;
}

void netSocketManger::setStatusDelegate(SocketStatusDelegate *delegate)
{
    m_statusDelegate = delegate;
}
SocketStatusDelegate* netSocketManger::getStatusDelegate()
{
    return m_statusDelegate;
}

//主线程更新
void netSocketManger::update(float dt)
{
    if (!m_mainQueue.IsEmpty()) {
        SocketData *data = m_mainQueue.Pop();
        
        if (data->eventType == REQUEST) {
            if (m_pushDelegate) {
                m_pushDelegate->pushHandler(data);
            }
        }else if (data->eventType == RESPONSE) {
            SendDelegateMap::iterator it = m_sendDelegateList.find(data->sn);
            if (it != m_sendDelegateList.end()) {
                SendDataDelegate *delegate = it->second;
                m_sendDelegateList.erase(it);
                delegate->sendHandler(data);
            }
        }else if (data->eventType == CONNECT_SUCCEED || data->eventType == CONNECT_FAIL || data->eventType == DISCONNECT) {
            if (data->eventType != CONNECT_SUCCEED) {
                if (!threadSend.joinable()) {//线程已启动
                    threadSend.~thread();
                    delete m_sendEvent;
                    m_sendEvent = NULL;
                    
                }
                if (!threadRecive.joinable()) {
                    threadRecive.~thread();
                }
                
                while (!m_sendQueue.IsEmpty()) {
                    SocketData *sendData = m_sendQueue.Pop();
                    //litaoming update
                    //CC_SAFE_FREE(data->body);
                    //CC_SAFE_FREE(sendData->reciveBody);
                    free(sendData);
                }
                
                while (!m_mainQueue.IsEmpty()) {
                    SocketData *mainData = m_mainQueue.Pop();
                    if (mainData != data) {
                        //CC_SAFE_FREE(mainData->body);
                        //CC_SAFE_FREE(mainData->addContent);
                    }
                    
                }
                if (isConnect) {
                    cSocket.Close();
                    cSocket.Clean();
                    isConnect = false;
                }
                m_isFirst = true;
                m_sendDelegateList.clear();
            }
            if (m_statusDelegate) {
                m_statusDelegate->statusHandler(data->eventType);
            }
        }
        //CC_SAFE_FREE(data->body);
        //CC_SAFE_FREE(data->addContent);
        free(data);
    }
}
void netSocketManger::connectSocket()
{
    
    if (!isConnect) {
        cSocket.Init();
        cSocket.Create(AF_INET,SOCK_STREAM,0);
        if (m_sendEvent == NULL) {
            m_sendEvent = new CEvent();
        }
        
        s_tea = 0;
        threadSend = std::thread(&netSocketManger::sendThread,this);//创建一个分支线程，回调到sendThread函数里
        threadRecive = std::thread(&netSocketManger::reciveThread,this);
        threadSend.detach();
    }
    
    log("send thread is run");
}
void netSocketManger::endSocket()
{
    if (!threadSend.joinable()) {//线程已启动
        threadSend.~thread();
        delete m_sendEvent;
        m_sendEvent = NULL;
        
    }
    if (!threadRecive.joinable()) {
        threadRecive.~thread();
    }

    while (!m_sendQueue.IsEmpty()) {
        SocketData *sendData = m_sendQueue.Pop();
        //CC_SAFE_FREE(sendData->body);
        free(sendData);
    }
    
    while (!m_mainQueue.IsEmpty()) {
        SocketData *mainData = m_mainQueue.Pop();
        CC_SAFE_FREE(mainData);
        //CC_SAFE_FREE(mainData->addContent);
    }
    
    if (isConnect) {
        cSocket.Close();
        cSocket.Clean();
        isConnect = false;
    }
    m_isFirst = true;
    m_sendDelegateList.clear();
}
std::list<ServerAdressST> netSocketManger::getServerList()
{
    return m_serverList;
}
void netSocketManger::startReciveThread()
{
    threadRecive.detach();//启动接收线程
}
//发送数据线程
void netSocketManger::sendThread()
{

    bool connect = cSocket.Connect(kServerIP,kServerPort);
   // cSocket.Send("bbb",strlen("bbb")+1,0);

    if (connect) {
        isConnect = true;
        SocketData *errorData = newSocketData();
        errorData->eventType = CONNECT_SUCCEED;
        m_mainQueue.Push(errorData);
        netSocketManger::sharednetSocketManger()->startReciveThread();
        m_sendEvent->Lock();
        while (true) {
            while (!m_sendQueue.IsEmpty()) {
                
                SocketData *data = m_sendQueue.Pop();
                
                uLong comprLen = data->bodyLen;
                //std::string _datastr = data->body;
                const char *compr = data->sendData;
                
                T_MSGHEAD_T msgHead;
                
                msgHead.cmd = (unsigned short)data->module.cmd;
                msgHead.com = 0;
                msgHead.enc = 0;
                msgHead.eno = 0;
                msgHead.idx = (uInt)data->sn;
                msgHead.len = (unsigned short)comprLen;
                msgHead.tea = s_tea;
                
            
                uint siz = sizeof(T_MSGHEAD_T);
                
                unsigned char *sendData = (unsigned char*)malloc(siz+comprLen);
                unsigned int pos = 0;
                
                *(LP_MSGHEAD_T)sendData = msgHead;//包标识
                pos += siz;
                
                memcpy(&sendData[pos], compr, comprLen);//body
                pos += comprLen;

    //包头+protobuf

               int ret = cSocket.Send((char*)sendData,pos,0);
                
                if (ret <= 0) {
                    m_sendEvent->Unlock();
                    free(sendData);
                    SocketData *errorData = newSocketData();
                    errorData->eventType = DISCONNECT;
                    m_mainQueue.Push(errorData);
                    //exit(0);
                    return;
                }
                
                free(data->sendData);
                free(data);
                free(sendData);
                log("-----发送数据长度len:%d------",msgHead.len);
                log("-----------");
                
            }
            m_sendEvent->Wait();
        }
        m_sendEvent->Unlock();
    }else {
        isConnect = false;
        SocketData *errorData = newSocketData();
        errorData->eventType = CONNECT_FAIL;
        m_mainQueue.Push(errorData);
    }
}
//接收数据线程
void netSocketManger::reciveThread()
{
    char buff[MAX_BUFF];
    int recv_len = 0;
    bool hasMorePackets = false;
 
    while(true)
    {
        if( !hasMorePackets ) {
            
            int ret = cSocket.Recv(buff, MAX_BUFF - recv_len, 0);
            
            if (ret <= 0) {
                isConnect = false;
                SocketData *errorData = newSocketData();
                errorData->eventType = DISCONNECT;
                m_mainQueue.Push(errorData);
                break;
            }
            if(ret < 1)
                break;
        }
        
        T_MSGHEAD_T reciveCmd;
        
        reciveCmd = *(LP_MSGHEAD_T)&buff[0];
        
        uint siz = sizeof(T_MSGHEAD_T);
        log("*****************************************");
        
        unsigned int pos = siz;
        SocketData *data = newSocketData();
        
        log("get data len=%d",reciveCmd.len);// 数据体长度
        log("get data cmd=%d",reciveCmd.cmd);// 协议号
        data->module.cmd = reciveCmd.cmd;
        log("get data eno=%d",reciveCmd.eno);// 错误码
        if (reciveCmd.eno == 10) { //10错误码表示服务器推送消息
            data->eventType = REQUEST;  //服务器请求,或者也叫推送
        }else{
            data->eventType = RESPONSE; //服务器回应
        }
        log("get data enc=%02X",reciveCmd.enc);// 加密
        log("get data com=%02X",reciveCmd.com);// 压缩
        log("get data tea=%d",reciveCmd.tea);// 会话
        s_tea = reciveCmd.tea;
        log("get data idx=%d",reciveCmd.idx);// 包索引
        data->sn = reciveCmd.idx;
        
       // std::string _data(&buff[pos], reciveCmd.len);
       
        //data->body->ParseFromArray(&buff[pos], reciveCmd.len);
        std::string datax(&buff[pos], reciveCmd.len);
        data->body = std::string(datax);
        pos += reciveCmd.len;
        data->bodyLen = reciveCmd.len;
        
        log("*************************************************");
        log("*************************************************");
        
        m_mainQueue.Push(data);
        
        hasMorePackets = false;

        //exit(0);
        //
        
//        if(recv_len > packetLen)
//        {
//            memcpy(buff, &buff[packetLen], recv_len - packetLen);
//            hasMorePackets = true;
//        }else {
//            hasMorePackets = false;
//        }
//recv_len -= packetLen;
        
    }
    
}