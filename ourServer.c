//inspirado en el archivo de geeksforgeeks 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <errno.h>
#include <math.h>
#define PORT 8080 
#define READ 0
#define WRITE 1

extern int run();
extern int gdbme();

void desafio1(int socket, char * text, char * enunciado);
void desafio5(int socket, char * rta, char * enunciado);
void desafio8(int socket);
void desafio9(int socket);
void desafio12(int socket);
void desafio13(int socket);

double drand();
double random_normal();

char desafio[] = "------------- DESAFIO -------------";
char pregunta[] = "----- PREGUNTA PARA INVESTIGAR -----";


int main(int argc, const char *argv[]){ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char hello[] = "Hello from server"; 

    //-------------------------------------------------------------
    //                      Creacion del server
    //-------------------------------------------------------------

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    //-------------------------------------------------------------
    //                  Termina creacion del server
    //-------------------------------------------------------------
    
    //no decia tal cual esto pero ponele que era así 
    //desafio 2
    desafio1(new_socket, "entendido\n","Bienvenidos al primer desafío, para continuar, enviar una señal que diga \"entendido\\n\"\n");

    //desafio 3
    desafio1(new_socket, "itba\n", "The wire, S01E05: 5295 888 6288\n");

    //desafio 4
    desafio1(new_socket,"M4GFKZ289aku\n","https://ibb.co/tc0Hb6w \n");

    //desafio 5
    desafio5(new_socket, "fk3wfLCm3QvS\n", "EBADF ...");

    //desafio 6 --> no esta terminado! hay que ver como guardar el string
    desafio5(new_socket, "fk3wfLCm3QvS\n", "Respuesta= strings:277");

    //Desafio 7 --> .RUN_ME

    //desafio 8 --> filter error
    desafio8(new_socket);

    //desafio 9 - letras negras
    desafio9(new_socket);

    //desafio 10
    desafio1(new_socket, "u^v\n", "Latexme:\n dy=:u^v\\cdot \\left(v'\\cdot \\ln \\left(u\right)+v\\cdot \frac{u'}{u}\right)\n");

    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n");

    //desafío 11 --> GDB
    desafio12(new_socket);

    //desafío 12 --> Distribución normal
    desafio13(new_socket);
} 

int kill_debugger(){
    int pid = getpid();
    if ( fork() == 0 ){
        char command[250];
        sprintf(command , "grep Tracer /proc/%d/status | cut -f 2" , pid );
        execl("/bin/sh", "sh", "c" , command, (char*) 0);
    }
}

void desafio1(int socket, char * text, char * enunciado){
    system("clear");
    puts(desafio);
    printf("%s", enunciado);
    char buffer[1024] = {0};
    int valread = read(socket, buffer, 1024);
    while(strcmp(buffer, text) != 0){
        printf("Mensaje incorrecto: %s", buffer);
        valread = read(socket, buffer, 1024);
        sleep(1);
        system("clear");
        printf("%s", enunciado);
    }
    return;
}

void desafio5(int socket, char * rta, char * enunciado){
    system("clear");
    puts(desafio);
    puts(enunciado);
    char respuesta[60] = "La respuesta es:";
    strcat(respuesta, rta);
    char buffer[1024] = {0};
    int valread = read(socket, buffer, 1024);
    while(strcmp(buffer, rta) != 0){
        printf("Mensaje incorrecto: %s", buffer);
        valread = read(socket, buffer, 1024);
        sleep(1);
        system("clear");
        printf("%s", enunciado);
    }
    return;
}

void gen_random(char *s, const int len) {
    static const char alphanum[] =     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz<çÇ-_.,´+``¨¨+``{}>!·$&/()=?¿çΧΨΩαβγδεζηθικλμνξοπρςστυφϒϖχψωא";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void desafio8 (int socket){
    system("clear");
    printf("Filter error\n");
    write(1, "La respuesta es: 12345678", 26);
    write(2 , "\rjfbglabgabrgkvbrlvbrajbvierqbgvjrbvirfbiubverivbierbvrbv\n", 59 );
    char buffer[1024] = {0};
    char random[82];
    int valread = read(socket, buffer, 1024);
    while(strcmp(buffer, "12345678\n") != 0){
        printf("Mensaje incorrecto: %s", buffer);
        valread = read(socket, buffer, 1024);
        sleep(1);
        system("clear");
        printf("Filter error\n");
        write(1, "La respuesta es: 12345678", 26);
        gen_random(random, 82);
        random[0] = '\r';
        random[82] = '\n';
        write(2 , random, 83 );
    }
}

