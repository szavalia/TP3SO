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

void desafio1(int socket, char * text, char * enunciado, FILE * stream);
void desafio5(int socket, char * rta, char * enunciado, FILE * stream);
void desafio7(int socket, FILE * stream);
void desafio8(int socket, FILE * stream);
void desafio9(int socket, FILE * stream);
void desafio11(int socket, FILE * stream);
void desafio12(int socket, FILE * stream);
void desafio13(int socket, FILE * stream);

double drand();
double random_normal();

char desafio[] = "------------- DESAFIO -------------";
char pregunta[] = "----- PREGUNTA PARA INVESTIGAR -----";

int kill_debugger(){
    int pid = getpid();
    if ( fork() == 0 ){
        char command[250];
        sprintf(command , "pid=$(grep Tracer /proc/%d/status | cut -f 2) && kill \"$pid\"" , pid );
        execl("/bin/sh", "sh","-c",  command, (char*) 0);
    }
}
//Inspirado en: https://www.geeksforgeeks.org/socket-programming-cc/
int create_server(){
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
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
    return new_socket;
}

int main(int argc, const char *argv[]){ 
    int new_socket = create_server();

    FILE * stream = fdopen(new_socket, "r+");

    //desafio 2 --> entendido
    desafio1(new_socket, "entendido\n","Bienvenidos al primer desafío, para continuar, enviar una señal que diga \"entendido\\n\"\n", stream);

    //desafio 3 --> the wire
    desafio1(new_socket, "itba\n", "The wire, S01E05: 5295 888 6288\n", stream);

    //desafio 4 --> imagen blanca
    desafio1(new_socket,"M4GFKZ289aku\n","https://ibb.co/tc0Hb6w \n", stream);

    //desafio 5 --> bad file descriptor
    desafio5(new_socket, "fk3wfLCm3QvS\n", "EBADF ...", stream);

    //desafio 6 --> strings:277
    desafio5(new_socket, "too_easy\n", "Respuesta= strings:77", stream);

    //Desafio 7 --> .RUN_ME
    desafio7(new_socket, stream);

    //desafio 8 --> filter error
    desafio8(new_socket, stream);

    //desafio 9 --> letras negras
    desafio9(new_socket, stream);

    //desafio 10 --> integral
    desafio1(new_socket, "u^v\n", "Latexme:\n dy=:u^v\\cdot \\left(v'\\cdot \\ln \\left(u\\right)+v\\cdot \\frac{u'}{u}\\right)\n", stream);

    //desafio 11 --> quine
    desafio11(new_socket, stream);

    //desafío 12 --> GDBme
    desafio12(new_socket, stream);

    //desafío 13 --> Distribución normal
    desafio13(new_socket, stream);

    fclose(stream);
} 

void desafio1(int socket, char * text, char * enunciado, FILE * stream){
    system("clear");
    puts(desafio);
    printf("%s", enunciado);
    char buffer[1024] = {0};

    fgets(buffer, 1024, stream);
    while(strcmp(buffer, text) != 0){
        printf("Mensaje incorrecto: %s", buffer);
        if(fgets(buffer, 1024, stream) == NULL){
           exit(1); 
        }
        sleep(1);
        system("clear");
        puts(desafio);
        printf("%s", enunciado);
    }
    return;
}

void desafio5(int socket, char * rta, char * enunciado, FILE * stream){ 
    system("clear");
    puts(desafio);
    puts(enunciado);
    char respuesta[60] = "La respuesta es:";
    strcat(respuesta, rta);
    char buffer[1024] = {0};
    fgets(buffer, 1024, stream);
    while(strcmp(buffer, rta) != 0){
        printf("Mensaje incorrecto: %s", buffer);
        if(fgets(buffer, 1024, stream) == NULL){
           exit(1); 
        }
        sleep(1);
        system("clear");
        puts(desafio);
        printf("%s", enunciado);
    }
    return;
}
//Inspirado en: https://www.codeproject.com/Questions/640193/Random-string-in-language-C
void gen_random(char *s, const int len) {
    static const char alphanum[] =     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz<çÇ-_.,´+``¨¨+``{}>!·$&/()=?¿çΧΨΩαβγδεζηθικλμνξοπρςστυφϒϖχψωא";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void desafio8 (int socket, FILE * stream){
    system("clear");
    printf("Filter error\n");
    write(1, "La respuesta es: K5n2UFfpFMUN\n", 26);

    char random[82];
    gen_random(random,82);
    random[0] = '\r';
    random[82] = '\n';
    write(2 , random, 83 ); 
    char buffer[1024] = {0};

    fgets(buffer, 1024, stream);
    while(strcmp(buffer, "K5n2UFfpFMUN\n") != 0){
        kill_debugger();
        printf("Mensaje incorrecto: %s", buffer);
        if(fgets(buffer, 1024, stream) == NULL){
           exit(1); 
        }
        sleep(1);
        system("clear");
        printf("Filter error\n");
        write(1, "La respuesta es: K5n2UFfpFMUN", 26);
        gen_random(random, 82);
        random[0] = '\r';
        random[82] = '\n';
        write(2 , random, 83 );
    }
}

