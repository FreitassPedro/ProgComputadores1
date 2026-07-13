// Nome: Pedro da Silva Pereira de Freitas
// matricula: 26102678

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
###### IMPORTANTE ###### IMPORTANTE  ###### IMPORTANTE  ###### IMPORTANTE


Embora o desafio não permita o uso de variáveis globais, tive que especificar o PATH completo no meu PC que não estava acessando os arquivos FILE.
#define ARQUIVO_SAIDA "C:\\Users\\jogui\\Documents\\Coding\\C\\ProgComputadores1\\DESAFIO DE PC FASE 1\\tarefas_out.txt"
#define ARQUIVO_ENTRADA "C:\\Users\\jogui\\Documents\\Coding\\C\\ProgComputadores1\\DESAFIO DE PC FASE 1\\tarefas_in.txt"


Se o avaliador conseguir da forma que deveria ser correta, mantive a indicação.
###### IMPORTANTE  ###### IMPORTANTE  ###### IMPORTANTE  ###### IMPORTANTE
*/
#define ARQUIVO_SAIDA "tarefas_out.txt"
#define ARQUIVO_ENTRADA "tarefas_in.txt"

// Fusao Tarefa e Celula
typedef struct cel
{
    char nome[50];
    char descricao[100];
    char data_limite[11];
    char categoria[20];
    int prioridade;
    int concluida;
    struct cel *prox;
} Celula;

typedef struct
{
    Celula *cabeca;
    Celula *cauda;
    int qttTarefas;
} ListaTarefas;

void imprimir_celula(Celula celula);
void inserir_tarefa(ListaTarefas *lista, Celula *cel);
void concluir(Celula *celula);
Celula *buscar(ListaTarefas listaTarefas, char nome[]);
void excluir(ListaTarefas *listaTarefas, char nome[]);
void salvar();
void editar(Celula *celula);

void inicializar_lista(ListaTarefas *lista);
Celula *criar_celula();
void ler_input(char *palavra, int size);
void imprimir_menu();

void listar(ListaTarefas lista, int filtro);
void salvar_lista(ListaTarefas lista);
/*
Inserir: Solicitar ao usuário os campos necessários e armazenar os dados na lista encadeada de
tarefas, ordenada pela data_limite.
• Concluir: Solicitar ao usuário o nome da tarefa e marcá-la como concluída.
• Buscar: Buscar tarefa pelo nome e exibir seus dados completos.
• Listar: Listar todas as tarefas de acordo com o filtro selecionado pelo usuário.
• Editar: Buscar uma tarefa pelo nome, perguntar qual campo será editado, solicitar o novo valor
e atualizar a lista encadeada.
• Excluir: Excluir uma tarefa buscando pelo nome.
• Salvar tarefas: Salvar a lista encadeada de tarefas em um arquivo de texto, seguindo o formato
especificado abaixo
*/

