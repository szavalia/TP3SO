// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <signal.h>
#include <errno.h>
#define PORT 8080 

//inspirado de https://www.geeksforgeeks.org/socket-programming-cc/
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char message[1024]; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr )<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    }    
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    /*send(sock , "entendido\n" , strlen("entendido\n"), 0 );
    send(sock, "itba\n", strlen("itba\n"), 0);
    send(sock, "M4GFKZ289aku\n", strlen("M4GFKZ289aku\n"), 0);
    send(sock, "fk3wfLCm3QvS\n", strlen("fk3wfLCm3QvS\n"), 0);
    send(sock, "too_easy\n", strlen("too_easy\n"), 0);
    send(sock, ".RUN_ME\n", strlen(".RUN_ME\n"), 0);
    send(sock, "K5n2UFfpFMUN\n", strlen("K5n2UFfpFMUN\n"), 0);
    send(sock, "BUmyYq5XxXGt\n", strlen("BUmyYq5XxXGt\n"), 0);
    send(sock, "u^v\n", strlen("u^v\n"), 0); 
    send(sock, "chin_chu_lan_cha\n", strlen("chin_chu_lan_cha\n"), 0);
    send(sock, "gdb_rules\n", strlen("gdb_rules\n"), 0);
    send(sock, "normal\n", strlen("normal\n"), 0);*/


    while(1){
        scanf("%s", message);
        printf("Message: %s\n", message);
        send(sock , strcat(message, "\n") , strlen(message)+1 , 0 ); 
    }
    return 0; 
} 