#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 



int main(int argc, char *argv[])
{
	  int sockfd, portno, n;
	      struct sockaddr_in serv_addr;
              struct hostent *server;

	      char buffer[256];
	         
	      portno =2050;
	     sockfd = socket(AF_INET, SOCK_STREAM, 0);
		 if (sockfd < 0) {
		 printf("ERROR opening socket");
		 exit(1);}
		   server = gethostbyname("127.0.0.1");
		 if (server == NULL) {
		  printf("ERROR, no such host");
			  exit(0);
				  }
		  bzero((char *) &serv_addr, sizeof(serv_addr));
		  serv_addr.sin_family = AF_INET;
		  bcopy((char *)server->h_addr, 
		 (char *)&serv_addr.sin_addr.s_addr,
		  server->h_length);
		  serv_addr.sin_port = htons(portno);
	         if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		 {
			 printf("Error connecting");
			 exit(1);
		 }
		 while(1){
		  printf("Please enter the message: ");
			 bzero(buffer,256);
		  fgets(buffer,255,stdin);
		 
	       n = write(sockfd,buffer,strlen(buffer));
	       
			 if (n < 0){ 
		 printf("ERROR writing to socket");
				 break;}
		 if(buffer[0]==':'&&buffer[1]=='q')
		      {printf("Closing client\n");
                          break;}
                      bzero(buffer,256);
		 n = read(sockfd,buffer,255);
		        if (n < 0) 
	     printf("ERROR reading from socket");
		 printf("Receiving from server:%s\n",buffer);
		   }close(sockfd);
		 return 0;		 
}

