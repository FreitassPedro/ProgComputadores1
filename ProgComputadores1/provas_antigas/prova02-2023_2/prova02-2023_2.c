#include <stdio.h>
#include <stdlib.h>

typedef struct letra
{
    char letra;
    struct letra *prox;
} Letra;

typedef struct lista
{
    // Manter minúsculo
    struct letra *cabeca;
} Lista;

int main()
{
    FILE *fp = fopen("entrada.txt", "r");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    Lista *vogais = (Lista *)malloc(sizeof(Lista));
    Lista *consoantes = (Lista *)malloc(sizeof(Lista));

    vogais->cabeca = NULL;
    consoantes->cabeca = NULL;

    char vogaisArray[5] = {'A', 'E', 'I', 'O', 'U'};

    char linha[5];

    while (fgets(linha, sizeof(linha), fp))
    {
        char letra;
        sscanf(linha, "%c", &letra);
        // Se 1 sim, se nao 0
        int isVogal = 0;
        Letra *novaLetra = (Letra *)malloc(sizeof(Letra));

        novaLetra->letra = letra;
        novaLetra->prox = NULL;

        for (int i = 0; i < sizeof(vogaisArray); i++)
        {
            if (letra == vogaisArray[i])
            {
                isVogal = 1;
                break;
            }
        }

        Lista *aux;
        if (isVogal == 1)
            aux = vogais;
        else
            aux = consoantes;

        Letra *atual = aux->cabeca;
        if (atual == NULL)
        {
            aux->cabeca = novaLetra;
        }
        else
        {
            while (atual->prox != NULL)
            {
                atual = atual->prox;
            }
            atual->prox = novaLetra;
        }
    }
    fclose(fp);

    // Reordenar listas
    /*
    Lista *auxiliar = vogais;
    Letra *atualOrd = auxiliar->cabeca;
    Letra *nula = NULL;

    while ()
    while (atualOrd != NULL)
    {
        Letra *nula = NULL;

        atualOrd = atualOrd->prox;
    }
*/
    // Funcao de salvar
    FILE *fpSaida = fopen("saida.txt", "w");
    if (fpSaida == NULL)
    {
        printf("Erro");
        return 1;
    }

    Letra *aux = vogais->cabeca;
    int listasImpressas = 0;
    int titulo = 0;

    while (aux != NULL)
    {
        if (titulo == 0)
        {
            titulo = 1;
            if (listasImpressas == 0)
            {
                fprintf(fp, "Vogais:\n");
            }
            else
                fprintf(fp, "Consoantes:\n");
        }

        fprintf(fpSaida, "%c\n", aux->letra);

        if (aux->prox == NULL && listasImpressas == 0)
        {
            titulo = 0;
            aux = consoantes->cabeca;
            listasImpressas++;
            continue;
        }
        aux = aux->prox;
    }

    fclose(fpSaida);
    return 0;
}