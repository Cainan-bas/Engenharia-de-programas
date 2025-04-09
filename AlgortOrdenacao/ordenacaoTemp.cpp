#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar um vetor com números aleatórios
void gerarVetorAleatorio(int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = rand() % 1000; // Números aleatórios entre 0 e 999
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

// Função para imprimir um vetor
void imprimirVetor(const int* vetor, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    srand((unsigned)time(0)); // Semente para geração de números aleatórios

    // Vetores de tamanhos 10, 100 e 1000
    int vetor10[10], vetor100[100], vetor1000[1000];

    // Gerar números aleatórios para cada vetor
    gerarVetorAleatorio(vetor10, 10);
    gerarVetorAleatorio(vetor100, 100);
    gerarVetorAleatorio(vetor1000, 1000);

    // Ordenar e imprimir cada vetor com marcação de tempo
    printf("Vetor original (tamanho 10):\n");
    imprimirVetor(vetor10, 10);
    clock_t inicio = clock();
    ordenarBolha(vetor10, 10);
    clock_t fim = clock();
    printf("Vetor ordenado (tamanho 10):\n");
    imprimirVetor(vetor10, 10);
    printf("Tempo de ordenação (tamanho 10): %.6f segundos\n\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    printf("Vetor original (tamanho 100):\n");
    imprimirVetor(vetor100, 100);
    inicio = clock();
    ordenarBolha(vetor100, 100);
    fim = clock();
    printf("Vetor ordenado (tamanho 100):\n");
    imprimirVetor(vetor100, 100);
    printf("Tempo de ordenação (tamanho 100): %.6f segundos\n\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    printf("Vetor original (tamanho 1000):\n");
    imprimirVetor(vetor1000, 1000);
    inicio = clock();
    ordenarBolha(vetor1000, 1000);
    fim = clock();
    printf("Vetor ordenado (tamanho 1000):\n");
    imprimirVetor(vetor1000, 1000);
    printf("Tempo de ordenação (tamanho 1000): %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    return 0;
}
