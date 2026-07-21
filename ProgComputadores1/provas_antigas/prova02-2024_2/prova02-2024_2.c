#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct pragas
{
    char nome_popular[200];
    char nome_cientifico[200];
    char culturas[200];
    int quantidade;
    int temperatura_min;
    int temperatura_max;
    char condicoes[200];
    struct pragas *prox;
};

struct pragas *cria(void);

void imprime(struct pragas *lista);
void carrega(struct pragas *lista);
void inserir(struct pragas *lista, struct pragas *novaPraga);

int main()
{
    struct pragas *lista;

    lista = cria();
    carrega(lista);
    imprime(lista);

    return 0;
}

struct pragas *cria()
{
    struct pragas *praga = (struct pragas *)malloc(sizeof(struct pragas));

    praga->prox = NULL;

    return praga;
}

void carrega(struct pragas *lista)
{
    FILE *fp = fopen("entrada.txt", "r");

    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.");
        return;
    }

    char linha[100];
    int dadosColetados = 0;

    struct pragas *novaPraga = (struct pragas *)malloc(sizeof(struct pragas));
    novaPraga->prox = NULL;

    while (fgets(linha, sizeof(linha), fp))
    {
        linha[strcspn(linha, "\n")] = '\0'; // o strcspn
        switch (dadosColetados)
        {
        case 0:

            strcpy(novaPraga->nome_popular, linha);
            dadosColetados++;
            break;
        case 1:
            strcpy(novaPraga->nome_cientifico, linha);
            dadosColetados++;
            break;
        case 2:
            strcpy(novaPraga->culturas, linha);
            dadosColetados++;
            break;
        case 3:
            sscanf(linha, "%d", &novaPraga->quantidade);
            dadosColetados++;
            break;
        case 4:
            sscanf(linha, "%d", &novaPraga->temperatura_min);
            dadosColetados++;
            break;
        case 5:
            sscanf(linha, "%d", &novaPraga->temperatura_max);
            dadosColetados++;
            break;
        case 6:
            strcpy(novaPraga->condicoes, linha);
            dadosColetados++;

            inserir(lista, novaPraga);

            novaPraga = (struct pragas *)malloc(sizeof(struct pragas));
            novaPraga->prox = NULL;
            dadosColetados = 0;
            break;
        }
    }

    fclose(fp);
}

void imprime(struct pragas *lista)
{

    struct pragas *atual = lista->prox;

    while (atual->prox != NULL)
    {
        printf("\n\n%s", atual->nome_popular);

        printf("%s\n", atual->nome_popular);
        printf("%s\n", atual->nome_cientifico);
        printf("%s\n", atual->culturas);
        printf("%d\n", atual->quantidade);
        printf("%d\n", atual->temperatura_min);
        printf("%d\n", atual->temperatura_max);
        printf("%s\n", atual->condicoes);

        atual = atual->prox;
    }
}

void inserir(struct pragas *lista, struct pragas *novaPraga)
{
    struct pragas *atual = lista;
    while (atual->prox != NULL)
    {
        if (strcmp(atual->prox->nome_popular, novaPraga->nome_popular) < 0)
        {
            break;
        }
        atual = atual->prox;
    }
    novaPraga->prox = atual->prox;
    atual->prox = novaPraga;
}
