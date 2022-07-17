#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Detalhamento.h"

void div_reg(struct viga *V)
{

    int raizes [V->malha.N+1] ; // Vetor com as raízes do diagrama de momento decalado
    int numRaizes = 0         ; // Número de raízes totais do diagrama de momento decalado

    raizes[numRaizes++] = 0 ;
    
    for (int ponto = 1; ponto < (V->malha.N-1); ponto++)
    {
        double momentoAtual = V->solicit.Md_dec [ponto    ] ;
        double momentoProx  = V->solicit.Md_dec [ponto + 1] ;
       
        if ( (momentoAtual == 0 && momentoProx !=0) || ( momentoAtual * momentoProx < 0.0 )) 
        {
            raizes[numRaizes++] = ponto ;
        }
     }
    
    raizes[numRaizes++] = V->malha.N-1;

    V->malha.raizes     = malloc(numRaizes * sizeof(int)) ; // Alocação da memória necessária dada a quantidade de raízes calculadas
    V->malha.numRegioes = numRaizes - 1                   ; // Número de regiões do diagrama de momento decalado

for (int i = 0; i < numRaizes ; i++)
{
    V->malha.raizes[i] = raizes[i];
}

    if (DETALHAR_DIVISAO_REGIOES == 1)
    {
        printf("--------------------------------------------------\n");
        printf("-----------------DIVISÃO_REGIÕES------------------\n");
        printf("Número de Regiões : %d\n\n",V->malha.numRegioes);

        for (int i = 0; i < V->malha.numRegioes ; i++)    
        printf("REGIÃO: %d - Limite [ %d , %d ] \n", i , V->malha.raizes [i], V->malha.raizes [i+1]);      

        printf("--------------------------------------------------\n\n");
    }
}