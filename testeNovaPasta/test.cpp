#include <stdlib.h>
#include <stdio.h>

int main() {
    int tamanho = 1000; // Tamanho do vetor
    int* vetor = (int*)malloc(tamanho * sizeof(int)); // Alocação de memória para o vetor

    // Verifica se a alocação foi bem-sucedida
    if (vetor == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Preenche o vetor com números aleatórios
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = rand() % 1000; // Números aleatórios entre 0 e 999
    }

    // Libera a memória alocada
    free(vetor);

    return 0;
}	