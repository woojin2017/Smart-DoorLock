// C++ TCP 클라이언트 프로그램

#include <mysql/mysql.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <fstream>



#include <fstream>


using namespace std;

#define BUF_SIZE 1024

char message[BUF_SIZE];

void finish_with_error(MYSQL *mysql){
						fprintf(stderr, "%s\n", mysql_error(mysql));
						mysql_close(mysql);
						exit(1);
					}


int main(int argc, char *argv[])
{

    void error_handling(char *message);
void menu_num(int menu);

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
	int num1, num2, num3, num4;
	char num[100];
	char ran_pwd[4];
	int num_fields;
    int i;


int sock;
char menu[100];
char pwd[10];
char ox[10];
char id[10];
char id_pwd[10];
char time[100];
int n1=0;


string str;
int str_len;
struct sockaddr_in serv_adr;


    mysql_init(mysql);
    if(!mysql_real_connect(mysql, "127.0.0.1", "root","1234", "test" ,3306, (char *)NULL, 0))
    {
        printf("%s\n",mysql_error(mysql));
        exit(1);
    }

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
        fputs(" 1.계정 생성 \n 2. 로그인 \n 3.랜덤 비밀번호 생성   \n 4.로그 기록 보기 \n 5.계정 정보 보기 \n메뉴 선택:", stdout);


        
        fgets(menu, BUF_SIZE, stdin);
        if(!strcmp(menu,"q\n") || !strcmp(menu,"Q\n")|| !strcmp(menu,"0\n"))
            break;
        
        write(sock,menu,strlen(menu));

        switch ((char)*menu)
        {
        
        case '1':
            fputs("id ", stdout);
            fgets(id, BUF_SIZE, stdin);
            write(sock,id,strlen(id));
            fputs("암호 입력 ", stdout);
            fgets(id_pwd, BUF_SIZE, stdin);
            write(sock,id_pwd,strlen(id_pwd));

            read(sock, ox, BUF_SIZE-1);
            // 문자열의 끝을 알리기 위해서 추가
          

            //cout<<"ox: "<<ox<<endl;  신호 확인용

            if(*ox=='1'){
                cout<<"Completion "<<endl;
            }

            break;
        case '2':

            fputs("id ", stdout);
            fgets(id, BUF_SIZE, stdin);
            write(sock,id,strlen(id));
            fputs("암호 입력 ", stdout);
            fgets(id_pwd, BUF_SIZE, stdin);
            write(sock,id_pwd,strlen(id_pwd));
            
            read(sock, ox, BUF_SIZE-1);
            if(*ox=='1'){
                cout<<"로그인 성공  "<<ox<<endl;
            }else{
                cout<<"로그인 실패 "<<ox<<endl;
            }

           
            break;
        case '3':
            read(sock, ran_pwd, BUF_SIZE-1);
            cout<<"랜덤 비밀번호: "<<ran_pwd<<endl;
            break;

        case '4':   //id별 암호 생성
            fputs("id ", stdout);
            fgets(id, BUF_SIZE, stdin);
            write(sock,id,strlen(id));
            fputs("암호 입력 ", stdout);
            fgets(id_pwd, BUF_SIZE, stdin);
            write(sock,id_pwd,strlen(id_pwd));

            sentence_aux = "select join_time from logdata where id = '%s' ";
			sentence = new char[sentence_aux.length()+1];
			strcpy(sentence,sentence_aux.c_str());

			consult = new char[strlen(sentence) + sizeof(int) + strlen(id)+ sizeof(float)];
			sprintf(consult,sentence,id);



            if(mysql_query(mysql,consult))
                {
                    cout <<"ERROR:  " <<mysql_error(mysql)<<endl;
					
					
                }
                else
                {
                    //cout << " " <<endl;
                }

					
				
					
				

					//mysql_store_result(mysql);
					result = mysql_store_result(mysql);
						if(result == NULL)
						{
							finish_with_error(mysql);
						}

						num_fields = mysql_num_fields(result);

						while(row =mysql_fetch_row(result))
						{
							for(i=0; i<num_fields; i++)
							{
							    printf("%s   ", row[i] ? row[i] : "MULL");
								
								
							}
							printf("\n");
							
						}

						mysql_free_result(result);
					cout<<" endl"<<endl;
               

            

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
        cout<<"\n"<<endl;
        
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