/*
## COMENTARIOS E ANOTAÇÔES ##
Celula *nova -> inserir(&nova); Alterar proprio ponteiro
Celula *nova ->

char *palavra ou char palavra[] sãp a mesma coisa
correto: lerInput(nome, sizeof(nome))

funcaoA(Objeto *obj);
funcaoB(Objeto obj);

Obejeto *ptr_para_obj = malloc(...);
Obejeto obj;
funcaoA(ptr_para_obj);
funcaoA(&obj);

funcaoB(*ptr_para_obj);
funcaoB(obj);

//
Entendendo os Símbolos
imprimir(Celula celula) -> imprmir(celula);
atual: É o endereço de memória (o ponteiro).
*atual: É o conteúdo dentro desse endereço (a estrutura Celula inteira).
&atual: É o endereço do próprio ponteiro (raramente usado aqui).
*/
int main()
{

    ListaTarefas listaTarefas;
    inicializar_lista(&listaTarefas);

    int escolha;
    do
    {
        imprimir_menu();
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha)
        {
        case 1:
        {
            Celula *nova = criar_celula();
            inserir_tarefa(&listaTarefas, nova);
            break;
        } // 1. Inserir
        case 2:
        {
            printf("Digite nome da tarefa pra buscar: ");
            char nome[50];
            ler_input(nome, sizeof(nome));
            Celula *cel = buscar(listaTarefas, nome);
            if (cel == NULL)
            {
                printf("Tarefa nao encontrada\n");
                break;
            }
            imprimir_celula(*cel);
            break;

        } // 2. Buscar
        case 3:
        {
            int filtro = 0;
            printf("Filtrar por: \n");
            printf("1. Todas as Tarefas: \n");
            printf("2. Apenas concluidas: \n");
            printf("3. Apenas nao concluidas: \n");
            printf("Escolha: ");
            scanf("%d", &filtro);

            listar(listaTarefas, filtro);
            break;
        } // 3; Listar
        case 4:
        {
            printf("Nome tarefa pra editar: ");

            char nome[50];
            ler_input(nome, 50);
            Celula *cel = buscar(listaTarefas, nome);
            if (cel != NULL)
                editar(cel);
            else
                printf("Não encontrada.\n");
            break;

        } // 4. Editar
        case 5:
        {
            printf("Nome tarefa pra excluir: ");

            char nome[50];
            ler_input(nome, sizeof(nome));

            excluir(&listaTarefas, nome);
            break;
        } // 5. Excluir
        case 6:
        {
            printf("Nome tarefa pra concluir: ");

            char nome[50];
            ler_input(nome, sizeof(nome));
            Celula *cel = buscar(listaTarefas, nome);
            if (cel != NULL)
                concluir(cel);
            else
                printf("Digite tarefa existente\n");
            break;

        } // 6. Concluir
        case 7: // Salvar Arquivo
        {
            salvar_lista(listaTarefas);
            break;
        }
        }
    } while (escolha != 8);
    return 0;
}

void inicializar_lista(ListaTarefas *lista)
{
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qttTarefas = 0;

    FILE *fp;
    fp = fopen(ARQUIVO_ENTRADA, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada\n");
        return;
    }

    char linha[300];
    while (fgets(linha, sizeof(linha), fp))
    {
        Celula *celulaAtual = (Celula *)malloc(sizeof(Celula));
        if (celulaAtual == NULL)
        {
            printf("Erro de memoria ao carregar tarefas\n");
            fclose(fp);
            return;
        }
        char *nome;
        char *descricao;
        char *data;
        char *categoria;
        char *prioridade;
        char *concluida;

        nome = strtok(linha, "|");
        descricao = strtok(NULL, "|");
        data = strtok(NULL, "|");
        categoria = strtok(NULL, "|");
        prioridade = strtok(NULL, "|");
        concluida = strtok(NULL, "|\n");

        printf("Nome: %s\n", nome);
        printf("Descricao: %s\n", descricao);
        printf("Data: %s\n", data);
        printf("Categoria: %s\n", categoria);
        printf("Prioridade: %s\n", prioridade);
        printf("Concluida: %s\n\n", concluida);

        strcpy(celulaAtual->nome, nome);
        strcpy(celulaAtual->descricao, descricao);
        strcpy(celulaAtual->data_limite, data);
        strcpy(celulaAtual->categoria, categoria);
        celulaAtual->prioridade = atoi(prioridade);
        celulaAtual->concluida = atoi(concluida);
        celulaAtual->prox = NULL;

        if (lista->cabeca == NULL)
            lista->cabeca = celulaAtual;
        else
            lista->cauda->prox = celulaAtual;

        lista->cauda = celulaAtual;

        lista->qttTarefas++;
    }

    fclose(fp);

    // Reordenar lista
    if (lista->cabeca == NULL || lista->cabeca->prox == NULL)
        return;

    int trocou;
    do
    {
        trocou = 0;
        Celula *anterior = NULL;
        Celula *atual = lista->cabeca;

        while (atual != NULL && atual->prox != NULL)
        {
            Celula *proximo = atual->prox;

            // Se a data de atual for maior que a do proximo, troca os nos
            if (strcmp(atual->data_limite, proximo->data_limite) > 0)
            {
                atual->prox = proximo->prox;
                proximo->prox = atual;

                if (anterior == NULL)
                    lista->cabeca = proximo;
                else
                    anterior->prox = proximo;

                anterior = proximo;
                trocou = 1;
            }
            else
            {
                anterior = atual;
                atual = atual->prox;
            }
        }

    } while (trocou == 1); // Se houve troca, o algoritmo reitera até acabar as trocas.

    lista->cauda = lista->cabeca; // Garante que elemento único seja cabeça também
    while (lista->cauda->prox != NULL)
        lista->cauda = lista->cauda->prox;
}

