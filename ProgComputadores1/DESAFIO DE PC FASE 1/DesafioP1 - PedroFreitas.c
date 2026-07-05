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
            Celula celula = criar_celula()
                inserir_tarefa(&listaTarefas, &nova);

        } // Inserir

        case 2:
        {
            char nome[50];
            input(&nome, sizeof(nome));
            Celula cel = buscar(nome);
        } // 2. Buscar
        case 3:
        {
            listar(listaTarefas);
        } // 3; Listar
        case 4:
        {
            Celula *cel = buscar();
            editar(&cel);
        } // 4. Editar
        case 5:
        {
            Celula *cel = buscar();
            excluir(&listaTarefas, &cel);
        } // 5. Excluir
        case 6:
        {
            Celula *cel = buscar();
            concluir(&cel);
        } // 6. Concluir
        case 7: // Salvar
        {
        }
        case 8:
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
Celula criar_celula()
{
    Celula novaTarefa;

    printf("Nome: ");
    input(novaTarefa.categoria, sizeof(novaTarefa.categoria));

    printf("Descricao: ");
    printf("Data Limite: ");
    printf("Categoria: ");
    printf("Prioridade: ");
    printf("Concluida: ");

    novaTarefa.prox = NULL;
    return novaTarefa;
};

Celula buscar(ListaTarefas *lista, char nome)
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