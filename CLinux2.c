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
          sprintf(comando,"#%dP%d",BAS_SERVO,base);
          printf("\n");
       }
       if(tecla == 96){
          base = base - MOVIMENTACAO;
          sprintf(comando,"#%dP%d",BAS_SERVO,base);
          printf("\n");
       }
       if(base<=BAS_MIN){
          printf("Você atingiu o limite mínimo de movimentação");
          break;
       }
       if(base>=BAS_MAX){
          printf("Você atingiu o limite máximo de movimentação");
          break;
       }
      /* if(tecla == 100){
          ombro = ombro + MOVIMENTACAO;
          sprintf(comando,"#%dP%d",SHL_SERVO,ombro);
          printf("\n");
       }
       if(tecla == 96){
          ombro = ombro - MOVIMENTACAO;
          sprintf(comando,"#%dP%d",SHL_SERVO,ombro);
          printf("\n");
       }
       if(ombro<=SHL_MIN){
          printf("Você atingiu o limite mínimo de movimentação");
          break;
       }
       if(ombro>=SHL_MAX){
          printf("Você atingiu o limite máximo de movimentação");
          break;
       }
       if(tecla == 100){
          cotovelo = cotovelo + MOVIMENTACAO;
          sprintf(comando,"#%dP%d",ELB_SERVO,cotovelo);
          printf("\n");
       }
       if(tecla == 96){
          ombro = ombro - MOVIMENTACAO;
          sprintf(comando,"#%dP%d",ELB_SERVO,cotovelo);
          printf("\n");
       }
       if(cotovelo<=ELB_MIN){
          printf("Você atingiu o limite mínimo de movimentação");
          break;
       }
       if(cotovelo>=ELB_MAX){
          printf("Você atingiu o limite máximo de movimentação");
          break;
       }
       if(tecla == 100){
          punho = punho + MOVIMENTACAO;
          sprintf(comando,"#%dP%d",WRI_SERVO,punho);
          printf("\n");
       }
       if(tecla == 96){
          punho = punho - MOVIMENTACAO;
          sprintf(comando,"#%dP%d",WRI_SERVO,punho);
          printf("\n");
       }
       if(punho<=WRI_MIN){
          printf("Você atingiu o limite mínimo de movimentação");
          break;
       }
       if(punho>=WRI_MAX){
          printf("Você atingiu o limite máximo de movimentação");
          break;
       }
       if(tecla == 100){
          garra = garra + MOVIMENTACAO;
          sprintf(comando,"#%dP%d",GRI_SERVO,garra);
          printf("\n");
       }
       if(tecla == 96){
          garra = garra - MOVIMENTACAO;
          sprintf(comando,"#%dP%d",GRI_SERVO,garra);
          printf("\n");
       }
       if(garra<=GRI_MIN){
          printf("Você atingiu o limite mínimo de movimentação");
          break;
       }
       if(garra>=GRI_MAX){
          printf("Você atingiu o limite máximo de movimentação");
          break;
       }*/
       enviar_comando(comando,serial_fd);
       memset(comando, 0, BUFSIZE);
    }while(tecla!=122);
       fechar_porta(serial_fd);
    }
    return 0;
}
