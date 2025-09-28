#include <stdio.h>
#include <stdlib.h>

int num_match_check(int* num_arr_new, int* N) {
	int cur_num = 2, cur_check = 2, num_vol = 0;
	while (cur_num <= *N) {
		while (cur_check < cur_num) {
			if (cur_num % cur_check == 0 && cur_num % cur_check != cur_num) { break; }
			else { 
				num_arr_new = (int*)realloc(num_arr_new, sizeof(int) * (num_vol + 1)); 
				num_arr_new[num_vol] = cur_num;
				num_vol++;
			}
			cur_check++;
		}
		cur_num++;
	}
	return num_vol + 1;
}

int main() {
	int N = 1, num_arr_old_len = 0, num_arr_new_len = 0, cur_num_ind = 0;
	int* num_arr_old = (int*)malloc(sizeof(int)), * num_arr_new = (int*)malloc(sizeof(int));
	while(N){
		N = 1;
		printf("Enter the limit: ");
		scanf_s("%d", &N);
		printf("\n");
		if (N == 0) { return 0; }
		num_arr_new_len = num_match_check(num_arr_new, &N);
		num_arr_old = (int*)realloc(num_arr_old, sizeof(int) * num_arr_new_len);
		while (cur_num_ind < num_arr_new_len) {
			if (num_arr_new[cur_num_ind] == num_arr_old[cur_num_ind]) {
				printf("%d  ", num_arr_new[cur_num_ind]);
			}
			else {
				printf("%d  ", num_arr_new[cur_num_ind]);
			}
			cur_num_ind++;
		}
		if (num_arr_new_len > num_arr_old_len) {
			while (cur_num_ind < num_arr_new_len) {
				printf("%d  ", num_arr_new[cur_num_ind]);
				num_arr_old[cur_num_ind] = num_arr_new[cur_num_ind];
				cur_num_ind++;
			}
			num_arr_old_len = num_arr_new_len;
		}
		cur_num_ind = 0;
		printf("\n");
		printf("Press any key to restart: ");
		scanf_s("%d", &N);
		printf("\n");
	}
	free(num_arr_old);
	free(num_arr_new);
	return 0;
}
