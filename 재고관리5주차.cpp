#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5       // ��ǰ ����
#define NAME_LEN 30  // ��ǰ�� �ִ� ����

// �Է� ���۸� ���� �Լ� ����
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

    // �ʱ� ��ǰ���� (�̸�����)���� ����
    for (int i = 0; i < SIZE; i++) {
        strcpy_s(productNames[i], NAME_LEN, "(�̸�����)");
    }

    int menu;
    printf("[���θ� ���� ���α׷�]\n");

    while (1) {
        printf("\n���ϴ� �޴��� �����ϼ���. (1. �԰�, 2. �Ǹ�, 3. ��ǰ��Ȳ, 4. ��ǰ�� �Է�, 5. ����)\n> ");
        if (scanf_s("%d", &menu) != 1) {
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
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
            printf("���α׷��� �����մϴ�.\n");
            break;
        }
        else {
            printf("�߸��� �����Դϴ�. 1~5 �߿��� �����ϼ���.\n");
        }
    }
    return 0;
}

// �Է� ���۸� ���� �Լ��� ����
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// �԰� ó��
void inputStock(int* stock, int* sold, int* remain) {
    int mode;
    printf("�԰���� �Է�: ��ü ��ǰ �԰�(1), ���� ��ǰ �԰�(2) ����\n> ");
    if (scanf_s("%d", &mode) != 1) {
        printf("�߸��� �Է�\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (mode == 1) { // ��ü �Է�
        printf("��ü ��ǰ�� �԰������ �������� �����Ͽ� %d�� �Է��ϼ���.\n", SIZE);
        for (int i = 0; i < SIZE; i++) {
            int qty = 0;
            if (scanf_s("%d", &qty) == 1) {
                *(stock + i) += qty;
            }
            *(remain + i) = *(stock + i) - *(sold + i);
        }
        clearInputBuffer();
    }
    else if (mode == 2) { // ���� �Է�
        int id, qty;
        printf("��ǰID (1~%d): ", SIZE);
        if (scanf_s("%d", &id) != 1 || id < 1 || id > SIZE) {
            printf("ID ���� ����\n");
            clearInputBuffer();
            return;
        }
        printf("�԰����: ");
        if (scanf_s("%d", &qty) != 1) {
            printf("�߸��� �Է�\n");
            clearInputBuffer();
            return;
        }
        clearInputBuffer();

        *(stock + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
        printf("ID %d ��ǰ %d�� �԰� �Ϸ�.\n", id, qty);
    }
    else {
        printf("�߸��� �����Դϴ�.\n");
    }
}

// �Ǹ� ó��
void sellProduct(int* stock, int* sold, int* remain) {
    int id, qty;
    printf("�Ǹ��� ��ǰID (1~%d): ", SIZE);
    if (scanf_s("%d", &id) != 1 || id < 1 || id > SIZE) {
        printf("ID ���� ����\n");
        clearInputBuffer();
        return;
    }
    printf("�Ǹż���: ");
    if (scanf_s("%d", &qty) != 1 || qty < 0) {
        printf("�߸��� �Է�\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (qty > *(remain + (id - 1))) {
        printf("[�Ǹ� �Ұ�] ��� �����մϴ�. (���� ���: %d)\n", *(remain + (id - 1)));
    }
    else {
        *(sold + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
        printf("ID %d ��ǰ %d�� �Ǹ� �Ϸ�. (���� ���: %d)\n", id, qty, *(remain + (id - 1)));
    }
}

// ��ǰ�� �Է� (���� ���� ����)
void inputProductNames(char productNames[SIZE][NAME_LEN]) {
    for (int i = 0; i < SIZE; i++) {
        printf("ID %d ��ǰ�� �Է�: ", i + 1);
        if (scanf_s(" %29[^\n]", productNames[i], (unsigned)NAME_LEN) != 1) {
            clearInputBuffer();
            strncpy_s(productNames[i], NAME_LEN, "(�̸�����)", _TRUNCATE);
        }
    }
}


// ��ǰ ��Ȳ ���
void showStatus(int* stock, int* sold, int* remain, char productNames[SIZE][NAME_LEN]) {
    int total_stock = 0, total_sold = 0;
    int max_id = 0, min_id = 0;

    printf("\n====================[ ��ǰ ��Ȳ ]====================\n");
    printf("%-20s | %-8s | %-8s | %-8s\n", "��ǰ��", "�԰�", "�Ǹŷ�", "���");
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

    printf("�� �� �Ǹŷ� : %d (��ü �Ǹ���: %.2f%%)\n", total_sold, rate);
    printf("�� Best  Seller: %s (ID %d, %d�� �Ǹ�)\n", productNames[max_id], max_id + 1, *(sold + max_id));
    printf("�� Worst Seller: %s (ID %d, %d�� �Ǹ�)\n", productNames[min_id], min_id + 1, *(sold + min_id));

    printf("\n[��� ���� �˸� (2�� ����)]\n");
    int low_stock_count = 0;
    for (int i = 0; i < SIZE; i++) {
        if (*(remain + i) <= 2) {
            printf("  - ID %d: %s (���� ���: %d��)\n", i + 1, productNames[i], *(remain + i));
            low_stock_count++;
        }
    }
    if (low_stock_count == 0) {
        printf("  - ��� ���� ��ǰ�� �����ϴ�.\n");
    }
    printf("======================================================\n");
}