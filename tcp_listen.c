#include <stdio.h>
#include <p_net.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

int p_listen(int port,int backlog){
    int s_fd;
    SA4 serv;//服务器的地址

    //创建一个socket。基于TCP/IPV4
    s_fd=socket(AF_INET,SOCK_STREAM,0);
    if(s_fd==-1){
        perror("socket");
        return -1;
    }
    //初始化服务器的IP地址和端口号
    //INADDR_ANY这个宏代表本机的所有ip地址
    serv.sin_family=AF_INET;
    serv.sin_port=htons(port);
    serv.sin_addr.s_addr=htonl(INADDR_ANY);

    //将s_fd和本地的ip地址和端口号绑定.6666
    int b=bind(s_fd,(SA *)&serv,sizeof(serv));
    if(b==-1){
        perror("bind");
        return -1;
    }
    //监听s_fd
    listen(s_fd,backlog);
    return s_fd;
}
