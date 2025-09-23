#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 함수 프로토타입 선언
void Menu();
void all_stock(int n, int in_stock[]);
void all_sold(int n, int sold[]);
void R_stock(int* inventory, int n);
double total_sold(int n, int* sold);
void percent_total(int total_t, int n, int* in_stock);
void lack(int* inventory, int n);

int main(void) {
    int n = 0;
    int in_stock[101] = {0,};
    int sold[101] = {0,};
    int inventory[101] = {0,};
    int id;
    int a, i;
    char ch;

    printf("상품 갯수를 입력하세요 (1~100): ");
    scanf("%d", &n);
    if (n <= 0 || n > 100) {
        printf("잘못된 상품 개수입니다. 프로그램을 종료합니다.\n");
        return 1;
    }

    while (1) {
        Menu();
        scanf(" %c", &ch);

        if (ch == '4') {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        switch (ch) {
        case '1': // 입고 메뉴
            printf("입고수량 입력 : 전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택\n");
            char menu_1;
            scanf(" %c", &menu_1);

            if (menu_1 == '1') {
                all_stock(n, in_stock);
            } else if (menu_1 == '2') {
                printf("상품ID : ");
                scanf("%d", &i);
                if (i > 0 && i <= n) {
                    printf("입고수량 : ");
                    scanf("%d", &a);
                    in_stock[i - 1] += a;
                } else {
                    printf("잘못된 상품 ID입니다.\n");
                }
            } else {
                printf("잘못된 메뉴 선택입니다.\n");
            }
            break;

        case '2': // 판매 메뉴
            printf("판매수량 입력 : 전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택\n");
            char menu_2;
            scanf(" %c", &menu_2);

            if (menu_2 == '1') {
                all_sold(n, sold);
            } else if (menu_2 == '2') {
                printf("상품ID : ");
                scanf("%d", &i);
                if (i > 0 && i <= n) {
                    printf("판매수량 : ");
                    scanf("%d", &a);
                    sold[i - 1] += a;
                } else {
                    printf("잘못된 상품 ID입니다.\n");
                }
            } else {
                printf("잘못된 메뉴 선택입니다.\n");
            }
            break;

        case '3': // 상품 현황 메뉴
            for (int j = 0; j < n; j++) {
                inventory[j] = in_stock[j] - sold[j];
            }

            // 재고수량 출력
            printf("재고수량 : ");
            for (int k = 0; k < n; k++) {
                printf("%d ", inventory[k]);
            }
            printf("\n");

            // 총 판매량 및 판매율 출력
            int total_t = (int)total_sold(n, sold);
            percent_total(total_t, n, in_stock);

            // 가장 많이/적게 판매된 상품 찾기
            if (n > 0) {
                int max_sold_val = sold[0];
                int max_sold_id = 1;
                int min_sold_val = sold[0];
                int min_sold_id = 1;

                for (int j = 1; j < n; j++) {
                    if (sold[j] > max_sold_val) {
                        max_sold_val = sold[j];
                        max_sold_id = j + 1;
                    }
                    if (sold[j] < min_sold_val) {
                        min_sold_val = sold[j];
                        min_sold_id = j + 1;
                    }
                }
                printf("가장 많이 판매된 상품 : ID %d, 판매량 %d\n", max_sold_id, max_sold_val);
                printf("가장 적게 판매된 상품 : ID %d, 판매량 %d\n", min_sold_id, min_sold_val);
            }
            
            // 재고 부족 알림
            lack(inventory, n);
            break;

        default:
            printf("올바른 메뉴 값을 입력하세요.\n");
            break;
        }
    }
    return 0;
}

// (나머지 함수들은 이전과 동일합니다.)

void Menu() {
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("1. 입고 | 2. 판매 | 3. 상품 현황 | 4. 종료\n");
    printf("메뉴 선택: ");
}

void all_stock(int n, int in_stock[]) {
    printf("전체 상품의 입고수량을 입력 (띄어쓰기로 구분): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &in_stock[i]);
    }
}

void all_sold(int n, int sold[]) {
    printf("전체 상품의 판매수량을 입력 (띄어쓰기로 구분): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &sold[i]);
    }
}

void R_stock(int* inventory, int n) {
    // 이 함수는 더 이상 사용하지 않습니다.
}

double total_sold(int n, int* sold) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += sold[i];
    }
    return (double)sum;
}

void percent_total(int total_t, int n, int* in_stock) {
    int total_stock = 0;
    for (int i = 0; i < n; i++) {
        total_stock += in_stock[i];
    }
    if (total_stock == 0) {
        printf("총 판매량: %d (판매율: 0.00%%)\n", total_t);
        return;
    }
    double rate = ((double)total_t / total_stock) * 100;
    printf("총 판매량: %d (판매율 %.2f%%)\n", total_t, rate);
}

void lack(int* inventory, int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        if (inventory[i] < 3) {
            printf("상품 ID %d : 재고부족(%d)\n", i + 1, inventory[i]);
        }
    }
}
