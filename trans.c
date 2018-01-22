#include <stdio.h>
#include <string.h>
#include "p_web.h"
#include <unistd.h>
#include <strings.h>

char work_dir[256]="/home/tarena/www";
static void get_request(int fd,req_t *req){
    char buf[512];
    char file[256];
    bzero(file,256);
    int r=read(fd,buf,512);
    sscanf(buf,"%s %s %s\r\n",req->method,\
            req->path,req->protocol);
    //处理一下请求文件的路径
    strcat(file,work_dir);
    strcat(file,req->path);
    strcpy(req->path,file);
    return ;
}

static int get_code(const char *path){
    printf("get_code:%s\n",path);
    if(access(path,F_OK|R_OK))
        return 404;
    return 200;
}
#if 0
/*响应信息*/
/*
 * HTTP1.1 200
 * Content-Type:
 *
 * */
typedef struct{
    char protocol[16];
    int code;//200  404
    char file_type[32];//text/html   image/jpg   image/jnp
}res_t;
#endif
static void get_response(req_t *rq,res_t *rt){
    strcpy(rt->path,rq->path);
    strcpy(rt->protocol,rq->protocol);
    //获取code
    rt->code=get_code(rq->path);
    //获取文件的类型
    return;
}
/*response browser 404*/
static void response_b_404(int fd){
    char *first="HTTP/1.1 404\r\n";
    char *content="Content-Type:text/html\r\n\r\n";
    char *html="<html><head><title>error</title></head><body>file not found!</body></html>";
    write(fd,first,strlen(first));
    write(fd,content,strlen(content));
    write(fd,html,strlen(html));
    return;
}

static void response_b_200(int fd,const char *file){
    char *first="HTTP/1.1 200\r\n";
    char *content="Content-Type:text/html\r\n\r\n";
    dup2(fd,1);//将1重定向到浏览器

    write(1,first,strlen(first));
    write(1,content,strlen(content));
    //使用cat命令将文件的内容输出到浏览器
    execlp("cat","cat",file,NULL);
    return;
}
static void response_b(int fd,res_t *rt){
    if(rt->code==404)
        response_b_404(fd);
    else
        response_b_200(fd,rt->path);
    return;
}

void p_trans(int fd){
    req_t rq;
    res_t rt;
    bzero(&rq,sizeof(req_t));
    //获取客户端的请求信息
    get_request(fd,&rq);
    printf("%s\n",rq.path);
    //处理请求信息,获取到响应信息
    get_response(&rq,&rt);

    //根据rt中的内容，组织响应浏览器的信息
    response_b(fd,&rt);
    return;
}
