#include <stdio.h>
#include <stdlib.h>
#define PI 3.1415926535

double cinedireta1(base,ombro,cotovelo,punho)

{

double x, A1,A2,A3,A4;

A1 = ((base-500)*0.09 + 180)*(PI/180);

A2 = ((ombro-500)*0.09)*(PI/180);

A3 = ((cotovelo-500)*0.09)*(PI/180);

A4 = ((punho-500)*0.09 - 90)*(PI/180);

x = cos(A1)*(cos(A2+A3+A4)*5.7+cos(A2+A3)*18.6+cos(A2)*14.6);



return x;



}

double cinedireta2(base,ombro,cotovelo,punho)

{

double y, A1,A2,A3,A4;

A1 = ((base-500)*0.09 + 180)*(PI/180);

A2 = ((ombro-500)*0.09)*(PI/180);

A3 = ((cotovelo-500)*0.09)*(PI/180);

A4 = ((punho-500)*0.09 - 90)*(PI/180);

y = sin(A1)*(cos(A2+A3+A4)*5.7+cos(A2+A3)*18.6+cos(A2)*14.6 );



return y;



}

double cinedireta3(base,ombro,cotovelo,punho)

{

double z, A1,A2,A3,A4;

A1 = ((base-500)*0.09 + 180)*(PI/180);

A2 = ((ombro-500)*0.09)*(PI/180);

A3 = ((cotovelo-500)*0.09)*(PI/180);

A4 = ((punho-500)*0.09 - 90)*(PI/180);

z = sin(A2+A3+A4)*5.7 + sin(A2+A3)*18.6 + sin(A2)*14.6 + 6.6;

return z;



}
int main()
{
    double r1,r2,r3;
    int base = 1500, ombro = 2000, cotovelo = 1500, punho = 2500, garra = 1500;
     r1 = cinedireta1(base,ombro,cotovelo,punho);

        r2 = cinedireta2(base,ombro,cotovelo,punho);

        r3 = cinedireta3(base,ombro,cotovelo,punho);

        printf("valor x: %.3f ",r1);

        printf("valor y: %.3f ",r2);

        printf("valor z: %.3f ",r3);
}
