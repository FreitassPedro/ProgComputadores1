#include <stdio.h>
#include <stdlib.h>

struct cel
{
    int prioridade;
    int custo;
    struct cel *prox;
} Celula;

typedef struct cel;

typedef struct lista
{
    struct cel *cabeca;
} Lista;

int main()
{
    
}