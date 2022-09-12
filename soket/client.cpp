// C++ TCP 클라이언트 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <fstream>


using namespace std;

#define BUF_SIZE 1024
void error_handling(char *message);
void menu_num(int menu);

int sock;
char message[BUF_SIZE];
char menu[100];
char pwd[10];
char ox[10];
char id[10];
char id_pwd[10];


string str;
int str_len;
struct sockaddr_in serv_adr;


int main(int argc, char *argv[])
{

    if(argc!=3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
	
    sock=socket(PF_INET, SOCK_STREAM, 0);   
    if(sock==-1)
        error_handling("socket() error");
	
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));
	
    // 클라이언트가 서버와의 연결을 위해 연결요청을 한다.
    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("connect() error!");
    else
        puts("Connected...........");
	
    // 사용자가 q를 입력할 때까지 반복
    while(1) 
    {   
        

        // fputs("메뉴 선택 ", stdout);
        // fgets(menu, BUF_SIZE, stdin);

        // write(sock,menu,strlen(menu));
        // str_len=read(sock,menu,BUF_SIZE-1);
        while(1){
        fputs("메뉴 선택: ", stdout);
        
        fgets(menu, BUF_SIZE, stdin);
        if(!strcmp(menu,"q\n") || !strcmp(menu,"Q\n")|| !strcmp(menu,"0\n"))
            break;
        
        write(sock,menu,strlen(menu));

        switch ((char)*menu)
        {
        
        case '1':
            fputs("암호 설정 ", stdout);
            fgets(pwd, BUF_SIZE, stdin);
            write(sock,pwd,strlen(pwd));
            break;
        case '2':
            fputs("암호 확인 ", stdout);
            fgets(pwd, BUF_SIZE, stdin);
            write(sock,pwd,strlen(pwd));
            read(sock, ox, BUF_SIZE-1);
            cout << ox << endl;
            if(ox[0]==1){
                cout << "암호 일치" <<endl;
            }else{
                cout << "암호 불일치" <<endl;
            }
            break;
        case '4':   //id별 암호 생성
            fputs("id ", stdout);
            fgets(id, BUF_SIZE, stdin);
            write(sock,id,strlen(id));
            fputs("암호 입력 ", stdout);
            fgets(id_pwd, BUF_SIZE, stdin);
            write(sock,id_pwd,strlen(id_pwd));
            break;
        case '5':   //암호 판별
            fputs("로그인 id ", stdout);
            fgets(id, BUF_SIZE, stdin);
            write(sock,id,strlen(id));
            fputs("암호 입력 ", stdout);
            fgets(id_pwd, BUF_SIZE, stdin);
            write(sock,id_pwd,strlen(id_pwd));
            




            str_len=read(sock, ox, BUF_SIZE-1);
            // 문자열의 끝을 알리기 위해서 추가
            ox[str_len]=0;

            //cout<<"ox: "<<ox<<endl;  신호 확인용

            if(*ox=='1'){
                cout<<"로그인 성공"<<endl;
            }else{
                cout<<"로그인 실패"<<endl;
            }
            break;

        case '9': 
            cout<< "비밀번호 확인 메뉴"<<endl;
            break;

        
        }
        
    }

         
	

       
       

        /*
        // 콘솔창에 출력하는 함수
        fputs("Input message(Q to quit): ", stdout);
        // 사용자의 입력을 받는다.
        fgets(message, BUF_SIZE, stdin);
		
        // strcmp는 문자열의 크기를 비교하는 함수인데,
        // 쉽게 생각해서 앞에 것이 크면 1, 뒤에 것이 크면 -1이다.
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
            break;
	
        // 서버에게 입력한 데이터를 보낸다.
        write(sock, message, strlen(message));
        // 서버로부터 데이터를 받는다. 반환되는 값은 받아온 바이트 수
        // 실패 시에 -1을 반환
        str_len=read(sock, message, BUF_SIZE-1);
        // 문자열의 끝을 알리기 위해서 추가
        message[str_len]=0;
    
       printf("Message from server: %s", message);
       */
    }
	
    close(sock);
    return 0;
}



void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
