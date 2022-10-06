// C++ 서버 프로그램
/*	
	error1 : "message": ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
	- "ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]"는 경고메시지 (삼각형에 !는 경고메시지)


*/

//#include "/usr/include/mysql/mysql.h"

#include <mysql/mysql.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <iostream>

#include <fstream>

using namespace std;

#define BUF_SIZE 1024			//메시지 최대 길이
#define MAX_CLNT 10			//최대 동시 접속자 수

void *handle_clnt(void *arg);				//클라이언트 쓰레드용 함수 (함수포인터)
void send_msg(char *message, int len);		//메시지 전달 함수
void error_handling(char *message);			//예외처리함수	

int clnt_cnt=0;							//현재 접속중인 클라이언트 수
int clnt_socks[MAX_CLNT];				 // 클라이언트 최대
pthread_mutex_t mutx;						// mutex 선언 - 다중 스레드끼리 전역변수 사용시 데이터의 혼선 방지

char menu[100];
char pwd[10];
char pwd_save[10];
char random_pwd[6];
char ox[10];
char id[10];
string id_pwdsave[5];
char idid[5];
string id_save[5];
char id_pwd[10];


int main(int argc, char *argv[])
{

	MYSQL* mysql;
	char sql[1024];
    MYSQL_RES* result;
    MYSQL_ROW row;
    char str1[1024], str2[1024];
	char* consult;
    char* sentence;
    string sentence_aux;
	char a[10];
	char b[10];


	int serv_sock, clnt_sock;							// 소켓 통신용 서버 소켓과 임시 클라이언트 소켓	
	char message[BUF_SIZE];

	
	int  str_len = 0, i=0;

	struct sockaddr_in serv_adr, clnt_adr;				// 서버 주소, 클라이언트 주소 구조체
	socklen_t clnt_adr_sz;								// 클라이언트 주소 구조체	
	

	//mariadb sql connect
	 mysql_init(mysql);
    if(!mysql_real_connect(mysql, "127.0.0.1", "root","1234", "test" ,3306, (char *)NULL, 0))
    {
        printf("%s\n",mysql_error(mysql));
        exit(1);
    }


	// 포트 입력이 안되었을 경우
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);    
	if(serv_sock==-1)
        error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));			//서버 주소 구조체 초기화
    serv_adr.sin_family=AF_INET;					//인터넷 통신
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);		//현재 ip 이용
    serv_adr.sin_port=htons(atoi(argv[1]));			//사용자가 지정한 포트 이용
	
	//서버 소켓에 주소 할당
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("bind() error");
	
	//서버 소켓을 서버로 이용
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
	



	// 수정 ------------------
	while(1)	
    {
    clnt_adr_sz=sizeof(clnt_adr);														//클라이언트 구조체의 크기 불러옴
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);				//클라이언트의 접속을 받기위해 멈춤
		
		if(clnt_sock==-1)
            error_handling("accept() error");
        else
            printf("Connected client %d \n", i=i+1);

		


		while(read(clnt_sock, menu, BUF_SIZE-1)!=0) {
			
            cout << "메뉴 :"<<menu << endl;
		
	

			switch((char)*menu){
				
				case '1':	//개별 비밀번호 생성
					read(clnt_sock,id,BUF_SIZE-1);
					read(clnt_sock,id_pwd,BUF_SIZE-1);
					cout << "id : " << id << "pwd: " <<id_pwd <<endl;
						
						//if(id_pwdsave[0]==""){
			
						//*id_pwd;
					sentence_aux = "INSERT INTO testdb(id, pwd) VALUES( '%s','%s')";
					sentence = new char[sentence_aux.length()+1];
					strcpy(sentence,sentence_aux.c_str());

					consult = new char[strlen(sentence) + sizeof(int) + strlen(id)+ strlen(id_pwd) + sizeof(float)];
					sprintf(consult,sentence,id,id_pwd);

					
					mysql_query(mysql,consult);
					mysql_store_result(mysql);

					cout<<" endl"<<endl;
					break;
					
				case '2':	//암호 확인
					cout << pwd_save <<endl;
					cout << pwd <<endl;
					read(clnt_sock, pwd, BUF_SIZE-1);
					if(pwd_save==pwd){
						ox[0]=1;
						write(clnt_sock, ox, str_len);
						cout << " 암호 일치" <<endl;
					}else{
						ox[0]=0;
						write(clnt_sock, ox, str_len);
						cout << " 암호 불일치" <<endl;
					}
					break;

				case '4':	//개별 비밀번호 생성
					read(clnt_sock,id,BUF_SIZE-1);
					cout << "id : ";
					*id_pwd=NULL;
					switch ((char) *id)
					{
					case '1':
						//if(id_pwdsave[0]==""){
						read(clnt_sock,id_pwd,BUF_SIZE-1);
						id_pwdsave[0] = id_pwd;
						cout<<id<<" pwd : "+id_pwdsave[0]<<"저장"<<endl;
						
						strcpy(sql, "INSERT INTO testdb VALUES('%s', '%s',a,b)");
						if(mysql_query(mysql, sql) != 0){
      					  printf("inster error");
  						  }			
						*id_pwd = NULL;

						cout<<"endl"<<endl;
						
						break;
					case '2':
						read(clnt_sock,id_pwd,BUF_SIZE-1);
						id_pwdsave[1] = id_pwd;
						cout<<id<<" pwd : "+id_pwdsave[1]<<"저장"<<endl;
						*id_pwd = NULL;
						break;
					
					case '3':
						read(clnt_sock,id_pwd,BUF_SIZE-1);
						id_pwdsave[2] = id_pwd;
						cout<<id<<" pwd : "+id_pwdsave[2]<<"저장"<<endl;
						*id_pwd = NULL;
						break;
					
					case '4':
						read(clnt_sock,id_pwd,BUF_SIZE-1);
						id_pwdsave[3] = id_pwd;
						cout<<id<<" pwd : "+id_pwdsave[3]<<"저장"<<endl;
						*id_pwd = NULL;
						break;
					}
					break;
				case '5':	//개별 비밀번호 확인
					read(clnt_sock,id,BUF_SIZE-1);
					cout << "id : ";
					*id_pwd=NULL;
					*ox=NULL;
					switch ((char) *id)
					{
						case '1'
                        :
							//if(id_pwdsave[0]==""){
							read(clnt_sock,id_pwd,BUF_SIZE-1);
							if(id_pwdsave[0]==id_pwd){
								cout<<id<<" 로그인tle"<<endl;
								*ox='1';
								cout<<"ox "<<ox<<endl;

								write(clnt_sock, ox, strlen(ox));
								cout<<"전송 완료"<<endl;
							}else{
								cout<<id<<" 로그인 실패"<<endl;
								*ox='0';
								cout<<"ox "<<ox<<endl;

								write(clnt_sock, ox, strlen(ox));
								cout<<"전송 완료"<<endl;
							}
							*id_pwd = NULL;
							
							break;
					
					}
					break;
				
				case '8': //로그 기록확인

				case '9': 
					for(i=0;i<4;i++){
						if(id_pwdsave[i]==""){
							cout<<"값 없음"<<endl;
						}else
						{
							cout<<"id: "<<i+1<<" 암호: "<<id_pwdsave[i]<<endl;
						}
					}
					break;
				default :
				
					break;
			}
			//  write(clnt_sock, pwd, str_len);
			// read(clnt_sock, pwd, BUF_SIZE);
			// cout << "암호 : "<< pwd << "저장 완료"<<endl;
        }


		
		/*
        // 클라이언트로부터 전송된 데이터를 수신한다.
        // 그리고 다시 클라이언트에게 받았던 데이터를 송신한다.
        while((str_len=read(clnt_sock, message, BUF_SIZE))!=0) {
            write(clnt_sock, message, str_len);
            std::cout << message << std::endl;
        }
		*/

        close(clnt_sock);
    }

	close(serv_sock);						//쓰레드가 끝나면 소켓을 닫아준다 
	return 0;
}





//예외처리 함수
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