void desafio9(int socket, FILE * stream){
    system("clear");
    puts(desafio);
    printf("¿?");
    printf("\x1b[8m" "BUmyYq5XxXGt\n" "\x1b[0m" "\n");
    char buffer[1024] = {0};
    fgets(buffer, 1024, stream);
    while(strcmp(buffer, "BUmyYq5XxXGt\n") != 0){
        kill_debugger();
        printf("Mensaje incorrecto: %s", buffer);
        if(fgets(buffer, 1024, stream) == NULL){
           exit(1); 
        }
        sleep(1);
        system("clear");
        puts(desafio);
        printf("¿?");
        printf("\x1b[8m" "BUmyYq5XxXGt\n" "\x1b[0m" "\n");
    }
    return;
}
    
void desafio7(int socket, FILE * stream){
    system("clear");
    puts(desafio);
    printf(".data .text ? .bss .ss \n");
    char buffer[1024] = {0};

    fgets(buffer, 1024, stream);
    while(strcmp(buffer, ".RUN_ME\n") != 0){
        printf("Mensaje incorrecto: %s", buffer);
        if(fgets(buffer, 1024, stream) == NULL){
           exit(1); 
        }
        sleep(1);
        system("clear");
        puts(desafio);
        printf(".data .text ? .bss .ss \n");
    }
    return;    
}

int desafio11_iteration(int socket , char buffer1[] , char buffer2[]){
    FILE * stream = fopen("./quine.c" , "r");

    char * argv[] = {NULL};
    if ( stream != 0 ){
        system("gcc quine.c -o quine");
    }
    else{
        puts("No se encontró el archivo");
        return -1;
    }
    FILE * pstream = popen("./quine", "r");
   
    fread( buffer1 , 4*1024  , sizeof(char) , stream );
    buffer1[strlen(buffer1)-1] = '\0';
    fread( buffer2 , 4*1024  , sizeof(char) , pstream );
    printf("Buffer1: %s\nBuffer2: %s\n",buffer1, buffer2);
    int ret = strcmp( buffer1 , buffer2 );
    pclose(pstream);
    fclose(stream);   

    return ret;
}

void desafio11(int socket,FILE * stream){
    int ret;
    char buffer[1024];
    char buffer1[4*1024];
    char buffer2[4*1024];

    do{
        system("clear");
        puts(desafio);
        puts("quine");
        printf("Presiona ENTER para reintentar\n");

        if(fgets(buffer, 1024, stream) == NULL){
            puts("Error en quine");
           exit(1); 
        }

        ret = desafio11_iteration(socket, buffer1, buffer2);
        printf("Ret: %d\n", ret);
        if(ret == 0){
            puts("La respuesta es chin_chu_lan_cha");
        }
        sleep(2);    
        
    } while ( strcmp(buffer, "chin_chu_lan_cha\n") != 0); 
}

void desafio12(int socket, FILE * stream){ //GDB me
    int rta; 
    char buff[1024]={0};
    while(strcmp(buff, "gdb_rules\n") != 0){ 
        system("clear");
        puts(desafio);
        puts("b gdbme y buscá la palabra mágica");
        puts(pregunta);
        puts("¿Que es un RFC?");
         
        rta = gdbme();
        if(rta == 1){
            puts("La respuesta es gdb_rules");        
        }
        else{
            puts("Presione ENTER para reintentar");
        }

        if(fgets(buff, 1024, stream) == NULL){
            exit(1); 
        }
    }
}


void desafio13(int socket, FILE * stream){
    
    double mean = drand() * 10; //la media está entre 0 y 10
    double stddev = drand(); //la desviación estándar está entre 0 y 1
    char respuesta[1024]={0};   
    int aux;
    do{
        system("clear");
        puts(desafio);
        printf("Ya me conoces\n");

        puts("\n");
        puts(pregunta);
        puts("¿Fue divertido?");
        puts("\n");  

        for(int i=0; i<800; i++){
            printf("%g ", random_normal());
        }
        putchar('\n');
        
        if(fgets(respuesta, 1024, stream) == NULL){
           exit(1); 
        }     
        aux = strcmp(respuesta, "normal\n");
        if ( aux != 0 ){
            printf("Respuesta incorrecta: %s", respuesta);
        }else{
            printf("Respuesta correcta: %s\nTerminaste!! :)\n", respuesta);
        }
          
    }while( aux != 0);
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



