#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Detalhamento.h"




void Entrada(struct viga *V)
{

    /*---Malha---*/

    V->malha.N = 201;  // Numero de pontos na malha

    /*Alocação de memória*/

    V->solicit.Md_dec = malloc(V->malha.N * sizeof(double));
    V->solicit.Vd     = malloc(V->malha.N * sizeof(double));
    V->arm.A_comp     = malloc(V->malha.N * sizeof(double));
    V->arm.A_neg      = malloc(V->malha.N * sizeof(double));
    V->arm.A_const    = malloc(V->malha.N * sizeof(double));
    V->arm.Asw        = malloc(V->malha.N * sizeof(double));

    V->barras.Bt_pos   = malloc(V->malha.N * sizeof(float));
    V->barras.Bt_const = malloc(V->malha.N * sizeof(float));
    V->barras.Bt_neg   = malloc(V->malha.N * sizeof(float));
    
    V->barras.N_comp  = malloc(V->malha.N * sizeof(int));
    V->barras.N_const = malloc(V->malha.N * sizeof(int));
    V->barras.N_Lmin  = malloc(V->malha.N * sizeof(int));
    V->barras.N_neg   = malloc(V->malha.N * sizeof(int));

    /*Solicitações */

    double Mdec [] =
{
-59.2 ,
-56.2 ,
-53.3 ,
-50.5 ,
-47.6 ,
-44.9 ,
-42.2 ,
-39.5 ,
-36.9 ,
-34.3 ,
-31.8 ,
-29.3 ,
-26.9 ,
-24.6 ,
-22.2 ,
-20.0 ,
-17.8 ,
-15.6 ,
-13.5 ,
-11.4 ,
-9.4 ,
-7.4 ,
-5.5 ,
-3.7 ,
-1.8 ,
-0.1 ,
1.6 ,
3.3 ,
4.9 ,
6.5 ,
8.0 ,
9.5 ,
10.9 ,
12.3 ,
13.6 ,
14.8 ,
16.1 ,
17.2 ,
18.3 ,
19.4 ,
20.4 ,
21.4 ,
22.3 ,
23.2 ,
24.0 ,
24.7 ,
25.5 ,
26.1 ,
26.7 ,
27.3 ,
27.8 ,
28.3 ,
28.7 ,
29.1 ,
29.4 ,
29.6 ,
29.9 ,
30.0 ,
30.1 ,
30.2 ,
30.2 ,
30.2 ,
30.1 ,
30.0 ,
29.8 ,
29.6 ,
29.3 ,
28.9 ,
28.6 ,
28.1 ,
27.6 ,
27.1 ,
26.5 ,
25.9 ,
25.2 ,
24.5 ,
23.7 ,
22.8 ,
22.0 ,
21.0 ,
20.0 ,
19.0 ,
17.9 ,
16.8 ,
15.6 ,
14.4 ,
13.1 ,
11.7 ,
10.4 ,
8.9 ,
7.4 ,
5.9 ,
4.3 ,
2.7 ,
1.0 ,
-0.7 ,
-2.5 ,
-4.3 ,
-6.2 ,
-8.2 ,
-10.1 ,
-13.2 ,
-16.3 ,
-19.4 ,
-22.6 ,
-25.8 ,
-29.1 ,
-32.4 ,
-35.8 ,
-39.3 ,
-42.7 ,
-40.6 ,
-38.5 ,
-36.5 ,
-34.5 ,
-32.5 ,
-30.6 ,
-28.8 ,
-27.0 ,
-25.2 ,
-23.5 ,
-21.9 ,
-20.3 ,
-18.8 ,
-17.3 ,
-15.8 ,
-14.4 ,
-13.1 ,
-11.8 ,
-10.5 ,
-9.3 ,
-8.2 ,
-7.1 ,
-6.1 ,
-5.1 ,
-4.1 ,
-3.2 ,
-2.4 ,
-1.6 ,
-0.8 ,
-0.1 ,
0.5 ,
1.1 ,
1.6 ,
2.1 ,
2.6 ,
3.0 ,
3.3 ,
3.6 ,
3.9 ,
4.1 ,
4.2 ,
4.3 ,
4.3 ,
4.3 ,
4.3 ,
4.2 ,
4.0 ,
3.8 ,
3.6 ,
3.3 ,
2.9 ,
2.5 ,
2.0 ,
1.5 ,
1.0 ,
0.4 ,
-0.3 ,
-1.0 ,
-1.7 ,
-2.5 ,
-3.4 ,
-4.3 ,
-5.2 ,
-6.3 ,
-7.3 ,
-8.4 ,
-9.6 ,
-10.8 ,
-12.0 ,
-13.3 ,
-12.1 ,
-10.9 ,
-9.8 ,
-8.7 ,
-7.7 ,
-6.8 ,
-5.9 ,
-5.0 ,
-4.3 ,
-3.5 ,
-2.9 ,
-2.3 ,
-1.8 ,
-1.3 ,
-0.9 ,
-0.6 ,
-0.3 ,
-0.1 ,
-0.0 ,
0.0 };


    double Vd   [] = 
{
59.8  ,
58.8  ,
57.8  ,
56.8  ,
55.8  ,
54.8  ,
53.8  ,
52.8  ,
51.8  ,
50.8  ,
49.8  ,
48.8  ,
47.8  ,
46.8  ,
45.8  ,
44.8  ,
43.8  ,
42.8  ,
41.8  ,
40.8  ,
39.8  ,
38.8  ,
37.8  ,
36.8  ,
35.8  ,
34.8  ,
33.8  ,
32.8  ,
31.8  ,
30.8  ,
29.8  ,
28.8  ,
27.8  ,
26.8  ,
25.8  ,
24.8  ,
23.8  ,
22.8  ,
21.8  ,
20.8  ,
19.8  ,
18.8  ,
17.8  ,
16.8  ,
15.8  ,
14.8  ,
13.8  ,
12.8  ,
11.8  ,
10.8  ,
9.8  ,
8.8  ,
7.8  ,
6.8  ,
5.8  ,
4.8  ,
3.8  ,
2.8  ,
1.8  ,
0.8  ,
-0.2  ,
-1.2  ,
-2.2  ,
-3.2  ,
-4.2  ,
-5.2  ,
-6.2  ,
-7.2  ,
-8.2  ,
-9.2  ,
-10.2 ,
-11.2 ,
-12.2 ,
-13.2 ,
-14.2 ,
-15.2 ,
-16.2 ,
-17.2 ,
-18.2 ,
-19.2 ,
-20.2 ,
-21.2 ,
-22.2 ,
-23.2 ,
-24.2 ,
-25.2 ,
-26.2 ,
-27.2 ,
-28.2 ,
-29.2 ,
-30.2 ,
-31.2 ,
-32.2 ,
-33.2 ,
-34.2 ,
-35.2 ,
-36.2 ,
-37.2 ,
-38.2 ,
-39.2 ,
-60.2 ,
-61.2 ,
-62.2 ,
-63.2 ,
-64.2 ,
-65.2 ,
-66.2 ,
-67.2 ,
-68.2 ,
-69.2 ,
-70.2 ,
42.4 ,
41.4 ,
40.4 ,
39.4 ,
38.4 ,
37.4 ,
36.4 ,
35.4 ,
34.4 ,
33.4 ,
32.4 ,
31.4 ,
30.4 ,
29.4 ,
28.4 ,
27.4 ,
26.4 ,
25.4 ,
24.4 ,
23.4 ,
22.4 ,
21.4 ,
20.4 ,
19.4 ,
18.4 ,
17.4 ,
16.4 ,
15.4 ,
14.4 ,
13.4 ,
12.4 ,
11.4 ,
10.4 ,
9.4 ,
8.4 ,
7.4 ,
6.4 ,
5.4 ,
4.4 ,
3.4 ,
2.4 ,
1.4 ,
0.4 ,
-0.6 ,
-1.6 ,
-2.6 ,
-3.6 ,
-4.6 ,
-5.6 ,
-6.6 ,
-7.6 ,
-8.6 ,
-9.6 ,
-10.6 ,
-11.6 ,
-12.6 ,
-13.6 ,
-14.6 ,
-15.6 ,
-16.6 ,
-17.6 ,
-18.6 ,
-19.6 ,
-20.6 ,
-21.6 ,
-22.6 ,
-23.6 ,
-24.6 ,
-25.6 ,
-26.6 ,
24.0 ,
22.9 ,
21.9 ,
20.8 ,
19.7 ,
18.5 ,
17.4 ,
16.2 ,
15.0 ,
13.7 ,
12.5 ,
11.2 ,
9.9 ,
8.5 ,
7.2 ,
5.8 ,
4.4 ,
2.9 ,
1.5 ,
-0.0
};

    for (int i = 0; i < V->malha.N; i++)
    {
        V->solicit.Md_dec[i] = Mdec[i];
    }

    for (int i = 0; i < V->malha.N; i++)
    {
        V->solicit.Vd[i] = Vd[i];
    }

    /*geometria */

    V->geo.altura      = 0.55  ; // altura (m)
    V->geo.largura     = 0.15  ; // largura(m)
    V->geo.comprimento = 10    ; // comprimento(m)
    V->geo.cob         = 0.03 ; // cobrimento (m)

    /*propriedades */

    V->prop.Ec  = 25  ; // módulo de elasticidade do concreto (GPa)
    V->prop.Es  = 210 ; // módulo de elasticidade do aço (GPa)
    V->prop.fck = 30  ; // fck

    V->prop.classeAgressividade = 3 ; // Classe de agressividade
    

}

