#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

//--------------------------------------------------------
// STRUCT PRINCIPAL DO SISTEMA
//--------------------------------------------------------
typedef struct {
    char nome[40];
    char tipo[40];
    int prioridade;
} Componente;

//--------------------------------------------------------
// VARIÁVEIS GLOBAIS
//--------------------------------------------------------
Componente mochila[MAX];
int numItens = 0;

// Para análise de desempenho
long comparacoes = 0;

//--------------------------------------------------------
// FUNÇÕES DE APOIO
//--------------------------------------------------------

// Remove newline ao usar fgets
void limparEnter(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

// Exibir todos os componentes
void mostrarComponentes(Componente v[], int n) {
    printf("\n===== MOCHILA ATUAL =====\n");
    for (int i = 0; i < n; i++) {
        printf("%2d. Nome: %-15s | Tipo: %-15s | Prioridade: %d\n",
               i+1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("===========================\n\n");
}

//--------------------------------------------------------
// ALGORITMOS DE ORDENAÇÃO
//--------------------------------------------------------

/*
 * Selection Sort — ordena por prioridade (maior para menor)
 */
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int max = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade > v[max].prioridade)
                max = j;
        }
        if (max != i) {
            Componente temp = v[i];
            v[i] = v[max];
            v[max] = temp;
        }
    }
}

/*
 * Insertion Sort — ordena por tipo (ordem alfabética)
 */
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        comparacoes++;
        v[j + 1] = chave;
    }
}

/*
 * Bubble Sort — ordena por nome
 */
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    int trocou = 1;

    while (trocou) {
        trocou = 0;

        for (int i = 0; i < n - 1; i++) {
            comparacoes++;
            if (strcmp(v[i].nome, v[i + 1].nome) > 0) {
                Componente temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                trocou = 1;
            }
        }
    }
}

//--------------------------------------------------------
// BUSCA BINÁRIA (somente se vetor estiver ordenado por nome)
//--------------------------------------------------------
int buscaBinariaPorNome(Componente v[], int n, char nome[]) {
    comparacoes = 0;

    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;

        int cmp = strcmp(nome, v[meio].nome);

        if (cmp == 0)
            return meio;

        if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

//--------------------------------------------------------
// FUNÇÃO PARA MEDIR TEMPO DE ALGORITMOS
//--------------------------------------------------------
void medirTempo(void (*algoritmo)(Componente[], int),
                Componente v[], int n,
                const char *nomeAlgoritmo) {

    // Criar cópia para não modificar o vetor original
    Componente copia[MAX];
    memcpy(copia, v, sizeof(Componente) * n);

    clock_t inicio = clock();

    algoritmo(copia, n);

    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Algoritmo: %s\n", nomeAlgoritmo);
    printf("Comparações: %ld\n", comparacoes);
    printf("Tempo: %.6f segundos\n", tempo);

    mostrarComponentes(copia, n);
}

//--------------------------------------------------------
// INSERIR COMPONENTE
//--------------------------------------------------------
void inserirComponente() {
    if (numItens >= MAX) {
        printf("Mochila cheia!\n");
        return;
    }

    Componente c;

    printf("Nome: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    limparEnter(c.nome);

    printf("Tipo: ");
    fgets(c.tipo, sizeof(c.tipo), stdin);
    limparEnter(c.tipo);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &c.prioridade);
    getchar(); // limpar buffer

    mochila[numItens++] = c;

    printf("Componente inserido!\n\n");
}

//--------------------------------------------------------
// MENU PRINCIPAL
//--------------------------------------------------------
int main() {
    int op;

    do {
        printf("========== MENU MESTRE ==========\n");
        printf("1. Inserir componente\n");
        printf("2. Mostrar mochila\n");
        printf("3. Ordenar por prioridade (Selection Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por nome (Bubble Sort)\n");
        printf("6. Busca binária por nome\n");
        printf("7. Comparar algoritmos (tempo + comparações)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar(); // limpar ENTER
        printf("\n");

        char nome[40];

        switch (op) {
        case 1:
            inserirComponente();
            break;

        case 2:
            mostrarComponentes(mochila, numItens);
            break;

        case 3:
            selectionSortPrioridade(mochila, numItens);
            printf("Ordenado por prioridade!\n");
            mostrarComponentes(mochila, numItens);
            break;

        case 4:
            insertionSortTipo(mochila, numItens);
            printf("Ordenado por tipo!\n");
            mostrarComponentes(mochila, numItens);
            break;

        case 5:
            bubbleSortNome(mochila, numItens);
            printf("Ordenado por nome!\n");
            mostrarComponentes(mochila, numItens);
            break;

        case 6:
            printf("Digite o nome para buscar: ");
            fgets(nome, sizeof(nome), stdin);
            limparEnter(nome);

            bubbleSortNome(mochila, numItens); // garantir ordem
            int pos;
            pos = buscaBinariaPorNome(mochila, numItens, nome);

            if (pos >= 0) {
                printf("\nEncontrado na posição %d!\n", pos + 1);
                printf("Comparações: %ld\n", comparacoes);
            } else {
                printf("\nComponente não encontrado!\n");
            }
            break;

        case 7:
            printf("========== COMPARAÇÃO DE ALGORITMOS ==========\n\n");

            medirTempo(selectionSortPrioridade, mochila, numItens,
                       "Selection Sort (prioridade)");

            medirTempo(insertionSortTipo, mochila, numItens,
                       "Insertion Sort (tipo)");

            medirTempo(bubbleSortNome, mochila, numItens,
                       "Bubble Sort (nome)");
            break;
        }

    } while (op != 0);

    printf("Saindo...\n");
    return 0;
}
