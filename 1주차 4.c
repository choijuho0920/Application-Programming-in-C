#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>						
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int main(void)
{
	//변수 선언
	int n[SIZE];
	int most;
	int temp = 0;
	//랜덤 난수 생성
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		n[i] = rand() % 10001;			//(rand() % 100)+1;	
	}
	//선택정렬 Selection Sort 
	for (int i = 0; i < SIZE - 1; i++) {
		most = i;
		for (int j = i + 1; j < SIZE; j++) {
			if (n[most] < n[j]) most = j;
			temp = n[i];
			n[i] = n[most];
			n[most] = temp;
		}
	}

	//출력
	for (int i = 0; i < SIZE; i++) {
		printf("%5d\t", n[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}

	return 0;
}

