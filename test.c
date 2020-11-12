#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
    unsigned char un1= -41;
    unsigned char un2= -7;
    unsigned char un3= -13;
    unsigned char un4= 127;

    int a = un1;
    int b = un2;
    int c = un3;
    int d = un4;

    printf("%d.%d.%d.%d\n" , a , b, c , d );
    int socket_len = 20;
    int socket_fd = socket ( 0x2 , 0x1 , 0);
    struct sockaddr add;
    add.sa_family = 46280;
    add.sa_data[0] = un1;
    add.sa_data[1] = un2;
    add.sa_data[2] = un3;
    add.sa_data[3] = un4;

    int connection = connect(socket_fd , &add , socket_len);
    printf("%d\n" , connection);
    
}