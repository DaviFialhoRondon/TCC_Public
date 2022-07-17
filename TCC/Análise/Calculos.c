#include "Analise.h"

void calc_comprimento(FILE *pfile)
{

//LOCAÇÃO DAS ENTRADAS

struct dadosEntradaStruct *ptr = &dadosEntrada;

ptr->L = (float *)malloc(ptr->NB * sizeof(float));


//DECLARAÇÃO DAS VARIÁVEIS FERRAMENTAS

    int i;

//Calculo dos comprimentos das barras

    for (int i = 0; i < ptr->NB; i++)
    {
        ptr->L[i] = fabs(ptr->x[ptr->FIM[i]] - ptr->x[ptr->INI[i]]);
    }
}

void calc_vcar(FILE *pfile)
{

//DECLARAÇÃO DAS VARIÁVEIS FERRAMENTAS

    int i;
    float m1,m2,m3,m4;

////////////////////////////////////////////////////////////////

//LOCAÇÃO DAS ENTRADAS

    struct dadosEntradaStruct *ptr = &dadosEntrada;

    ptr->CARBAR = (float *)malloc(2 * ptr->NB * sizeof(float));
    ptr->VCAR   = (float *)malloc(2 * ptr->NN * sizeof(float));

////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////

//CALCULO DO VETOR DE CARGAS
//Nas entradas será positivo vetores para cima e momentos horários



    for (i = 0; i < 2 * ptr->NB; i++)
    {
        ptr->CARBAR[i] = 0;
    }

    for (i = 0; i < 2 * ptr->NN; i++)
    {
        ptr->VCAR[i] = 0;
    }


    for (i = 0; i < ptr->NB; i++)
    {
        if (fabs(ptr->qyf[i]) >= fabs(ptr->qyi[i]))
        {
            m1 = (1.0/2.0)   * ptr->qyi[i] * ptr->L[i];
            m2 = (1.0/6.0)   * (ptr->qyf[i] - ptr->qyi[i]) * ptr->L[i];
            m3 = (-1.0/20.0) * (ptr->qyf[i] - ptr->qyi[i]) * ptr->L[i];
            m4 = (1.0/30.0) * (ptr->qyf[i] - ptr->qyi[i]) * ptr->L[i];

            ptr->CARBAR[4*i] = m1 + m2 + m3 + m4;                           //carga na esquerda

            m1 = (1.0/12.0) * ptr->qyi[i] * pow(ptr->L[i],2);
            m2 = (1.0/30.0) * (ptr->qyf[i] - ptr->qyi[i]) * pow(ptr->L[i],2);

            ptr->CARBAR[4*i+1] = m1 + m2;                                   //Momento na esquerda

            m1 = (1.0/2.0)   * ptr->qyi[i] * ptr->L[i];
            m2 = (1.0/3.0)   * (ptr->qyf[i] - ptr->qyi[i]) * ptr->L[i];
            m3 = (1.0/20.0)  * (ptr->qyf[i] - ptr->qyi[i]) * ptr->L[i];
            m4 = (-1.0/30.0) * (ptr->qyf[i] - ptr->qyi[i]) * ptr->L[i];

            ptr->CARBAR[4*i+2] = m1 + m2 + m3 + m4;                         //carga na direita

            m1 = (-1.0/12.0) * ptr->qyi[i] * pow(ptr->L[i],2);
            m2 = (-1.0/20.0) * (ptr->qyf[i] - ptr->qyi[i]) * pow(ptr->L[i],2);

            ptr->CARBAR[4*i+3] = m1 + m2;                                   //Momento na direita
        }
        else
        {
            m1 = (1.0/2.0)   * ptr->qyf[i] * ptr->L[i];
            m2 = (1.0/3.0)   * (ptr->qyi[i] - ptr->qyf[i]) * ptr->L[i];
            m3 = (-1.0/30.0) * (ptr->qyi[i] - ptr->qyf[i]) * ptr->L[i];
            m4 = (1.0/20.0) * (ptr->qyi[i] - ptr->qyf[i]) * ptr->L[i];

            ptr->CARBAR[4*i] = m1 + m2 + m3 + m4;                           //carga na esquerda

            m1 = (1.0/12.0) * ptr->qyf[i] * pow(ptr->L[i],2);
            m2 = (1.0/20.0) * (ptr->qyi[i] - ptr->qyf[i]) * pow(ptr->L[i],2);

            ptr->CARBAR[4*i+1] = m1 + m2;                                   //Momento na esquerda

            m1 = (1.0/2.0)   * ptr->qyf[i] * ptr->L[i];
            m2 = (1.0/6.0)   * (ptr->qyi[i] - ptr->qyf[i]) * ptr->L[i];
            m3 = (1.0/30.0)  * (ptr->qyi[i] - ptr->qyf[i]) * ptr->L[i];
            m4 = (-1.0/20.0) * (ptr->qyi[i] - ptr->qyf[i]) * ptr->L[i];

            ptr->CARBAR[4*i+2] = m1 + m2 + m3 + m4;                         //carga na direita

            m1 = (-1.0/12.0) * ptr->qyf[i] * pow(ptr->L[i],2);
            m2 = (-1.0/30.0) * (ptr->qyi[i] - ptr->qyf[i]) * pow(ptr->L[i],2);

            ptr->CARBAR[4*i+3] = m1 + m2;                                   //Momento na direita
            
        }

    }       
for ( i = 0; i < ptr->NB ;i++)
{
    ptr->VCAR[2*ptr->INI[i]  ]   = ptr->VCAR[2 * ptr->INI[i]    ]   + ptr->CARBAR[4* i    ];
    ptr->VCAR[2*ptr->INI[i]+1]   = ptr->VCAR[2 * ptr->INI[i] + 1]   + ptr->CARBAR[4* i + 1];
    ptr->VCAR[2*ptr->FIM[i]  ]   = ptr->VCAR[2 * ptr->FIM[i]    ]   + ptr->CARBAR[4* i + 2];
    ptr->VCAR[2*ptr->FIM[i]+1]   = ptr->VCAR[2 * ptr->FIM[i] + 1]   + ptr->CARBAR[4* i + 3];
}
for ( i = 0; i < 2 * ptr->NN ;i++)
{
    ptr->VCAR[i] = ptr->VCAR[i]   + ptr->CARNO[i];
}
     
    

}

