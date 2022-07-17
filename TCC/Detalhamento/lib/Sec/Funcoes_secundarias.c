#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Detalhamento.h"

// Achar elemento máximo de um array int
double elemento_max(double array[], int arraySize)
{

    int Max      = 0 ;
    int valorMax = 0 ;

    for (int elemento = 0; elemento < arraySize; elemento++)
    {
        if (array[elemento]> valorMax)
        {
            valorMax = array[elemento];
            Max      = elemento;
        }
    }
    return Max;
}

// Calcular a linha Neutra de uma seção no estádio II
double linha_neutra_2(double alphaE , double armaduraTracao , double armaduraCompressao , double largura , double alturaTracao , double alturaCompressao )
{

    double x     ; // (m) Linha neutra no estádio 2
    double A , B ; //     Parâmetros para cálculo

    double alphaE2 = alphaE - 1 ; // Parâmetro para calculo

    A = ( alphaE * armaduraTracao + alphaE2 * armaduraCompressao ) / largura ;

    B = 2 * ( alphaE * armaduraTracao * alturaTracao + alphaE2 * armaduraCompressao * alturaCompressao ) / largura ;

    x = - A + sqrt( pow(A,2) + B ) ;

    return x ;
}

// Calcular a Inércia de uma seção no estádio II
double inercia_2( double alphaE , double armaduraTracao , double armaduraCompressao , double largura , double alturaTracao , double alturaCompressao )
{

    double x ; // (m ) Linha neutra no estádio 2
    double I ; // (m4) Inercia no estágio 2
    double A ; //      Parâmetros para cálculo
    double B ; //      Parâmetros para cálculo
    double C ; //      Parâmetros para cálculo

    double alphaE2 = alphaE - 1 ; // Parâmetro para calculo

    x = linha_neutra_2( alphaE , armaduraTracao , armaduraCompressao , largura , alturaTracao , alturaCompressao ) ;

    A = ( largura * pow( x , 3 ) ) / 3.0 ;

    B = alphaE * armaduraTracao * pow( (x - alturaTracao) , 2 ) ;

    C = alphaE2 * armaduraCompressao * pow( (x - alturaCompressao) , 2 ) ;

    I = A + B + C ;

    return I ;
}

// Calcular o número máximo de barras para primeira camada
int maxbarras_camada (double larguraEfetiva , double espacamentoHorizontalmáximo , double bitola)
{
    int numeroBarras;

    numeroBarras = floor( (larguraEfetiva + espacamentoHorizontalmáximo) / (bitola + espacamentoHorizontalmáximo) ) ;

    return numeroBarras;
}

// Calcular o espaçamento dado um número de barras na camada
double espacamento_camada (double larguraEfetiva , int numeroBarrasCamada , double bitola)
{
    double espacamento;

    espacamento = ( larguraEfetiva - (numeroBarrasCamada * bitola) ) / ( numeroBarrasCamada - 1 ) ;

    return espacamento;
}

