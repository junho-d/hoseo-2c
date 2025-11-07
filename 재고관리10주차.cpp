#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5       // 상품 개수
#define NAME_LEN 21  // 상품명 최대 길이

// 구조체 정의
typedef struct {
    char name[NAME_LEN]; // 상품명
    int price;           // 상품 가격
    int stock;           // 총 입고량
    int sold;            // 총 판매량
    int isSet;           // 정보 입력 여부(0: 입력안됨, 1: 입력됨)
} Product;

// 함수 선언
void inputProduct(Product* items);
void sellProduct(Product* items);
void showProductDetail(Product* items);
void showAllStatus(Product* items);
void saveData(Product* items); // 바이너리 파일 저장 함수
void loadData(Product* items); // 바이너리 파일 불러오기 함수

int main() {
    // 구조체 배열 하나로 관리
    Product items[SIZE];
    int menu;

    // 구조체 배열 초기화
    for (int i = 0; i < SIZE; i++) {
        strcpy_s(items[i].name, NAME_LEN, "(미등록)");
        items[i].price = 0;
        items[i].stock = 0;
        items[i].sold = 0;
        items[i].isSet = 0;
    }

    // 프로그램 시작 시 저장된 데이터 불러오기
    loadData(items);

    printf("[쇼핑몰 재고 관리 프로그램]\n");

    while (1) {

        printf("\n원하는 메뉴를 선택하세요. (1.입고, 2.판매, 3.개별상품정보, 4.전체상품정보, 5.상품정보 저장, 6.종료)\n> ");

        if (scanf_s(" %d", &menu) != 1) {
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (menu) {
        case 1:
            inputProduct(items);
            break;
        case 2:
            sellProduct(items);
            break;
        case 3:
            showProductDetail(items);
            break;
        case 4:
            showAllStatus(items);
            break;
        case 5:
            // [바이너리 파일] 5번 메뉴 선택 시 저장 함수 호출
            saveData(items);
            break;
        case 6:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 1~6 중에서 선택하세요.\n");
            break;
        }
    }
    return 0;
}

// 상품정보 저장 함수
void saveData(Product* items) {
    FILE* fp;

    errno_t err = fopen_s(&fp, "products.dat", "wb");

    if (err != 0 || fp == NULL) {
        printf("[오류] 파일 열기에 실패했습니다.\n");
        return;
    }


    size_t written = fwrite(items, sizeof(Product), SIZE, fp);

    if (written == SIZE) {
        printf("\n>> 상품 정보가 'products.dat' 파일에 성공적으로 저장되었습니다.\n");
    }
    else {
        printf("\n[오류] 파일 쓰기에 실패했습니다.\n");
    }

    fclose(fp);
}

// 상품정보 가져오기 함수
void loadData(Product* items) {
    FILE* fp;

    errno_t err = fopen_s(&fp, "products.dat", "rb");

    if (err != 0 || fp == NULL) {
        printf("\n[알림] 저장된 'products.dat' 파일을 찾을 수 없습니다. (첫 실행)\n");
        return;
    }

    size_t read = fread(items, sizeof(Product), SIZE, fp);

    if (read == SIZE) {
        printf("\n>> 'products.dat' 파일에서 상품 정보를 성공적으로 불러왔습니다.\n");
    }
    else {
        printf("\n[오류] 파일 읽기에 실패했습니다.\n");
    }

    fclose(fp);
}


// 입고 처리 함수
void inputProduct(Product* items) {
    int id, qty, price;
    char name_buffer[NAME_LEN];

    printf("상품ID (1~%d): ", SIZE);
    if (scanf_s(" %d", &id) != 1 || id < 1 || id > SIZE) {
        printf("ID 범위 오류 (1-%d)\n", SIZE);
        int c; while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    // 버퍼 비우기
    int c; while ((c = getchar()) != '\n' && c != EOF);

    Product* p = &items[id - 1];

    printf("상품명: ");
    if (fgets(name_buffer, NAME_LEN, stdin)) {
        name_buffer[strcspn(name_buffer, "\n")] = 0; // fgets로 생긴 엔터키 제거
        strcpy_s(p->name, NAME_LEN, name_buffer);
    }

    printf("입고량: ");
    scanf_s(" %d", &qty);
    p->stock += qty; // 기존 재고에 누적

    printf("판매가격: ");
    scanf_s(" %d", &price);
    p->price = price; // 가격은 새로 덮어쓰기

    p->isSet = 1; // 정보가 입력되었음을 표시
    printf("\n>> ID %d 상품 정보 업데이트 완료.\n", id);
}

// 판매 처리 함수
void sellProduct(Product* items) {
    int id, qty;
    printf("판매할 상품ID (1~%d): ", SIZE);
    if (scanf_s(" %d", &id) != 1 || id < 1 || id > SIZE) {
        printf("ID 범위 오류\n");
        return;
    }

    Product* p = &items[id - 1];

    if (p->isSet == 0) {
        printf("[판매 불가] ID %d 에 등록된 상품 정보가 없습니다.\n", id);
        return;
    }

    int remain = p->stock - p->sold; // 현재 재고 계산

    printf("판매수량 (현재 재고: %d): ", remain);
    if (scanf_s(" %d", &qty) != 1 || qty < 0) {
        printf("잘못된 입력\n");
        return;
    }

    if (qty > remain) {
        printf("[판매 불가] 재고가 부족합니다.\n");
    }
    else {
        p->sold += qty;
        printf("\n>> ID %d 상품 %d개 판매 완료. (남은 재고: %d)\n", id, qty, p->stock - p->sold);
    }
}

// 개별 상품 정보 출력 함수
void showProductDetail(Product* items) {
    int id;
    printf("정보를 확인할 상품ID (1~%d): ", SIZE);
    if (scanf_s(" %d", &id) != 1 || id < 1 || id > SIZE) {
        printf("ID 범위 오류\n");
        return;
    }

    Product p = items[id - 1];

    if (p.isSet == 0) {
        printf("\n>> ID %d 에 등록된 상품 정보가 없습니다.\n", id);
        return;
    }

    printf("\n------[ ID %d 상품 상세 정보 ]------\n", id);
    printf("상품명 : %s\n", p.name);
    printf("상품가격 : %d 원\n", p.price);
    printf("총 입고량 : %d\n", p.stock);
    printf("총 판매량 : %d\n", p.sold);
    printf("현재 재고량 : %d\n", p.stock - p.sold);
    printf("총 판매금액 : %lld 원\n", (long long)p.price * p.sold);  // long long 형 변환
    printf("----------------------------------\n");
}

// 전체 상품 현황 출력 함수
void showAllStatus(Product* items) {
    long long total_sales_amount = 0;
    int total_sold_count = 0;
    int max_id = -1, min_id = -1;

    printf("\n=============================[ 전체 상품 현황 ]==============================\n");
    printf("%-5s | %-18s | %-8s | %-8s | %-8s | %-12s\n", "ID", "상품명", "판매가격", "입고량", "판매량", "총판매금액");
    printf("---------------------------------------------------------------------------\n");

    for (int i = 0; i < SIZE; i++) {
        if (items[i].isSet) {
            long long current_sales = (long long)items[i].price * items[i].sold;
            printf("%-5d | %-18s | %-8d | %-8d | %-8d | %-12lld\n",
                i + 1, items[i].name, items[i].price, items[i].stock, items[i].sold, current_sales);

            total_sales_amount += current_sales;
            total_sold_count += items[i].sold;

            if (max_id == -1 || items[i].sold > items[max_id].sold) max_id = i;
            if (min_id == -1 || items[i].sold < items[min_id].sold) min_id = i;
        }
    }
    printf("===========================================================================\n");

    printf("▶ 총 판매량 : %d개\n", total_sold_count);
    printf("▶ 총 판매액 : %lld원\n", total_sales_amount);

    if (max_id != -1) {
        printf("▶ Best  Seller: %s (ID %d, %d개 판매)\n", items[max_id].name, max_id + 1, items[max_id].sold);
    }
    if (min_id != -1) {
        printf("▶ Worst Seller: %s (ID %d, %d개 판매)\n", items[min_id].name, min_id + 1, items[min_id].sold);
    }
    printf("===========================================================================\n");
}