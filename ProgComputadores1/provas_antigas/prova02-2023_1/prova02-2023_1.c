#include <stdio.h>
#include <stdlib.h>

typedef struct coord
{
    int x;
    int y;
    struct coord *prox;
} Coordenada;

typedef struct
{
    struct coord *cabeca;
} Lista;

int main()
{

    Lista *q1 = (Lista *)malloc(sizeof(Lista));
    Lista *q2 = (Lista *)malloc(sizeof(Lista));
    Lista *q3 = (Lista *)malloc(sizeof(Lista));
    Lista *q4 = (Lista *)malloc(sizeof(Lista));

    q1->cabeca = NULL;
    q2->cabeca = NULL;
    q3->cabeca = NULL;
    q4->cabeca = NULL;

    FILE *fp = fopen("entrada.txt", "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.");
        return 1;
    }
    int x, y;

    char linha[8];

    while (fgets(linha, sizeof(linha), fp) != NULL)
    {
        Coordenada *coord = (Coordenada *)malloc(sizeof(Coordenada));

        if (sscanf(linha, "%d %d", &coord->x, &coord->y) != 2)
        {
            free(coord);
            continue;
        }

        coord->prox = NULL;
        printf("Lendo variáveis %d %d\n", coord->x, coord->y);

        int quadrante = 0;
        // Se x > 0, ou quadrante 2 ou 3
        if (coord->x > 0)
        {
            if (coord->y > 0)
                quadrante = 1;
            else
                quadrante = 4;
        }
        else
        {
            if (coord->y > 0)
                quadrante = 2;
            else
                quadrante = 3;
        };

        Lista *auxiliar = q1;
        printf("Reservand ao quadrante %d\n", quadrante);
        switch (quadrante)
        {
        case 1:
            auxiliar = q1;
            break;
        case 2:
            auxiliar = q2;
            break;

        case 3:
            auxiliar = q3;
            break;
        case 4:
            auxiliar = q4;
            break;
        default:
            break;
        }

        if (auxiliar->cabeca == NULL)
        {
            auxiliar->cabeca = coord;
        }
        else
        {
            Coordenada *atual = auxiliar->cabeca;
            while (atual->prox != NULL)
                atual = atual->prox;

            atual->prox = coord;
        }
    }

    fclose(fp);

    FILE *fpW = fopen("saida.txt", "w");
    if (fpW == NULL)
    {
        printf("Erro ao abrir arquivo saida.txt\n");
        return 0;
    }

    int imprimindoQuadrante = 1;
    while (imprimindoQuadrante <= 4)
    {
        Lista *quadrante = q1;
        switch (imprimindoQuadrante)
        {
        case 1:
            quadrante = q1;
            break;
        case 2:
            quadrante = q2;
            break;
        case 3:
            quadrante = q3;
            break;
        case 4:
            quadrante = q4;
            break;
        default:
            break;
        }

        Coordenada *atual = quadrante->cabeca;
        printf("Q%d:\n", imprimindoQuadrante);

        fprintf(fpW, "Q%d:\n", imprimindoQuadrante);
        while (atual != NULL)
        {
            printf("%d %d\n", atual->x, atual->y);

            fprintf(fpW, "%d %d\n", atual->x, atual->y);
            atual = atual->prox;
        }
        imprimindoQuadrante++;
    }

    fclose(fpW);

    return 0;
}