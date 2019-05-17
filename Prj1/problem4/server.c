#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<semaphore.h>
sem_t g_semt;
void *serve(void *newsockfd);
int main(int argc, char *argv[]){
	int sockfd,newsockfd,portno,clilen,n;
        pthread_t thread1;
	int maxsize=2;
	int ret=sem_init(&g_semt,0,maxsize);
	if(0 !=ret)
		return -1;
	struct sockaddr_in serv_addr,cli_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		printf("ERROR opening socket\n");
		exit(1);
	}
	bzero((char *)& serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	portno=2050;
	serv_addr.sin_port=htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	  if (bind(sockfd, (struct sockaddr *) &serv_addr,
				  sizeof(serv_addr)) < 0) 
	{printf("Error on binding\n");
		exit(1);
	}
	  listen(sockfd,5);
	  clilen=sizeof(cli_addr);
	  printf("sever initialing...\n");
  while(1)
  {       
	  newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
	  if(newsockfd<0)
	  {printf("Error on accept\n");
            exit(1);
	   }
	  sem_wait(&g_semt);
	  if(pthread_create( &thread1,NULL,serve,&newsockfd)==-1)
	  {printf("pthread_create() error\n");
		  exit(1);}
		  pthread_detach(thread1);
	 }close(sockfd);
  
  return 0;
}
void *serve(void*sockfd){

	int newsockfd=(int)(*((int*)sockfd));
while(1){
	    
	char buffer[256];
	bzero(buffer,256);
	int n=read(newsockfd,buffer,255);
	printf("Receiving message:%s\n",buffer);
	int i;
	for(i=0;i<n-1;i++){
		
	        if(buffer[0]==':'&&buffer[1]=='q'){
			printf("Server thread closing\n");
			sem_post(&g_semt);
		return NULL;	}
		if((buffer[i]>='a'&&buffer[i]<='z'||(buffer[i]>='A'&&buffer[i]<='Z')))
		{buffer[i]=buffer[i]+3;
		if((buffer[i]>'Z'&&buffer[i]<='Z'+3)||(buffer[i]>'z')&&(buffer[i]<='z'+3))
		buffer[i]=buffer[i]-26;
		}
		
		}
		write(newsockfd,buffer,n);}
		close(newsockfd);
		return NULL;
		}

