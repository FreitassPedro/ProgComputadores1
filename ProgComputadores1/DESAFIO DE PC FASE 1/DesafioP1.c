#include <stdio.h>
#include <string.h>

/*
// Nome: Pedro da Silva Pereira de Freitas
// matrícula: 26102678 
*/

typedef struct // Diz ao Compilador como a estrutura Tarefa é
{
    char nome[50];
    char descricao[100];
    char data[10];
    char categoria[20];
    int prioridade;
} Tarefa;

void exibirMenu();

void inserirTarefa(Tarefa tarefas[], int *ocupadas, int tamanho, Tarefa novaTarefa);
Tarefa buscarTarefa(Tarefa tarefas[], int indice);
void listarTarefas(Tarefa tarefas[], int ocupadas);
void editarTarefa(Tarefa tarefas[], int indice);
void excluirTarefa(Tarefa tarefas[], int *ocupadas, int indice);
Tarefa criarTarefa(void);

void lerInput(char *palavra, int tamanho);
int encontrarIndice(Tarefa tarefas[], int tamanho, char nome[]);

void imprimirTarefa(Tarefa tarefa);

/*Anotações
- em C, passar listas em parametros na verdade é passar o ponteiro para primeiro elemento. Se quiser manipular uma cópia, teria que criar uma.
- coleção de char ("Ex char nome[]") funciona como ponteiros. Utilizar *nome passa indice 0 do char, assim, *nome == nome[0].
*/
int main()
{

    int tamanho = 50;
    int ocupadas = 0;
    Tarefa tarefas[tamanho];

    int choice = 0;

    while (choice != 6)
    {
        exibirMenu();

        printf("Escolha:  ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {

        case 1: // 1. Inserir Tarefa
        {
            Tarefa novaTarefa = criarTarefa();

            inserirTarefa(tarefas, &ocupadas, tamanho, novaTarefa);
            break;
        }
        case 2: // 2. Buscar tarefa
        {
            printf("Digite nome da Tarefa: \n");
            char nome[50];

            lerInput(nome, 50);
            int indice = encontrarIndice(tarefas, ocupadas, nome);
            if (indice == -1)
            {
                printf("Tarefa não encontrada.\n");
                break;
            }
            printf("Tarefa encontrada.\n");
            Tarefa tarefa = buscarTarefa(tarefas, indice);

            imprimirTarefa(tarefa);
            printf("\n");
            break;
        }
        case 3: //  3. Listar tarefas
        {
            listarTarefas(tarefas, ocupadas);
            break;
        }
        case 4: // 4. Editar tarefa
        {
            printf("Nome da tarefa para editar: ");
            char nome[50];
            lerInput(nome, 50);
            int indice = encontrarIndice(tarefas, ocupadas, nome);
            if (indice == -1)
                printf("Tente novamente.\n");

            editarTarefa(tarefas, indice);

            Tarefa tarefa = buscarTarefa(tarefas, indice);
            imprimirTarefa(tarefa);
            break;
        }
        case 5: // 5. Excluir tarefa
        {
            printf("Nome da Tarefa para excluir: ");
            char nome[50];
            lerInput(nome, 50);

            int indice = encontrarIndice(tarefas, ocupadas, nome);

            excluirTarefa(tarefas, &ocupadas, indice);
            break;
        }
        default:
            printf("Opção Inválida, digite novamente\n");
        }
    }

    return 0;
}

void lerInput(char *palavra, int tamanho)
{
    int i = 0;

    char c;
    while ((c = getchar()) != '\n' && (i < tamanho))
    {
        palavra[i] = c;
        i++;
    };

    palavra[i] = '\0';
}

void exibirMenu(void)
{
    printf("\n ----- MENU ----- \n");
    printf("Qual operação deseja realizar?\n");
    printf("1. Inserir tarefa\n");
    printf("2. Buscar tarefa\n");
    printf("3. Listar tarefas\n");
    printf("4. Editar tarefa\n");
    printf("5. Excluir tarefa\n");
    printf("6. Sair do programa\n");
    printf("\n");
}

