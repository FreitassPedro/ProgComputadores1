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

void bubbleSort(Lista *lista);

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

    vogais->cabeca = (Letra *)malloc(sizeof(Letra));
    consoantes->cabeca = (Letra *)malloc(sizeof(Letra));

    vogais->cabeca->prox = NULL;
    consoantes->cabeca->prox = NULL;

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

        // EM ASCII, o 'a' < 'b' < 'c'
        while (atual->prox != NULL && novaLetra->letra > atual->prox->letra)
        {
            atual = atual->prox;
        }
        novaLetra->prox = atual->prox;
        atual->prox = novaLetra;
    }
    fclose(fp);

    // Reordenar listas
    //  bubbleSort(vogais);
    // bubbleSort(consoantes);

    // Funcao de salvar
    FILE *fpSaida = fopen("saida.txt", "w");
    if (fpSaida == NULL)
    {
        printf("Erro");
        return 1;
    }

    Letra *aux = vogais->cabeca->prox;
    int listasImpressas = 0;
    int titulo = 0;

    while (aux != NULL)
    {
        if (titulo == 0)
        {
            titulo = 1;
            if (listasImpressas == 0)
            {
                fprintf(fpSaida, "Vogais:\n");
            }
            else
                fprintf(fpSaida, "Consoantes:\n");
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

void bubbleSort(Lista *lista)
{
    if (lista == NULL || lista->cabeca == NULL)
        return;

    int trocou;

    do
    {
        trocou = 0;
        Letra *anterior = NULL;
        Letra *atual = lista->cabeca;

        while (atual != NULL && atual->prox != NULL)
        {
            Letra *prox = atual->prox;

            if (atual->letra > prox->letra)
            {
                /* swap atual and prox */
                if (anterior == NULL)
                {
                    lista->cabeca = prox;
                }
                else
                {
                    anterior->prox = prox;
                }

                atual->prox = prox->prox;
                prox->prox = atual;

                trocou = 1;

                /* after swap, 'prox' is before 'atual' */
                anterior = prox;
            }
            else
            {
                anterior = atual;
                atual = atual->prox;
            }
        }

    } while (trocou);
}