void imprimir_menu()
{
    printf("\nQual operação deseja realizar?\n");
    printf("1. Inserir tarefa\n");
    printf("2. Buscar tarefa\n");
    printf("3. Listar tarefas\n");
    printf("4. Editar tarefa\n");
    printf("5. Excluir tarefa\n");
    printf("6. Marcar tarefa como concluida\n");
    printf("7. Salvar lista\n");
    printf("8. Sair do programa\n\n");
}

void inserir_tarefa(ListaTarefas *lista, Celula *nova)
{
    if (nova == NULL)
        return;

    // If estrutura vazia, insira 1° elemento
    if (lista->cabeca == NULL)
    {
        lista->cabeca = nova;
        nova->prox = NULL;
        lista->qttTarefas = 1;
        return;
    }

    // Se não, adicione intermedio ou na cauda
    Celula *atual = lista->cabeca;
    Celula *anterior = NULL;

    // Identifica se o novo é menor que a cabeça
    if (strcmp(atual->nome, nova->nome) > 0)
    {
        nova->prox = lista->cabeca;
        lista->cabeca = nova;
        free(atual);
        return;
    }
    else
    {
        anterior = atual;
        atual = atual->prox;
    }

    while (atual != NULL)
    {

        // strcmp == 0 string iguais
        // < 0: a primeira vem antes da segunda
        // > 0: a primeira vem DEPOIS da segunda
        if (strcmp(atual->data_limite, nova->data_limite) >= 0)
        {
            // Se a data for igual mas priodidade atual é maior que a nova, insiere depois
            if (strcmp(atual->data_limite, nova->data_limite) == 0 && (atual->prioridade > nova->prioridade))
            {
                nova->prox = atual->prox;
                atual->prox = nova;
            }
            else
            {
                anterior->prox = nova;
                nova->prox = atual;
            }
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Se durante o loop a nova nao foi adicionada no meio, adicione-a como cauda
    if (nova->prox == NULL)
    {
        atual->prox = nova;
        lista->cauda = nova;
    }

    lista->qttTarefas++;
}

void excluir(ListaTarefas *lista, char nome[])
{
    if (lista->cabeca == NULL)
    {
        printf("ERRO: Tarefa não existe. \n");
        return;
    }

    Celula *atual = lista->cabeca;
    Celula *anterior = NULL;

    // Verifica primeiro se o primeiro elemento é a cabeça, e define a cauda
    if (strcmp(atual->nome, nome) == 0)
    {
        lista->cabeca = lista->cabeca->prox;

        if (lista->cabeca == NULL)
        {
            lista->cauda == NULL;
        }
        free(atual);
        lista->qttTarefas--;
        printf("Tarefa excluida.\n");
        return;
    }
    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("ERRO: Tarefa não existe. \n");

        return; // encerra se não encontrar
    }
    else
    {
        if (atual->prox == NULL)
            lista->cauda = anterior;
        anterior->prox = atual->prox;
    }
    free(atual);
    lista->qttTarefas--;
    printf("Tarefa excluida.\n");
}
Celula *criar_celula()
{
    Celula *novaTarefa = (Celula *)malloc(sizeof(Celula));
    printf("Digite informações da nova Tarefa.\n");

    printf("Nome: ");
    ler_input(novaTarefa->nome, sizeof(novaTarefa->nome));

    printf("Descricao: ");
    ler_input(novaTarefa->descricao, sizeof(novaTarefa->descricao));

    printf("Data Limite (AAAA-MM-DD): ");
    ler_input(novaTarefa->data_limite, sizeof(novaTarefa->data_limite));

    int invalidInput = 1;
    do
    {
        printf("Categoria (Prova, Trabalho ou Outra): ");
        ler_input(novaTarefa->categoria, sizeof(novaTarefa->categoria));
        if (strcmp(novaTarefa->categoria, "Trabalho") != 0 && strcmp(novaTarefa->categoria, "Prova") != 0 && strcmp(novaTarefa->categoria, "Outra") != 0)
        {
            printf("Categoria inválida. Escolha Prova, Trabalho ou Outra.\n");
        }
        else
            invalidInput = 0;
    } while (invalidInput != 0);

    invalidInput = 1;
    do
    {
        printf("Prioridade (1, 2 ou 3): ");
        scanf("%d", &novaTarefa->prioridade);
        if (novaTarefa->prioridade >= 1 && novaTarefa->prioridade <= 3)
            invalidInput = 0;
    } while (invalidInput != 0);

    novaTarefa->concluida = 0;

    novaTarefa->prox = NULL;
    return novaTarefa;
};

Celula *buscar(ListaTarefas lista, char nome[])
{
    Celula *atual = lista.cabeca;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
            return atual;
        atual = atual->prox;
    }
    printf("Tarefa não encontrada: %s\n", nome);
    return NULL;
}

