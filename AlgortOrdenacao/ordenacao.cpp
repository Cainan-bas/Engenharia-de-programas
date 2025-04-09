#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarVetorAleatorio(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = rand() % 1000;
    }
}

void gerarVetorCrescente(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = i;
    }
}

void gerarVetorDecrescente(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = tamanho - i - 1;
    }
}

// Implementação do Bubble Sort
void ordenarBolha(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = 0; j < tamanho - i - 1; ++j) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void imprimirVetor(const int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

// Função para medir o tempo de execução de uma ordenação
double medirTempoOrdenacao(void (*funcOrdenacao)(int*, int), int* vetor, int tamanho) {
    clock_t inicio = clock();
    funcOrdenacao(vetor, tamanho);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

int main() {
    int tamanhos[] = {100, 1000, 10000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("Tamanho\tCaso\t\tTempo (s)\n");
    printf("-------------------------------------\n");

    for (int t = 0; t < numTamanhos; ++t) {
        int tamanho = tamanhos[t];
        int* vetor = (int*)malloc(tamanho * sizeof(int));

        // Caso aleatório
        gerarVetorAleatorio(vetor, tamanho);
        printf("%d\tAleatorio\t%.6f\n", tamanho, medirTempoOrdenacao(ordenarBolha, vetor, tamanho));

        // Caso crescente
        gerarVetorCrescente(vetor, tamanho);
        printf("%d\tCrescente\t%.6f\n", tamanho, medirTempoOrdenacao(ordenarBolha, vetor, tamanho));

        // Caso decrescente
        gerarVetorDecrescente(vetor, tamanho);
        printf("%d\tDecrescente\t%.6f\n", tamanho, medirTempoOrdenacao(ordenarBolha, vetor, tamanho));

        printf("-------------------------------------\n");

        free(vetor);
    }

    return 0;
}