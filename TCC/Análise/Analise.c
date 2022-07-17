#include "Analise.h"

int main()
{
    FILE *pfile;

    pfile = fopen("Entradas.txt", "r");

    if (pfile == NULL)
    {
        printf("ERROR");
    }

    // Leitura das entradas


    struct dadosEntradaStruct *ptr = &dadosEntrada;

    Entra_dados(pfile); //função Entrada de dados (Entra_dados)

    calc_comprimento(pfile); //Função calcular comprimento de barras (Calculos)

    calc_vcar(pfile); //Função calcular vetor carregamento (Calculos)

    Determinar_matriz(pfile); //Função determina matriz de rigidez (Calculos)

    /*----------------------------------------------------------------*/

    
    // Saídas
    printf("\n");
    printf("VALORES GLOBAIS\n\n");
    printf("NN = %d\n", ptr->NN); // ptr->NN
    printf("NB = %d\n", ptr->NB); // ptr->NN'


    printf("COORDENADAS DOS NOS\n\n");
    for (int i = 0; i < ptr->NN; i++) // coordenadas
    {
        printf("x[%d] = %f\n", i, ptr->x[i]);
    }
    printf("\n");

    printf("PROPRIEDADE DAS BARRAS\n\n");
    for (int i = 0; i < ptr->NB; i++) // propriedades
     {
        printf("BARRA %d\n", i);
        printf("INI[%d] = %d\n", i, ptr->INI[i]);
        printf("FIM[%d] = %d\n", i, ptr->FIM[i]);
        printf("E[%d] = %.2f GPa\n", i, ptr->E[i]);
        printf("I[%d] = %.4f m4\n", i, ptr->In[i]);
        printf("\n");
    }
    printf("\n");

    printf("VINCULOS\n\n");
    for (int i = 0; i < ptr->NN; i++) // Vinculos
    {
        if (((ptr->VINC[2 * i]) + ptr->VINC[2 * i + 1]) == 0)
        {
            printf("NÓ %d  -  Livre (%d,%d)\n", i, ptr->VINC[2 * i], ptr->VINC[2 * i + 1]);
        }
        if (((ptr->VINC[2 * i]) + ptr->VINC[2 * i + 1]) == 1)
        {
            printf("NÓ %d  -  Apoio (%d,%d)\n", i, ptr->VINC[2 * i], ptr->VINC[2 * i + 1]);
        }
        if (((ptr->VINC[2 * i]) + ptr->VINC[2 * i + 1]) == 2)
        {
            printf("NÓ %d  -  Engaste (%d,%d)\n", i, ptr->VINC[2 * i], ptr->VINC[2 * i + 1]);
        }
    }

    printf("\n");

    printf("CARGAS NODAIS\n\n");
    for (int i = 0; i < ptr->NN; i++)
    {
        if (ptr->CARNO[2 * i] + ptr->CARNO[2 * i + 1] != 0)
        {
            printf("NÓ %d\n", i);
            printf("F = %.3f kN\n", ptr->CARNO[2 * i]);
            printf("M = %.3f kNm\n\n", ptr->CARNO[2 * i + 1]);
        }
    }

    printf("\n");

    printf("CARGAS NAS BARRAS\n\n");
    for (int i = 0; i < ptr->NB; i++)
    {
        if (ptr->qyi[i] + ptr->qyf[i] != 0)
        {
            printf("BARRA %d\n", i);
            printf("ptr->qyi = %.3f kN\n", ptr->qyi[i]);
            printf("ptr->qyf = %.3f kNm\n\n", ptr->qyf[i]);
        }
    }

    printf("COMPRIMENTO DS BARRAS\n\n");
    for (int i = 0; i < ptr->NB; i++)
    {
        printf("L [%d] = %f\n", i, ptr->L[i]);
    }

       printf("\nVETOR CARGA BARRAS\n\n");
    for (int i = 0; i < ptr->NN; i++)
    {
        printf("Força   [%d] = %f\n",i , ptr->VCAR[2*i]);
        printf("Momento [%d] = %f\n\n",i , ptr->VCAR[2*i+1]);
    }



    /*for (i = 0; i < ptr->NB; i++)
    {
        printf("%.3f\n", ptr->qyi[i]);
    }
    */








    free(ptr->x);
    free(ptr->VINC);
    free(ptr->CARNO);
    free(ptr->INI);
    free(ptr->FIM);
    free(ptr->In);
    free(ptr->E);
    free(ptr->qyi);
    free(ptr->qyf);
    free(ptr->CARBAR);
    free(ptr->L);
    free(ptr->VCAR);
    return 0;
}