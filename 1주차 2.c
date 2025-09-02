#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>						
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int main(void)
{
	//변수 선언
	int n[SIZE];
  
	//랜덤 난수 생성
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		n[i] = rand() % 101;			//(rand() % 100)+1;	
	}
  
	//출력
	for (int i = 0; i < SIZE; i++) {
		printf("%3d\t", n[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}
	return 0;
}
