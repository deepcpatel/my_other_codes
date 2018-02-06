#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define BUF_LEN 10000
#define SERVER_PORT 11000
#define CLIENT_PORT 11001

void err(char *s)
{
	perror(s);
	exit(1);
}

int main(int argc, char *argv[])
{
	int flag = 0;
	struct sockaddr_in my_addr, serv_addr; 			 // structure to specify the socket address(IP address + port + family)
	int sockfd, slen = sizeof(serv_addr);			 // socket desciptor and length of sockaddr_in
	char buffer[BUF_LEN]; 					 // buffer to store data
	
	if(argc != 2) // check if ip address is specified or not, name of the op file also counts as argument
	{
		printf("Not enough arguments");
		exit(0);
	}
	
	// Create a udp socket of family AF_INET. SOCK_DGRAM specify datagram socket
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		err("Client : socket creation failed");
	else
		printf("\n Client : Socket creation successful"); //initialize client_addr struct with 0s
	
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET; // assign family to server address structure
	my_addr.sin_port = htons(CLIENT_PORT);// assign port to sockaddr_in,same as specified in server
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// accept data from any  address
	// bind the socket to that ip address, so that clients can send data to the ip a address and it gets delivered to the socket

	if(bind(sockfd, (struct sockaddr*) &my_addr, sizeof(my_addr)) == -1)
		err("bind");
	else
		printf("\n Client : bind successful");		// initialize serv_addr struct with 0s
		
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; // assign family to server address structure
	serv_addr.sin_port = htons(SERVER_PORT); // assign port to sockaddr_in, same as specified in server
	
	// s_addr is of long type so convert our IP address from decimal notation to long using inet_aton

	if(inet_aton(argv[1], &serv_addr.sin_addr) == 0)
	{
		err("address assignment failed");
	}

	// to keep the program alive we have an infinite loop
	
	while(1)
	{
		if(flag==0)
		{
			printf("\n Enter your stat from exam: ");
			scanf("%s", buffer);
			getchar(); // to accomodate the enter
			// send the file name to the server address using socket created
			if(sendto(sockfd, buffer, BUF_LEN, 0, (struct sockaddr*)&serv_addr, slen) == -1)
				err("Client : sending of file name failed");

			// receive data from the server on the specified socket(IP Address + port number)
			if(recvfrom(sockfd, buffer, BUF_LEN, 0, (struct sockaddr*)&serv_addr,&slen) == -1)
				err("receiving error");

			// write the data to a file or display it on screen.
			printf("Received from %s:%d\nData : %s\n\n",
			inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port), buffer);
			flag = 1;
		}
		else
		{
			char ans[5];
			printf("\n Enter answers(without any space):");
			gets(ans);
			bzero(buffer,sizeof(buffer));
			strcpy(buffer,ans);
			if(sendto(sockfd, buffer, BUF_LEN, 0, (struct sockaddr*)&serv_addr, slen) == -1)
				err("Client : sending of file name failed");

			bzero(buffer,sizeof(buffer));
			
			if(recvfrom(sockfd, buffer, BUF_LEN, 0, (struct sockaddr*)&serv_addr,&slen) == -1)
					err("receiving error");				// open the file specified
			printf("%s\n",buffer);
			flag = 0;
			exit(0);	
			
		}	
	}

	close(sockfd);

	return 0;
}
