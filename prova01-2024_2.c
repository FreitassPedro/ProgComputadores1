#include <stdio.h>
#include <string.h>

void prova(char variedades[10][30],
int temp_min[10], int temp_max[10],
int prec_min[10], int prec_max[10],
int alti_min[10], int alti_max[10],
int valor_pergunta1, int valor_pergunta2,
char respostas[10][30], int *quantidade);


int main() {
    char variedade[10][30], resposta[10][30];
    int t_min[10], t_max[10];
    int p_min[10], p_max[10];
    int a_min[10], a_max[10];
    int i, qtde = 0, valor1, valor2;

    for (i = 0; i < 10; i++)
        scanf(”%s %d %d %d %d %d %d”, variedade[i],
        &t_min[i], &t_max[i],
        &p_min[i], &p_max[i],
        &a_min[i], &a_max[i]);

    printf(”Informe a precipitação anual da sua região:\n”);
    scanf(”%d”, &valor1);
    printf(”Informe a altitude da sua região:\n”);
    scanf(”%d”, &valor2);
    
    prova(variedade,
        t_min, t_max,
        p_min, p_max,
        a_min, a_max,
        valor1, valor2,
        resposta, &qtde);
    
    printf(”Variedade(s) indicada(s):\n”);
    
    for (i = 0; i < qtde; i++)
        printf(”%s\n”, resposta[i]);
    return 0;
}

void prova(char variedades[10][30],
                int temp_min[10], int temp_max[10],
                int prec_min[10], int prec_max[10],
                int alti_min[10], int alti_max[10],
                int valor_pergunta1, int valor_pergunta2,
                char respostas[10][30],
                 int *quantidade) {


    for (int i =0; i<10; i++) {

        if (valor_pergunta1 > prec_max[i] && valor_pergunta1 < prec_max[i] && valor_pergunta2 > alti_min[i]  && valor_pergunta2 > alti_max[i]) {
            respostas[i] = variedades[i];

            *quantidade = quantidade + 1;
        }

    }


}