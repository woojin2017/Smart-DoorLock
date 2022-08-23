// C++ 서버 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(const char *message);

int main(int argc, char *argv[])
{
    struct sockaddr_in clnt_addr; 
    
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
	
    // 소켓을 생성
    int serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");
	
    // 주소 정보 초기화
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    // INADDR_ANY는 서버 자신의 IP주소
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
	
    // 소켓에 위에서 생성한 주소 정보를 할당
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
        error_handling("bind() error"); 
	
    // 클라이언트가 연결요청이 가능하도록 5크기의 대기실 생성
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
	
    // accept()함수호출을 해서 실제 데이터를 보낼 수 있는 소켓을 생성
    socklen_t clnt_addr_size=sizeof(clnt_addr);
    int clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
    if(clnt_sock==-1)
        error_handling("accept() error");  
    
    // 메시지를 보낸다
    char message[]="Hello World!";
    write(clnt_sock, message, sizeof(message));

    
    // 서버, 클라이언트 소켓의 연결을 해제
    close(clnt_sock);	
    close(serv_sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}