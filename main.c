#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Protótipos das Funções ---
void swap(int* a, int* b);
void generate_random_array(int* arr, int size);
int int_compare(const void* a, const void* b);

// Algoritmo 1: Ordenação Completa
int find_kth_by_sorting(int* arr, int size, int k);

// Algoritmo 2: Seleção Parcial
int find_kth_by_partial_selection(int* arr, int size, int k);

// Algoritmo 3: Quickselect
int quickselect_partition(int* arr, int low, int high);
int find_kth_by_quickselect(int* arr, int size, int k);
int quickselect_recursive(int* arr, int low, int high, int k);


// --- Função Principal ---
int main() {
    // Parâmetros do experimento A SER MODIFICADOO
    int ARRAY_SIZE = 20000;
    int K_ELEMENT = ARRAY_SIZE / 2; // Encontra mediana

    printf("Buscando o %d-ésimo menor elemento em um vetor de %d posições.\n\n", K_ELEMENT, ARRAY_SIZE);

    // Aloca de 3 vetores idênticos pra fazer um teste justo
    int* arr1 = malloc(ARRAY_SIZE * sizeof(int));
    int* arr2 = malloc(ARRAY_SIZE * sizeof(int));
    int* arr3 = malloc(ARRAY_SIZE * sizeof(int));

    if (!arr1 || !arr2 || !arr3) {
        printf("Falha na alocação de memória!\n");
        return 1;
    }

    generate_random_array(arr1, ARRAY_SIZE);

    for(int i = 0; i < ARRAY_SIZE; i++) {
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
    
    clock_t start, end;
    double elapsed_time;
    int result;

    // --- Teste do Algoritmo 1 ---
    printf("--- Algoritmo 1: Ordenação Completa (qsort) - O(N log N) ---\n");
    start = clock();
    result = find_kth_by_sorting(arr1, ARRAY_SIZE, K_ELEMENT);
    end = clock();
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Resultado: %d\n", result);
    printf("Tempo de execução: %f segundos\n\n", elapsed_time);

    // --- Teste do Algoritmo 2 ---
    printf("--- Algoritmo 2: Seleção Parcial - O(k*N) ---\n");
    start = clock();
    result = find_kth_by_partial_selection(arr2, ARRAY_SIZE, K_ELEMENT);
    end = clock();
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Resultado: %d\n", result);
    printf("Tempo de execução: %f segundos\n\n", elapsed_time);

    // --- Teste do Algoritmo 3 ---
    printf("--- Algoritmo 3: Quickselect - O(N) em média ---\n");
    start = clock();
    result = find_kth_by_quickselect(arr3, ARRAY_SIZE, K_ELEMENT);
    end = clock();
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Resultado: %d\n", result);
    printf("Tempo de execução: %f segundos\n\n", elapsed_time);

    // Liberação da memória
    free(arr1);
    free(arr2);
    free(arr3);

    return 0;
}

// --- Implementações ---

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void generate_random_array(int* arr, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

int int_compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Algoritmo 1
int find_kth_by_sorting(int* arr, int size, int k) {
    if (k < 0 || k >= size) return -1;
    qsort(arr, size, sizeof(int), int_compare);
    return arr[k];
}

// Algoritmo 2
int find_kth_by_partial_selection(int* arr, int size, int k) {
    if (k < 0 || k >= size) return -1;
    // Repete k+1 vezes para encontrar o (k+1)-ésimo menor
    for (int i = 0; i <= k; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[i], &arr[min_idx]);
    }
    return arr[k];
}

// Algoritmo 3
int find_kth_by_quickselect(int* arr, int size, int k) {
    if (k < 0 || k >= size) return -1;
    return quickselect_recursive(arr, 0, size - 1, k);
}

int quickselect_recursive(int* arr, int low, int high, int k) {
    while (low <= high) {
        if (low == high) {
            return arr[low];
        }
        int pivot_index = quickselect_partition(arr, low, high);
        if (k == pivot_index) {
            return arr[k];
        } else if (k < pivot_index) {
            high = pivot_index - 1;
        } else {
            low = pivot_index + 1;
        }
    }
    return -1; // Não deve acontecer
}

int quickselect_partition(int* arr, int low, int high) {
    // Pivô simples (último elemento)
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}
