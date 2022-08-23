// C++ 서버 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;
	
    struct sockaddr_in serv_adr;
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz;
	
    if(argc!=2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
	
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);   
    if(serv_sock==-1)
        error_handling("socket() error");
	
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("bind() error");
	
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
	
    clnt_adr_sz=sizeof(clnt_adr);
	
    // 여러 클라이언트와의 통신을 위해서 반복문 추가
    for(i=0; i<5; i++)
    {
        // 서버와 각 클라이언트와의 통신을 위해서 생성된 소켓
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(clnt_sock==-1)
            error_handling("accept() error");
        else
            printf("Connected client %d \n", i+1);
		
        // 클라이언트로부터 전송된 데이터를 수신한다.
        // 그리고 다시 클라이언트에게 받았던 데이터를 송신한다.
        while((str_len=read(clnt_sock, message, BUF_SIZE))!=0) {
            write(clnt_sock, message, str_len);
            std::cout << message << std::endl;
        }

        close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
