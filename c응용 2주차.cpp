#include <stdio.h>

int main() {
    int N; // ��ǰ ���� ��
    int stock[101]; // �԰� ����
    int sold[101];  // �Ǹ� ����
    int remain[101]; // ��� ����
    int id;

    // ��ǰ ���� �Է�
    scanf_s("%d", &N);

    // �԰� ���� �Է�
    for (int i = 1; i <= N; i++) {
        scanf_s("%d", &stock[i]);
    }

    // �Ǹ� ���� �Է�
    for (int i = 1; i <= N; i++) {
        scanf_s("%d", &sold[i]);
    }

    // ��� ���� ���
    for (int i = 1; i <= N; i++) {
        remain[i] = stock[i] - sold[i];
    }

    // ��� ��� ���� (��� 2�� �̸��� ��ǰ�� Ȯ��)
    for (int i = 1; i <= N; i++) {
        if (remain[i] < 2) {
            printf("��ǰ ID %d: ������ 2�� �̸����� ���� ä���� �մϴ�.\n", i);
        }
    }

    // ��ȸ�� ID �Է�
    scanf_s("%d", &id);

    // �ش� ID ��ǰ ��� ���
    printf("%d\n", remain[id]);

    // ��� ��ǰ ��� ���
    for (int i = 1; i <= N; i++) {
        printf("%d ", remain[i]);
    }
    printf("\n");

    // ��ü �Ǹ��� ��� 
    for (int i = 1; i <= N; i++) {
        if (stock[i] > 0) {
            float sales_rate = (float)sold[i] / stock[i] * 100;
            printf("��ǰ ID %d�� �Ǹ���: %.2f%%\n", i, sales_rate);
        }
        else {
            printf("��ǰ ID %d�� �Ǹ���: 0.00%% (�԰��� 0)\n", i);
        }
    }

    // �ִ� �Ǹŷ� �� �ּ� �Ǹŷ� ��ǰ ���
    int max_sales = 0, min_sales = 1000000000; // ����� ū ������ �ʱ�ȭ
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

    printf("�ִ� �Ǹŷ� ��ǰ ID: %d, �Ǹŷ�: %d\n", max_sales_id, max_sales);
    printf("�ּ� �Ǹŷ� ��ǰ ID: %d, �Ǹŷ�: %d\n", min_sales_id, min_sales);

    return 0;
}