void ler_input(char *palavra, int size)
{
    char c;
    int contador = 0;
    while ((c = getchar()) != '\n' && (contador < size))
    {
        palavra[contador] = c;
        contador++;
    }

    palavra[contador] = '\0';
}

void concluir(Celula *celula)
{
    celula->concluida = 1;
}

void listar(ListaTarefas lista, int filtro)
{
    Celula *atual = lista.cabeca;

    printf("\n----Listando Tarefas---\n");
    while (atual != NULL)
    {
        int imprimir = 0;
        // O '*' passa o conteudo do ponteiro
        switch (filtro)
        {
        case 1:
            imprimir = 1;
            break;
        case 2:
            if (atual->concluida == 1)
                imprimir = 1;
            break;
        case 3:
            if (atual->concluida == 0)
                imprimir = 1;
            break;
        default:
            break;
        }
        if (imprimir == 1)
            imprimir_celula(*atual);
        atual = atual->prox;
    }

    printf("\n----Tarefas Listadas----\n");
}

void imprimir_celula(Celula celula)
{
    printf("\n");
    printf("Nome: %s\n", celula.nome);
    printf("Descricao: %s\n", celula.descricao);
    printf("Data Limite: %s\n", celula.data_limite);
    printf("Categoria: %s\n", celula.categoria);
    printf("Prioridade: %d\n", celula.prioridade);
    printf("Concluida: %d\n", celula.concluida);
    printf("\n");
}

void editar(Celula *cel)
{

    printf("Qual campo deseja editar?\n");
    printf("1. Nome\n");
    printf("2. Descricao\n");
    printf("3. Data Limite\n ");
    printf("4. Categoria\n");
    printf("5. Prioridade\n");
    printf("6. Concluir\n");

    int escolha;
    switch (escolha)
    {
    case 1:
        printf("Novo nome:");
        ler_input(cel->nome, sizeof(cel->nome));
        break;
    case 2:
        printf("Novo Descricao:");
        ler_input(cel->descricao, sizeof(cel->descricao));
        break;
    case 3:
        printf("Nova Data Limite:");
        ler_input(cel->data_limite, sizeof(cel->data_limite));
        break;
    case 4:
        printf("Novo Categoria:");
        ler_input(cel->categoria, sizeof(cel->categoria));
        break;
    case 5:
        printf("Nova Prioridade");
        scanf("%d", &cel->prioridade);
        break;
    case 6:
        printf("Concluir?");
        scanf("%d", &cel->concluida);
        break;
    default:
        break;
    }
}

void salvar_lista(ListaTarefas lista)
{
    Celula *cel = lista.cabeca;

    FILE *fp = fopen(ARQUIVO_SAIDA, "w");
    while (cel != NULL)
    {
        if (fprintf(fp, "%s|%s|%s|%s|%d|%d\n",
                    cel->nome,
                    cel->descricao,
                    cel->data_limite,
                    cel->categoria,
                    cel->prioridade,
                    cel->concluida) < 0)
        {
            printf("Erro ao salvar.");
            fclose(fp);
            break;
        }

        cel = cel->prox;
    }

    fclose(fp);
    printf("Salvo.\n");
}