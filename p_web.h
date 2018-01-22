#ifndef P_WEB_H_
#define P_WEB_H_
typedef struct{
    char method[8];//请求方法
    char path[128];//请求的路径
    char protocol[16];//使用的协议
}req_t;
 /*响应信息*/
 /*
* HTTP1.1 200
* Content-Type:
* 
* */
typedef struct{
    char path[128];
    char protocol[16];
    int code;//200  404
    char file_type[32];//text/html \
                image/jpg   image/jnp
}res_t;


#endif
