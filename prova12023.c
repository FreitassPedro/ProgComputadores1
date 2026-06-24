#include <stdio.h>

#define TAM 1000
void numeros_amigos(int n, int amigos[TAM][2], int *q);

int somatorio_divisores(int num);
int main() {
    int n, i, q;
    int pares_amigos[TAM][2];
    scanf("%d", &n);

    numeros_amigos(n, pares_amigos, &q);

    for (i = 0; i < q; i++)
        printf("(%d,%d)\n", pares_amigos[i][0], pares_amigos[i][1]);

    return 0;
}


void numeros_amigos(int n, int amigos[TAM][2], int *q) {
    // Calcular somatório de divisores X e Y
    int a, b;
    int pares_encontrados = 0;

    printf("Iniciando...");
    for (int i = 0; i < n; i++) {
        if (i==0) continue;

        int somaA = 0;
        int somaB = 0;
        somaA = somatorio_divisores(i);
    
        for (int j=0; j<i; j++) {
            if (j==0) continue;

            somaB = somatorio_divisores(j);


            if (somaB == i && somaA == j) {
                printf("encontrados! %d %d\n", i, j);

                amigos[pares_encontrados][0] = j;
                amigos[pares_encontrados][1] = i; 
                pares_encontrados++;
            }
        }

    }

    // Em funções fora da main, utilizar 'q = &a' não funciona pois o 'q' original (la no main) deixará de existir quando a função terminar. para corrigir, altere o valor guardado em 'q' com '*' '*q = b' 
    *q = pares_encontrados;
    
}


int somatorio_divisores(int num) {
    int soma=0;

    for (int i=0; i<=num; i++) {
        if (i==0 || i==1) continue;

        // Se houver resto, nao é divisível
        if ((num % i) != 0) continue; 

        int divisao = num / i;
        soma = soma + divisao;

    }

    return soma;
}

