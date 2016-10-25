/*
    C ECHO client example using sockets
*/
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
  
#define TRUE   1
#define FALSE  0
#define IPa "127.0.0.1"
#define PORTa 8888
#define PORTb 8889

int clientele_listen();
int clientele_chat();
int server();

	
void printmenu()
{

               int choice;
    do
    {

         printf("1. regester with server\n");
         printf("2. Exit\n");
         printf("choice?: ");
         scanf("%d",&choice);
        
   
         switch (choice)
        {
            case 1: server();
                break;
            case 2: 
            printf("Goodbye\n");
                break;
                default: printf("Wrong Choice. Enter again\n");
                    break;
        }    
  
    } 
    while (choice != 2);
     
}

int server(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
    
    
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("\n Could not create socket");
    }
  //  puts("\n Socket created");
     
    server.sin_addr.s_addr = inet_addr(IPa);
    server.sin_family = AF_INET;
    server.sin_port = htons( PORTa );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("\n connect failed. Error");
        return 1;
    }
     
    //puts("\n Connected\n");
     
    //keep communicating with server
    while(1)
    {
        printf("\n i am client B\n\n ");
       
      //  printf("\nEnter message : ");
      //  scanf("%s\n" , message);
         
        //Send some data
        
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
         
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
         
        puts("Server reply :");
        puts(server_reply);
          
        

		int choice;
    do
    {
        
         printf("1. listen to client\n");
         printf("2. chat with client\n");
         printf("3. Exit\n");
         printf("choice?: ");
         scanf("%d", &choice);
        
      
   
         switch (choice)
        {
 
            case 1: clientele_listen();
                break;
            case 2: clientele_chat();
                break;
            case 3: 
            printf("Goodbye\n");
                break;
                default: printf("Wrong Choice. Enter again\n");
                    break;
        }    
  
    } 
    while (choice != 3);
    }
     
    close(sock);
   
    return 0;
}

int clientele_listen(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    char response[2000];
    
    
    						FILE *fPtr = fopen("client_list.txt", "r");
						if(fPtr == NULL){
							perror("Error opening read file");
						}
							int id,port,addr;
							fscanf(fPtr ,"%d %d %d",&id,&port,&addr);
							while(!feof(fPtr)){
								
								printf("\t %d\t %d\t %d\n\n",id,port,addr);
								fscanf(fPtr ,"%d %d %d",&id,&port,&addr);
							}
							fclose(fPtr);
							
						
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORTb );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
   puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        // message back to client
        printf("\nmessage: %s\n", client_message);
        printf("reply: %s", response);
        scanf("%s" , response);
         
        //Send some data
        if( send(client_sock , response , strlen(response) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
      
        write(client_sock , response , strlen(response));
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     
    return 0;
	 return 0;
	 }
	 
int clientele_chat(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , reply[2000];
     
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( PORTb );

    //Connect to remote client
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with client
    while(1)
    {
        printf("Enter message : ");
        scanf("%s" , message);
         
        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
         
        //Receive a reply from the client
        if( recv(sock , reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
         
        puts("clients reply :");
        puts(reply);
    }
     
   close(sock);
  
 return 0;
 }

void main(){
	
	printmenu();
	
	}
