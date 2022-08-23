// C++ TCP 클라이언트 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(const char *message);

int main(int argc, char* argv[])
{
    if(argc!=3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
	
    int sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");
	
    // 클라이언트와 마찬가지로 주소정보를 초기화
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
		
    // 서버의 주소정보로 클라이언트 소켓이 연결요청을 한다.
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
        error_handling("connect() error!");
	
    // 성공적으로 서버에게서 메시지를 받아오면
    // 0을 반환하고 실패하면 -1을 반환한다.
    char message[30];
    int str_len;
    str_len=read(sock, message, sizeof(message)-1);
    if(str_len==-1)
        error_handling("read() error!");
	
    printf("Message from server: %s \n", message);  
    close(sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}