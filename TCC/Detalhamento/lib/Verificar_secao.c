#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "Detalhamento.h"
#include "Definition.h"

bool verificar_Seçao(struct viga *V)
{

    bool saida ;   // Se TRUE - seção esta OK

    double espaçamentoHorizontal  ; // (m ) Espaçamento horizontal entre face de barras
    double espaçamentoVertical    ; // (m ) Espaçamento vertical entre face de barras
    int    numeroBarrasFaltantes  ; // (  ) Número de barras faltantes na seção
    int    numeroBarrasSeçao      ; // (  ) Número de barras calculadas na seção
    int    numeroBarrascalculadas ; // (  ) Número de barras calculadas na camada
    float  bitolaSeçao            ; // (mm) Bitola da seção
    double dReal                  ; // (m ) Altura útil calculada para cada seção
    int    camada                 ; // (  ) Camada de barras na seção

    double larguraEfetiva = V->geo.largura - 2 * V->geo.cob ; // (m) Largura Útil da viga




for ( int seçao = 0; seçao < V->malha.N ; seçao++)
{
    
    // TODO Verificação se na seção esta sendo utilizando ARMADURA COMP ou ARMADURA MÍNIMA
    if (V->barras.N_comp[seçao] == 0)
    {
        numeroBarrasSeçao = V->barras.N_Lmin  [seçao] ;
    }
   
    else
    {
        numeroBarrasSeçao = V->barras.N_comp  [seçao] ;
    }

    bitolaSeçao           = V->barras.Bt_pos [seçao] ;
    numeroBarrasFaltantes = numeroBarrasSeçao        ;
    camada                = 0                        ;
    dReal                 = 0                        ;   





    // TODO Calculo do espaçamento Horizontal e Verical máximo
    espaçamentoHorizontal = fmax(fmax(0.02,bitolaSeçao * 0.001), 1.2 * dimensaoAgregado) ;
    espaçamentoVertical   = fmax(fmax(0.02,bitolaSeçao * 0.001), 0.5 * dimensaoAgregado) ;

    // TODO Calculo das camadas
    while (numeroBarrasFaltantes >= 0)
    {

        if (camada == 0)
        {
            numeroBarrascalculadas = maxbarras_camada(larguraEfetiva , espaçamentoHorizontal , bitolaSeçao*0.001) ;
        }
        else
        {
            numeroBarrascalculadas = 2 ;
        }

        dReal = dReal + ( (double) numeroBarrascalculadas / ( (double) numeroBarrasSeçao ) ) * ( ( (bitolaSeçao*0.001)/2.0 ) + ( (double) camada * espaçamentoVertical) ) ;

        numeroBarrasFaltantes = numeroBarrasFaltantes -  numeroBarrascalculadas ;

        camada = camada + 1; ;

    }

    //Verificação Da altura útil calculada
    if (dReal > V->geo.d)
    {
        saida = false ;
        break ;
    }
    else
    {
        saida = true ;
    }
    
}

    if (CALCULO_SEÇOES == 1)
    {

    printf("*****************************************************\n"   );
    printf("*************  VERIFICAÇÃO DAS SEÇÕES  **************\n\n" );
    printf("*****************************************************\n"   );

    printf("VERIFICAÇÃO OK  = %i\n", saida );

    }
    return saida;
}