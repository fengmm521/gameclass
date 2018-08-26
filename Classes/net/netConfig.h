//
//  netConfig.h
//  sockettest
//  使用结构体来进行游戏属性存储会比较方便快捷
//
//  Created by 俊盟科技1 on 11/13/14.
//
//

#ifndef sockettest_netConfig_h
#define sockettest_netConfig_h

using namespace std;

typedef unsigned long  uLong; /* 32 bits or more */
//socket服务器
#define MAX_BUFF    1024*1000
//#define kServerIP "192.168.1.77"
#define kServerPort 9101
#define kServerIP "192.168.1.6"
//内网还有一个服务器，发内部测试版的时候用
//192.168.1.6 ： 9101

#define kFormid       "JM"         //没有平台时，设置为JM
#define kFromuid      ""           //没有时可以为空
#define kSession      "testEmpty"  //
#define kToken  "6c0da7ccc6855ef6" //服务器加密项,为服务器平台效验
#define kVersionClient "1000"      //客户端版本,大版本号x1000 + 小版本号如，1.0版本＝1000
#define kDeviceNumber "12345"      //终端设备型号
#define kSystemVersion "android"   //终端系统版本,大版本号x1000 + 小版本号如，1.0版本＝1000
#define kUniqueness   "1"          //终端设备号，服务器以些编号确定用户id


enum client_protocol {
    CP_START_NUMBER 	= 10000,
    
    CP_ECHO_TEST 		= 10001,		// 回路测试
    
    CP_LOGIN_SERVER 	= 11001,	// 登陆	// Request: Login_Request, Response: Login_Response
    
//客户端登陆
//    // 第一步伪装登陆
//    message Login_Request {
//        optional bytes formid  = 1;		// 平台ID
//        optional bytes fromuid = 2;		// 平台用户ID
//        optional bytes session = 3; 	// 平台登陆会话
//        optional bytes token   = 4; 	// 服务器加密项
//        optional bytes version = 5; 	// 客户端游戏版本
//        optional bytes device  = 6; 	// 终端设备型号
//        optional bytes system  = 7; 	// 终端系统版本
//        optional bytes uniqueness = 8; 	// 终端设备号
//    }
//服务器返回
//    // 第一步伪装登陆
//    message Login_Response {
//        optional bytes uid  = 1;		// 用户ID
//        optional bytes fromuid = 2;		// 平台用户ID
//    }
    
    CP_LOGOUT_SERVER 	= 11002,	// 登出
    
    CP_LOAD_ROLE		= 11101,	// 获取主角   	// Request: NULL, Response: Role
    
//客户端发送空数据
//服务器返回
//    message Role {
//        optional sint32 figure 	= 1;	// 形象
//        optional sint32 viplv 	= 2;	// VIP 等级
//        optional sint32 viptub 	= 3; 	// VIP 经验
//        optional sint32 mclv  	= 4;    // 主角等级
//        optional sint32 mctub 	= 5;    // 主角经验
//        optional sint32 newbies = 6;	// 新手
//        optional bytes name 	= 7;	// 主角色名称
//    }
    CP_CREATE_ROLE 		= 11102,	// 创建主角 		// Request: CreateRole_Request, Response: Role
//客户端发送
//    message CreateRole_Request {
//        optional sint32 figure = 1;		// 形像
//        optional bytes  name   = 2;		// 角色名
//    }
//服务器端返回
//    message Role {
//        optional sint32 figure 	= 1;	// 形象
//        optional sint32 viplv 	= 2;	// VIP 等级
//        optional sint32 viptub 	= 3; 	// VIP 经验
//        optional sint32 mclv  	= 4;    // 主角等级
//        optional sint32 mctub 	= 5;    // 主角经验
//        optional sint32 newbies = 6;	// 新手
//        optional bytes name 	= 7;	// 主角色名称
//    }

    CP_CHECK_NAME 		= 11103,	// 检查昵称 		// Request: NULL, Response: NULL
    
    CP_LOAD_HEROS		= 11201,	// 获取英雄   	// Request: NULL, Response: HeroList
    CP_MAKE_HERO		= 11202,	// 生成英雄		// Request: NULL, Response: Hero
    
    CP_LOAD_TEAM		= 11301,	// 获取队列   	// Request: NULL, Response: NULL
    
    CP_LOAD_ITEMS		= 11401,	// 获取物品   	// Request: NULL, Response: ItemList
    CP_ITEM_INDEX 		= 11402,	// 检查昵称 		// Request: NULL, Response: NULL
    
    CP_LUCKY_CARD 		= 11501, 	// 抽卡 			// Request: NULL, Response: ItemList
    CP_END_NUMBER 		= 30000,
};

// TCP 数据包头 16 bit
// 网关与客户的交互
typedef struct tag_msghead_t {
    unsigned short 	len;	// 数据体长度
    unsigned short  cmd;	// 协议号
    unsigned short 	eno;	// 错误码
    unsigned char 	enc;	// 加密
    unsigned char 	com;	// 压缩
    unsigned int 	tea;	// 会话
    unsigned int 	idx;	// 包索引
}T_MSGHEAD_T, *LP_MSGHEAD_T;

//服务器返回错误码
enum ERROR_CODE {
    ERROR_FAILURE = -1,
    ERROR_SUCCESS = 0,
    ERROR_NET_PUSH = 10,	// 推送消息标识
    ERROR_NO_RESPONSE = 100,
    ERROR_NET_TEA = 101,	// 交互会话出错
    ERROR_NET_DATA = 102,	// 数据体长度不对
    ERROR_NET_CMD = 103,	// 协议不能匹配
    ERROR_NET_PACKET = 104,	// 数据体解析出错
    
    ERROR_LOCAL_MEM = 106,	// 本地内存分配
    ERROR_LOCAL_OBJECT = 107,
    ERROR_NET_UID = 108,		// UID 错误
    ERROR_LISE_SIZE = 109,
    ERROR_LOAD_DATA = 110,		// 数据未加载
    ERROR_SYSTEM_CONFIG = 111,		//
    ERROR_URL_DECODE	= 112,		// 错误的urldecode
    ERROR_RSA_SIGN	= 113,			// 错误的RSA签名
    ERROR_NOTIFY_DATA	= 114,		// 错误的回复数据
    ERROR_NET_BUSINESS  = 115,		// 充值处理异常
    ERROR_NET_HEADER	= 116,		//
    ERROR_SERVER_REPAIR = 121,		// 服务器维护中
    ERROR_SERVER_VERSION = 122,		// 服务器版本
    
    ERROR_DB_QUERY		= 201,
    ERROR_DB_CACHED 	= 202,		// 数据据操作失败
    ERROR_DB_KEY 		= 203,		// 数据据操作失败
    ERROR_DB_ARGS 		= 204,		// 数据据操作失败
    ERROR_DB_METHOD		= 205,		//
    ERROR_DB_EXSIT		= 206,		// 数据已经存在
    ERROR_DB_PARSER		= 207,		// 数据已经存在
    ERROR_DB_NOFIND		= 208,		// 数据已经存在
    
    ERROR_ROLE_NOFIND  	= 10001,	//	角色不存在
    ERROR_ROLE_NAME  	= 10002,	//  角色名重复
};

#endif
