/*************************
 MD5,只是用来验证密码；即输入
 
 **************************/


#ifndef MD5_H

#define MD5_H

typedef struct

{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
    
}MD5_CTX;


#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))

#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define FF(a,b,c,d,x,s,ac) {a += F(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s);  a += b; }
#define GG(a,b,c,d,x,s,ac) {a += G(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s);  a += b; }
#define HH(a,b,c,d,x,s,ac) {a += H(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s);  a += b; }
#define II(a,b,c,d,x,s,ac) {a += I(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s);  a += b; }

class  MD5{
    
public:
    
    
void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context,unsigned char *input,unsigned int inputlen);
void MD5Final(MD5_CTX *context,unsigned char digest[16]);
void MD5Transform(unsigned int state[4],unsigned char block[64]);
void MD5Encode(unsigned char *output,unsigned int *input,unsigned int len);
void MD5Decode(unsigned int *output,unsigned char *input,unsigned int len);
    
    
void  MD5Made(char*  inchar, char* outchar );
    
//public:
//    unsigned char PADDING[]={0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//        
//        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//        
//        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//        
//        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    
};


#endif

/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

int main(int argc, char *argv[])

{
    MD5_CTX md5;
    MD5Init(&md5);

    unsigned char encrypt[] ="admin";    //输入的明文；  //21232f297a57a5a743894a0e4a801fc3
    unsigned char decrypt[16];           //输出的密文；
    
    MD5Update(&md5,encrypt,strlen((char *)encrypt));
    MD5Final(&md5,decrypt);
 
 
    //输出；
    printf("加密前:%s\n加密后:",encrypt);
    int i;
    for(i=0;i<16;i++){  printf("%02x",decrypt[i]);}
    
    getchar();
    
    return 0;
    
}

*/





