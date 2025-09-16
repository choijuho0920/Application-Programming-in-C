#define _CRT_SECURE_NO_WARNINGS //#pragma warning(disable:4996)
#pragma warning(disable:6031)
#include <stdio.h>
double totalP(int n, int* sold);


int main(void) {
    int n;  // 상품 개수5
    
    int in_stock[101], sold[101];  // 입고 수량, 판매 수량 (문자열로 받음)
    int inventory[101];  // 최종 재고
    int id;

    // 1. 상품 개수 입력
    printf("상품 갯수를 입력:");
    scanf("%d", &n);
    if (n > 101 || n <0) {
        printf("1~100 사이의 수를 입력해주세요");
        
        return 0;
    }

    printf("입고 수량 입력: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &in_stock[i]);
    }

    printf("판매 수량 입력: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &sold[i]);
    }

    // 4. 재고 계산
    for (int i = 0; i < n; i++) {
        inventory[i] = in_stock[i] - sold[i];
    }


    // 5. 확인할 상품 ID 입력
    printf("확인할 상품 ID 입력:");
    scanf("%d", &id);

    // 6. 해당 상품 재고 출력
    if (id >= 1 && id <= n) {
        printf("%d의 남은 재고는 %d개 입니다.\n", id, inventory[id - 1]);


        // 7. 전체 상품 재고 출력 (띄어쓰기 없이 이어붙임)
        printf("전체 남은 재고는 ");
        for (int i = 0; i < n; i++) {
            printf("%d", inventory[i]);
            if (i < n - 1) {
                printf(" ");  // 마지막 숫자 뒤에는 공백 안 넣음
            }
        }
        printf(" 개 입니다.");
        int total_t = totalP(n, sold);
        int total_stock = 0;
        for (int i = 0; i < n; i++) {
            total_stock += in_stock[i];
        }
        double rate = ((double)total_t / total_stock) * 100;
        printf("총 판매량: %d (판매율: %.2f%%)\n", total_t, rate);


        printf("\n");


        //재고 부족 알림
        for (int i = 0; i < n; i++) {
            if (inventory[i] < 3) {
                printf("상품ID : %d 재고부족(%d)", i, inventory[i]);
            }
        }
        
    }
    else {
        printf("잘못된 상품 ID입니다. 1부터 %d 사이로 입력하세요.\n", n);
    }
    return 0;
}


double totalP(int n, int* sold) {
    int Sum = 0;
    for (int i = 0; i < n; i++) {
        Sum += sold[i];
    }
    return (double)Sum;
}

