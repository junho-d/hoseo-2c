#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
void inputProduct(Product* items, int productCount);
void sellProduct(Product* items, int productCount);
void showProductDetail(Product* items, int productCount);
void showAllStatus(Product* items, int productCount);
void saveData(Product* items, int productCount);
void loadData(Product* items, int productCount);

int main() {
    Product* items; 
    int menu;
    int productCount;

    printf("관리할 최대 상품 개수를 입력하세요: ");
    if (scanf_s(" %d", &productCount) != 1 || productCount <= 0) {
        printf("잘못된 입력입니다. 프로그램을 종료합니다.\n");
        return 1;
    }

    // malloc을 사용해 (Product 구조체 크기 * 개수) 만큼 동적 메모리 할당
    items = (Product*)malloc(sizeof(Product) * productCount);

    // 동적 할당 실패 시 예외 처리
    if (items == NULL) {
        printf("메모리 할당에 실패했습니다. 프로그램을 종료합니다.\n");
        return 1;
    }

   
    for (int i = 0; i < productCount; i++) {
        strcpy_s(items[i].name, NAME_LEN, "(미등록)");
        items[i].price = 0;
        items[i].stock = 0;
        items[i].sold = 0;
        items[i].isSet = 0;
    }

    
    loadData(items, productCount);

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
            inputProduct(items, productCount);
            break;
        case 2:
            sellProduct(items, productCount);
            break;
        case 3:
            showProductDetail(items, productCount);
            break;
        case 4:
            showAllStatus(items, productCount);
            break;
        case 5:
            saveData(items, productCount);
            break;
        case 6:
            printf("프로그램을 종료합니다.\n");
            free(items); // main 함수 종료 직전, 할당받은 메모리 해제
            return 0;
        default:
            printf("잘못된 선택입니다. 1~6 중에서 선택하세요.\n");
            break;
        }
    }
   
    free(items);
    return 0;
}

// 상품정보 저장 함수
void saveData(Product* items, int productCount) {
    FILE* fp;
    errno_t err = fopen_s(&fp, "products.dat", "wb");

    if (err != 0 || fp == NULL) {
        printf("[오류] 파일 열기에 실패했습니다.\n");
        return;
    }


    size_t written = fwrite(items, sizeof(Product), productCount, fp);

    if (written == productCount) {
        printf("\n>> 상품 정보가 'products.dat' 파일에 성공적으로 저장되었습니다.\n");
    }
    else {
        printf("\n[오류] 파일 쓰기에 실패했습니다.\n");
    }

    fclose(fp);
}

// 상품정보 가져오기 함수
void loadData(Product* items, int productCount) {
    FILE* fp;
    errno_t err = fopen_s(&fp, "products.dat", "rb");

    if (err != 0 || fp == NULL) {
        printf("\n[알림] 저장된 'products.dat' 파일을 찾을 수 없습니다. (첫 실행)\n");
        return;
    }
    size_t read = fread(items, sizeof(Product), productCount, fp);

    if (read == productCount) {
        printf("\n>> 'products.dat' 파일에서 상품 정보를 성공적으로 불러왔습니다.\n");
    }
    else {
        // 첫 실행 후, 상품 개수를 다르게 설정하여 실행하면 크기가 안 맞을 수 있음
        printf("\n[경고] 저장된 데이터와 현재 설정된 상품 개수가 다릅니다. 데이터가 일부만 로드되었을 수 있습니다.\n");
    }

    fclose(fp);
}

// 입고 처리 함수
void inputProduct(Product* items, int productCount) {
    int id, qty, price;
    char name_buffer[NAME_LEN];

   
    printf("상품ID (1~%d): ", productCount);
    if (scanf_s(" %d", &id) != 1 || id < 1 || id > productCount) {
        printf("ID 범위 오류 (1-%d)\n", productCount);
        int c; while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    int c; while ((c = getchar()) != '\n' && c != EOF);

    Product* p = &items[id - 1];

    printf("상품명: ");
    if (fgets(name_buffer, NAME_LEN, stdin)) {
        name_buffer[strcspn(name_buffer, "\n")] = 0;
        strcpy_s(p->name, NAME_LEN, name_buffer);
    }

    printf("입고량: ");
    scanf_s(" %d", &qty);
    p->stock += qty;

    printf("판매가격: ");
    scanf_s(" %d", &price);
    p->price = price;

    p->isSet = 1;
    printf("\n>> ID %d 상품 정보 업데이트 완료.\n", id);
}

// 판매 처리 함수
void sellProduct(Product* items, int productCount) {
    int id, qty;
 
    printf("판매할 상품ID (1~%d): ", productCount);
    if (scanf_s(" %d", &id) != 1 || id < 1 || id > productCount) {
        printf("ID 범위 오류\n");
        return;
    }

    Product* p = &items[id - 1];

    if (p->isSet == 0) {
        printf("[판매 불가] ID %d 에 등록된 상품 정보가 없습니다.\n", id);
        return;
    }

    int remain = p->stock - p->sold;

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
void showProductDetail(Product* items, int productCount) {
    int id;
   
    printf("정보를 확인할 상품ID (1~%d): ", productCount);
    if (scanf_s(" %d", &id) != 1 || id < 1 || id > productCount) {
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
    printf("총 판매금액 : %lld 원\n", (long long)p.price * p.sold);
    printf("----------------------------------\n");
}

// 전체 상품 현황 출력 함수
void showAllStatus(Product* items, int productCount) {
    long long total_sales_amount = 0;
    int total_sold_count = 0;
    int max_id = -1, min_id = -1;

    printf("\n=============================[ 전체 상품 현황 ]==============================\n");
    printf("%-5s | %-18s | %-8s | %-8s | %-8s | %-12s\n", "ID", "상품명", "판매가격", "입고량", "판매량", "총판매금액");
    printf("---------------------------------------------------------------------------\n");

    for (int i = 0; i < productCount; i++) {
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