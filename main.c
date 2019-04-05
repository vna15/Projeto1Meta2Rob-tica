#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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
	int base = 1500;
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

		printf("\nCOLOCANDO O BRA�O ROB�TICO NA POSI��O INICIAL\n");

		sprintf(comando,"%s",POS_INICIAL);
		enviar_comando(comando,serial_fd);
		memset(comando, 0, BUFSIZE);

		printf("Use as setas para movimentar cada servo do bra�o rob�tico\nAp�s terminar a movimenta��o aperte a tecla Z\n");
		printf("Primeiro movimente o servo da base");

		do{
        tecla = getch();
        if(tecla == 224){
            tecla = getch();
                if(tecla == INCREMENTAR){
                   base = base + KEY_RIGHT;
                }
                else if(tecla == REDUZIR){
                   base = base - KEY_LEFT;
                }
                else{
                   printf("Voc� apertou uma tecla inv�lida.\nTente novamente");
                }
         }
         else if(tecla != 122){
            printf("Voc� apertou uma tecla inv�lida.\nTente novamente");
         }
         if(base<=500){
            printf("Voc� atingiu o limite m�nimo de movimenta��o");
            break;
         }
         if(base>=2380){
            printf("Voc� atingiu o limite m�ximo de movimenta��o");
            break;
         }
         sprintf(comando,"#%dP%d",BAS_SERVO,base);
		 enviar_comando(comando,serial_fd);
         }while(tecla!=122);


   return 0;

}

