#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Detalhamento.h"

void dimensionar_armadura(struct viga *V)
{

    double *ptrArmaduraLongitudinal = NULL ; // Ponteiro que receberá o resultado do dimensionamento da armadura longitudinal
    double *ptrArmaduraTransversal  = NULL ; // Ponteiro que receberá o resultado do dimensionamento da armadura transversal

//--------Armaduras Longitudinais-----------//
    if (CALCULO_ARMADURAS_LONG == 1){
        printf("*******************************************************\n"   );
        printf("*********  CÁLCULO DA ARMADURA LONGITUDINAL  **********\n"   );
        printf("*******************************************************\n\n" );
    }

    for (int i = 0; i < (V->malha.N); i++)
    {

        if (CALCULO_ARMADURAS_LONG == 1){
            printf("--------------------SEÇÃO %d----------------------\n" , i );
        }

    // Momento negativo
        if (V->solicit.Md_dec[i] < 0.0) 
        {

            // Calculo armadura dupla/simples 
            ptrArmaduraLongitudinal = arm_long(V->solicit.Md_dec[i],V);      

            // Armadura negativa será resultado em tração ou armadura mínima
            V->arm.A_neg [i]  = fmax( (*(ptrArmaduraLongitudinal)) , V->arm.Al_min );                      


            
            if (*(ptrArmaduraLongitudinal + 1) <= V->arm.Al_min)        // Armadura mínima é suficiente para arm de compressão
            {                    
                V->arm.A_comp[i] = 0.0;                                                                             
            }                                         

            else                                                        // Haverá armadura complementar e armadura mínima                                                  
            {                                                                                                       
                V->arm.A_comp[i] = (*(ptrArmaduraLongitudinal + 1));
            }                                                                                   
        }   
    
    // Momento positivo
        else if (V->solicit.Md_dec[i] > 0.0)
        {   
            ptrArmaduraLongitudinal   = arm_long(V->solicit.Md_dec[i],V);

            if (*(ptrArmaduraLongitudinal) > V->arm.Al_min)             // Armadura de tração é maior que armadura mínima -> haverá Arm comp + Arm min
            {
                V->arm.A_comp [i]  = (*(ptrArmaduraLongitudinal)) - V->arm.Al_min ; 
            }
            else{                                                       // Armadura de tração é menor que armadura mínima -> Não haverá Armadura complementar
                V->arm.A_comp [i]  = 0.0;
            }
            
            V->arm.A_neg  [i]  =  *(ptrArmaduraLongitudinal + 1);       // Armadura dupla (caso haja)

        }

    // Momento nulo
        else
        {
            V->arm.A_neg  [i] = 0.0;
            V->arm.A_comp [i] = 0.0;
        }

        if (CALCULO_ARMADURAS_LONG == 1)
        {
            printf("arm.mínima         = %f [m²]\n" , V->arm.Al_min    );
            printf("arm.A_complementar = %f [m²]\n" , V->arm.A_comp [i]);
            printf("arm.A_negativa     = %f [m²]\n" , V->arm.A_neg  [i]);
            printf("--------------------------------------------------\n");
            printf("\n");
        }
        


    }

//--------Armaduras Transversais-----------//

    if (CALCULO_ARMADURAS_TRANS == 1){
        printf("******************************************************\n"     );
        printf("*********  CÁLCULO DA ARMADURA TRANSVERSAL  **********\n"     );
        printf("******************************************************\n\n"   );
    }

    for (int i = 0; i < (V->malha.N); i++)
    {

        if (CALCULO_ARMADURAS_TRANS == 1){
            printf("--------------------SEÇÃO %d----------------------\n" , i );
        }

        ptrArmaduraTransversal = calc_arm_transv(V->solicit.Vd[i],V);

        // Cortante nulo será utilizado a armadura mínima
        if (*ptrArmaduraTransversal < V->arm.Asw_min)
        {
            V->arm.Asw[i] = V->arm.Asw_min;
        }

        else
        {
            V->arm.Asw[i] = *ptrArmaduraTransversal;
        }

        if (CALCULO_ARMADURAS_TRANS == 1){

            printf(" Armadura utilizada = %f [m²/m]\n" , V->arm.Asw[i]    );
            printf("--------------------------------------------------\n" );
            printf("\n");
        }
    }
}
