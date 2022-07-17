#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "Detalhamento.h"
#include "Definition.h"



void calcular_barras(struct viga *V)
{
//--------Número de barras-----------//

int associarBarras[5][2] = {{3,5},{3,3},{3,4},{3,3},{3,2}}; // Para cada região haverá { Arm positiva , Arm negativa }

double areaMinimaEfetiva ; // (m²) Área mínima efetiva

for (int regiao = 0; regiao < V->malha.numRegioes; regiao++)
    {

        for (int ponto = V->malha.raizes[regiao]; ponto <= V->malha.raizes[regiao+1]; ponto++)
        {

        // TODO Armadura positiva
        if (V->arm.A_comp [ ponto ] == 0)                                                // * Somente armadura mínima -> Min
        {
            V->barras.Bt_pos  [ ponto ] = Bitolas_padrão[associarBarras[regiao][0]] ;

            V->barras.N_Lmin  [ ponto ] = ceil( V->arm.Al_min / (M_PI * pow(V->barras.Bt_pos[ponto]/1000,2) / 4.0 )) ;

            V->barras.N_comp  [ ponto ] = 0 ;
        }
      
        else  // * Caso haja armadura complementar, deve-se verificar se essa será maior que a armadura mínima efetiva calculada                                        
        {
            V->barras.Bt_pos [ ponto ] = Bitolas_padrão[associarBarras[regiao][0]] ;
            
            V->barras.N_Lmin [ ponto ] = ceil( V->arm.Al_min / ( M_PI * pow( V->barras.Bt_pos [ ponto ] / 1000 , 2 ) / 4.0 )) ;

            areaMinimaEfetiva = V->barras.N_Lmin [ ponto ] * ( M_PI * pow( V->barras.Bt_pos [ ponto ] / 1000 , 2 ) / 4.0 ) ;

            if (V->arm.A_comp [ ponto ] >= areaMinimaEfetiva)                            // * Armadura complementar maior que a mínima efetiva -> Min + Comp
            {
                V->barras.N_comp [ ponto ] = ceil( V->arm.A_comp[ponto] / ( M_PI * pow( ( V->barras.Bt_pos[ ponto ] / 1000 ) , 2 ) / 4.0 )) ; 
            }
    
            else                                                                         // * Armadura mínima efetiva maior que complementar -> Min
            {
                V->barras.N_comp  [ ponto ] = 0 ;   
            }
            
        }

        // TODO Arm negativa

            V->barras.Bt_neg [ ponto ] = Bitolas_padrão[associarBarras[regiao][1]] ;
            V->barras.N_neg  [ ponto ] = ceil( V->arm.A_neg[ponto] / (M_PI * pow((V->barras.Bt_neg[ponto]/1000),2) / 4.0 )) ;

        // TODO Arm construtivo

        if (V->barras.N_neg[ ponto ] == 0)
        {
            V->barras.N_const [ ponto ] = 2;
            V->barras.Bt_const[ ponto ] = Bitolas_padrão[0] ;
        }

        else
        {
            V->barras.N_const [ponto] = 0;
            V->barras.Bt_const[ponto] = 0;
        }            
        }
    }
    
    if (DETALHAR_SEÇÕES_ARMADURAS == 1)
    
    {

    printf("*****************************************************\n"   );
    printf("******************  BARRAS SEÇÕES  ******************\n\n" );
    printf("*****************************************************\n"   );

    for (int ponto = 0; ponto < V->malha.N; ponto++)
    {    
        printf("------------------SEÇÃO %d------------------------\n",ponto); 
        printf("Arm_min   -- %d \u03C6 %.1f mm \n" , V->barras.N_Lmin  [ponto] , V->barras.Bt_pos   [ponto] );
        printf("Arm_comp  -- %d \u03C6 %.1f mm \n" , V->barras.N_comp  [ponto] , V->barras.Bt_pos   [ponto] );
        printf("Arm_neg   -- %d \u03C6 %.1f mm \n" , V->barras.N_neg   [ponto] , V->barras.Bt_neg   [ponto] );
        printf("Arm_const -- %d \u03C6 %.1f mm \n" , V->barras.N_const [ponto] , V->barras.Bt_const [ponto] );
        printf("--------------------------------------------------\n");
        printf("\n\n");
    }
    }

}
