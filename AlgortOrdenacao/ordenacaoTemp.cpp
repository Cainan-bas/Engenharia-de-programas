#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// FunÃ§Ãµes para gerar vetores
void gerarVetorAleatorio(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = rand() % 10000;
    }
}

void gerarVetorCrescente(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = i;
    }
}

void gerarVetorDecrescente(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = tamanho - i;
    }
}

// Bubble Sort com contador de trocas
void ordenarBolha(int* vetor, int tamanho, int* trocas) {
    *trocas = 0;
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = 0; j < tamanho - i - 1; ++j) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*trocas)++;
            }
        }
    }
}

// Insertion Sort com contador de trocas
void ordenarInsercao(int* vetor, int tamanho, int* trocas) {
    *trocas = 0;
    for (int i = 1; i < tamanho; ++i) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
            (*trocas)++;
        }
        vetor[j + 1] = chave;
        if (j + 1 != i) (*trocas)++; // conta a troca final
    }
}

// Selection Sort com contador de trocas
void ordenarSelecao(int* vetor, int tamanho, int* trocas) {
    *trocas = 0;
    for (int i = 0; i < tamanho - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < tamanho; ++j) {
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = vetor[i];
            vetor[i] = vetor[min_idx];
            vetor[min_idx] = temp;
            (*trocas)++;
        }
    }
}

void merge(int* vetor, int inicio, int meio, int fim, int* trocas) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int* esq = (int*)malloc(n1 * sizeof(int));
    int* dir = (int*)malloc(n2 * sizeof(int));

    // Copia os dados para vetores auxiliares e conta como troca
    for (int i = 0; i < n1; i++) {
        esq[i] = vetor[inicio + i];
        (*trocas)++;
    }
    for (int j = 0; j < n2; j++) {
        dir[j] = vetor[meio + 1 + j];
        (*trocas)++;
    }

    int i = 0, j = 0, k = inicio;

    // Merge dos vetores auxiliares de volta ao vetor original
    while (i < n1 && j < n2) {
        if (esq[i] <= dir[j]) {
            vetor[k] = esq[i];
            i++;
        } else {
            vetor[k] = dir[j];
            j++;
        }
        (*trocas)++;  // movimentaÃ§Ã£o de dado para o vetor original
        k++;
    }

    // Copia os elementos restantes de esq[] (se houver)
    while (i < n1) {
        vetor[k] = esq[i];
        i++;
        k++;
        (*trocas)++;
    }

    // Copia os elementos restantes de dir[] (se houver)
    while (j < n2) {
        vetor[k] = dir[j];
        j++;
        k++;
        (*trocas)++;
    }

    free(esq);
    free(dir);
}

void mergeSortTrocas(int* vetor, int inicio, int fim, int* trocas) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSortTrocas(vetor, inicio, meio, trocas);
        mergeSortTrocas(vetor, meio + 1, fim, trocas);
        merge(vetor, inicio, meio, fim, trocas);
    }
}

void ordenarMerge(int* vetor, int tamanho, int* trocas) {
    *trocas = 0;
    mergeSortTrocas(vetor, 0, tamanho - 1, trocas);
}

// Quick Sort com contador de trocas
int particionar(int* vetor, int inicio, int fim, int* trocas) {
    int pivo = vetor[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (vetor[j] < pivo) {
            i++;
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            (*trocas)++;
        }
    }
    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = temp;
    (*trocas)++;
    return i + 1;
}

void quickSort(int* vetor, int inicio, int fim, int* trocas) {
    if (inicio < fim) {
        int pi = particionar(vetor, inicio, fim, trocas);
        quickSort(vetor, inicio, pi - 1, trocas);
        quickSort(vetor, pi + 1, fim, trocas);
    }
}

void ordenarQuick(int* vetor, int tamanho, int* trocas) {
    *trocas = 0;
    quickSort(vetor, 0, tamanho - 1, trocas);
}

// Medir tempo e contar trocas
double medirTempoOrdenacao(void (*funcOrdenacao)(int*, int, int*), int* vetor, int tamanho, int* trocas) {
    clock_t inicio = clock();
    funcOrdenacao(vetor, tamanho, trocas);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

void copiarVetor(int* origem, int* destino, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        destino[i] = origem[i];
    }
}

int main() {
    srand(time(NULL));

    int tamanhos[] = {100, 1000, 10000, 100000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    const char* nomesAlgoritmos[] = {
        "Bubble", "Insertion", "Selection", "Merge", "Quick"
    };
    void (*funcoesOrdenacao[])(int*, int, int*) = {
        ordenarBolha, ordenarInsercao, ordenarSelecao, ordenarMerge, ordenarQuick
    };
    int numAlgoritmos = sizeof(funcoesOrdenacao) / sizeof(funcoesOrdenacao[0]);

    printf("Tamanho\tCaso\t\tAlgoritmo\tTempo (s)\tTrocas\n");
    printf("---------------------------------------------------------------\n");

    for (int t = 0; t < numTamanhos; ++t) {
        int tamanho = tamanhos[t];
        int* base = (int*)malloc(tamanho * sizeof(int));
        int* copia = (int*)malloc(tamanho * sizeof(int));

        void (*geradores[])(int*, int) = {
            gerarVetorAleatorio, gerarVetorCrescente, gerarVetorDecrescente
        };
        const char* nomesCasos[] = {"Aleatorio", "Crescente", "Decrescente"};

        for (int c = 0; c < 3; ++c) {
            geradores[c](base, tamanho);

            for (int a = 0; a < numAlgoritmos; ++a) {
                copiarVetor(base, copia, tamanho);
                int trocas = 0;
                double tempo = medirTempoOrdenacao(funcoesOrdenacao[a], copia, tamanho, &trocas);
                printf("%d\t%-10s\t%-10s\t%.6f\t%d\n", tamanho, nomesCasos[c], nomesAlgoritmos[a], tempo, trocas);
            }
        }

        printf("---------------------------------------------------------------\n");

        free(base);
        free(copia);
    }

    return 0;
}