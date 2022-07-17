#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Detalhamento.h"

double * arm_long(double MomentoEntrada , struct viga *V){

    double Mcalc     ; // (kNm) Momento calculado
    double alpha_c   ; // (adm) Parâmetro de calculo do concreto
    double lambda    ; // (adm) Parâmetro de calculo do concreto
    double x_max     ; // ( m ) Posição máxima da linha neuytra
    double x, x1, x2 ; // ( m ) Posição da linha neutra e seus resultados após a solução da eq de 2º grau
    double Md_max    ; // (kNm) Momento máximo para armadura simples
    double Delta_M   ; // (kNm) Diferença entre o momento máximo e o momento solicitante para o caso de armadura dupla

    double gama_m = 1.4 ; // fator de segurança do concreto

    double Arm_T ; // (cm²) Armadura de tração calculada
    double Arm_C ; // (cm²) Armadura de compressão calculada

    double  result[2]          ; // Vetor resultados
    double *ptr_saida = result ; // Ponteiro saida de resultados

    //Transformação quando momento é negativo
    if (MomentoEntrada < 0)
    {
        Mcalc = -MomentoEntrada;
    }
    else
    {
        Mcalc = MomentoEntrada;
    }
    
    
    // Calculo de lamba , alpha_c e Md_max
    if (V->prop.fck <= 50)
    {
        alpha_c = 0.85 ;
        lambda  = 0.8  ;

        x_max   = 0.45 * V->geo.d;

        Md_max  = (lambda) * (x_max) * (alpha_c) * ((V->prop.fck * pow(10, 3)) / gama_m) * (V->geo.largura) * (V->geo.d - (0.5) * (lambda) * (x_max));
    }

    else
    {
        alpha_c = 0.85 * (1 - ((V->prop.fck - 50) / 200)) ;
        lambda  = 0.8  - ((V->prop.fck - 50) / 400)       ;

        x_max   = 0.35 * V->geo.d ;

        Md_max  = (lambda) * (x_max) * (alpha_c) * ((V->prop.fck * pow(10, 3)) / gama_m) * (V->geo.largura) * (V->geo.d - (0.5) * (lambda) * (x_max));
    }

    /*---------Verificação da armadura dupla / simples------------*/

    if (Mcalc <= Md_max) // Armadura simples
    {
        //Verificar armadura dupla somente

        // Posição da linha neutra
        x1 = (V->geo.d / lambda) * (1.0 + (sqrt(1.0 - ((Mcalc) / ((0.5) * (alpha_c) * (V->geo.largura) * (pow(V->geo.d, 2)) * ((V->prop.fck * pow(10, 3)) / gama_m))))));
        x2 = (V->geo.d / lambda) * (1.0 - (sqrt(1.0 - ((Mcalc) / ((0.5) * (alpha_c) * (V->geo.largura) * (pow(V->geo.d, 2)) * ((V->prop.fck * pow(10, 3)) / gama_m))))));

        if (x1 <= V->geo.altura)
        {
            x = x1;
        }
        if (x2 < V->geo.altura)
        {
            x = x2;
        }
        else
        {
            printf("Não foi possivel calcular Linha neutra\n");
        }

        if (x > x_max)
        {
            printf("X/D > X_lim");
        }

        Arm_T = Mcalc / ((V->prop.fyd * pow(10, 3)) * ((V->geo.d) - (0.5) * (lambda) * (x)));
        Arm_C = 0;

    }

    if (Mcalc > Md_max) // Armadura dupla
    {
        Delta_M = Mcalc - Md_max;
        x = x_max;

        Arm_C = Delta_M / ((V->geo.d - V->geo.d2) * (V->prop.fyd * pow(10, 3)));
        Arm_T = Md_max / ((V->prop.fyd * pow(10, 3)) * ((V->geo.d) - (0.5) * (lambda) * (x_max))) + Arm_C;

    }

    ptr_saida[0] = Arm_T;
    ptr_saida[1] = Arm_C;


    if (CALCULO_ARMADURAS_LONG == 1)
        {
            printf("Momento calculado     = %f [kNm] \n" ,  MomentoEntrada    );
            printf("Parâmetro Lambda      = %f       \n" , lambda             );
            printf("Parâmetro Alpha_c     = %f       \n" , alpha_c            );
            printf("Altura útil elemento  = %f [m]   \n" , V->geo.d           );
            printf("Largura elemento      = %f [m]   \n" , V->geo.largura     );
            printf("fcd do concreto       = %f [MPa] \n" , V->prop.fck/gama_m );
            printf("Momento máximo        = %f [kNm] \n" , Md_max             );
            printf("Momento mínimo        = %f [kNm] \n" , V->solicit.Md_min  );
            printf("Altura linha neutra   = %f [m]   \n" , x                  );

            printf("\n");
            
            printf("Armadura Tração     = %f [m²] \n" , Arm_T               );
            printf("Armadura Compressão = %f [m²] \n" , Arm_C               );
            printf("Armadura mínima     = %f [m²] \n" , V->arm.Al_min       );
            printf("--------------------------------------------------\n\n" );
        }
    
    return ptr_saida;
};


/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/


void arm_long_min(struct viga *V){


    double alpha_c      ; // ( ) Parâmetro de calculo do concreto
    double lambda       ; // ( ) Parâmetro de calculo do concreto
    double x1,x2,x      ; // (m) Posição da linha neutra e seus resultados após a solução da eq de 2º grau
    double gama_m = 1.4 ; // fator de segurança do concreto

    double W0 = (V->geo.largura * pow(V->geo.altura, 2)) / 6.0; // (m³) Módulo de resistência da seção 


    // Calculo de lamba e alpha_c
    if (V->prop.fck <= 50)
    {
        alpha_c = 0.85;
        lambda = 0.8;
    }

    else
    {
        alpha_c = 0.85 * (1 - ((V->prop.fck - 50) / 200));
        lambda = 0.8 - ((V->prop.fck - 50) / 400);
    }


    V->solicit.Md_min = 0.8 * W0 * pow(10, 3) * V->prop.fctk_sup;   // (kNm) Momento mínimo de cálculo
    

    // Posição da linha neutra
    x1 = (V->geo.d / lambda) * (1.0 + (sqrt(1.0 - ((V->solicit.Md_min) / ((0.5) * (alpha_c) * (V->geo.largura) * (pow(V->geo.d, 2)) * ((V->prop.fck * pow(10, 3)) / gama_m))))));
    x2 = (V->geo.d / lambda) * (1.0 - (sqrt(1.0 - ((V->solicit.Md_min) / ((0.5) * (alpha_c) * (V->geo.largura) * (pow(V->geo.d, 2)) * ((V->prop.fck * pow(10, 3)) / gama_m))))));

    if (x1 < V->geo.altura)
    {
        x = x1;
    }
    if (x2 < V->geo.altura)
    {
        x = x2;
    }

    V->arm.Al_min = V->solicit.Md_min / ((V->prop.fyd * pow(10, 3)) * ((V->geo.altura * 0.8) - (0.5) * (lambda) * (x)));

    
}

void calc_arm_pele(struct viga *V)
{
    if (V->geo.altura > 0.60)
    {

        V->arm.A_pele = 0.0010 * V->geo.altura * V->geo.largura;
    }
    else
    {
        V->arm.A_pele = 0;
    }
};