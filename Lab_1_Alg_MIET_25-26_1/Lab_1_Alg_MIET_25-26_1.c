#include <stdio.h>

int* num_arr_fill(int N, int num_cnt, int* num_arr) {
	while (num_cnt < N) {
		num_arr[num_cnt] = num_cnt;
		num_cnt++;
	}
	return *num_arr;
}

int simp_num_check(int N, int num_cnt, int* num_arr) {
	int local_num_cnt = 0;
	while (1) {
		num_arr[local_num_cnt]
	}
}
int simp_num_fill(int N, int num_cnt, int* num_arr, int* simp_arr) {
	int simp_num = 2;
	while (num_cnt < N) {
		simp_arr[num_cnt] = simp_num;
		while (1) {
		if (num_arr[num_cnt]
		}
	}
}
int main() {
	int* num_arr = NULL, *simp_arr = NULL, num_cnt = 0, N;
	while (1) {
		scanf_s("%d", &N);
		num_arr = (int)malloc(N * sizeof(int));
	}
}
