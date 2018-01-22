#include <stdio.h>
#include <p_net.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(void){
    int conn_fd;
    int s_fd=p_listen(7878,5);
    if(s_fd==-1)return -1;
    while(1){
        conn_fd=accept(s_fd,NULL,NULL);
        if(conn_fd==-1){
            perror("accept");
            return -1;
        }
        pid_t pid=fork();
        if(pid==-1){
            perror("fork");
            return -1;
        }
        if(pid==0){
            close(s_fd);
            //具体和浏览器的通讯
            p_trans(conn_fd);
            close(conn_fd);
            exit(0);
        
        }else{
            close(conn_fd);
            waitpid(-1,NULL,WNOHANG);
        }
    }
    return 0;
}