Tarefa criarTarefa(void)
{
    printf("Insira os dados para criar a Tarefa: \n ");
    Tarefa novaTarefa;

    printf("Nome: ");
    lerInput(novaTarefa.nome, sizeof(novaTarefa.nome));

    printf("Descricao: ");
    lerInput(novaTarefa.descricao, sizeof(novaTarefa.descricao));

    printf("Data: ");
    lerInput(novaTarefa.data, sizeof(novaTarefa.data));

    printf("Categoria: ");
    lerInput(novaTarefa.categoria, sizeof(novaTarefa.categoria));

    int prioridade = 0;
    do
    {
        printf("Prioridade (1-3): ");
        scanf("%d", &prioridade);
        getchar();
    } while (prioridade < 1 || prioridade > 3);
    novaTarefa.prioridade = prioridade;

    return novaTarefa;
}
void inserirTarefa(Tarefa tarefas[], int *ocupados, int tamanho, Tarefa novaTarefa)
{
    if ((*ocupados) == tamanho)
    {
        printf("A Lista está cheia!. Delete um item para esvaziar\n");
        return;
    }

    // Aponta para o endereço da novaTarefa
    tarefas[*ocupados] = novaTarefa;
    (*ocupados)++;
    printf("Tarefa Inserida com sucesso.\n");
}

// Assume-se que o indice foi encontrado!
Tarefa buscarTarefa(Tarefa tarefas[], int indice)
{
    return tarefas[indice];
}

void listarTarefas(Tarefa tarefas[], int ocupadas)
{
    printf("----Tarefas registradas --- \n\n");
    for (int i = 0; i < ocupadas; i++)
    {
        imprimirTarefa(tarefas[i]);
    }

    printf("----Tarefas registradas --- \n\n");
}

void editarTarefa(Tarefa tarefas[], int indice)
{
    int choice = 0;
    Tarefa tarefa = tarefas[indice];
    printf("Qual campo deseja editar?\n");
    printf("1: Nome\n");
    printf("2: Descrição\n");
    printf("3: Data\n");
    printf("4: Categoria\n");
    printf("5: Prioridade\n");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        printf("Digite o novo nome: ");
        lerInput(tarefa.nome, sizeof(tarefa.nome));
        break;
    case 2:
        printf("Digite a nova descrição: ");
        lerInput(tarefa.descricao, sizeof(tarefa.descricao));
        break;
    case 3:
        printf("Digite a nova data: ");
        lerInput(tarefa.data, sizeof(tarefa.data));
        break;
    case 4:
        printf("Digite a nova categoria: ");
        lerInput(tarefa.categoria, sizeof(tarefa.categoria));
        break;
    case 5:

        int prioridade = 0;
        do
        {
            printf("Prioridade (1-3): ");
            scanf("%d", &prioridade);
            if (prioridade < 1 || prioridade > 3)
                printf("Error... A prioridade deve ser 1, 2 ou 3.");

            getchar();
        } while (prioridade < 1 || prioridade > 3);
        tarefa.prioridade = prioridade;
    }

    tarefas[indice] = tarefa;
}

void excluirTarefa(Tarefa tarefas[], int *ocupadas, int indiceAlvo)
{
    
    tarefas[indiceAlvo].nome[0] = '\0';
    tarefas[indiceAlvo].descricao[0] = '\0';
    tarefas[indiceAlvo].data[0] = '\0';
    tarefas[indiceAlvo].prioridade = 0;
    tarefas[indiceAlvo].categoria[0] = '\0';

    printf("Tarefa Excluida.\n");

    printf("Reorgnizando a lista...\n");
    // Shifting

    for (int i = indiceAlvo; i < (*ocupadas); i++)
    {
        tarefas[i] = tarefas[i + 1];
    };

    (*ocupadas)--;
    printf("Lista reorganizada.\n");
}

void imprimirTarefa(Tarefa tarefa)
{
    printf("Nome: %s\n", tarefa.nome);
    printf("Descrição: %s\n", tarefa.descricao);
    printf("Data: %s\n", tarefa.data);
    printf("Categoria: %s\n", tarefa.categoria);
    printf("Prioridade: %d\n\n", tarefa.prioridade);
}

// Encontrar Índice facilita na coleta da tarefa; Além de despoluir o código
int encontrarIndice(Tarefa tarefas[], int ocupadas, char nome[])
{
    for (int i = 0; i < ocupadas; i++)
    {
        // o Strcmp compara valores de String em C
        if (strcmp(tarefas[i].nome, nome) == 0)
            return i;
    }
    return -1;
};