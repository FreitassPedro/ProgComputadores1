#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lfrutas
{
    char nome[100];
    char tipo[100];
    int horas_frio_min;
    int horas_frio_max;
    struct lfrutas *prox;
};

struct lfrutas *cria(void);
void carrega(struct lfrutas *lista);
void salva(struct lfrutas *lista);

int main()
{
    struct lfrutas *l = cria();

    carrega(l);

    salva(l);

    return 0;
}

struct lfrutas *cria(void)
{
    struct lfrutas *frutas = (struct lfrutas *)malloc(sizeof(struct lfrutas));

    frutas->prox = NULL;

    return frutas;
}

void carrega(struct lfrutas *lista)
{
    FILE *fp = fopen("entrada.txt", "r");

    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.");
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), fp) != NULL)
    {
        struct lfrutas *novaFruta = (struct lfrutas *)malloc(sizeof(struct lfrutas));

        if (sscanf(linha, "%[^;];%[^;];%d;%d", novaFruta->nome, novaFruta->tipo, &novaFruta->horas_frio_min, &novaFruta->horas_frio_max) == 4)
        {
            printf("Lido: %s %s %d %d\n", novaFruta->nome, novaFruta->tipo, novaFruta->horas_frio_min, novaFruta->horas_frio_max);
            struct lfrutas *atual = lista;

            while (atual->prox != NULL)
            {
                if (strcmp(atual->prox->nome, novaFruta->nome) > 0)
                {
                    break;
                }
                atual = atual->prox;
            }

            novaFruta->prox = atual->prox;
            atual->prox = novaFruta;
        }
    }

    fclose(fp);
}

void salva(struct lfrutas *lista)
{

    FILE *fp = fopen("saida.txt", "w");
    if (fp == NULL)
        return;

    printf("\nImprimindo lista:\n");
    struct lfrutas *atual = lista->prox;

    while (lista->prox != NULL)
    {
        printf("%s:%s:%d:%d\n", atual->nome, atual->tipo, atual->horas_frio_min, atual->horas_frio_max);

        fprintf(fp, "%s:%s:%d:%d\n", atual->nome, atual->tipo, atual->horas_frio_min, atual->horas_frio_max);

        atual = atual->prox;
    }

    fclose(fp);
}