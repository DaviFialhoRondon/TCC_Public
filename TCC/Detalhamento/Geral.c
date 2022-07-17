#include "Detalhamento.h" 
#include "Definition.h" 

/*Funções externas*/
double dimensaoAgregado = 0.019 ; // (m) Dimensão máxima agregado graúdo

float Bitolas_padrão[] = { 5.0 , 6.3 , 8.0 , 10.0 , 12.5 , 16.0 , 20.0 , 25.0 , 32.0 };

/** 
 * ! Notas
 * * Passar a estrutura viga como ponteiro
 * * Verificar dimensões do agregado
 * * Verificar o pré-dimensionamento da altura d2
 * * Rever cálculo do momento de inercia para estádio 2 (ELS-W e ELS-DEF)
 * * Recalcular a expressão da abertura de fissura (só é necessário verificar a camada inferior)
 * * Para as seções máximas na abertura de fissura, verificar se o num de raizes para combinação frequente será o mesmo
 * ! VERIFICAR LINHA 82 DETALHAMENTO - PONTEIRO ESTA CORRETO?
 * ! CORRIGIR CHUTE BITOLA TRASNVERSAL EM ELS-W
 * ! Adotar alphaE como 15  
 * 
 * 
 * ! Premissas de projeto:
 * * Vigas em flexão simples 
 * * Seções retangulares
 * * É necessário a ultização de uma discretização da viga tão menor possivel pois as raízes das funções das solicitações será aproximada para os pontos da malha
*/

int main()
{

    /*--------------------ENTRADA--------------------*/

    struct viga V1;

    Entrada ( &V1 ) ;

    calculo_propriedades ( &V1 ) ;

    /*------------------ANÁLISE------------------*/



    /*-------------DETALHAMENTO-------------*/


    arm_long_min   ( &V1 ) ; // Armaduras mínima flexão
    arm_transv_min ( &V1 ) ; // Armaduras mínima cortante

    div_reg ( &V1 ) ;

    dimensionar_armadura ( &V1 ) ;

    bool verificaçaoELSW ;
    bool verificaçaoSeçao ;
/*
    int armMin  ;
    int armComp ;
    int armNeg  ;
    int regiao  ;

    int numReg = V1.malha.numRegioes ;

    int barrasRegiao[3][numReg];

    for (regiao = 0; regiao < numReg; regiao++)
        {
            for ( armMin = 0; armMin <= 3; armMin++)
            {
                for ( armComp = 1; armComp <= 8; armComp++)
                {
                    for ( armNeg = 1; armNeg <= 8; armNeg++)
                    {
                        barrasRegiao[0][regiao] = armMin;
                        barrasRegiao[1][regiao] = armComp;
                        barrasRegiao[2][regiao] = armNeg;

                        // Calcular barras cm o barrasRegiao

                        //Verificações
            




                        //printf(" ELS_W = %i  SEÇÃO = %i \n" , verificaçaoELSW , verificaçaoSeçao);

                    }
                }
            }
        }
*/
    calcular_barras( &V1 );

    verificaçaoELSW  = verificar_ELS_W( &V1 );

    verificaçaoSeçao = verificar_Seçao( &V1 );

    //comprimento_barras( &V1 );

    printf("verificaçaoELSW = %d\n",verificaçaoELSW);
    printf("verificaçaoSeçao = %d\n",verificaçaoSeçao);






    /*---------------------SAÍDAS---------------------*/


printf("FIM\n") ;

    //*------------------FREE----------------------*/

    free( V1.solicit.Md_dec  );
    free( V1.arm.A_comp      );
    free( V1.arm.A_neg       );
    free( V1.arm.A_const     );
    free( V1.barras.Bt_pos   );
    free( V1.barras.Bt_const );
    free( V1.barras.Bt_neg   );
    free( V1.barras.N_comp   );
    free( V1.barras.N_const  );
    free( V1.barras.N_Lmin   );
    free( V1.barras.N_neg    );
    free( V1.malha.raizes    );

    int a = 0;
    scanf("%d", &a);
    return 0;
}