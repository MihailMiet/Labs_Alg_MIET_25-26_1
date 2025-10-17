#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void find_primes(int N, int** num_arr, int* count) {
    int probe_num;
    int found_count = 0;
    
    for (int i = 0; i < *count && found_count < N; i++) {
        printf("x| %d\n", (*num_arr)[i]);
        found_count++;
    }
    
    int start = (*count > 0) ? (*num_arr)[*count - 1] + 1 : 2;
    
    for (int i = start; found_count < N; i++) {
        int is_prime = 1;
        for (probe_num = 2; probe_num * probe_num <= i; probe_num++) {
            if (i % probe_num == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
           printf(" | %d\n", i);
           (*num_arr)[*count] = i;
           (*count)++;
           found_count++;
        }
    }
}

int main() {
    int N = 0, * num_arr = NULL, count = 0, size = 10;
    num_arr = (int*)malloc(size * sizeof(int));
    if (!num_arr) {
        perror("Memory allocation failed\n");
        return 1;
    }
    printf("Enter the needed volume (0 to exit): ");
    scanf("%d", &N);
    printf("\n");
    while (N) {
        system("clear");
        int start_time = clock();
        if (N > size) {
            size = (N) * 2;
            int* temp = (int*)realloc(num_arr, size * sizeof(int));
            if (!temp) {
                perror("Memory allocation failed\n");
                free(num_arr);
                return 1;
            }
            num_arr = temp;
        }
        find_primes(N, &num_arr, &count);
        int elapsed_time = clock() - start_time;
        printf("\n\nTime: %.10f s\n", (float)elapsed_time / CLOCKS_PER_SEC);
        printf("\nEnter the needed volume (0 to exit): ");
        scanf("%d", &N);
        printf("\n");
    }
    free(num_arr);
    return 0;
}
