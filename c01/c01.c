#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
//#pragma warning(disable:6031)
#include <stdio.h>						
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int main(void)
{
	//���� ����
	int n[SIZE];
	int total = 0;
	int max, min;
	double avg = 0.0;

	//���� ���� ����
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		n[i] = rand() % 101;			//(rand() % 100)+1;	
	}

	//���� ���ϱ�
	for (int i = 0; i < SIZE; i++) {
		total += n[i];
	}

	//���
	for (int i = 0; i < SIZE; i++) {
		printf("%3d\t", n[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}

	//��� ���ϱ�
	avg = (double)total / SIZE;


	//�ִ� �ּ� ���ϱ�
	max = 0;
	min = 0;
	for (int i = 1; i < SIZE; i++) {
		if (n[max] < n[i]) max = i;
		if (n[min] > n[i]) min = i;
	}
	printf("avg = %.1f \n max = %d \n min = %d", avg, n[max], n[min]);
	
	//�������� Selection Sort 



		
	return 0;
}

