#include <stdio.h>
#include <stdlib.h>


#include "ufrn_al5d.h"

#define POS_INICIAL_GLOBAL "#0P1500#1P1500#2P1500#3P1500#4P1500"
#define KEY_RIGHT 11
#define KEY_LEFT 11
#define INCREMENTAR 77
#define REDUZIR 75


int main()
{
    ufrn_header();

int serial_fd, tecla;
int base = 1500, ombro = 1500, cotovelo = 1500, punho = 1500, garra = 1500;
char *comando;


printf("INICIALIZANDO...\n\n");

serial_fd = abrir_porta();

if(serial_fd == -1)
{
 printf("Erro ao abrir a porta serial /dev/ttyS0\nAbortando o programa...");
 return -1;
}
else
{
 printf("Porta serial /dev/ttyS0 aberta com sucesso\n");

 if(configurar_porta(serial_fd) == -1)
 {
     printf("Erro inicializando a porta\n");
     close(serial_fd);
     return -1;
 }

 comando = (char*) malloc(sizeof(char)*BUFSIZE);

 printf("\nCOLOCANDO O BRAÇO ROBÓTICO NA POSIÇÃO INICIAL\n");

 sprintf(comando,"%s",POS_INICIAL_GLOBAL);
 enviar_comando(comando,serial_fd);
 memset(comando, 0, BUFSIZE);

 printf("Use as setas para movimentar cada servo do braço robótico\nApós terminar a movimentação aperte a tecla Z\n");
 printf("Primeiro movimente o servo da base");

 do{
        tecla = getchar();
        if(tecla == 100){
                   base = base + KEY_RIGHT;
        }
        if(tecla == 97){
                   base = base - KEY_RIGHT;
        }

         if(base<=BAS_MIN){
            printf("Você atingiu o limite mínimo de movimentação");
            break;
         }
         if(base>=BAS_MAX){
            printf("Você atingiu o limite máximo de movimentação");
            break;
         }
         sprintf(comando,"#%dP%d",BAS_SERVO,base);
  enviar_comando(comando,serial_fd);
  memset(comando, 0, BUFSIZE);
         }while(tecla!= 122);

        printf("Agora vamos movimentar o servo do ombro");

 do{
        tecla = getchar();
        if(tecla == 100){
                   ombro = ombro + KEY_RIGHT;
        }
        if(tecla == 97){
                   ombro = ombro - KEY_RIGHT;
        }
         if(base<=SHL_MIN){
            printf("Você atingiu o limite mínimo de movimentação");
            break;
         }
         if(base>=SHL_MAX){
            printf("Você atingiu o limite máximo de movimentação");
            break;
         }
         sprintf(comando,"#%dP%d",SHL_SERVO,ombro);
  enviar_comando(comando,serial_fd);
  memset(comando, 0, BUFSIZE);
         }while(tecla!=122);

         printf("Movimentando agora o cotovelo");

 do{
        tecla = getchar();
        if(tecla == 100){
                   cotovelo = cotovelo + KEY_RIGHT;
        }
        if(tecla == 97){
                   cotovelo = cotovelo - KEY_RIGHT;
        }
         if(base<=ELB_MIN){
            printf("Você atingiu o limite mínimo de movimentação");
            break;
         }
         if(base>=ELB_MAX){
            printf("Você atingiu o limite máximo de movimentação");
            break;
         }
         sprintf(comando,"#%dP%d",ELB_SERVO,cotovelo);
  enviar_comando(comando,serial_fd);
  memset(comando, 0, BUFSIZE);
         }while(tecla!=122);

         printf("Punho...");

 do{
        tecla = getchar();
        if(tecla == 100){
                   punho = punho + KEY_RIGHT;
        }
        if(tecla == 97){
                   punho = punho - KEY_RIGHT;
        }
         if(base<=WRI_MIN){
            printf("Você atingiu o limite mínimo de movimentação");
            break;
         }
         if(base>=WRI_MAX){
            printf("Você atingiu o limite máximo de movimentação");
            break;
         }
         sprintf(comando,"#%dP%d",WRI_SERVO,punho);
  enviar_comando(comando,serial_fd);
  memset(comando, 0, BUFSIZE);
         }while(tecla!=122);

         printf("E finalmente a garra");

 do{
        tecla = getchar();
        if(tecla == 100){
                   garra = garra + KEY_RIGHT;
        }
        if(tecla == 97){
                   garra = garra - KEY_RIGHT;
        }
         if(base<=GRI_MIN){
            printf("Você atingiu o limite mínimo de movimentação");
            break;
         }
         if(base>=GRI_MAX){
            printf("Você atingiu o limite máximo de movimentação");
            break;
         }
         sprintf(comando,"#%dP%d",GRI_SERVO,garra);
  enviar_comando(comando,serial_fd);
  memset(comando, 0, BUFSIZE);
         }while(tecla!=122);

         fechar_porta(serial_fd);
}


   return 0;

}