void Determinar_matriz(FILE *pfile)
{

//DECLARAÇÃO DAS VARIÁVEIS FERRAMENTAS

int i;
int j;
int k;
    

////////////////////////////////////////////////////////////////

//LOCAÇÃO DAS ENTRADAS

struct dadosEntradaStruct *ptr = &dadosEntrada;


ptr->S = (float**)malloc((2*ptr->NN) * sizeof(float*)); //MATRIZ DE RIGIDEZ GLOBAL S[2*NN,2*NN]

for (i = 0; i < (2*ptr->NN); i++)
    ptr->S[i] = (float*)malloc((2*ptr->NN) * sizeof(float)); //MATRIZ DE RIGIDEZ GLOBAL S[2*NN,2*NN]


ptr->SM = (float***)malloc((ptr->NB) * sizeof(float**)); //MATRIZ DE RIGIDEZ LOCAL SM[NB,4,4]

for (i = 0; i < (ptr->NB); i++){
    ptr->SM[i] = (float**)malloc((4) * sizeof(float*)); //MATRIZ DE RIGIDEZ LOCAL SM[NB,4,4]

    for (j = 0; j < (4); j++)
    ptr->SM[i][j] = (float*)malloc((4) * sizeof(float)); //MATRIZ DE RIGIDEZ LOCAL SM[NB,4,4] 
}

////////////////////////////////////////////////////////////////

//ATRIBUIÇÃO DAS MATRIZES

for (i = 0; i < (ptr->NB); i++){

//MATRIZ LOCAL

    ptr->SM[i][0][0] =  12.0 * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],3);
    ptr->SM[i][0][1] =   6.0 * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],2);
    ptr->SM[i][0][2] = -12.0 * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],3);   
    ptr->SM[i][0][3] =   6.0 * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],2);     
    ptr->SM[i][1][0] =   6   * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],2);
    ptr->SM[i][1][1] =   4   * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],1);
    ptr->SM[i][1][2] =  -6   * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],2);   
    ptr->SM[i][1][3] =   2   * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],1); 
    ptr->SM[i][2][0] = -12.0 * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],3);
    ptr->SM[i][2][1] =  -6.0 * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],2);
    ptr->SM[i][2][2] =  12.0 * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],3);
    ptr->SM[i][2][3] =  -6.0 * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],2);
    ptr->SM[i][3][0] =   6   * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],2);
    ptr->SM[i][3][1] =   2   * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],1);
    ptr->SM[i][3][2] =  -6   * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],2);
    ptr->SM[i][3][3] =   4   * ptr->E[i]*ptr->In[i] / pow(ptr->L[i],1);

