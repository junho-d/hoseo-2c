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

    // 조회할 ID 입력
    scanf_s("%d", &id);

    // 해당 ID 상품 재고 출력
    printf("%d\n", remain[id]);

    // 모든 상품 재고 출력
    for (int i = 1; i <= N; i++) {
        printf("%d ", remain[i]);
    }
    printf("\n");

    return 0;
}