void calculo_propriedades(struct viga *V)
{

    // Vigas - definições gerais
    V->prop.Ic = V->geo.largura * pow(V->geo.altura,3)/12.0 ;  // Momento de inércia


    V->prop.fyd = 500.0 / 1.15                        ; // Resistência de calculo das barras longitudinais do aço CA-50 (MPa)
    V->prop.fywd = 500.0 / 1.15                       ; // Resistência de calculo das barras transversais do aço CA-50 (MPa)

    V->geo.d = 0.9 * V->geo.altura                    ; // altura útil para armadura de tração(m)
    V->geo.d2 = 0.055                                 ; // altura util para armadura de compressão (m)
    V->prop.fctd = 0.15 * pow(V->prop.fck, 0.6666667) ; // Resistência à tração do concreto (MPa)

    // Fct_m - Resistência a tração média do concreto (MPa)
    if (V->prop.fck <= 50)
    {
        V->prop.fct_m = 0.3 * pow(V->prop.fck, (2.0 / 3.0));
    }
    else
    {
        V->prop.fct_m = 2.12 * log(1 + 0.11 * V->prop.fck);
    }

    V->prop.fctk_sup = 1.3 * V->prop.fct_m; // Resistência à tração superior (MPa)
    V->prop.fctk_inf = 0.7 * V->prop.fct_m; // Resistência à tração inferior (MPa)

}