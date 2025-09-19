#include <stdio.h>

#define SIZE 5   // ��ǰ ���� 

void inputStock(int* stock, int* sold, int* remain);
void sellProduct(int* stock, int* sold, int* remain);
void showStatus(int* stock, int* sold, int* remain);

int main() {
    int stock[SIZE] = { 0 };   // �԰� ����
    int sold[SIZE] = { 0 };    // �Ǹ� ����
    int remain[SIZE] = { 0 };  // ��� ����

    int menu;
    printf("[���θ� ���� ���α׷�]\n");

    while (1) {
        printf("\n���ϴ� �޴��� �����ϼ���. (1. �԰�, 2. �Ǹ�, 3. ��ǰ��Ȳ, 4. ����)\n> ");
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
            printf("���α׷��� �����մϴ�.\n");
            break;
        }
        else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �����ϼ���.\n");
        }
    }

    return 0;
}

// �԰� ó�� �Լ�
void inputStock(int* stock, int* sold, int* remain) {
    int mode;
    printf("�԰���� �Է�: ��ü ��ǰ �԰���� �Է� 1, ���� ��ǰ �Է� 2 ����\n> ");
    scanf_s("%d", &mode);

    if (mode == 1) { // ��ü ��ǰ �԰�
        for (int i = 0; i < SIZE; i++) {
            scanf_s("%d", stock + i);
            *(remain + i) = *(stock + i) - *(sold + i);
        }
    }
    else if (mode == 2) { // ���� ��ǰ �԰�
        int id, qty;
        printf("��ǰID: ");
        scanf_s("%d", &id);
        printf("�԰����: ");
        scanf_s("%d", &qty);

        *(stock + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
    }
    else {
        printf("�߸��� �Է��Դϴ�.\n");
    }
}

// �Ǹ� ó�� �Լ�
void sellProduct(int* stock, int* sold, int* remain) {
    int mode;
    printf("�Ǹż��� �Է�: ��ü ��ǰ �Ǹż��� �Է� 1, ���� ��ǰ �Է� 2 ����\n> ");
    scanf_s("%d", &mode);

    if (mode == 1) { // ��ü ��ǰ �Ǹ�
        for (int i = 0; i < SIZE; i++) {
            scanf_s("%d", sold + i);
            *(remain + i) = *(stock + i) - *(sold + i);
        }
    }
    else if (mode == 2) { // ���� ��ǰ �Ǹ�
        int id, qty;
        printf("��ǰID: ");
        scanf_s("%d", &id);
        printf("�Ǹż���: ");
        scanf_s("%d", &qty);

        *(sold + (id - 1)) += qty;
        *(remain + (id - 1)) = *(stock + (id - 1)) - *(sold + (id - 1));
    }
    else {
        printf("�߸��� �Է��Դϴ�.\n");
    }
}

//��ǰ ��Ȳ ��� �Լ�
void showStatus(int* stock, int* sold, int* remain) {
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
    printf("���� ���� �Ǹŵ� ��ǰ : ID %d, �Ǹŷ� %d\n", max_id + 1, *(sold + max_id));
    printf("���� ���� �Ǹŵ� ��ǰ : ID %d, �Ǹŷ� %d\n", min_id + 1, *(sold + min_id));

    for (int i = 0; i < SIZE; i++) {
        if (*(remain + i) <= 2) {
            printf("��ǰ ID %d : ������(%d)\n", i + 1, *(remain + i));
        }
    }
}