#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "List.h"
#include <string.h>

#define maxMsgLength 100 

List displayMsgList;
List sendMsgList;

int rv;
struct addrinfo hints, *res;
int sockfd;

int rvo;
struct addrinfo houts, *resout;

pthread_mutex_t receivingLock, sendingLock;
	
void *print_message_function(void *empty){
	char message[maxMsgLength];
	while(1){
		pthread_mutex_lock(&receivingLock);
		while(ListCount(displayMsgList) != 0){
			strcpy(message, (char*) ListRemove(displayMsgList));
			printf("remote user: %s", message);	 
		}
		pthread_mutex_unlock(&receivingLock);
	}
}

void *keyboard_message_function(void *empty){
	char message[maxMsgLength];
	while(1){
		fgets(message, maxMsgLength, stdin);
		if( strcmp(message, "!\n") == 0)
			exit(1);
		pthread_mutex_lock(&sendingLock);
		ListAdd(sendMsgList, message);
		pthread_mutex_unlock(&sendingLock);
	}
}

void *UDP_send_function(void *empty){
	char sending[maxMsgLength];
	while(1){
		pthread_mutex_lock(&sendingLock);
		while(ListCount(sendMsgList) > 0){
			strcpy(sending, (char*) ListRemove(sendMsgList));
			int i = sendto(sockfd, sending, sizeof(sending), 0, resout->ai_addr, resout->ai_addrlen);
		}
		pthread_mutex_unlock(&sendingLock);
	}
}

void *UDP_receive_function(void *empty){
	char received[maxMsgLength];
	while(1){
		while(recvfrom(sockfd, received, sizeof(received), 0, resout->ai_addr, &(resout->ai_addrlen))!=-1){
			pthread_mutex_lock(&receivingLock);
			ListAdd(displayMsgList, received);
			pthread_mutex_unlock(&receivingLock);
		}			
	}
}

int main(int argc, char **argv){

	// For Network Config
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	memset(&houts, 0, sizeof houts);
	houts.ai_family = AF_UNSPEC;
	houts.ai_socktype = SOCK_DGRAM;
	

	// Setting inward socket
	if((rv = getaddrinfo(NULL, argv[1], &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	if((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
		perror("listener: socket");
	} 
	if(bind(sockfd, res->ai_addr, res->ai_addrlen) == -1){
		close(sockfd);
		perror("listner: bind");
	}
	
	struct hostent *ho = gethostbyname(argv[2]);
	
	if((rvo = getaddrinfo(inet_ntoa(*(struct in_addr*)ho->h_addr_list[0]), argv[3], &houts, &resout)) !=0){
		fprintf(stderr, "getaddrinfo (out): %s\n", gai_strerror(rvo));
		return 1;
	}
	// For Network Config End


	// List of strings which remotely connected user input
	//		and which will be displayed on local machine
	displayMsgList = LISTCreate();

	// List of strings which local user input 
	//		and which will be sent to remotely connected user
	sendMsgList = LISTCreate();
	
	if (pthread_mutex_init(&sendingLock, NULL) != 0){
		perror("listenr: sending mutex");
	}
	if(pthread_mutex_init(&receivingLock, NULL) != 0){
		perror("listner: receiving mutex");
	}

	pthread_t thread1, thread2, thread3, thread4;
	
	int iret1, iret2, iret3, iret4;
	
	iret1 = pthread_create( &thread1, NULL, print_message_function, NULL);
	iret2 = pthread_create( &thread2, NULL, keyboard_message_function, NULL);
	iret3 = pthread_create( &thread3, NULL, UDP_send_function, NULL);
	iret4 = pthread_create( &thread4, NULL, UDP_receive_function, NULL);

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	pthread_join( thread3, NULL);
	pthread_join( thread4, NULL);
	return 0;
}

	// code for socket 
	/*	
	int rv;
	struct addrinfo hints, *res;
	int sockfd;
	
	int rvo;
	struct addrinfo houts, *resout;
	int sockfdo;
		
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	memset(&houts, 0, sizeof houts);
	houts.ai_family = AF_UNSPEC;
	houts.ai_socktype = SOCK_DGRAM;
	

	// Setting inward socket
	if((rv = getaddrinfo(NULL, argv[1], &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	if((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
		perror("listener: socket");
	} 
	if(bind(sockfd, res->ai_addr, res->ai_addrlen) == -1){
		close(sockfd);
		perror("listner: bind");
	}
	
	struct hostent *ho = gethostbyname(argv[2]);
	
	if((rvo = getaddrinfo(inet_ntoa(*(struct in_addr*)ho->h_addr_list[0]), argv[3], &houts, &resout)) !=0){
		fprintf(stderr, "getaddrinfo (out): %s\n", gai_strerror(rvo));
		return 1;
	}

	char test[100] = "hello?";
	char testResult[100];
	int i = sendto(sockfd, test, sizeof(test), 0, resout->ai_addr, resout->ai_addrlen);
	recvfrom(sockfd, testResult, sizeof(testResult), 0, resout->ai_addr, &(resout->ai_addrlen));
	printf("result: %d %s\n", i, testResult);
	*/
	
