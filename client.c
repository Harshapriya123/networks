#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define _BSD_SOURCE
#define PORT 4444

int main () {
    int  clientSocket,ret;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    
     clientSocket = socket(AF_INET,SOCK_STREAM,0); // AF--> Address Family ,SOCK_STREAM --> TCP ,0--> IP
     if(clientSocket < 0) {
        printf("\n Error in connection");
        exit(1);
     }
     printf("\n Client Socket Created successfully");
    
     memset(&serverAddr,'\0',sizeof(serverAddr));
     serverAddr.sin_family = AF_INET;
     serverAddr.sin_port = htons(PORT);
     serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
     
     ret = connect(clientSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
     if(ret < 0) {
       printf("Error in connection of socket");
       exit(1);
        }
     printf("\n Connected to the server");
     
     while(1){
         printf("Client:\t");
         scanf("%s",&buffer[0]);
         send(clientSocket,buffer, strlen(buffer), 0);
         
         if(strcmp(buffer, "bye") == 0) {
           close(clientSocket);
           printf("\n Disconnected from the server");  
           exit(1);
           }
         if(recv(clientSocket, buffer, 1024, 0)) {
            printf("\n Error in receiving data");
          }
          else {
             printf("Server:\t%s\n", buffer);
          }
         
       }
return 0;
}
