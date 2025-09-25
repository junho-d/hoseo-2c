#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5       // 상품 개수 
#define NAME_LEN 30  // 상품명 최대 길이 

void inputStock(int* stock, int* sold, int* remain);
void sellProduct(int* stock, int* sold, int* remain);
void showStatus(int* stock, int* sold, int* remain, char productNames[SIZE][NAME_LEN]);
void inputProductNames(char productNames[SIZE][NAME_LEN]);

int main() {
    int stock[SIZE] = { 0 };
    int sold[SIZE] = { 0 };
    int remain[SIZE] = { 0 };
    char productNames[SIZE][NAME_LEN] = { "" };

    int menu;
    printf("[쇼핑몰 관리 프로그램]\n");

    while (1) {
        printf("\n원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 상품현황, 4. 상품명 입력, 5. 종료)\n> ");
        if (scanf_s("%d", &menu) != 1) {

            int c; while ((c = getchar()) != EOF && c != '\n');
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
            continue;
        }

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

// 입고 처리
void inputStock(int* stock, int* sold, int* remain) {
    int mode;
    printf("입고수량 입력: 전체 상품 입고(1), 개별 상품 입고(2) 선택\n> ");
    if (scanf_s("%d", &mode) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("잘못된 입력\n"); return; }

    if (mode == 1) { // 전체 입력
        printf("전체 상품의 입고수량을 공백으로 구분하여 %d개 입력하세요.\n", SIZE);
        for (int i = 0; i < SIZE; i++) {
            if (scanf_s("%d", stock + i) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); *(stock + i) = 0; }
            *(remain + i) = *(stock + i) - *(sold + i);
        }
    }
    else if (mode == 2) { // 개별 입력
        int id, qty;
        printf("상품ID (1~%d): ", SIZE);
        if (scanf_s("%d", &id) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("잘못된 입력\n"); return; }
        if (id < 1 || id > SIZE) { printf("ID 범위 오류\n"); return; }
        printf("입고수량: ");
        if (scanf_s("%d", &qty) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("잘못된 입력\n"); return; }

        *(stock + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
    }
    else {
        printf("잘못된 선택입니다.\n");
    }
}

// 판매 처리
void sellProduct(int* stock, int* sold, int* remain) {
    int mode;
    printf("판매수량 입력: 전체 상품 판매(1), 개별 상품 판매(2) 선택\n> ");
    if (scanf_s("%d", &mode) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("잘못된 입력\n"); return; }

    if (mode == 1) {
        printf("전체 상품의 판매수량을 공백으로 구분하여 %d개 입력하세요.\n", SIZE);
        for (int i = 0; i < SIZE; i++) {
            if (scanf_s("%d", sold + i) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); *(sold + i) = 0; }
            *(remain + i) = *(stock + i) - *(sold + i);
        }
    }
    else if (mode == 2) {
        int id, qty;
        printf("상품ID (1~%d): ", SIZE);
        if (scanf_s("%d", &id) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("잘못된 입력\n"); return; }
        if (id < 1 || id > SIZE) { printf("ID 범위 오류\n"); return; }
        printf("판매수량: ");
        if (scanf_s("%d", &qty) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("잘못된 입력\n"); return; }

        *(sold + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
    }
    else {
        printf("잘못된 선택입니다.\n");
    }
}

// 상품명 입력 (공백 포함 가능)
void inputProductNames(char productNames[SIZE][NAME_LEN]) {
    for (int i = 0; i < SIZE; i++) {
        printf("ID %d 상품명 입력: ", i + 1);
        if (scanf_s(" %29[^\n]", productNames[i], (unsigned)_countof(productNames[i])) != 1) {
            // 입력 실패 시 기본명 지정
            strncpy_s(productNames[i], NAME_LEN, "(이름없음)", _TRUNCATE);
        }
    }
}


// 상품 현황 출력 
void showStatus(int* stock, int* sold, int* remain, char productNames[SIZE][NAME_LEN]) {
    int total_stock = 0, total_sold = 0;
    int max_id = 0, min_id = 0;


    printf("재고수량 : ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", *(remain + i));
        total_stock += *(stock + i);
        total_sold += *(sold + i);

        if (i == 0 || *(sold + i) > *(sold + max_id)) max_id = i;
        if (i == 0 || *(sold + i) < *(sold + min_id)) min_id = i;
    }
    printf("\n");

    double rate = 0.0;
    if (total_stock > 0)
        rate = (double)total_sold / total_stock * 100.0;

    printf("총 판매량 : %d (판매율 %.2f%%)\n", total_sold, rate);

    // 상품명이 비어있으면 (이름없음)으로 표시
    const char* maxName = (productNames[max_id][0] != '\0') ? productNames[max_id] : "(이름없음)";
    const char* minName = (productNames[min_id][0] != '\0') ? productNames[min_id] : "(이름없음)";

    printf("가장 많이 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", max_id + 1, maxName, *(sold + max_id));
    printf("가장 적게 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", min_id + 1, minName, *(sold + min_id));

    for (int i = 0; i < SIZE; i++) {
        if (*(remain + i) <= 2) {
            const char* name = (productNames[i][0] != '\0') ? productNames[i] : "(이름없음)";
            printf("상품 ID %d : 상품명 : %s 재고부족(%d)\n", i + 1, name, *(remain + i));
        }
    }
}