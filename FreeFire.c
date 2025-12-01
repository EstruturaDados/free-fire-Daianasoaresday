#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

//-----------------------------------
// STRUCT DOS ITENS
//-----------------------------------
typedef struct {
    char nome[30];
    char tipo[30];
    int quantidade;
} Item;

//-----------------------------------
// LISTA ENCADEADA
//-----------------------------------
typedef struct Nodo {
    Item item;
    struct Nodo *prox;
} Nodo;

//-----------------------------------
// VARIÁVEIS GLOBAIS
//-----------------------------------
Item mochilaVetor[MAX_ITENS];
int numItensVetor = 0;

Nodo *lista = NULL;

long comparacoesSequencial = 0;
long comparacoesBinaria = 0;

//-----------------------------------
// FUNÇÕES AUXILIARES
//-----------------------------------
void limparTela() {
    for (int i = 0; i < 40; i++) printf("\n");
}

//-----------------------------------
// SISTEMA COM VETOR
//-----------------------------------

void inserirItemVetor() {
    if (numItensVetor >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[numItensVetor++] = novo;
    printf("Item inserido no vetor!\n");
}

void removerItemVetor() {
    char nome[30];
    printf("Nome do item para remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < numItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < numItensVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];
            numItensVetor--;
            printf("Removido!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

void listarVetor() {
    if (numItensVetor == 0) {
        printf("Vetor vazio!\n");
        return;
    }

    printf("\n====== Itens no Vetor ======\n");
    for (int i = 0; i < numItensVetor; i++) {
        printf("%d. %s | %s | %d\n",
               i + 1,
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

void ordenarVetor() {
    for (int i = 1; i < numItensVetor; i++) {
        Item chave = mochilaVetor[i];
        int j = i - 1;

        while (j >= 0 && strcmp(mochilaVetor[j].nome, chave.nome) > 0) {
            mochilaVetor[j + 1] = mochilaVetor[j];
            j--;
        }
        mochilaVetor[j + 1] = chave;
    }
    printf("Vetor ordenado por nome!\n");
}

int buscarSequencialVetor(char *nome) {
    comparacoesSequencial = 0;

    for (int i = 0; i < numItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

int buscarBinariaVetor(char *nome) {
    comparacoesBinaria = 0;

    int ini = 0, fim = numItensVetor - 1;
    while (ini <= fim) {
        comparacoesBinaria++;
        int meio = (ini + fim) / 2;

        int cmp = strcmp(nome, mochilaVetor[meio].nome);

        if (cmp == 0) return meio;
        if (cmp > 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

//-----------------------------------
// SISTEMA COM LISTA ENCADEADA
//-----------------------------------

void inserirItemLista() {
    Nodo *novo = (Nodo *) malloc(sizeof(Nodo));

    printf("Nome: ");
    scanf(" %[^\n]", novo->item.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo->item.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->item.quantidade);

    novo->prox = lista;
    lista = novo;

    printf("Item inserido na lista!\n");
}

void removerItemLista() {
    char nome[30];
    printf("Nome do item para remover: ");
    scanf(" %[^\n]", nome);

    Nodo *ant = NULL, *atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->item.nome, nome) == 0) {
            if (ant == NULL)
                lista = atual->prox;
            else
                ant->prox = atual->prox;

            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
    printf("Item não encontrado!\n");
}

void listarLista() {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    printf("\n====== Itens na Lista ======\n");
    Nodo *p = lista;
    int i = 1;

    while (p != NULL) {
        printf("%d. %s | %s | %d\n",
               i++,
               p->item.nome,
               p->item.tipo,
               p->item.quantidade);
        p = p->prox;
    }
}

int buscarSequencialLista(char *nome) {
    comparacoesSequencial = 0;

    Nodo *p = lista;
    while (p != NULL) {
        comparacoesSequencial++;
        if (strcmp(p->item.nome, nome) == 0)
            return 1;  // encontrado
        p = p->prox;
    }
    return 0; // não encontrado
}

//-----------------------------------
// MENUS
//-----------------------------------

void menuVetor() {
    int op;
    do {
        printf("\n===== MENU VETOR =====\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar vetor\n");
        printf("5. Buscar sequencial\n");
        printf("6. Buscar binária\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        limparTela();

        char nome[30];
        int pos;

        switch(op) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarVetor(); break;
            case 4: ordenarVetor(); break;
            case 5:
                printf("Nome para buscar: ");
                scanf(" %[^\n]", nome);
                pos = buscarSequencialVetor(nome);
                printf(pos != -1 ?
                       "Encontrado na posição %d\n" :
                       "Não encontrado\n", pos);
                printf("Comparações: %ld\n", comparacoesSequencial);
                break;
            case 6:
                printf("Nome para buscar: ");
                scanf(" %[^\n]", nome);
                pos = buscarBinariaVetor(nome);
                printf(pos != -1 ?
                       "Encontrado na posição %d\n" :
                       "Não encontrado\n", pos);
                printf("Comparações: %ld\n", comparacoesBinaria);
                break;
        }

    } while (op != 0);
}

void menuLista() {
    int op;
    do {
        printf("\n===== MENU LISTA =====\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar sequencial\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        limparTela();

        char nome[30];
        int achou;

        switch(op) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarLista(); break;
            case 4:
                printf("Nome para buscar: ");
                scanf(" %[^\n]", nome);
                achou = buscarSequencialLista(nome);
                printf(achou ? "Encontrado!\n" : "Não encontrado!\n");
                printf("Comparações: %ld\n", comparacoesSequencial);
                break;
        }

    } while (op != 0);
}

//-----------------------------------
// MAIN
//-----------------------------------

int main() {
    int op;

    do {
        printf("\n======== SISTEMA DE MOCHILA - NÍVEL AVENTUREIRO ========\n");
        printf("1. Usar Vetor\n");
        printf("2. Usar Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        limparTela();

        switch (op) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
        }

    } while (op != 0);

    printf("Saindo...\n");
    return 0;
}