void desafio9(int socket){
    system("clear");
    puts(desafio);
    printf("¿?");
    printf("\x1b[8m" "respuestilla" "\x1b[0m" "\n");
    char buffer[1024] = {0};
    int valread = read(socket, buffer, 1024);
    while(strcmp(buffer, "fk3wfLCm3QvS\n") != 0){
        printf("Mensaje incorrecto: %s", buffer);
        valread = read(socket, buffer, 1024);
        sleep(1);
        system("clear");
        printf("respuestilla");
    }
    return;
}
    
void desafio7(int socket){
    system("clear");
    puts(desafio);
    printf(".data .text ? .bss .ss \n");
    char buffer[1024] = {0};
    int valread = read(socket, buffer, 1024);
    while(strcmp(buffer, ".run_me\n") != 0){
        printf("Mensaje incorrecto: %s", buffer);
        valread = read(socket, buffer, 1024);
        sleep(1);
        system("clear");
        printf("respuestilla");
    }
    return;    
}

void read_line(int fd , char * buffer , int max){
    char c;
    int i = 0;
    while( read(fd , &c , 1) != 1 || i < max ){
        buffer[i] = c;
        i++;
        if ( c == '\n'){
            return;
        }
    }
}
int desafio11_iteration(int socket){
    char buffer1[4*1024];
    char buffer2[4*1024];
    char * argv[] = {NULL};
    FILE * stream = fopen("./quine.c" , "r+");
    if ( stream != 0 ){
        system("gcc quine.c -o quine");
    }
    else{
        puts("No se encontró el archivo");
        return -1;
    }
    int fd[2];
    int ret;
    pipe(fd);
    //TODO: Ver que onda este while
    //Segun jerusa puede llegar a entrar a en un bloque
    if ( fork() == 0 ){
        close(fd[READ]);
        dup2( 1 , fd[WRITE]);
        execv("./quine" , argv);
    }
    close(fd[WRITE]);
    fread( buffer1 , 4*1024  , sizeof(char) , stream );
    read( fd[READ] ,  buffer2 , 4*1024 );
    ret = strcmp( buffer1 , buffer2 );
    close(fd[READ]);
    return ret;
}
void desafio11(int socket){
    int ret;
    FILE * stream = fdopen(socket, "r+");
    char buffer[1024];
    do{
        system("clear");
        puts(desafio);
        printf("Presiona ENTER para reintentar\n");
        ret = desafio11_iteration(socket);
        fgets(buffer, 1024, stream);
    } while ( ret != 0);    
}

void desafio12(int socket){ //GDB me
    system("clear");
    puts(desafio);
    puts("b gdbme y buscá la palabra mágica");
    puts(pregunta);
    puts("¿Que es un RFC?");
    FILE * stream;
    int rta = gdbme(); 
    char buff[1024];
    if(rta != 1){ //no hizo la tarea
        puts("Muy mal! Pésimo!");
        sleep(1);
        fdopen(socket, "r+");
        fgets(buff, 1024, stream);
        fclose(stream);
        desafio11(socket);
    }        
}


void desafio13(int socket){
    system("clear");
    puts(desafio);
    printf("Ya me conoces\n");
    double mean = drand() * 10; //la media está entre 0 y 10
    double stddev = drand(); //la desviación estándar está entre 0 y 1
    char respuesta[1024];

    for(int i=0; i<1000; i++){
        printf("%g ", random_normal());
    }

    puts("\n");
    puts(pregunta);
    puts("¿Fue divertido?");
    puts("\n");
    
    FILE * stream = fdopen(socket, "r+");;
    fgets(respuesta, 1024, stream);
    fclose(stream);

    if(strcmp(respuesta, "normal\n") != 0){
        printf("Respuesta incorrecta: %s", respuesta);
        desafio12(socket);
    }
}

//código obtenido de https://stackoverflow.com/questions/7034930/how-to-generate-gaussian-pseudo-random-numbers-in-c-for-a-given-mean-and-varianc
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double drand()   /* uniform distribution, (0..1] */
{
  return (rand()+1.0)/(RAND_MAX+1.0);
}

double random_normal() 
 /* normal distribution, centered on 0, std dev 1 */
{
  return sqrt(-2*log(drand())) * cos(2*M_PI*drand());
}



