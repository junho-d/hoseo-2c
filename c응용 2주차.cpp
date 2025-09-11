#include <stdio.h>

int main() {
    int N; // 상품 종류 수
    int stock[101];   // 입고 수량
    int sold[101];    // 판매 수량
    int remain[101];  // 재고 수량
    int total_sold = 0, total_stock = 0;
    int max_id = 1, min_id = 1;

    // 상품 개수 입력
    scanf_s("%d", &N);

    // 입고 수량 입력
    for (int i = 1; i <= N; i++) {
        scanf_s("%d", &stock[i]);
        total_stock += stock[i];
    }

    // 판매 수량 입력
    for (int i = 1; i <= N; i++) {
        scanf_s("%d", &sold[i]);
        remain[i] = stock[i] - sold[i];
        total_sold += sold[i];
    }

    // 모든 상품 재고 출력
    printf("재고수량 : ");
    for (int i = 1; i <= N; i++) {
        printf("%d", remain[i]);
    }
    printf("\n");

    // 전체 판매량 및 판매율 출력
    double rate = 0.0;
    if (total_stock > 0) {
        rate = (double)total_sold / total_stock * 100.0;
    }
    printf("총 판매량 : %d (판매율 %.2f%%)\n", total_sold, rate);

    // 최다 판매, 최소 판매 상품 찾기
    for (int i = 2; i <= N; i++) {
        if (sold[i] > sold[max_id]) max_id = i;
        if (sold[i] < sold[min_id]) min_id = i;
    }
    printf("가장 많이 판매된 상품 : ID %d, 판매량 %d\n", max_id, sold[max_id]);
    printf("가장 적게 판매된 상품 : ID %d, 판매량 %d\n", min_id, sold[min_id]);

    // 재고 부족 경고 (재고 수량이 2 이하일 때)
    for (int i = 1; i <= N; i++) {
        if (remain[i] <= 2) {
            printf("상품 ID %d : 재고부족(%d)\n", i, remain[i]);
        }
    }

    return 0;
}