// Calcular a menor taxa de armadura nos tirante de concreto armado
double calc_taxa_armadura ( double cobrimento , float bitolaLongitudinal , float bitolaTransversal , double espacamentoHorizontal )
{

    double areaCriticaBordas    ; // (  m² ) Área critica do tirante posicionado nas bordas da seção
    double areaCriticaCentro    ; // (  m² ) Área critica do tirante posicionado no centro da seção
    double taxaArmadura         ; // (m²/m²) Área de armadura por área de tirante

    double padrao = 7.5 * bitolaLongitudinal ;

    double b1 ; // Parâmetro para cálculo das áreas dos tirantes de concreto
    double b2 ; // Parâmetro para cálculo das áreas dos tirantes de concreto
    double h1 ; // Parâmetro para cálculo das áreas dos tirantes de concreto
    double h2 ; // Parâmetro para cálculo das áreas dos tirantes de concreto 

//* Utilizando somente a camada inferior

// Área crítica nas bordas
    b1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    b2 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    h1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    h2 = padrao ;

    areaCriticaBordas = (b1 + b2) * (h1 + h2) ;

    // Área crítica no centro
    b1 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    b2 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    h1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    h2 = padrao ;

    areaCriticaCentro = (b1 + b2) * (h1 + h2) ;

    taxaArmadura      = ( M_PI * 0.25 * pow( bitolaLongitudinal , 2 ) ) / fmax( areaCriticaBordas , areaCriticaCentro ) ;


/*if (maxBarrasPrimeiraCamada >= numeroBarras) //Caso 1 - Somente uma camada
{
    // Área crítica nas bordas
    b1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    b2 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    h1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    h2 = padrao ;

    areaCriticaBordas = (b1 + b2) * (h1 + h2) ;

    // Área crítica no centro
    b1 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    b2 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    h1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    h2 = padrao ;

    areaCriticaCentro = (b1 + b2) * (h1 + h2) ;

    taxaArmadura      = ( M_PI * 0.25 * pow( bitolaLongitudinal , 2 ) ) / fmax( areaCriticaBordas , areaCriticaCentro ) ;

}

else if (numeroBarras - maxBarrasPrimeiraCamada <= 2 ) //Caso 2 - duas camadas
{
    // Área crítica nas bordas
    b1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    b2 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    h1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    h2 = fmin( 0.5 * espacamentoVertical + 0.5 * bitolaLongitudinal , padrao ) ;

    areaCriticaBordas = (b1 + b2) * (h1 + h2) ;

    // Área crítica no centro
    b1 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    b2 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    h1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    h2 = fmin( 0.5 * espacamentoVertical + 0.5 * bitolaLongitudinal , padrao ) ;

    areaCriticaCentro = (b1 + b2) * (h1 + h2) ;

    // Área crítica superior
    b1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    b2 = fmin( 0.5 * larguraEfetiva - 0.5 * bitolaLongitudinal, padrao )            ; // considerando o caso de que a distância padrão seja maior que metade da largura efetiva (seções pequenas com grandes bitolas)
    h1 = fmin( 0.5 * espacamentoVertical + 0.5 * bitolaLongitudinal , padrao )      ;
    h2 = padrao ;

    areaCriticaSuperior1 = (b1 + b2) * (h1 + h2) ;

    taxaArmadura = ( M_PI * 0.25 * pow( bitolaLongitudinal , 2 ) ) / fmax( fmax( areaCriticaBordas , areaCriticaCentro ) , areaCriticaSuperior1 ) ;
}

else //Caso 3 - Mais de duas camadas
{
    // Área crítica nas bordas
    b1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    b2 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    h1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    h2 = fmin( 0.5 * espacamentoVertical + 0.5 * bitolaLongitudinal , padrao ) ;

    areaCriticaBordas = (b1 + b2) * (h1 + h2) ;

    // Área crítica no centro
    b1 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    b2 = fmin( 0.5 * espacamentoHorizontal + 0.5 * bitolaLongitudinal , padrao ) ;
    h1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    h2 = fmin( 0.5 * espacamentoVertical + 0.5 * bitolaLongitudinal , padrao ) ;

    areaCriticaCentro = (b1 + b2) * (h1 + h2) ;

    // Área crítica superior intermediária
    b1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    b2 = fmin( 0.5 * larguraEfetiva - 0.5 * bitolaLongitudinal, padrao )            ; // considerando o caso de que a distância padrão seja maior que metade da largura efetiva (seções pequenas com grandes bitolas)
    h1 = fmin( 0.5 * espacamentoVertical + 0.5 * bitolaLongitudinal , padrao )      ;
    h2 = fmin( 0.5 * espacamentoVertical + 0.5 * bitolaLongitudinal , padrao )      ;

    areaCriticaSuperior1 = (b1 + b2) * (h1 + h2) ;

    // Área crítica superior final
    b1 = fmin( 0.5 * bitolaLongitudinal + bitolaTransversal + cobrimento , padrao ) ;
    b2 = fmin( 0.5 * larguraEfetiva - 0.5 * bitolaLongitudinal, padrao )            ; // considerando o caso de que a distância padrão seja maior que metade da largura efetiva (seções pequenas com grandes bitolas)
    h1 = fmin( 0.5 * espacamentoVertical + 0.5 * bitolaLongitudinal , padrao )      ;
    h2 = padrao ;

    areaCriticaSuperior2 = (b1 + b2) * (h1 + h2) ;

    taxaArmadura = ( M_PI * 0.25 * pow( bitolaLongitudinal , 2 ) ) / fmax ( fmax ( fmax( areaCriticaBordas , areaCriticaCentro ) , areaCriticaSuperior1 ) , areaCriticaSuperior2 ) ;   
}
*/

    return taxaArmadura ;
}

// Calcular o comprimento de decalagem
double comprimento_decalagem (double alturaUtil , double largura , double fctd , double cortanteMaximo )
{
    double teta      ; // (rad) Ângulo da biela de concreto 
    double decalagem ; // ( m ) Comprimento de decalagem
    double Vc        ; // (kN ) Força resistente do concreto

    teta = M_PI / 4 ;  

    Vc = 0.6 * (fctd * pow(10, 3)) * largura * alturaUtil ;

    decalagem = ( alturaUtil * ( cortanteMaximo ) / ( 2 * ( cortanteMaximo - Vc ) ) ) * ( ( 1 + 1 / tan( teta ) ) - 1 / tan( teta ) ) ;

    if ( decalagem >= alturaUtil )
    {
        decalagem = alturaUtil ;
    }

    return decalagem ;
}

// Calcular a ancoragem necessária
double ancoragem_necessaria ( bool gancho , double momento , double bitola  , double fctd , double fyd , double AsCalc , double AsEf )
{

    double n1    ; // (   ) Influência da superfície das barras na aderência
    double n2    ; // (   ) Influência da região das barras na aderência
    double n3    ; // (   ) Influência Diâmetro das barras na aderência
    double fbd   ; // (MPa) Resistencia de aderência de cálculo
    double lb    ; // ( m ) Comprimento básico de aderência
    double lbMin ; // ( m ) Comprimento mínimo de aderência
    double lbNec ; // ( m ) Comprimento necessário de aderência
    double a1    ; // ( m ) Coeficiente pela presença de gancho
    
////////////////////////////////////////////////////////////////////////////

// - Cálculo da resistencia de aderência (fbd)

    n1 = 2.25 ; // barras nervuradas
    n3 = 1.0  ; // Barras menores que 32mm

    if (momento < 0)
    {
        n2 = 0.7 ;
    }
    else
    {
        n2 = 1.0 ;
    }
    
    fbd = n1 * n2 * n3 * fctd ;

// - Cálculo da ancoragem básica

    lb = fmax ( ( bitola / 4 ) * ( fyd / fbd ) , ( 25 * bitola ) ) ;

// - Cálculo da ancoragem mínima

    lbMin = fmax ( fmax ( 0.3 * lb , 10 * bitola ) , 0.1 ) ;

// - Cálculo da ancoragem necessária

    if (gancho) 
    {
        a1 = 0.7 ;
    }
    else
    {
        a1 = 1.0 ;
    }

    lbNec = fmax ( a1 * lb * ( AsCalc / AsEf ) , lbMin ) ;

    return lbNec ;

}