#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ufrn_al5d.h"

#define POS_INICIAL_GLOBAL "#0P1500#1P1500#2P1500#3P1500#4P1500"
#define MOVIMENTACAO 11
#define PI 3.1415926535

double cinedireta1(base,ombro,cotovelo,punho)
{
double x, A1,A2,A3,A4;
A1 = ((base-500)*0.09)*(PI/180);
A2 = ((ombro-500)*0.09)*(PI/180);
A3 = ((cotovelo-500)*0.09)*(PI/180);
A4 = ((punho-500)*0.09)*(PI/180);
x = cos(A1)*(cos(A2+A3+A4)*5.7+cos(A2+A3)*18.6+cos(A2)*14.6);

return x;

}
double cinedireta2(base,ombro,cotovelo,punho)
{
double y, A1,A2,A3,A4;
A1 = ((base-500)*0.09)*(PI/180);
A2 = ((ombro-500)*0.09)*(PI/180);
A3 = ((cotovelo-500)*0.09)*(PI/180);
A4 = ((punho-500)*0.09)*(PI/180);
y = sin(A1)*(cos(A2+A3+A4)*5.7+cos(A2+A3)*18.6+cos(A2)*14.6);

return y;

}
double cinedireta3(base,ombro,cotovelo,punho)
{
double z, A1,A2,A3,A4;
A1 = ((base-500)*0.09)*(PI/180);
A2 = ((ombro-500)*0.09)*(PI/180);
A3 = ((cotovelo-500)*0.09)*(PI/180);
A4 = ((punho-500)*0.09)*(PI/180);
z = sin(A2+A3+A4)*5.7 + sin(A2+A3)*18.6 + sin(A2)*14.6 + 6.6;
return z;

}


int main()
{
double r1,r2,r3;
    ufrn_header();

    int serial_fd, tecla, n_servo;
    int base = 1500, ombro = 1500, cotovelo = 1500, punho = 1500, garra = 1500, tempo = 1500;
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

        sprintf(comando,"%sT%d",POS_INICIAL_GLOBAL,tempo);
        enviar_comando(comando,serial_fd);
        memset(comando, 0, BUFSIZE);

        printf("DIGITE O NUMERO REFERENTE AO SERVO DA BASE QUE QUEIRA MOVIMENTAR\n");
        printf("base - 0\nOMBRO - 1\nCOTOVELO - 2\nPUNHO - 3\nGARRA - 4\n");
        printf("USE AS TECLAS A E D PARA MOVIMENTAR O SERVO\n\n");


        do
        {
            scanf("%i",&n_servo);
            do
            {
                tecla = getchar();
                if(n_servo == 0)
                {
                    if(tecla == 100)
                    {
                        base = base + MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",BAS_SERVO,base,tempo);
                    }
                    if(tecla == 97)
                    {
                        base = base - MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",BAS_SERVO,base,tempo);
                    }
                    if(base<=BAS_MIN)
                    {
                        printf("Você atingiu o limite mínimo de movimentação\n");
                        break;
                    }
                    if(base>=BAS_MAX)
                    {
                        printf("Você atingiu o limite máximo de movimentação\n");
                        break;
                    }
                }
                if(n_servo == 1)
                {
                    if(tecla == 100)
                    {
                        ombro = ombro + MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",SHL_SERVO,ombro,tempo);
                    }
                    if(tecla == 97)
                    {
                        ombro = ombro - MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",SHL_SERVO,ombro,tempo);
                    }
                    if(ombro<=SHL_MIN)
                    {
                        printf("Você atingiu o limite mínimo de movimentação\n");
                        break;
                    }
                    if(ombro>=SHL_MAX)
                    {
                        printf("Você atingiu o limite máximo de movimentação\n");
                        break;
                    }
                }
                if(n_servo == 2)
                {
                    if(tecla == 100)
                    {
                        cotovelo = cotovelo + MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",ELB_SERVO,cotovelo,tempo);
                    }
                    if(tecla == 97)
                    {
                        cotovelo = cotovelo - MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",ELB_SERVO,cotovelo,tempo);
                    }
                    if(cotovelo<=ELB_MIN)
                    {
                        printf("Você atingiu o limite mínimo de movimentação\n");
                        break;
                    }
                    if(cotovelo>=ELB_MAX)
                    {
                        printf("Você atingiu o limite máximo de movimentação\n");
                        break;
                    }
                }
                if(n_servo == 3)
                {
                    if(tecla == 100)
                    {
                        punho = punho + MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",WRI_SERVO,punho,tempo);
                    }
                    if(tecla == 97)
                    {
                        punho = punho - MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",WRI_SERVO,punho,tempo);
                    }
                    if(punho<=WRI_MIN)
                    {
                        printf("Você atingiu o limite mínimo de movimentação\n");
                        break;
                    }
                    if(punho>=WRI_MAX)
                    {
                        printf("Você atingiu o limite máximo de movimentação\n");
                        break;
                    }
                }
                if(n_servo == 4)
                {
                    if(tecla == 100)
                    {
                        garra = garra + MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",GRI_SERVO,garra,tempo);
                    }
                    if(tecla == 97)
                    {
                        garra = garra - MOVIMENTACAO;
                        sprintf(comando,"#%dP%dT%d",GRI_SERVO,garra,tempo);
                    }
                    if(garra<=GRI_MIN)
                    {
                        printf("Você atingiu o limite mínimo de movimentação\n");
                        break;
                    }
                    if(garra>=GRI_MAX)
                    {
                        printf("Você atingiu o limite máximo de movimentação\n");
                        break;
                    }
                }
                enviar_comando(comando,serial_fd);
                memset(comando, 0, BUFSIZE);
            }
            while(tecla!=122);
        }
        while(n_servo!=5);
        fechar_porta(serial_fd);
        r1 = cinedireta1(base,ombro,cotovelo,punho);
        r2 = cinedireta2(base,ombro,cotovelo,punho);
        r3 = cinedireta3(base,ombro,cotovelo,punho);
        printf("valor x: %.3f ",r1);
        printf("valor y: %.3f ",r2);
        printf("valor z: %.3f ",r3);
        printf("%d  ",base);
        printf("%d  ",ombro);
        printf("%d  ",cotovelo);
        printf("%d  ",punho);

    }

    return 0;
}
