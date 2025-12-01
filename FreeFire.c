#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Struct Item: representa um item básico da mochila
typedef struct {
    char nome[30];
    char tipo[30];
    int quantidade;
} Item;

// Vetor da mochila
Item mochila[MAX_ITENS];
int numItens = 0;

// Limpa a tela
void limparTela() {
    for (int i = 0; i < 40; i++) printf("\n");
}

// Exibe o menu principal
void exibirMenu() {
    printf("=====================================\n");
    printf("     INVENTARIO - NIVEL NOVATO       \n");
    printf("=====================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

// Insere um item na mochila
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia! Remova algum item antes de adicionar outro.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[numItens] = novo;
    numItens++;

    printf("\nItem adicionado com sucesso!\n");
}

// Remove um item pelo nome
void removerItem() {
    if (numItens == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
}

// Lista todos os itens
void listarItens() {
    if (numItens == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    printf("\n====== ITENS NA MOCHILA ======\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        limparTela();

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("Saindo do inventario...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
            limparTela();
        }

    } while (opcao != 0);

    return 0;
}
