#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

/* Item da mochila */
typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade;
} Item;

/* Critérios para ordenar */
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

Item mochila[MAX];
int numItens = 0;
bool ordenadaPorNome = false;

/* limpa a tela */
void limparTela() {
    for (int i = 0; i < 30; i++)
        printf("\n");
}

/* mostra menu */
void exibirMenu() {
    printf("========== MOCHILA ==========\n");
    printf("Itens armazenados: %d\n", numItens);
    printf("Ordenada por nome: %s\n", ordenadaPorNome ? "SIM" : "NÃO");
    printf("-----------------------------\n");
    printf("1 - Adicionar item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Ordenar itens\n");
    printf("5 - Buscar item (binária)\n");
    printf("0 - Sair\n");
    printf("> ");
}

/* inserir item */
void inserirItem() {
    if (numItens >= MAX) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\nNome: ");
    scanf(" %[^\n]", mochila[numItens].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", mochila[numItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &mochila[numItens].prioridade);

    numItens++;
    ordenadaPorNome = false;

    printf("\nItem adicionado!\n");
}

/* remover item */
void removerItem() {
    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[50];
    printf("\nNome do item para remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(nome, mochila[i].nome) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            ordenadaPorNome = false;
            printf("\nItem removido!\n");
            return;
        }
    }

    printf("\nItem não encontrado.\n");
}

/* listar */
void listarItens() {
    if (numItens == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n===== ITENS =====\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d) Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

/* insertion sort */
int insertionSort(CriterioOrdenacao criterio) {
    int comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item aux = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;

            int trocar = 0;

            if (criterio == ORDENAR_NOME)
                trocar = strcmp(aux.nome, mochila[j].nome) < 0;

            else if (criterio == ORDENAR_TIPO)
                trocar = strcmp(aux.tipo, mochila[j].tipo) < 0;

            else if (criterio == ORDENAR_PRIORIDADE)
                trocar = aux.prioridade < mochila[j].prioridade;

            if (!trocar)
                break;

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = aux;
    }

    if (criterio == ORDENAR_NOME)
        ordenadaPorNome = true;
    else
        ordenadaPorNome = false;

    return comparacoes;
}

/* menu para ordenar */
void menuDeOrdenacao() {
    printf("\nOrdenar por:\n");
    printf("1 - Nome\n");
    printf("2 - Tipo\n");
    printf("3 - Prioridade\n");
    printf("> ");

    int op;
    scanf("%d", &op);

    int comp = insertionSort(op);
    printf("\nItens ordenados! Comparações: %d\n", comp);
}

/* busca binária */
int buscaBinariaPorNome(char nome[]) {
    int ini = 0, fim = numItens - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nome, mochila[meio].nome);

        if (cmp == 0)
            return meio;

        if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

/* busca binária + exibição */
void buscarItem() {
    if (!ordenadaPorNome) {
        printf("\nA busca binária exige que a lista esteja ordenada por NOME.\n");
        return;
    }

    char nome[50];
    printf("\nNome a buscar: ");
    scanf(" %[^\n]", nome);

    int pos = buscaBinariaPorNome(nome);

    if (pos >= 0) {
        printf("\nItem encontrado!\n");
        printf("Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
               mochila[pos].nome,
               mochila[pos].tipo,
               mochila[pos].quantidade,
               mochila[pos].prioridade);
    } else {
        printf("\nItem não encontrado.\n");
    }
}

/* programa principal */
int main() {
    int opc;

    do {
        exibirMenu();
        scanf("%d", &opc);

        switch (opc) {
        case 1:
            inserirItem();
            break;
        case 2:
            removerItem();
            break;
        case 3:
            listarItens();
            break;
        case 4:
            menuDeOrdenacao();
            break;
        case 5:
            buscarItem();
            break;
        case 0:
            printf("\nEncerrando...\n");
            break;
        default:
            printf("\nOpção inválida!\n");
        }

    } while (opc != 0);

    return 0;
}
