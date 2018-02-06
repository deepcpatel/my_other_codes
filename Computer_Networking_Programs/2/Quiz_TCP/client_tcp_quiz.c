#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    int flag = 0;
    char answer[100];
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) 
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
    }
    
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
        error("ERROR opening socket");
        
    server = gethostbyname(argv[1]);
    
    if (server == NULL) 
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    	
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
        
    while(1) 
    {    
	    if(flag==0)
	    {
		    printf("Enter your state for Quiz:");
		    fgets(buffer,255,stdin);
		    n = write(sockfd,buffer,strlen(buffer));

		    if (n < 0) 
				error("ERROR writing to socket");
		    
		    bzero(buffer,256);
		    
		    n = read(sockfd,buffer,256);
		    
		    if (n < 0) 
				error("ERROR reading from socket");

		    printf("%s\n",buffer);
		    flag = 1;	
		    bzero(buffer,256);    
	 	}
     
     	else
	 	{
	 	    printf("Enter your Answer Quiz:");
		    fgets(buffer,255,stdin);
		    
		    n = write(sockfd,buffer,strlen(buffer));

		    if (n < 0) 
				error("ERROR writing to socket");
		    
		    bzero(buffer,256);
		    
		    n = read(sockfd,buffer,256);
		    
		    if (n < 0) 
				error("ERROR reading from socket");

		    printf("%s\n",buffer);	
		    
		    bzero(buffer,256);
		    
		    break;	  
	 	}
   	}   

	return 0;
}
