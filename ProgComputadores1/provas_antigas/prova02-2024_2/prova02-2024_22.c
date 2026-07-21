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
int main()
{
    struct pragas *lista;
    lista = cria();
    carrega(lista);
    imprime(lista);
    return 0;
}

struct pragas *cria(void)
{
    struct pragas *praga = (struct pragas *)malloc(sizeof(struct pragas));

    praga->prox = NULL;
    return praga;
}
void imprime(struct pragas *lista)
{
    struct pragas *atual = lista->prox;
    while (atual != NULL)
    {
        printf("Nome Popular: %s\n", atual->nome_popular);
        printf("Nome científico: %s\n", atual->nome_cientifico);

        printf("Culturas Aintigdas: %s\n", atual->culturas);

        printf("Limites: %d\n", atual->quantidade);
        printf("T minimia ideal: %d\n", atual->temperatura_min);
        printf("T máxima ideal: %d\n", atual->temperatura_max);
        printf("Condicoes ideias: %s\n", atual->condicoes);

        atual = atual->prox;
    }
}
void carrega(struct pragas *lista)
{

    FILE *fp = fopen("entrada.txt", "r");

    char linha[200];
    int registrado = 0;
    struct pragas *novaPraga = (struct pragas *)malloc(sizeof(struct pragas));

    while (fgets(linha, sizeof(linha), fp))
    {
        switch (registrado)
        {
        case 0:
            sscanf(linha, "%s", novaPraga->nome_popular);
            registrado++;
            break;
        case 1:
            sscanf(linha, "%s", novaPraga->nome_cientifico);
            registrado++;

            break;
        case 2:
            sscanf(linha, "%s", novaPraga->culturas);
            registrado++;

            break;
        case 3:
            sscanf(linha, "%d", &novaPraga->quantidade);
            registrado++;

            break;
        case 4:
            sscanf(linha, "%d", &novaPraga->temperatura_min);
            registrado++;

            break;
        case 5:
            sscanf(linha, "%d", &novaPraga->temperatura_max);
            registrado++;

            break;
        case 6:
            sscanf(linha, "%s", novaPraga->condicoes);

            struct pragas *pragaAtual = lista;

            while (pragaAtual->prox != NULL)
            {
                if (strcmp(pragaAtual->prox->nome_popular, novaPraga->nome_popular) > 0)
                    break;

                pragaAtual = pragaAtual->prox;
            }

            novaPraga->prox = pragaAtual->prox;
            pragaAtual->prox = novaPraga;

            registrado = 0;
            novaPraga = malloc(sizeof(struct pragas));
            break;

        default:
            break;
        }
    }
    fclose(fp);
}