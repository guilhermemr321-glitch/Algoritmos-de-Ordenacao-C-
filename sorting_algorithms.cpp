#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Funções Auxiliares ---

void printArray(int arr[], int size) {
    // Imprime apenas os primeiros 20 elementos para não poluir a tela
    int limit = size < 20 ? size : 20;
    printf("[ ");
    for (int i = 0; i < limit; i++) {
        printf("%d ", arr[i]);
    }
    if (size > 20) printf("... ");
    printf("]\n");
}

// Copia o array original para um temporário (para o teste ser justo)
void copyArray(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

// Gera números aleatórios entre 0 e 9999
void generateRandomData(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
}

// --- Algoritmos de Ordenação ---

// 1. Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 2. Selection Sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// 3. Insertion Sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 4. Merge Sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Alocação dinâmica para evitar estouro de pilha em arrays grandes
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void callMergeSort(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

// 5. Quick Sort
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void callQuickSort(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

// 6. Shell Sort
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// --- Execução e Medição ---

void executeAndMeasure(void (*sortFunc)(int[], int), int arr[], int n, const char* name) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    sortFunc(arr, n);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("| %-15s | %f s |\n", name, cpu_time_used);
}

int main() {
    srand(time(NULL));
    int size = 20000; // Tamanho padrão bom para notar diferença
    int choice;
    int *originalArray = NULL;
    int *testArray = NULL;

    // Alocação inicial
    originalArray = (int*)malloc(size * sizeof(int));
    testArray = (int*)malloc(size * sizeof(int));
    generateRandomData(originalArray, size);

    do {
        printf("\n========================================\n");
        printf("    COMPARADOR DE ALGORITMOS (Kael)     \n");
        printf("    Elementos no Array: %d              \n", size);
        printf("========================================\n");
        printf("1. Testar TODOS e comparar tempos\n");
        printf("2. Mudar tamanho do Array\n");
        printf("3. Ver array (amostra)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- RESULTADOS (Tempo em Segundos) ---\n");
                printf("--------------------------------------\n");
                
                // Bubble Sort
                copyArray(originalArray, testArray, size);
                executeAndMeasure(bubbleSort, testArray, size, "Bubble Sort");

                // Selection Sort
                copyArray(originalArray, testArray, size);
                executeAndMeasure(selectionSort, testArray, size, "Selection Sort");

                // Insertion Sort
                copyArray(originalArray, testArray, size);
                executeAndMeasure(insertionSort, testArray, size, "Insertion Sort");

                // Shell Sort
                copyArray(originalArray, testArray, size);
                executeAndMeasure(shellSort, testArray, size, "Shell Sort");

                // Merge Sort
                copyArray(originalArray, testArray, size);
                executeAndMeasure(callMergeSort, testArray, size, "Merge Sort");

                // Quick Sort
                copyArray(originalArray, testArray, size);
                executeAndMeasure(callQuickSort, testArray, size, "Quick Sort");
                
                printf("--------------------------------------\n");
                break;

            case 2:
                printf("Novo tamanho (Ex: 10000, 50000): ");
                scanf("%d", &size);
                free(originalArray);
                free(testArray);
                originalArray = (int*)malloc(size * sizeof(int));
                testArray = (int*)malloc(size * sizeof(int));
                generateRandomData(originalArray, size);
                printf("Novo array gerado!\n");
                break;

            case 3:
                printf("Amostra do array atual: ");
                printArray(originalArray, size);
                break;

            case 0:
                printf("Saindo...\n");
                break;
        }
    } while (choice != 0);

    free(originalArray);
    free(testArray);
    return 0;
}