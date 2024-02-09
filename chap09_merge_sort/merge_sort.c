#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ex01    0
#define ex02    1

#if ex01
int n = 10;
int arr[1000001] = { 15, 25, 22, 357, 16, 23, -53, 12, 46, 3 };
int tmp[1000001]; // merge �Լ����� ����Ʈ 2���� ��ģ ����� �ӽ÷� �����ϰ� ���� ����

// mid = (st+en)/2��� �� �� arr[st:mid], arr[mid:en]�� �̹� ������ �Ǿ��ִ� ������ �� arr[st:mid]�� arr[mid:en]�� ��ģ��.
void merge(int st, int en) {
    int mid = (st + en) / 2;
    int lidx = st; // arr[st:mid]���� ���� ���� ���� ����ϴ� index
    int ridx = mid; // arr[mid:en]���� ���� ���� ���� ����ϴ� index
    for (int i = st; i < en; i++) {
        if (ridx == en) tmp[i] = arr[lidx++];
        else if (lidx == mid) tmp[i] = arr[ridx++];
        else if (arr[lidx] <= arr[ridx]) tmp[i] = arr[lidx++];
        else tmp[i] = arr[ridx++];
    }
    for (int i = st; i < en; i++) arr[i] = tmp[i]; // tmp�� �ӽ������ص� ���� a�� �ٽ� �ű�
}

// a[st:en]�� �����ϰ� �ʹ�.
void merge_sort(int st, int en) {
    if (en == st + 1) return; // ����Ʈ�� ���̰� 1�� ���
    int mid = (st + en) / 2;
    merge_sort(st, mid); // arr[st:mid]�� �����Ѵ�.
    merge_sort(mid, en); // arr[mid:en]�� �����Ѵ�.
    merge(st, en); // arr[st:mid]�� arr[mid:en]�� ��ģ��.
}

int main(void) {
    merge_sort(0, n);
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]); // -53 3 12 15 16 22 23 25 46 357
}
#endif
#if ex02
#define MAX_SIZE 11
int list[MAX_SIZE];
int n;
int sorted[MAX_SIZE];

/* i�� ���ĵ� ���ʸ���Ʈ�� ���� �ε���
   j�� ���ĵ� �����ʸ���Ʈ�� ���� �ε���
   k�� ���ĵ� ����Ʈ�� ���� �ε��� */
void merge(int list[], int left, int mid, int right)
{
    int i, j, k, l;
    i = left;  j = mid + 1;  k = left;

    /* ���� ���ĵ� list�� �պ� */
    while (i <= mid && j <= right) {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if (i > mid)	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
        for (l = j; l <= right; l++)
            sorted[k++] = list[l];
    else	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
        for (l = i; l <= mid; l++)
            sorted[k++] = list[l];
    /* �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �纹�� */
    for (l = left; l <= right; l++)
        list[l] = sorted[l];
}
//
void merge_sort(int list[], int left, int right)
{
    int mid;
    if (left < right) {
        mid = (left + right) / 2;     /* ����Ʈ�� �յ� ���� */
        merge_sort(list, left, mid);    /* �κ� ����Ʈ ���� */
        merge_sort(list, mid + 1, right); /* �κ� ����Ʈ ���� */
        merge(list, left, mid, right);    /* �պ� */
    }
}

void main()
{
    int i;
    n = MAX_SIZE;

    srand(time(NULL));
    for (i = 0; i < n; i++)      	/* ���� ���� �� ��� */
        list[i] = rand() % (50 - -50 + 1) + -50;/*���� �߻� ���� 0~MAX_SIZE*/

    merge_sort(list, 0, n); /* �������� ȣ�� */
    for (i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
    merge_sort(list, 0, n); /* �������� ȣ�� */
    for (i = 0; i < n; i++)
        printf("%d ", list[i]);
}
#endif