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

    // ��ȸ�� ID �Է�
    scanf_s("%d", &id);

    // �ش� ID ��ǰ ��� ���
    printf("%d\n", remain[id]);

    // ��� ��ǰ ��� ���
    for (int i = 1; i <= N; i++) {
        printf("%d ", remain[i]);
    }
    printf("\n");

    return 0;
}
