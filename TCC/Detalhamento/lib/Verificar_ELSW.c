#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "Detalhamento.h"
#include "Definition.h"

bool verificar_ELS_W(struct viga *V)
{

    bool saida; //retorna se a verificação esta ok ou não

    int    numBarrasTracao     ; // (   ) Numero de barras em tração da seção
    int    numBarrasCompressao ; // (   ) Numero de runbarras em compressão da seção
    int    maxBarrasCamada     ; // (   ) Numero de barras máximo na camada inferior
    int    limiteInicial       ; // (   ) Seção limite inferior da região
    int    limiteFinal         ; // (   ) Seção limite superior da região
    int    secaoCritica        ; // (   ) Seções em que há momento máximo em cada região

    float  wkMax              ; // ( mm ) Abertura máxima de fissura
    float  bitolaLongitudinal ; // (m  ) Bitola longitudinal da seção
    float  bitolaTransversal  ; // (m  ) Bitola trasnversal da seção

    double wk1                      ; // ( mm ) Parâmetro para calculo da expressão da fissuração 
    double wk2                      ; // ( mm ) Parâmetro para calculo da expressão da fissuração
    double wk                       ; // ( mm ) Abertura de fissura
    double taxaArmadura             ; // (m²/m) Taxa de armadura no tirante de armadura na seção NBR6118:2014 Seção 17.3.3.2
    double sigmaS                   ; // (MPa) Tensão na armadura de um tirante
    double linhaNeutra2             ; // (m  ) Linha neutra no estádio II
    double inercia2                 ; // (m4 ) Inercia no estádio II
    double momentoMaximo            ; // (kNm) Valor do momento máximo em cada região
    double armaduraTracao           ; // (m² ) Armadura efetiva Longidudinal na parte tracionada
    double armaduraCompressao       ; // (m² ) Armadura efetiva Longidudinal na parte comprimida
    double larguraEfetiva           ; // (m  ) Largura Útil da viga
    double espaçamentoHorizontalMin ; // (m  ) Espaçamento horizonalt máximo NBR6118:2014 Seção 18.3.2.2
    double espaçamentoHorizontal    ; // (m  ) Espaçamento horizonalt calculado entre as barras
    double espaçamentoVertical      ; // (m  ) Espaçamento vertical NBR6118:2014 Seção 18.3.2.2


    float  alphaE = 15  ; // (   ) Parâmetro divisão do modulo de young do aço contra o modulo secante do concreto (Norma estabelce como 15)
    float  neta1 = 2.25 ; // (   ) Coeficiente de aderência (Tabela 8.3 NBR6118:2014)


    // Abertura de dissura máximo
    switch (V->prop.classeAgressividade)
    {
    case 1 :
        wkMax = 0.4 ; 
        break;
    case 2 :
        wkMax = 0.3 ; 
        break;    
    case 3 :
        wkMax = 0.3 ; 
        break; 
    case 4 :
        wkMax = 0.2 ; 
        break;           
    }


for (int regiao = 0; regiao < V->malha.numRegioes ; regiao++)
{
    // TODO Estabelecendo os pontos limites de uma região
        limiteInicial    = V->malha.raizes [ regiao     ] ; 
        limiteFinal      = V->malha.raizes [ regiao + 1 ] ;

        momentoMaximo     = 0        ;
        secaoCritica      = 0        ;
        bitolaTransversal = 0.0063   ; // !!!!! UTILIZANDO BITOLA TRANSVERSAL 6,3 - desenvolver DETALHAMENTO TRASNVERSAL

        larguraEfetiva = V->geo.largura - 2 * V->geo.cob -2 * bitolaTransversal ;


    // TODO Descobrir as seções em que o momento é máximo
        for (int ponto = limiteInicial ; ponto < limiteFinal; ponto++)
        {
            if (fabs( V->solicit.Md_dec[ponto] ) > momentoMaximo )  // !!!!!!!!!!!!!!!!! UTILIZANDO MOMENTO DECALADO - desenvolver ANÁLISE PARA UTLIZAR MOMENTO FREQUENTE
            {
                momentoMaximo = fabs(V->solicit.Md_dec[ponto]) ; 
                secaoCritica  = ponto                    ; 
            }
            
        }

    // TODO Descobrir a bitola utilizada na seção critica
        if (V->solicit.Md_dec[ secaoCritica ] > 0)
        {
            bitolaLongitudinal =  V->barras.Bt_pos [ secaoCritica ] * 0.001 ;
        }
        else
        {
            bitolaLongitudinal =  V->barras.Bt_neg [ secaoCritica ] * 0.001 ;
        }


    // TODO número de barras, armadura de tracao e compressao na seção crítica
        if (V->solicit.Md_dec[ secaoCritica  ] > 0)
        {
            numBarrasTracao     =  V->barras.N_comp [ secaoCritica ] + V->barras.N_Lmin [ secaoCritica ] ;
            numBarrasCompressao =  V->barras.N_neg  [ secaoCritica ] ;

            armaduraTracao     = numBarrasTracao      * pow ( bitolaLongitudinal ,2 ) * 0.25 * M_PI ;
            armaduraCompressao = numBarrasCompressao  * pow ( V->barras.Bt_neg [ secaoCritica ] * 0.001 , 2 ) * 0.25 * M_PI ;

        }
        else
        {
            numBarrasTracao     =  V->barras.N_neg  [ secaoCritica ] ;
            numBarrasCompressao =  V->barras.N_comp [ secaoCritica ] + V->barras.N_Lmin [ secaoCritica ] ;

            armaduraTracao     = numBarrasTracao      * pow ( bitolaLongitudinal ,2 ) * 0.25 * M_PI ;
            armaduraCompressao = numBarrasCompressao  * pow ( V->barras.Bt_pos [ secaoCritica ] * 0.001 , 2 ) * 0.25 * M_PI ;    
        }



    // TODO Espaçamento para cada seção
        espaçamentoHorizontalMin = fmax(fmax(0.02,bitolaLongitudinal * 0.001), 1.2 * dimensaoAgregado) ;
        
        // Máximo de barras na primeira camada
        maxBarrasCamada          = maxbarras_camada( larguraEfetiva , espaçamentoHorizontalMin , bitolaLongitudinal ) ;

        // Espaçamento entre barras na primeira camada
        espaçamentoHorizontal    = fmax ( espaçamentoHorizontalMin , espacamento_camada ( larguraEfetiva , maxBarrasCamada , bitolaLongitudinal ) ) ;
        espaçamentoVertical      = fmax ( fmax(0.02,bitolaLongitudinal), 0.5 * dimensaoAgregado ) ;

    // TODO Taxa de armadura na seção 
    // ! CONSIDERAR SOMENTE A CAMADA INFERIOR
        taxaArmadura = calc_taxa_armadura ( V->geo.cob, bitolaLongitudinal , bitolaTransversal , espaçamentoHorizontal ) ;

    // TODO Linha neutra e Inercia no estádio 2 
        linhaNeutra2 = linha_neutra_2 ( alphaE , armaduraTracao , armaduraCompressao , V->geo.largura , V->geo.d , V->geo.d2 ) ;
        inercia2     = inercia_2      ( alphaE , armaduraTracao , armaduraCompressao , V->geo.largura , V->geo.d , V->geo.d2 ) ;


    // TODO Calcular a tensão máxima nas BARRAS 
        sigmaS = 0.001 * ( momentoMaximo * fabs( linhaNeutra2 - V->geo.d ) ) / inercia2  ; // Verificando somente a armadura inferior


    // TODO Abertura de fissura
        wk1 = ( bitolaLongitudinal * sigmaS * 3 * sigmaS ) / ( 12.5 * neta1 * V->prop.Es * V->prop.fct_m ) ;

        wk2 = ( ( bitolaLongitudinal * sigmaS ) / ( 12.5 * neta1 * V->prop.Es ) ) * ( ( 4 / taxaArmadura) + 45.0 ) ;


        printf("\n");

        wk  =   fmin( wk1, wk2 ) ;

        if (wk > wkMax)
        {
            saida = false ;
        }
        
    if (CALCULO_ELS_W == 1)
    {
        printf("*****************************************************\n");
        printf("*********************  ELS W  ***********************\n");
        printf("*****************************************************\n");
        printf("\n");
        printf("Seção crítica       [ %d ] = %d             \n " , regiao , secaoCritica             );
        printf("Momento máximo      [ %d ] = %f     (kNm)   \n " , regiao , momentoMaximo            );
        printf("Bitola Longitudinal [ %d ] = %f     ( m )   \n " , regiao , bitolaLongitudinal       );
        printf("NumBarrasTracao     [ %d ] = %d             \n " , regiao , numBarrasTracao          );   
        printf("NumBarrasCompressao [ %d ] = %d             \n " , regiao , numBarrasCompressao      );   
        printf("Max Barras camada   [ %d ] = %d             \n " , regiao , maxBarrasCamada          );   
        printf("Espaçamento max     [ %d ] = %f     ( m )   \n " , regiao , espaçamentoHorizontalMin );
        printf("Espaçamento Horiz   [ %d ] = %f     ( m )   \n " , regiao , espaçamentoHorizontal    );   
        printf("Espaçamento Vert    [ %d ] = %f     ( m )   \n " , regiao , espaçamentoVertical      );   
        printf("Taxa armadura       [ %d ] = %f    (m²/m²)  \n " , regiao , taxaArmadura             ); 
        printf("Armadura Tração     [ %d ] = %f     (m²)    \n " , regiao , armaduraTracao           ); 
        printf("Armadura Compr      [ %d ] = %f     (m²)    \n " , regiao , armaduraCompressao       ); 
        printf("Linha Neutra 2      [ %d ] = %f     (m )    \n " , regiao , linhaNeutra2             ); 
        printf("Inercia 2           [ %d ] = %f      (m4)   \n " , regiao , inercia2                 ); 
        printf("SigmaS              [ %d ] = %f     (MPa)   \n " , regiao , sigmaS                   );        
        printf("V->prop.Es          [ %d ] = %f   (GPa)     \n " , regiao , V->prop.Es               );        
        printf("V->prop.fct_m       [ %d ] = %f     (MPa)   \n " , regiao , V->prop.fct_m            );        
        printf("wk1                 [ %d ] = %0.10f (mm) \n " , regiao , wk1                         ); 
        printf("wk2                 [ %d ] = %0.10f (mm) \n " , regiao , wk2                         ); 
        printf("wk Max              [ %d ] = %0.10f (mm) \n " , regiao , wkMax                       ); 
        printf("\n\n");
    }
          
}
    
    return saida;

}
