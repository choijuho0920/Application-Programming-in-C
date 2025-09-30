#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include <stdio.h>
#include <string.h> // ✨ 추가: 문자열 처리 함수를 위해 필수
#include <ctype.h>  // 추가: 입력 유효성 검사를 위해 (선택적이지만 좋음)

// 최대 상품명 길이 정의
#define MAX_NAME_LEN 50 

// 함수 프로토타입 선언
void Menu();
void all_stock(int n, int in_stock[]);
void all_sold(int n, int sold[]);
// R_stock 함수는 사용되지 않으므로 제거했습니다.
double total_sold(int n, int* sold);
void percent_total(int total_t, int n, int* in_stock);
// ✨ 수정: lack 함수의 프로토타입에 names 인자 추가
void lack(int* inventory, int n, char names[][MAX_NAME_LEN]);
void change_name(int n, char names[][MAX_NAME_LEN]);
void print_status(int n, int* in_stock, int* sold, int* inventory, char names[][MAX_NAME_LEN]);

// 입력 버퍼를 비우는 헬퍼 함수
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    int n = 0;
    // 배열 크기는 최대 100개 상품에 맞게 100으로 줄여도 되지만,
    // 원본처럼 101을 유지하여 1-based ID와 0-based index의 혼동을 줄일 수 있습니다.
    int in_stock[101] = { 0, };
    int sold[101] = { 0, };
    int inventory[101] = { 0, };
    char names[101][MAX_NAME_LEN];
    int a, i;
    char ch;

    printf("상품 갯수를 입력하세요 (1~100): ");
    if (scanf("%d", &n) != 1) {
        printf("잘못된 입력 형식입니다. 프로그램을 종료합니다.\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer(); // 초기 입력 후 버퍼 비우기

    if (n <= 0 || n > 100) {
        printf("잘못된 상품 개수입니다. 프로그램을 종료합니다.\n");
        return 1;
    }

    // 상품명 자동 할당 (예: 상품1, 상품2, ...)
    for (i = 0; i < n; i++) {
        sprintf(names[i], "상품%d", i + 1);
    }

    while (1) {
        Menu();
        // 메뉴 선택 시 앞 공백을 이용해 잔여 공백 문자 무시
        if (scanf(" %c", &ch) != 1) {
            printf("메뉴 입력에 실패했습니다. 다시 시도해 주세요.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer(); // 메뉴 선택 후 버퍼 비우기

        if (ch == '5') { // 종료 메뉴는 '5'번
            printf("프로그램을 종료합니다.\n");
            break;
        }

        switch (ch) {
        case '1': // 입고 메뉴
            printf("입고수량 입력 : 전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택\n");
            char menu_1;
            if (scanf(" %c", &menu_1) != 1) {
                printf("메뉴 입력에 실패했습니다. 이전 메뉴로 돌아갑니다.\n");
                clear_input_buffer();
                break;
            }
            clear_input_buffer();

            if (menu_1 == '1') {
                all_stock(n, in_stock);
            }
            else if (menu_1 == '2') {
                printf("상품ID : ");
                if (scanf("%d", &i) != 1) {
                    printf("잘못된 입력 형식입니다.\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();

                if (i > 0 && i <= n) {
                    printf("%s 상품의 입고수량 : ", names[i - 1]);
                    if (scanf("%d", &a) != 1) {
                        printf("잘못된 입력 형식입니다.\n");
                        clear_input_buffer();
                        break;
                    }
                    in_stock[i - 1] += a;
                }
                else {
                    printf("잘못된 상품 ID입니다.\n");
                }
                clear_input_buffer(); // 개별 수량 입력 후 버퍼 비우기
            }
            else {
                printf("잘못된 메뉴 선택입니다.\n");
            }
            break;

        case '2': // 판매 메뉴 (입고 메뉴와 동일하게 버퍼 처리 적용)
            printf("판매수량 입력 : 전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택\n");
            char menu_2;
            if (scanf(" %c", &menu_2) != 1) {
                printf("메뉴 입력에 실패했습니다. 이전 메뉴로 돌아갑니다.\n");
                clear_input_buffer();
                break;
            }
            clear_input_buffer();

            if (menu_2 == '1') {
                all_sold(n, sold);
            }
            else if (menu_2 == '2') {
                printf("상품ID : ");
                if (scanf("%d", &i) != 1) {
                    printf("잘못된 입력 형식입니다.\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();

                if (i > 0 && i <= n) {
                    printf("%s 상품의 판매수량 : ", names[i - 1]);
                    if (scanf("%d", &a) != 1) {
                        printf("잘못된 입력 형식입니다.\n");
                        clear_input_buffer();
                        break;
                    }
                    sold[i - 1] += a;
                }
                else {
                    printf("잘못된 상품 ID입니다.\n");
                }
                clear_input_buffer(); // 개별 수량 입력 후 버퍼 비우기
            }
            else {
                printf("잘못된 메뉴 선택입니다.\n");
            }
            break;

        case '3': // 상품 현황 메뉴
            for (int j = 0; j < n; j++) {
                inventory[j] = in_stock[j] - sold[j];
            }
            print_status(n, in_stock, sold, inventory, names);
            break;

        case '4': // 상품명 수정 메뉴
            change_name(n, names);
            break;

        default:
            printf("올바른 메뉴 값을 입력하세요.\n");
            break;
        }
    }
    return 0;
}

// =========================================================================

void Menu() {
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("1. 입고 | 2. 판매 | 3. 상품 현황 | 4. 상품명 수정 | 5. 종료\n");
    printf("메뉴 선택: ");
}

void all_stock(int n, int in_stock[]) {
    printf("전체 상품 %d개의 입고수량을 입력 (띄어쓰기로 구분): ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &in_stock[i]) != 1) {
            printf("\n입력 형식 오류 또는 상품 개수 미달로 입력을 중단합니다.\n");
            clear_input_buffer();
            return;
        }
    }
    clear_input_buffer(); // 전체 입력 후 버퍼 비우기
}

void all_sold(int n, int sold[]) {
    printf("전체 상품 %d개의 판매수량을 입력 (띄어쓰기로 구분): ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &sold[i]) != 1) {
            printf("\n입력 형식 오류 또는 상품 개수 미달로 입력을 중단합니다.\n");
            clear_input_buffer();
            return;
        }
    }
    clear_input_buffer(); // 전체 입력 후 버퍼 비우기
}

// R_stock 함수는 삭제되었습니다.

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

// 재고 부족 알림 함수
void lack(int* inventory, int n, char names[][MAX_NAME_LEN]) {
    printf("\n--- 재고 부족 알림 ---\n");
    int found_lack = 0;
    for (int i = 0; i < n; i++) {
        if (inventory[i] < 3) {
            printf("상품 ID %d (%s) : 재고부족(%d)\n", i + 1, names[i], inventory[i]);
            found_lack = 1;
        }
    }
    if (!found_lack) {
        printf("모든 상품의 재고가 충분합니다.\n");
    }
    printf("--------------------\n");
}

// 상품명 수정 함수 (공백 포함 이름 입력 가능하도록 수정)
void change_name(int n, char names[][MAX_NAME_LEN]) {
    int id;
    char new_name[MAX_NAME_LEN];

    printf("\n--- 상품명 수정 ---\n");
    printf("현재 상품 목록:\n");
    for (int i = 0; i < n; i++) {
        printf("ID %d: %s\n", i + 1, names[i]);
    }

    printf("수정할 상품 ID를 입력하세요 (1~%d): ", n);
    if (scanf("%d", &id) != 1) {
        printf("잘못된 입력 형식입니다.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer(); // ID 입력 후 버퍼 비우기

    if (id > 0 && id <= n) {
        printf("새로운 상품명 (현재: %s, 공백 포함 가능, 최대 %d자) : ", names[id - 1], MAX_NAME_LEN - 1);

        // 공백을 포함한 문자열을 읽고, 최대 길이를 제한합니다.
        if (scanf("%49[^\n]", new_name) == 1) {
            // 상품명 복사 및 널 종료 보장
            strncpy(names[id - 1], new_name, MAX_NAME_LEN - 1);
            names[id - 1][MAX_NAME_LEN - 1] = '\0';

            printf("상품 ID %d의 이름이 '%s'로 수정되었습니다.\n", id, names[id - 1]);
        }
        else {
            printf("상품명 입력에 실패했거나 빈 문자열이 입력되었습니다.\n");
        }
        clear_input_buffer(); // 새로운 이름 입력 후 버퍼 비우기
    }
    else {
        printf("잘못된 상품 ID입니다.\n");
    }
}

// 상품 현황 출력 함수
void print_status(int n, int* in_stock, int* sold, int* inventory, char names[][MAX_NAME_LEN]) {
    printf("\n--- 상품 현황 ---\n");
    // 정렬을 위해 너비 지정
    printf("%-5s | %-20s | %-5s | %-5s | %-5s\n", "ID", "상품명", "입고", "판매", "재고");
    printf("--------------------------------------------------\n");
    for (int k = 0; k < n; k++) {
        printf("%-5d | %-20s | %-5d | %-5d | %-5d\n", k + 1, names[k], in_stock[k], sold[k], inventory[k]);
    }
    printf("--------------------------------------------------\n");

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
        printf("가장 많이 판매된 상품 : ID %d (%s), 판매량 %d\n", max_sold_id, names[max_sold_id - 1], max_sold_val);
        printf("가장 적게 판매된 상품 : ID %d (%s), 판매량 %d\n", min_sold_id, names[min_sold_id - 1], min_sold_val);
    }

    // 재고 부족 알림
    lack(inventory, n, names);
}
