/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int main()
{
    int i=3,j=5;
    int *p,*q;
    p=&i;
    q=&j;
    
    //Operador & retorna o endereço de uma variável (Address of)
    // Operador * (Deference Indirenção) retorna o valor armazenado no endereço apontado por um ponteiro
    // Operador ** (Indireção Dupla) retorna o valor armazenado no endereço apontado por um ponteiro de ponteiro
    printf("Valor de p: %p\n", p);
    printf("Valor de q: %p\n", q);
    printf("Valor de p - q %d", *p - *q);
    return 0;
}