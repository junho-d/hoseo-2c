#include <stdio.h>

int main() {
    int N; // ��ǰ ���� ��
    int stock[101];   // �԰� ����
    int sold[101];    // �Ǹ� ����
    int remain[101];  // ��� ����
    int total_sold = 0, total_stock = 0;
    int max_id = 1, min_id = 1;

    // ��ǰ ���� �Է�
    scanf_s("%d", &N);

    // �԰� ���� �Է�
    for (int i = 1; i <= N; i++) {
        scanf_s("%d", &stock[i]);
        total_stock += stock[i];
    }

    // �Ǹ� ���� �Է�
    for (int i = 1; i <= N; i++) {
        scanf_s("%d", &sold[i]);
        remain[i] = stock[i] - sold[i];
        total_sold += sold[i];
    }

    // ��� ��ǰ ��� ���
    printf("������ : ");
    for (int i = 1; i <= N; i++) {
        printf("%d", remain[i]);
    }
    printf("\n");

    // ��ü �Ǹŷ� �� �Ǹ��� ���
    double rate = 0.0;
    if (total_stock > 0) {
        rate = (double)total_sold / total_stock * 100.0;
    }
    printf("�� �Ǹŷ� : %d (�Ǹ��� %.2f%%)\n", total_sold, rate);

    // �ִ� �Ǹ�, �ּ� �Ǹ� ��ǰ ã��
    for (int i = 2; i <= N; i++) {
        if (sold[i] > sold[max_id]) max_id = i;
        if (sold[i] < sold[min_id]) min_id = i;
    }
    printf("���� ���� �Ǹŵ� ��ǰ : ID %d, �Ǹŷ� %d\n", max_id, sold[max_id]);
    printf("���� ���� �Ǹŵ� ��ǰ : ID %d, �Ǹŷ� %d\n", min_id, sold[min_id]);

    // ��� ���� ��� (��� ������ 2 ������ ��)
    for (int i = 1; i <= N; i++) {
        if (remain[i] <= 2) {
            printf("��ǰ ID %d : ������(%d)\n", i, remain[i]);
        }
    }

    return 0;
}
