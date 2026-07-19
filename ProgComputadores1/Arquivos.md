
`fscanf` retorna  EOF (END of File) quando o arquivo termina
```c
while (fscanf(arqiovp, "%d", &num) != EOF) {
    // Processar o número lido
}
```

`fgets` retorna NULL quando o arquivo termina
```c
while (fgets(buffer, sizeof(buffer), arqiovp) != NULL) {
 printf("%s", buffer);
}
```

`fgetc` le caracter por caracter até fim do arquivo EOF
```c
char ch;
while ((ch = fgetc(arquivo)) != EOF) {
    if (ch != '\n') {
        printf("%c", ch);
    }
}
```

`fscanf` extrai linha toda (ideal pra formatados csv) e retorna EOF quando o arquivo termina
```c
char linha[100];
while (fscanf(arquivo, "%[^\n]\n", linha) != EOF) {
    printf("%s\n", linha);
}
```
Também ideal para formatados, exemplo 1 caracteres, 1 inteiros e 1 float. 
```c
char ch;
int num;
float real;
// Podemos parar no EOF (!= EOF) ou até encontrar os dados (== 3)
while (fscanf(arquivo, " %c %d %f", &ch, &num, &real) != EOF) {
    printf("Caractere: %c, Inteiro: %d, Real: %.2f\n", ch, num, real);
}
```

