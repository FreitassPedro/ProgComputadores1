#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_SAIDA "C:\\Users\\jogui\\Documents\\Coding\\C\\ProgComputadores1\\DESAFIO DE PC FASE 1\\tarefas_out.txt"
<<<<<<< HEAD
#define ARQUIVO_ENTRADA "C:\\Users\\jogui\\Documents\\Coding\\C\\ProgComputadores1\\DESAFIO DE PC FASE 1\\tarefas_in.txt"
=======
#define ARQUIVO_ENTRADA "C:\\Users\\jogui\\Documents\\Coding\\C\\ProgComputadores1\\DESAFIO DE PC FASE 1\\tarefas_out.txt"
>>>>>>> 2ed7bc185cf6b40a56ee4854de83eb731050b096

// Fusao Tarefa e Celula
typedef struct cel
{
    char nome[50];
    char descricao[50];
    char data_limite[10];
    char categoria[15];
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
void filtrar();

void listar(ListaTarefas lista);
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
Celula *nova -> inserir(&nova); Alterar proprio ponteiro
Celula *nova ->

char *palavra ou char palavra[] sãp a mesma coisa
correto: lerInput(nome, sizeof(nome))


//
. Entendendo os Símbolos
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
            char nome[50];
            ler_input(nome, sizeof(nome));
            Celula *cel = buscar(listaTarefas, nome);
            imprimir_celula(*cel);
            break;

        } // 2. Buscar
        case 3:
        {
            listar(listaTarefas);
            break;
        } // 3; Listar
        case 4:
        {
            char nome[50];
            ler_input(nome, 50);
            Celula *cel = buscar(listaTarefas, nome);
            editar(cel);
            break;

        } // 4. Editar
        case 5:
        {
            char nome[50];
            ler_input(nome, sizeof(nome));

            excluir(&listaTarefas, nome);
            break;
        } // 5. Excluir
        case 6:
        {
            char nome[50];
            ler_input(nome, sizeof(nome));
            Celula *cel = buscar(listaTarefas, nome);
            concluir(cel);
            break;

        } // 6. Concluir
        case 7: // Salvar Arquivo
        {
            FILE *fp;
            fp = fopen(ARQUIVO_SAIDA, "w");
            if (fp == NULL)
            {
                printf("Falha ao abrir o arquivo.\n");
                break;
            }
            Celula *cel = listaTarefas.cabeca;

            printf("Salvando lista no txt...\n");
            if (fprintf(fp, "Testando\n") < 0)
            {
                printf("Falha ao escrever no arquivo.\n");
                fclose(fp);
                break;
            }
            while (cel != NULL)
            {
                imprimir_celula(*cel);
                salvar_lista(listaTarefas);
            }
            fclose(fp);
            printf("Arquivo Fechando\n");
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
<<<<<<< HEAD
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
=======
    fopen(ARQUIVO_ENTRADA, "r");

    char linha[300];
    Celula *celulaAtual = (Celula *)malloc(sizeof(Celula));
    Celula *celulaAnterior = (Celula *)malloc(sizeof(Celula));
    while (fgets(linha, sizeof(linha), fp))
    {
>>>>>>> 2ed7bc185cf6b40a56ee4854de83eb731050b096

        strcpy(celulaAtual->nome, strtok(linha, "|"));
        strcpy(celulaAtual->descricao, strtok(NULL, "|"));
        strcpy(celulaAtual->data_limite, strtok(NULL, "|"));
        strcpy(celulaAtual->categoria, strtok(NULL, "|"));
        // 'Atoi' ASCII TO INTEGER converte string para Int
        celulaAtual->prioridade = atoi(strtok(NULL, "|"));
        celulaAtual->concluida = atoi(strtok(NULL, "|\n"));
<<<<<<< HEAD
        celulaAtual->prox = NULL;
=======
>>>>>>> 2ed7bc185cf6b40a56ee4854de83eb731050b096

        if (lista->cabeca == NULL)
        {
            lista->cabeca = celulaAtual;
        }
        else
        {
<<<<<<< HEAD
            lista->cauda->prox = celulaAtual;
        }

        lista->cauda = celulaAtual;

        lista->qttTarefas++;
    }

    fclose(fp);
=======
            celulaAnterior->prox = celulaAtual;
            lista->cauda = celulaAtual;
        }

        lista->qttTarefas++;
    }

    free(celulaAnterior);
    free(celulaAnterior);

    salvar_lista(*lista);
>>>>>>> 2ed7bc185cf6b40a56ee4854de83eb731050b096
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
    while ((atual->prox != NULL))
    {
        atual = atual->prox;
    }
    atual->prox = nova;

    if (nova->prox == NULL)
        lista->cauda = nova;
    lista->qttTarefas++;
}

void excluir(ListaTarefas *lista, char nome[])
{
    Celula *atual, *anterior;
    atual = lista->cabeca;

    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        anterior = atual;
        atual = atual->prox;
    }

    anterior->prox = atual->prox;
    free(atual);
    lista->qttTarefas--;
}
Celula *criar_celula()
{
    Celula *novaTarefa = (Celula *)malloc(sizeof(Celula));
    printf("Digite informações da nova Tarefa.\n ");

    printf("Nome: ");
    ler_input(novaTarefa->nome, sizeof(novaTarefa->nome));

    printf("Descricao: ");
    ler_input(novaTarefa->descricao, sizeof(novaTarefa->descricao));

    printf("Data Limite: ");
    ler_input(novaTarefa->data_limite, sizeof(novaTarefa->data_limite));

    printf("Categoria: ");
    ler_input(novaTarefa->categoria, sizeof(novaTarefa->categoria));

    printf("Prioridade: ");
    scanf("%d", &novaTarefa->prioridade);

    novaTarefa->concluida = 0;

    novaTarefa->prox = NULL;
    return novaTarefa;
};

Celula *buscar(ListaTarefas lista, char nome[])
{
    Celula *atual = lista.cabeca;

    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        atual = atual->prox;
    }

    return atual;
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

void listar(ListaTarefas lista)
{
    Celula *atual;

    atual = lista.cabeca;
    printf("\n----Listando Tarefas---\n");

    while (atual != NULL)
    {
        // O '*' passa o conteudo do ponteiro
        imprimir_celula(*atual);
        atual = atual->prox;
    }
}

void imprimir_celula(Celula celula)
{
    printf("Nome: %s\n", celula.nome);
    printf("Descricao %s\n", celula.descricao);
    printf("Data Limite: %s\n", celula.data_limite);
    printf("Categoria %s\n", celula.categoria);
    printf("Prioridade %d\n", celula.prioridade);
    printf("Concluida %d\n", celula.concluida);
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
        printf("Data Limite:");
        ler_input(cel->data_limite, sizeof(cel->data_limite));
        break;
    case 4:
        printf("Novo Categoria:");
        ler_input(cel->categoria, sizeof(cel->nome));
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