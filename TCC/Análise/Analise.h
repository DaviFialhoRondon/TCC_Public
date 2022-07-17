#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct dadosEntradaStruct {

   int   NN         ; // número de nós G
   int   NB         ; // número de barras G

   float *x         ; // Vetor coordenadas dos nós [NN]
   int   NNVINC     ; // Número de vinculos 
   int   *VINC      ; // Vetor vínculos [NN]

   float *L         ; // Vetor compriento das barras [NB]

   int   NNCARNO    ; // Número de cargas nodais
   float *CARNO     ; // Vetor cargas nodais [2*NN]
   float *qyi       ; // Vetor carga início da barra [NB]
   float *qyf       ; // Vetor carga final da barra [NB]
   int   NNCARBAR   ; // Número de barras com carregamento
   float *CARBAR    ; // Vetor cargas nas barras [2*NB]
   float *VCAR      ; // Vetor carregamento geral [2*NN]
   
   int   *INI       ;  // Vetor nó de inicio da barra [NB]
   int   *FIM       ;  // Vetor nó de fim da barra [NB]
   float *In        ;  // Vetor inércia da barra [NB]
   float *E         ;  // Vetor módulo de elasticidade da barra [NB]
  
   float ***SM      ;  // Ficheiro de rigidez das barras [NB,4,4]
   float **S        ;  // Matriz de rigidez [2*NN,2*NN] 
} ;

extern struct dadosEntradaStruct dadosEntrada ;

void Entra_dados(FILE * pfile) ;
void calc_comprimento(FILE *pfile);
void calc_vcar(FILE *pfile);
void Determinar_matriz(FILE *pfile);
