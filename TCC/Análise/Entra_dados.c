#include "Analise.h"

struct dadosEntradaStruct dadosEntrada;

void Entra_dados(FILE *pfile)
{
    /*-------------VALORES GLOBAIS-----------------*/

    int i;         // iteração
    char c;        // char
    char str1[30]; // string
    int k;         // iteração

    struct dadosEntradaStruct *ptr = &dadosEntrada;

    while ((c = fgetc(pfile)) != ':')
    {
    }
    fscanf(pfile, "%d", &(ptr->NN)); // ptr->NN

    while ((c = fgetc(pfile)) != ':')
    {
    }
    fscanf(pfile, "%d", &(ptr->NB)); // ptr->NN

    // LOCAÇÃO DAS ENTRADA

    ptr->x      = (float *)malloc(ptr->NN * sizeof(float));
    ptr->VINC   = (int *)malloc(2 * ptr->NN * sizeof(int));
    ptr->CARNO  = (float *)malloc(2 * ptr->NN * sizeof(float));
    ptr->INI    = (int *)malloc(ptr->NB * sizeof(int));
    ptr->FIM    = (int *)malloc(ptr->NB * sizeof(int));
    ptr->In     = (float *)malloc(ptr->NB * sizeof(float));
    ptr->E      = (float *)malloc(ptr->NB * sizeof(float));
    ptr->qyi    = (float *)malloc(ptr->NB * sizeof(float));
    ptr->qyf    = (float *)malloc(ptr->NB * sizeof(float));


    /*-------------COORDENADAS-----------------*/

    while ((c = fgetc(pfile)) != ':')
    {
    }
    for (i = 0; i < ptr->NN; i++)
    {
        fscanf(pfile, "%s %d", str1, &k);
        fscanf(pfile, " %s %f", str1, &(ptr->x[k]));
    }

    /*-------------PROPRIEDADES-----------------*/

    while ((c = fgetc(pfile)) != ':')
    {
    }
    for (i = 0; i < ptr->NB; i++) // propriedades
    {
        fscanf(pfile, "%s %d", str1, &k);
        fscanf(pfile, " %s %d", str1, &(ptr->INI[k]));
        fscanf(pfile, " %s %d", str1, &(ptr->FIM[k]));
        fscanf(pfile, " %s %f", str1, &(ptr->E[k]));
        fscanf(pfile, " %s %f", str1, &(ptr->In[k]));
    }

    /*-------------VINCULAÇÃO-----------------*/
    // posições pares do vetor (0,2,4...) são vínculos lineares, e posições impares vinculos de rotação

    for (i = 0; i < 2 * ptr->NN; i++)
    {
        ptr->VINC[i] = 0;
    }

    while ((c = fgetc(pfile)) != ':')
    {
    }
    fscanf(pfile, "%d", &ptr->NNVINC);

    while ((c = fgetc(pfile)) != ':')
    {
    }

    for (i = 0; i < ptr->NNVINC; i++)
    {
        fscanf(pfile, "%s %d", str1, &k);
        fscanf(pfile, " %s %d", str1, &(ptr->VINC[2 * k]));
        fscanf(pfile, " %s %d", str1, &(ptr->VINC[2 * k + 1]));
    }

    /*-------------CARGAS NODAIS-----------------*/
    // posições pares do vetor (0,2,4...) são forças, e posições impares momentos

    for (i = 0; i < 2 * ptr->NN; i++)
    {
        ptr->CARNO[i] = 0;
    }

    while ((c = fgetc(pfile)) != ':')
    {
    }
    fscanf(pfile, "%d", &ptr->NNCARNO);

    while ((c = fgetc(pfile)) != ':')
    {
    }

    for (i = 0; i < ptr->NNCARNO; i++)
    {
        fscanf(pfile, "%s %d", str1, &k);
        fscanf(pfile, " %s %f", str1, &(ptr->CARNO[2 * k]));
        fscanf(pfile, " %s %f", str1, &(ptr->CARNO[2 * k + 1]));
    }

    /*-------------CARGAS NAS BARRAS-----------------*/
    // posições pares do vetor (0,2,4...) são forças, e posições impares momentos


    while ((c = fgetc(pfile)) != ':')
    {
    }
    fscanf(pfile, "%d", &(ptr->NNCARBAR));

    while ((c = fgetc(pfile)) != ':')
    {
    }

    for (i = 0; i < ptr->NNCARBAR; i++)
    {
        fscanf(pfile, "%s %d", str1, &k);
        fscanf(pfile, " %s %f", str1, &(ptr->qyi[k]));
        fscanf(pfile, " %s %f", str1, &(ptr->qyf[k]));
    }


}
