#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>						
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int main(void)
{
	//변수 선언
	int n[SIZE];
	int total = 0;
	int max, min;
	double avg = 0.0;

	//랜덤 난수 생성
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		n[i] = rand() % 101;			//(rand() % 100)+1;	
	}

	//총합 구하기
	for (int i = 0; i < SIZE; i++) {
		total += n[i];
	}

	//출력
	for (int i = 0; i < SIZE; i++) {
		printf("%3d\t", n[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}

	//평균 구하기
	avg = (double)total / SIZE;

	//최대 최소 구하기
	max = 0;
	min = 0;
	for (int i = 1; i < SIZE; i++) {
		if (n[max] < n[i]) max = i;
		if (n[min] > n[i]) min = i;
	}
	printf("avg = %.1f \n max = %d \n min = %d", avg, n[max], n[min]);

	return 0;
}

