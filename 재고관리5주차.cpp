#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5       // 상품 개수
#define NAME_LEN 30  // 상품명 최대 길이

// 입력 버퍼를 비우는 함수 선언
void clearInputBuffer();

void inputStock(int* stock, int* sold, int* remain);
void sellProduct(int* stock, int* sold, int* remain);
void showStatus(int* stock, int* sold, int* remain, char productNames[SIZE][NAME_LEN]);
void inputProductNames(char productNames[SIZE][NAME_LEN]);

int main() {
    int stock[SIZE] = { 0 };
    int sold[SIZE] = { 0 };
    int remain[SIZE] = { 0 };
    char productNames[SIZE][NAME_LEN];

    // 초기 상품명을 (이름없음)으로 설정
    for (int i = 0; i < SIZE; i++) {
        strcpy_s(productNames[i], NAME_LEN, "(이름없음)");
    }

    int menu;
    printf("[쇼핑몰 관리 프로그램]\n");

    while (1) {
        printf("\n원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 상품현황, 4. 상품명 입력, 5. 종료)\n> ");
        if (scanf_s("%d", &menu) != 1) {
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (menu == 1) {
            inputStock(stock, sold, remain);
        }
        else if (menu == 2) {
            sellProduct(stock, sold, remain);
        }
        else if (menu == 3) {
            showStatus(stock, sold, remain, productNames);
        }
        else if (menu == 4) {
            inputProductNames(productNames);
        }
        else if (menu == 5) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 선택입니다. 1~5 중에서 선택하세요.\n");
        }
    }
    return 0;
}

// 입력 버퍼를 비우는 함수의 정의
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// 입고 처리
void inputStock(int* stock, int* sold, int* remain) {
    int mode;
    printf("입고수량 입력: 전체 상품 입고(1), 개별 상품 입고(2) 선택\n> ");
    if (scanf_s("%d", &mode) != 1) {
        printf("잘못된 입력\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (mode == 1) { // 전체 입력
        printf("전체 상품의 입고수량을 공백으로 구분하여 %d개 입력하세요.\n", SIZE);
        for (int i = 0; i < SIZE; i++) {
            int qty = 0;
            if (scanf_s("%d", &qty) == 1) {
                *(stock + i) += qty;
            }
            *(remain + i) = *(stock + i) - *(sold + i);
        }
        clearInputBuffer();
    }
    else if (mode == 2) { // 개별 입력
        int id, qty;
        printf("상품ID (1~%d): ", SIZE);
        if (scanf_s("%d", &id) != 1 || id < 1 || id > SIZE) {
            printf("ID 범위 오류\n");
            clearInputBuffer();
            return;
        }
        printf("입고수량: ");
        if (scanf_s("%d", &qty) != 1) {
            printf("잘못된 입력\n");
            clearInputBuffer();
            return;
        }
        clearInputBuffer();

        *(stock + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
        printf("ID %d 상품 %d개 입고 완료.\n", id, qty);
    }
    else {
        printf("잘못된 선택입니다.\n");
    }
}

// 판매 처리
void sellProduct(int* stock, int* sold, int* remain) {
    int id, qty;
    printf("판매할 상품ID (1~%d): ", SIZE);
    if (scanf_s("%d", &id) != 1 || id < 1 || id > SIZE) {
        printf("ID 범위 오류\n");
        clearInputBuffer();
        return;
    }
    printf("판매수량: ");
    if (scanf_s("%d", &qty) != 1 || qty < 0) {
        printf("잘못된 입력\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (qty > *(remain + (id - 1))) {
        printf("[판매 불가] 재고가 부족합니다. (현재 재고: %d)\n", *(remain + (id - 1)));
    }
    else {
        *(sold + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
        printf("ID %d 상품 %d개 판매 완료. (남은 재고: %d)\n", id, qty, *(remain + (id - 1)));
    }
}

// 상품명 입력 (공백 포함 가능)
void inputProductNames(char productNames[SIZE][NAME_LEN]) {
    for (int i = 0; i < SIZE; i++) {
        printf("ID %d 상품명 입력: ", i + 1);
        if (scanf_s(" %29[^\n]", productNames[i], (unsigned)NAME_LEN) != 1) {
            clearInputBuffer();
            strncpy_s(productNames[i], NAME_LEN, "(이름없음)", _TRUNCATE);
        }
    }
}


// 상품 현황 출력
void showStatus(int* stock, int* sold, int* remain, char productNames[SIZE][NAME_LEN]) {
    int total_stock = 0, total_sold = 0;
    int max_id = 0, min_id = 0;

    printf("\n====================[ 상품 현황 ]====================\n");
    printf("%-20s | %-8s | %-8s | %-8s\n", "상품명", "입고량", "판매량", "재고량");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%-20s | %-8d | %-8d | %-8d\n", productNames[i], *(stock + i), *(sold + i), *(remain + i));
        total_stock += *(stock + i);
        total_sold += *(sold + i);

        if (*(sold + i) > *(sold + max_id)) max_id = i;
        if (*(sold + i) < *(sold + min_id)) min_id = i;
    }
    printf("======================================================\n");

    double rate = (total_stock > 0) ? (double)total_sold / total_stock * 100.0 : 0.0;

    printf("▶ 총 판매량 : %d (전체 판매율: %.2f%%)\n", total_sold, rate);
    printf("▶ Best  Seller: %s (ID %d, %d개 판매)\n", productNames[max_id], max_id + 1, *(sold + max_id));
    printf("▶ Worst Seller: %s (ID %d, %d개 판매)\n", productNames[min_id], min_id + 1, *(sold + min_id));

    printf("\n[재고 부족 알림 (2개 이하)]\n");
    int low_stock_count = 0;
    for (int i = 0; i < SIZE; i++) {
        if (*(remain + i) <= 2) {
            printf("  - ID %d: %s (남은 재고: %d개)\n", i + 1, productNames[i], *(remain + i));
            low_stock_count++;
        }
    }
    if (low_stock_count == 0) {
        printf("  - 재고 부족 상품이 없습니다.\n");
    }
    printf("======================================================\n");
}