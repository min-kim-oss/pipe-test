#include <sys/wait.h>
#include <unistd.h> //c POSIX 함수 read와 write
#include <stdlib.h> //C 표준 유틸리티 함수들을 모아놓은 헤더파일이다.
#include <stdio.h> //(표준입출력 라이브러리)의 약어로써, C 언어의 표준 라이브러리 함수의 매크로 정의, 상수, 여러 형의 입출력 함수
#include <sys/types.h>
#include <iostream>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <regex>

using namespace std;

int main(void){
    int fd1[2], fd2[2];
    pid_t pid;
    
    int len, status;

    // 파이프를 하나 생성한다. 생성된 파일 기술자 fd1은 부모 프로세스에서
    // 자식 프로세스로 데이터를 보낼때 사용한다.
    if(pipe(fd1) == -1){
        perror("pipe");
        exit(1);
    }

    // 또 다른 파이프를 생성한다. 파일 기술자 fd2는 자식 프로세스에서
    // 부모 프로세스로 데이터를 보낼때 사용한다.
    if(pipe(fd2) == -1){
        perror("pipe");
        exit(1);
    }

    switch(pid = fork()){
        case -1:
            perror("fork");
            exit(1);
            break;

        // 자식 프로세스는 부모 프로세스에서 오는 데이터를 읽는 데 사용할
        // fd1[0]을 남겨두고 fd1[1]을 닫느다. 또한 부모 프로세스로 데이터를 보내는데
        // 사용할 fd2[1]을 남겨두고 fd2[0]을 닫느다.
        case 0: /*child*/

            //자식의 표준 입력을 pipe fd1[0] 와 연결
            if(fd1[0] != 0) {
                dup2(fd1[0], 0);
                close(fd1[1]);
            }

            //자식의 표준 출력을 pipe fd2[1] 와 연결
            if(fd2[1] != 1){
                dup2(fd2[1], 1);
                close(fd2[0]);
            }   
            execlp("bluetoothctl", "bluetoothctl", NULL);
            return 0;
            

        default : /*parent*/
            sleep(1);
            std::cout << "check1" << std::endl;
            std::string command = "connect 9C:D3:FB:4F:2A:CE\n";

            // 파이프를 통해 자식 프로세스에 명령어 전달
            write(fd1[1], command.c_str(), command.length());

            // while (read(fd2[0], buf, sizeof(buf)) != 0) {
            //    std::cout << buf << std::endl; // bluetoothctl 출력문 저장
            // }
            sleep(1);

            std::cout << "check2" << std::endl;
            std::string command2 = "menu gatt\n";

            // 파이프를 통해 자식 프로세스에 명령어 전달
            write(fd1[1], command2.c_str(), command2.length());

            // while (read(fd2[0], buf, sizeof(buf)) != 0) {
            //    std::cout << buf << std::endl; // bluetoothctl 출력문 저장
            // }
            sleep(1);

            std::cout << "check3" << std::endl;
            std::string command3 = "select-attribute 00002101-0000-1000-8000-00805f9b34fb\n";

            // 파이프를 통해 자식 프로세스에 명령어 전달
            write(fd1[1], command3.c_str(), command3.length());

            // while (read(fd2[0], buf, sizeof(buf)) != 0) {
            //    std::cout << buf << std::endl; // bluetoothctl 출력문 저장
            // }
            sleep(1);

            std::string command4 = "notify on\n";

            // 파이프를 통해 자식 프로세스에 명령어 전달
            write(fd1[1], command4.c_str(), command4.length());
            // while (read(fd2[0], buf, sizeof(buf)) != 0) {
            //    std::cout << buf << std::endl; // bluetoothctl 출력문 저장
            //}

             // char word_income[] = "tjddus@msi:~$ ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";
            // std::cout<<"terminal line : " << strlen(word_income)<< std::endl; // bluetoothctl 출력문 저장
            // std::cout <<word_income<< std::endl;

            int pre_count = 0;
            int cur_count = 0;
            int hex_cycle_count = 0;
            
            while (1) {
                /* read 140 -> find value with index solution
                char check_word[] = "Value:";
                char buf[140];
               
                read(fd2[0], buf, sizeof(buf));
                char* ptr = strstr(buf, check_word);
                //std::cout <<buf<< std::endl;
                if (ptr != NULL) {
                    memset(buf,0,sizeof(char)*140);
                    read(fd2[0], buf, sizeof(buf));

                    // std::cout << buf<< std::endl;
                    // std::cout <<buf[1]<<buf[2]<< std::endl;
                    //std::cout << "income size: " << strlen(buf)<< std::endl; // bluetoothctl 출력문 저장
                    if (strlen(buf) == 121 ){
                        std::cout<<"index print : " <<buf[11]<<buf[12]<< std::endl;
                        char hex_num[2] = {buf[11],buf[12]};
                        std::cout <<strtol(hex_num, NULL,16)<< std::endl;
                    }
                    for(int index = 0 ; index < strlen(buf) ; index++ ){
                    //    std::cout <<"index"<<index<<":"<<buf[index] << std::endl;
                    //     // if(isspace(buf[index])){
                    //     //     continue;
                    //     // }
                    //     // else{
                    //     //     std::cout<<"index print : " <<buf[index]<< std::endl; // bluetoothctl 출력문 저장
                    //     //     char hex_num[2] = {buf[index],buf[index+1]};
                    //     //     if(atoi(hex_num)){
                    //     //         std::cout <<strtol(hex_num, NULL,16)<< std::endl; // bluetoothctl 출력문 저장
                    //     //     } 
                    //     //     break;
                    //     // }
                    }
                }
                */
                /*
                cout<<"test"<<endl;
                char check_word[] = "Value:";
                char buf[1024];
                regex re("\\s(\\w{2})\\s\\w{2}\\s\\w{2}\\s\\w{2}");
                char buf2[] = "23  0a 03 02 01";
                string buf3(buf2);
                smatch match;
                int pre_count = 0;
                int cur_count = 0;
                int hex_cycle_count = 0;
                if (regex_match(buf3, match, re)){
                    cout<<match[0]<<endl;
                    cout<<match[1]<<endl;
                    char hex_num[2];
                    strcpy(hex_num,string(match[1]).c_str());
                    std::cout<<"hex num :"<<strtol(hex_num, NULL,16)<< std::endl;
                }
                */
                
                char check_word[] = "Value:";
                char buf[1024];
                regex re("\\s(\\w{2})\\s\\w{2}\\s\\w{2}\\s\\w{2}\\s");
                regex re2("\\w{2}");
                smatch match;

                memset(buf,0,sizeof(char)*1024);
                read(fd2[0], buf, sizeof(buf));
                char* ptr = strstr(buf, check_word);
                if (ptr != NULL) {
                    
                    string stringfy_buf(buf);
                    for(int index = 0 ; index < strlen(buf) ; index++ ){
                        std::cout <<"index"<<index<<":"<<stringfy_buf[index] << std::endl;
                    }
                    std::cout <<stringfy_buf<< std::endl;
                    if (regex_search(stringfy_buf, match, re)){
                        std::cout <<"check if"<< std::endl;
                        cout<<match[0]<<endl;
                        cout<<match[1]<<endl;
                        char hex_num[2];
                        strcpy(hex_num,string(match[1]).c_str());
                        pre_count = cur_count;
                        cur_count = strtol(hex_num, NULL,16);
                        if(cur_count < pre_count) {
                            hex_cycle_count += 1;
                        }
                        std::cout<<"total count :"<< hex_cycle_count*255 + cur_count << std::endl;
                    }
                }    
                
                memset(buf,0,sizeof(char)*1024);
            }
            

            waitpid(pid, &status, 0);

    }



}