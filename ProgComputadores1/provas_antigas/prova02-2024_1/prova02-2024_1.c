#include <stdio.h>
#include <stdlib.h>

typedef struct cel
{
    int prioridade;
    int custo;
    struct cel *prox;
} Celula;

typedef struct lista
{
    struct cel *cabeca;
} Lista;

int main()
{

    FILE *fp = fopen("entrada.txt", "r");

    if (fp == NULL)
        return 0;

    Lista *list = (Lista *)malloc(sizeof(Lista));

    list->cabeca = (Celula *)malloc(sizeof(Celula));
    list->cabeca->prox = NULL;

    char linha[10];
    while (fgets(linha, sizeof(linha), fp))
    {
        Celula *novaCel = (Celula *)malloc(sizeof(Celula));
        sscanf(linha, "%d %d", &novaCel->prioridade, &novaCel->custo);

        Celula *atual = list->cabeca;

        while (atual->prox != NULL)
        {

            if (atual->prox->prioridade >= novaCel->prioridade)
            {
                if (atual->prox->prioridade > novaCel->prioridade)
                    break;

                if (atual->prox->prioridade == novaCel->prioridade && atual->prox->custo > novaCel->custo)
                    break;
            }
            atual = atual->prox;
        }

        novaCel->prox = atual->prox;
        atual->prox = novaCel;
    }

    fclose(fp);

    FILE *fpWrite = fopen("saida.txt", "w");
    Celula *atual = list->cabeca;
    while (atual->prox != NULL)
    {
        fprintf(fpWrite, "%d %d\n", atual->prox->prioridade, atual->prox->custo);
        atual = atual->prox;
    }

    fclose(fpWrite);
    return 0;
}