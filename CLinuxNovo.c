#include <stdio.h>
#include <stdlib.h>

#include "ufrn_al5d.h"

#define POS_INICIAL_GLOBAL "#0P1500#1P1500#2P1500#3P1500#4P1500"
#define MOVIMENTACAO 11

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

    do{
       tecla = getchar();
       if(tecla == 100){
          base = base + MOVIMENTACAO;
       }
       if(tecla == 96){
          base = base - MOVIMENTACAO;
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
    }while(tecla!=122)
    }
    return 0;
}
