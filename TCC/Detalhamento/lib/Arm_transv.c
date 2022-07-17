#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Detalhamento.h"

double *calc_arm_transv(double Vcalc , struct viga *V)
{

    //Transformação quando momento é negativo
    if (Vcalc < 0)
    {
        Vcalc = -Vcalc;
    }
    
    double A_sw;
    double *ptr_saida = NULL;

    // Angulo da biela
    double teta = M_PI / 4; // graus

    // Ângulo da diagonal tracionada (estribos = 90º)
    double alpha = M_PI / 2; // rad

    // Força resistente do concreto
    double Vc = 0.6 * (V->prop.fctd * pow(10, 3)) * V->geo.largura * V->geo.d;

    // Valor da armadura em (m²/m)
    A_sw = (Vcalc - Vc) / (0.9 * V->geo.d * (V->prop.fywd * pow(10, 3)) * ((1.0 / tan(teta)) + (1.0 / tan(alpha))) * sin(alpha));

    if (A_sw < 0.0)
    {
        A_sw = 0.0;
    }
    

    ptr_saida = &A_sw;

    if (CALCULO_ARMADURAS_TRANS == 1)
    {
        printf("Cortante calculado = %f  [kN]   \n" ,  Vcalc            );
        printf("Parâmetro teta     = %f  [rad]  \n" , teta              );
        printf("Parâmetro alpha    = %f  [rad]  \n" , alpha             );
        printf("Armadura estribos  = %f  [m²/m] \n" , A_sw              );
        printf("Armadura mínima    = %f  [m²/m] \n" , V->arm.Asw_min    );
        printf("--------------------------------------------------\n"   );
    }


    return ptr_saida;

}

void arm_transv_min(struct viga *V){

    double gama_s = 1.15; // Fator de majoração de resistência do aço

    // Ângulo da diagonal tracionada (estribos = 90º)
    double alpha = M_PI / 2; // rad

    V->arm.Asw_min = 0.2 * (V->prop.fct_m / (V->prop.fywd * gama_s)) * V->geo.largura * sin(alpha);



}