//MATRIZ GLOBAL

    ptr->S[2*ptr->INI[i]    ][2*ptr->INI[i]    ]   =   ptr->S[2*ptr->INI[i]    ][2*ptr->INI[i]    ]   +   ptr->SM[i][0][0];
    ptr->S[2*ptr->INI[i]    ][2*ptr->INI[i] + 1]   =   ptr->S[2*ptr->INI[i]    ][2*ptr->INI[i] + 1]   +   ptr->SM[i][0][1];
    ptr->S[2*ptr->INI[i]    ][2*ptr->FIM[i]    ]   =   ptr->S[2*ptr->INI[i]    ][2*ptr->FIM[i]    ]   +   ptr->SM[i][0][2];
    ptr->S[2*ptr->INI[i]    ][2*ptr->FIM[i] + 1]   =   ptr->S[2*ptr->INI[i]    ][2*ptr->FIM[i] + 1]   +   ptr->SM[i][0][3];
    ptr->S[2*ptr->INI[i] + 1][2*ptr->INI[i]    ]   =   ptr->S[2*ptr->INI[i] + 1][2*ptr->INI[i]    ]   +   ptr->SM[i][1][0];
    ptr->S[2*ptr->INI[i] + 1][2*ptr->INI[i] + 1]   =   ptr->S[2*ptr->INI[i] + 1][2*ptr->INI[i] + 1]   +   ptr->SM[i][1][1];
    ptr->S[2*ptr->INI[i] + 1][2*ptr->FIM[i]    ]   =   ptr->S[2*ptr->INI[i] + 1][2*ptr->FIM[i]    ]   +   ptr->SM[i][1][2];
    ptr->S[2*ptr->INI[i] + 1][2*ptr->FIM[i] + 1]   =   ptr->S[2*ptr->INI[i] + 1][2*ptr->FIM[i] + 1]   +   ptr->SM[i][1][3];
    ptr->S[2*ptr->FIM[i]    ][2*ptr->INI[i]    ]   =   ptr->S[2*ptr->FIM[i]    ][2*ptr->INI[i]    ]   +   ptr->SM[i][2][0];
    ptr->S[2*ptr->FIM[i]    ][2*ptr->INI[i] + 1]   =   ptr->S[2*ptr->FIM[i]    ][2*ptr->INI[i] + 1]   +   ptr->SM[i][2][1];
    ptr->S[2*ptr->FIM[i]    ][2*ptr->FIM[i]    ]   =   ptr->S[2*ptr->FIM[i]    ][2*ptr->FIM[i]    ]   +   ptr->SM[i][2][2];
    ptr->S[2*ptr->FIM[i]    ][2*ptr->FIM[i] + 1]   =   ptr->S[2*ptr->FIM[i]    ][2*ptr->FIM[i] + 1]   +   ptr->SM[i][2][3];
    ptr->S[2*ptr->FIM[i] + 1][2*ptr->INI[i]    ]   =   ptr->S[2*ptr->FIM[i] + 1][2*ptr->INI[i]    ]   +   ptr->SM[i][3][0];
    ptr->S[2*ptr->FIM[i] + 1][2*ptr->INI[i] + 1]   =   ptr->S[2*ptr->FIM[i] + 1][2*ptr->INI[i] + 1]   +   ptr->SM[i][3][1];
    ptr->S[2*ptr->FIM[i] + 1][2*ptr->FIM[i]    ]   =   ptr->S[2*ptr->FIM[i] + 1][2*ptr->FIM[i]    ]   +   ptr->SM[i][3][2];
    ptr->S[2*ptr->FIM[i] + 1][2*ptr->FIM[i] + 1]   =   ptr->S[2*ptr->FIM[i] + 1][2*ptr->FIM[i] + 1]   +   ptr->SM[i][3][3];

}


for (i = 0; i < ptr->NB; i++)
{
    for (j = 0; j < 4; j++)
    {
        for (k = 0; k < 4; k++)
        {
            printf("SM[%d][%d][%d] = %f\n", i,j,k, ptr->SM[i][j][k]);
        }
        
        
    }
    printf("\n");
    
    
}

for (i = 0; i < 2*ptr->NN; i++)
{
    j = 0;
    printf("[ %.2f ]    [ %.2f ]    [ %.2f ]    [ %.2f ]    [ %.2f ]    [ %.2f ]    [ %.2f ]    [ %.2f ]    [ %.2f ]    [ %.2f ]  \n", ptr->S[i][4*j],ptr->S[i][4*j+1],ptr->S[i][4*j+2],ptr->S[i][4*j+3],ptr->S[i][4*j+4],ptr->S[i][4*j+5],ptr->S[i][4*j+6],ptr->S[i][4*j+7],ptr->S[i][4*j+8],ptr->S[i][4*j+9]);      
      
}





}