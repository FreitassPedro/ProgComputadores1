#include <stdio.h>
#include <stdlib.h>
struct concreto
{
    int tipo;
    float cimento;
    float areia;
    float pedra;
    float agua;
    float rendimento;
    struct concreto *prox;
};
struct concretagem
{
    int tipo;
    float largura;
    float comprimento;
    float altura;
    struct concretagem *prox;
};
typedef struct concreto celula_concreto;
typedef struct concretagem celula_concretagem;
int main()
{

    FILE *fp = fopen("entrada.txt", "r");
    celula_concreto *concretos = (celula_concreto *)malloc(sizeof(celula_concreto));

    celula_concretagem *concrategens = (celula_concretagem *)malloc(sizeof(celula_concretagem));

    concretos->prox = NULL;
    concrategens->prox = NULL;

    char linha[100];

    float totalCimento = 0.0;
    float totalAreia = 0.0;
    float totalPedra = 0.0;
    float totalAgua = 0.0;

    int quantiaTipos = 0;
    int quantiaObras = 0;

    int interacoesTipos = 0;
    int iteracoesObras = 0;

    while (fgets(linha, sizeof(linha), fp))
    {
        if (quantiaTipos == 0)
        {
            sscanf(linha, "%d", &quantiaTipos);
        }
        else if (quantiaTipos > 0 && interacoesTipos < quantiaTipos)
        {
            celula_concreto *novoConcreto = (celula_concreto *)malloc(sizeof(celula_concreto));

            novoConcreto->tipo = interacoesTipos;
            sscanf(linha, "%f %f %f %f %f", &novoConcreto->cimento, &novoConcreto->areia, &novoConcreto->pedra, &novoConcreto->agua, &novoConcreto->rendimento);
            printf("%d %f %f %f %f %f\n", novoConcreto->tipo, novoConcreto->cimento, novoConcreto->areia, novoConcreto->pedra, novoConcreto->agua, novoConcreto->rendimento);

            celula_concreto *atual = concretos;
            while (atual->prox != NULL)
            {
                atual = atual->prox;
            }
            novoConcreto->prox = atual->prox;
            atual->prox = novoConcreto;

            interacoesTipos++;
        }

        else if (quantiaObras == 0)
        {
            sscanf(linha, "%d", &quantiaObras);
        }
        else if (quantiaObras > 0 && iteracoesObras < quantiaObras)
        {
            celula_concretagem *novaConcretagem = (celula_concretagem *)malloc(sizeof(celula_concretagem));

            sscanf(linha, "%d %f %f %f", &novaConcretagem->tipo, &novaConcretagem->largura, &novaConcretagem->comprimento, &novaConcretagem->altura);
            printf("%d %f %f %f\n", novaConcretagem->tipo, novaConcretagem->largura, novaConcretagem->comprimento, novaConcretagem->altura);

            celula_concretagem *atual = concrategens;
            while (atual->prox != NULL)
            {
                atual = atual->prox;
            }
            novaConcretagem->prox = atual->prox;
            atual->prox = novaConcretagem;
            iteracoesObras++;
        }
    }
    fclose(fp);

    FILE *fpWrite = fopen("saida.txt", "w");

    celula_concretagem *atualConcrategem = concrategens->prox;
    while (atualConcrategem != NULL)
    {
        celula_concreto *atualConcreto = concretos->prox;
        float volumeConcetragem = atualConcrategem->altura * atualConcrategem->comprimento * atualConcrategem->largura;
        while (atualConcreto != NULL)
        {
            if (atualConcrategem->tipo == atualConcreto->tipo)
            {
                float fator = volumeConcetragem / atualConcreto->rendimento;

                totalCimento += atualConcreto->cimento * fator;
                totalPedra += atualConcreto->pedra * fator;
                totalAreia += atualConcreto->areia * fator;
                totalAgua += atualConcreto->agua * fator;
                break;
            }
            atualConcreto = atualConcreto->prox;
        }
        atualConcrategem = atualConcrategem->prox;
    }

    printf("Cimento %f  Pedra: %f Areia: %f Agua: %f\n", totalCimento, totalPedra, totalAreia, totalAgua);
    fprintf(fp, "cimento: %.2f saco(s)\n", totalCimento);
    fprintf(fp, "areia: %.2f latas(s)\n", totalAreia);
    fprintf(fp, "pedra: %.2f latas(s)\n", totalPedra);
    fprintf(fp, "agua: %.2f latas(s)\n", totalAgua);
    fclose(fpWrite);

    return 0;
}