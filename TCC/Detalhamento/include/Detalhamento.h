#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Struct_det.h"

#define CALCULO_ARMADURAS_LONG              1
#define CALCULO_ARMADURAS_TRANS             0
#define DETALHAR_DIVISAO_REGIOES            1
#define DETALHAR_SEÇÕES_ARMADURAS           1
#define CALCULO_ELS_W                       0
#define CALCULO_SEÇOES                      0


double * arm_long        (double MomentoEntrada , struct viga *V) ;
void     arm_long_min    (struct viga *V                        ) ;
double * calc_arm_transv (double Vcalc , struct viga *V         ) ;
void     arm_transv_min  (struct viga *V                        ) ;

void    comprimento_barras ( struct viga * structViga   ) ;
void    div_reg            (struct viga *V              ) ;
void    dimensionar_armadura(struct viga *V             ) ;
void    calcular_barras     (struct viga *V             ) ;
bool    verificar_ELS_W     (struct viga *V             ) ;
bool    verificar_Seçao     (struct viga *V             ) ;

void    Entrada              (struct viga *V) ;
void    calculo_propriedades (struct viga *V) ;

double elemento_max          (double array[], int arraySize) ;
double linha_neutra_2        (double alphaE , double armaduraTracao , double armaduraCompressao , double largura , double alturaTracao , double alturaCompressao ) ;
double inercia_2             ( double alphaE , double armaduraTracao , double armaduraCompressao , double largura , double alturaTracao , double alturaCompressao     ) ;
int    maxbarras_camada      (double larguraEfetiva , double espacamentoHorizontalmáximo , double bitola) ;
double espacamento_camada    (double larguraEfetiva , int numeroBarrasCamada , double bitola) ;
double calc_taxa_armadura    (double cobrimento , float bitolaLongitudinal , float bitolaTransversal , double espacamentoHorizontal ) ;
double comprimento_decalagem (double alturaUtil , double largura , double fctd , double cortanteMaximo ) ;
double ancoragem_necessaria  ( bool gancho , double momento , double bitola  , double fctd , double fyd , double AsCalc , double AsEf ) ;

#endif