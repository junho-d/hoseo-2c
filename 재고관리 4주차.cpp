#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5       // ��ǰ ���� 
#define NAME_LEN 30  // ��ǰ�� �ִ� ���� 

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
    printf("[���θ� ���� ���α׷�]\n");

    while (1) {
        printf("\n���ϴ� �޴��� �����ϼ���. (1. �԰�, 2. �Ǹ�, 3. ��ǰ��Ȳ, 4. ��ǰ�� �Է�, 5. ����)\n> ");
        if (scanf_s("%d", &menu) != 1) {

            int c; while ((c = getchar()) != EOF && c != '\n');
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
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
            printf("���α׷��� �����մϴ�.\n");
            break;
        }
        else {
            printf("�߸��� �����Դϴ�. 1~5 �߿��� �����ϼ���.\n");
        }
    }

    return 0;
}

// �԰� ó��
void inputStock(int* stock, int* sold, int* remain) {
    int mode;
    printf("�԰���� �Է�: ��ü ��ǰ �԰�(1), ���� ��ǰ �԰�(2) ����\n> ");
    if (scanf_s("%d", &mode) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("�߸��� �Է�\n"); return; }

    if (mode == 1) { // ��ü �Է�
        printf("��ü ��ǰ�� �԰������ �������� �����Ͽ� %d�� �Է��ϼ���.\n", SIZE);
        for (int i = 0; i < SIZE; i++) {
            if (scanf_s("%d", stock + i) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); *(stock + i) = 0; }
            *(remain + i) = *(stock + i) - *(sold + i);
        }
    }
    else if (mode == 2) { // ���� �Է�
        int id, qty;
        printf("��ǰID (1~%d): ", SIZE);
        if (scanf_s("%d", &id) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("�߸��� �Է�\n"); return; }
        if (id < 1 || id > SIZE) { printf("ID ���� ����\n"); return; }
        printf("�԰����: ");
        if (scanf_s("%d", &qty) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("�߸��� �Է�\n"); return; }

        *(stock + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
    }
    else {
        printf("�߸��� �����Դϴ�.\n");
    }
}

// �Ǹ� ó��
void sellProduct(int* stock, int* sold, int* remain) {
    int mode;
    printf("�Ǹż��� �Է�: ��ü ��ǰ �Ǹ�(1), ���� ��ǰ �Ǹ�(2) ����\n> ");
    if (scanf_s("%d", &mode) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("�߸��� �Է�\n"); return; }

    if (mode == 1) {
        printf("��ü ��ǰ�� �Ǹż����� �������� �����Ͽ� %d�� �Է��ϼ���.\n", SIZE);
        for (int i = 0; i < SIZE; i++) {
            if (scanf_s("%d", sold + i) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); *(sold + i) = 0; }
            *(remain + i) = *(stock + i) - *(sold + i);
        }
    }
    else if (mode == 2) {
        int id, qty;
        printf("��ǰID (1~%d): ", SIZE);
        if (scanf_s("%d", &id) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("�߸��� �Է�\n"); return; }
        if (id < 1 || id > SIZE) { printf("ID ���� ����\n"); return; }
        printf("�Ǹż���: ");
        if (scanf_s("%d", &qty) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("�߸��� �Է�\n"); return; }

        *(sold + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
    }
    else {
        printf("�߸��� �����Դϴ�.\n");
    }
}

// ��ǰ�� �Է� (���� ���� ����)
void inputProductNames(char productNames[SIZE][NAME_LEN]) {
    for (int i = 0; i < SIZE; i++) {
        printf("ID %d ��ǰ�� �Է�: ", i + 1);
        if (scanf_s(" %29[^\n]", productNames[i], (unsigned)_countof(productNames[i])) != 1) {
            // �Է� ���� �� �⺻�� ����
            strncpy_s(productNames[i], NAME_LEN, "(�̸�����)", _TRUNCATE);
        }
    }
}


// ��ǰ ��Ȳ ��� 
void showStatus(int* stock, int* sold, int* remain, char productNames[SIZE][NAME_LEN]) {
    int total_stock = 0, total_sold = 0;
    int max_id = 0, min_id = 0;


    printf("������ : ");
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

    printf("�� �Ǹŷ� : %d (�Ǹ��� %.2f%%)\n", total_sold, rate);

    // ��ǰ���� ��������� (�̸�����)���� ǥ��
    const char* maxName = (productNames[max_id][0] != '\0') ? productNames[max_id] : "(�̸�����)";
    const char* minName = (productNames[min_id][0] != '\0') ? productNames[min_id] : "(�̸�����)";

    printf("���� ���� �Ǹŵ� ��ǰ : ID %d, ��ǰ�� : %s, �Ǹŷ� %d\n", max_id + 1, maxName, *(sold + max_id));
    printf("���� ���� �Ǹŵ� ��ǰ : ID %d, ��ǰ�� : %s, �Ǹŷ� %d\n", min_id + 1, minName, *(sold + min_id));

    for (int i = 0; i < SIZE; i++) {
        if (*(remain + i) <= 2) {
            const char* name = (productNames[i][0] != '\0') ? productNames[i] : "(�̸�����)";
            printf("��ǰ ID %d : ��ǰ�� : %s ������(%d)\n", i + 1, name, *(remain + i));
        }
    }
}