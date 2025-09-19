#include <stdio.h>

#define SIZE 5   // 상품 개수 

void inputStock(int* stock, int* sold, int* remain);
void sellProduct(int* stock, int* sold, int* remain);
void showStatus(int* stock, int* sold, int* remain);

int main() {
    int stock[SIZE] = { 0 };   // 입고 수량
    int sold[SIZE] = { 0 };    // 판매 수량
    int remain[SIZE] = { 0 };  // 재고 수량

    int menu;
    printf("[쇼핑몰 관리 프로그램]\n");

    while (1) {
        printf("\n원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 상품현황, 4. 종료)\n> ");
        scanf_s("%d", &menu);

        if (menu == 1) {
            inputStock(stock, sold, remain);
        }
        else if (menu == 2) {
            sellProduct(stock, sold, remain);
        }
        else if (menu == 3) {
            showStatus(stock, sold, remain);
        }
        else if (menu == 4) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}

// 입고 처리 함수
void inputStock(int* stock, int* sold, int* remain) {
    int mode;
    printf("입고수량 입력: 전체 상품 입고수량 입력 1, 개별 상품 입력 2 선택\n> ");
    scanf_s("%d", &mode);

    if (mode == 1) { // 전체 상품 입고
        for (int i = 0; i < SIZE; i++) {
            scanf_s("%d", stock + i);
            *(remain + i) = *(stock + i) - *(sold + i);
        }
    }
    else if (mode == 2) { // 개별 상품 입고
        int id, qty;
        printf("상품ID: ");
        scanf_s("%d", &id);
        printf("입고수량: ");
        scanf_s("%d", &qty);

        *(stock + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
    }
    else {
        printf("잘못된 입력입니다.\n");
    }
}

// 판매 처리 함수
void sellProduct(int* stock, int* sold, int* remain) {
    int mode;
    printf("판매수량 입력: 전체 상품 판매수량 입력 1, 개별 상품 입력 2 선택\n> ");
    scanf_s("%d", &mode);

    if (mode == 1) { // 전체 상품 판매
        for (int i = 0; i < SIZE; i++) {
            scanf_s("%d", sold + i);
            *(remain + i) = *(stock + i) - *(sold + i);
        }
    }
    else if (mode == 2) { // 개별 상품 판매
        int id, qty;
        printf("상품ID: ");
        scanf_s("%d", &id);
        printf("판매수량: ");
        scanf_s("%d", &qty);

        *(sold + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
    }
    else {
        printf("잘못된 입력입니다.\n");
    }
}

//상품 현황 출력 함수
void showStatus(int* stock, int* sold, int* remain) {
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
    printf("가장 많이 판매된 상품 : ID %d, 판매량 %d\n", max_id + 1, *(sold + max_id));
    printf("가장 적게 판매된 상품 : ID %d, 판매량 %d\n", min_id + 1, *(sold + min_id));

    for (int i = 0; i < SIZE; i++) {
        if (*(remain + i) <= 2) {
            printf("상품 ID %d : 재고부족(%d)\n", i + 1, *(remain + i));
        }
    }
}