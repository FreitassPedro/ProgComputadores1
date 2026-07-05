#include <stdio.h>
#include <stdlib.h>

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

void imprimir();
void inserir();
void concluir();
void buscar();
void excluir();
void salvar();

void filtrar();
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
int main()
{

    ListaTarefas listaTarefas;
    inicializar_lista(&listaTarefas);

    int escolha;
    do
    {
        imprimir();
        scanf("%d", &escolha);
        getchar();

        switch (escolha)
        {
        case 1:
        {
            Celula *nova = criar_celula();
            inserir_tarefa(&listaTarefas, &nova);
            break;
        } // 1. Inserir
        case 2:
        {
            char nome[50];
            input(&nome, sizeof(nome));
            Celula *cel;
            cel = buscar(&listaTarefas, nome);
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
            input(&nome, sizeof(nome));
            Celula *cel = buscar(&listaTarefas, nome);
            editar(&cel);
            break;

        } // 4. Editar
        case 5:
        {
            Celula *cel = buscar(&listaTarefas, nome);
            excluir(&listaTarefas, &cel);
            break;

        } // 5. Excluir
        case 6:
        {
            char nome[50];
            input(&nome, sizeof(nome));
            Celula *cel;
            cel = buscar(nome);

            concluir(&cel);
            break;

        } // 6. Concluir
        case 7: // Salvar Arquivo
        {
        }
        break;
        }
    } while (escolha != 8);
    return 0;
}

void inicializar_lista(ListaTarefas *lista)
{
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qttTarefas = 0;
}

void imprimir()
{
    printf("Qual operação deseja realizar?");
    printf("1. Inserir tarefa");
    printf("2. Buscar tarefa");
    printf("3. Listar tarefas");
    printf("4. Editar tarefa");
    printf("5. Excluir tarefa");
    printf("6. Marcar tarefa como concluida");
    printf("7. Salvar lista");
    printf("8. Sair do programa");
}

void inserir_tarefa(ListaTarefas *lista, Celula *nova)
{
    if (nova == NULL)
        return;

    Celula *nova = malloc(sizeof(Celula));
    // If estrutura vazia, insira 1° elemento
    if (lista->cabeca == NULL)
    {
        lista->cabeca = nova;
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

void remover_tarefa(ListaTarefas *lista, char nome)
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

    printf("Nome: ");
    input(novaTarefa->nome, sizeof(novaTarefa->nome));

    printf("Descricao: ");
    input(novaTarefa->descricao, sizeof(novaTarefa->descricao));

    printf("Data Limite: ");
    input(novaTarefa->data_limite, sizeof(novaTarefa->data_limite));

    printf("Categoria: ");
    input(novaTarefa->categoria, sizeof(novaTarefa->categoria));

    printf("Prioridade: ");
    scanf("%d", &novaTarefa->prioridade);
    printf("Concluida: ");
    novaTarefa->concluida = 0;

    novaTarefa->prox = NULL;
    return novaTarefa;
};

Celula *buscar(ListaTarefas *lista, char nome)
{
    Celula *atual;

    while (strcomp(atual->nome, nome))
    {
        atual = atual->prox;
    }

    return atual;
}

void input(char *palavra, int size)
{
    char c;
    int contador;
    while ((c = getchar != "\n") && (contador < size))
    {
        palavra[contador] = c;
        contador++;
    }

    palavra[contador] = "\n";
}

void concluir(Celula *celula)
{
    celula->concluida = 1;
}

void listar(ListaTarefas lista)
{
    Celula *atual;

    atual = lista.cabeca;
    while (atual != NULL)
    {
        imprimir_celula(atual);
        atual = atual->prox;
    }
}

void imprimir_celula(Celula celula)
{
    printf(celula.nome);
    printf(celula.descricao);
    printf(celula.data_limite);
    printf(celula.categoria);
    printf(celula.prioridade);
    printf(celula.concluida);
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
        input(cel->nome, sizeof(cel->nome));
        break;
    case 2:
        printf("Novo Descricao:");
        input(cel->descricao, sizeof(cel->descricao));
        break;
    case 3:
        printf("Data Limite:");
        input(cel->data_limite, sizeof(cel->data_limite));
        break;
    case 4:
        printf("Novo Categoria:");
        input(cel->categoria, sizeof(cel->nome));
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