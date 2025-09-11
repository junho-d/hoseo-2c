#include <stdio.h>

int main() {
    int N; // 상품 종류 수
    int stock[101]; // 입고 수량
    int sold[101];  // 판매 수량
    int remain[101]; // 재고 수량
    int id;

    // 상품 개수 입력
    scanf_s("%d", &N);

    // 입고 수량 입력
    for (int i = 1; i <= N; i++) {
        scanf_s("%d", &stock[i]);
    }

    // 판매 수량 입력
    for (int i = 1; i <= N; i++) {
        scanf_s("%d", &sold[i]);
    }

    // 재고 수량 계산
    for (int i = 1; i <= N; i++) {
        remain[i] = stock[i] - sold[i];
    }

    // 재고 경고 부족 (재고가 2개 미만인 상품을 확인)
    for (int i = 1; i <= N; i++) {
        if (remain[i] < 2) {
            printf("상품 ID %d: 수량이 2개 미만으로 남아 채워야 합니다.\n", i);
        }
    }

    // 조회할 ID 입력
    scanf_s("%d", &id);

    // 해당 ID 상품 재고 출력
    printf("%d\n", remain[id]);

    // 모든 상품 재고 출력
    for (int i = 1; i <= N; i++) {
        printf("%d ", remain[i]);
    }
    printf("\n");

    // 전체 판매율 계산 
    for (int i = 1; i <= N; i++) {
        if (stock[i] > 0) {
            float sales_rate = (float)sold[i] / stock[i] * 100;
            printf("상품 ID %d의 판매율: %.2f%%\n", i, sales_rate);
        }
        else {
            printf("상품 ID %d의 판매율: 0.00%% (입고량이 0)\n", i);
        }
    }

    // 최대 판매량 및 최소 판매량 상품 출력
    int max_sales = 0, min_sales = 1000000000; // 충분히 큰 값으로 초기화
    int max_sales_id = 0, min_sales_id = 0;

    for (int i = 1; i <= N; i++) {
        if (sold[i] > max_sales) {
            max_sales = sold[i];
            max_sales_id = i;
        }
        if (sold[i] < min_sales) {
            min_sales = sold[i];
            min_sales_id = i;
        }
    }

    printf("최대 판매량 상품 ID: %d, 판매량: %d\n", max_sales_id, max_sales);
    printf("최소 판매량 상품 ID: %d, 판매량: %d\n", min_sales_id, min_sales);

    return 0;
}
