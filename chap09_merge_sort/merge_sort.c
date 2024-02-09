#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ex01    0
#define ex02    1

#if ex01
int n = 10;
int arr[1000001] = { 15, 25, 22, 357, 16, 23, -53, 12, 46, 3 };
int tmp[1000001]; // merge 함수에서 리스트 2개를 합친 결과를 임시로 저장하고 있을 변수

// mid = (st+en)/2라고 할 때 arr[st:mid], arr[mid:en]은 이미 정렬이 되어있는 상태일 때 arr[st:mid]와 arr[mid:en]을 합친다.
void merge(int st, int en) {
    int mid = (st + en) / 2;
    int lidx = st; // arr[st:mid]에서 값을 보기 위해 사용하는 index
    int ridx = mid; // arr[mid:en]에서 값을 보기 위해 사용하는 index
    for (int i = st; i < en; i++) {
        if (ridx == en) tmp[i] = arr[lidx++];
        else if (lidx == mid) tmp[i] = arr[ridx++];
        else if (arr[lidx] <= arr[ridx]) tmp[i] = arr[lidx++];
        else tmp[i] = arr[ridx++];
    }
    for (int i = st; i < en; i++) arr[i] = tmp[i]; // tmp에 임시저장해둔 값을 a로 다시 옮김
}

// a[st:en]을 정렬하고 싶다.
void merge_sort(int st, int en) {
    if (en == st + 1) return; // 리스트의 길이가 1인 경우
    int mid = (st + en) / 2;
    merge_sort(st, mid); // arr[st:mid]을 정렬한다.
    merge_sort(mid, en); // arr[mid:en]을 정렬한다.
    merge(st, en); // arr[st:mid]와 arr[mid:en]을 합친다.
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

/* i는 정렬된 왼쪽리스트에 대한 인덱스
   j는 정렬된 오른쪽리스트에 대한 인덱스
   k는 정렬될 리스트에 대한 인덱스 */
void merge(int list[], int left, int mid, int right)
{
    int i, j, k, l;
    i = left;  j = mid + 1;  k = left;

    /* 분할 정렬된 list의 합병 */
    while (i <= mid && j <= right) {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if (i > mid)	/* 남아 있는 레코드의 일괄 복사 */
        for (l = j; l <= right; l++)
            sorted[k++] = list[l];
    else	/* 남아 있는 레코드의 일괄 복사 */
        for (l = i; l <= mid; l++)
            sorted[k++] = list[l];
    /* 배열 sorted[]의 리스트를 배열 list[]로 재복사 */
    for (l = left; l <= right; l++)
        list[l] = sorted[l];
}
//
void merge_sort(int list[], int left, int right)
{
    int mid;
    if (left < right) {
        mid = (left + right) / 2;     /* 리스트의 균등 분할 */
        merge_sort(list, left, mid);    /* 부분 리스트 정렬 */
        merge_sort(list, mid + 1, right); /* 부분 리스트 정렬 */
        merge(list, left, mid, right);    /* 합병 */
    }
}

void main()
{
    int i;
    n = MAX_SIZE;

    srand(time(NULL));
    for (i = 0; i < n; i++)      	/* 난수 생성 및 출력 */
        list[i] = rand() % (50 - -50 + 1) + -50;/*난수 발생 범위 0~MAX_SIZE*/

    merge_sort(list, 0, n); /* 머지정렬 호출 */
    for (i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
    merge_sort(list, 0, n); /* 머지정렬 호출 */
    for (i = 0; i < n; i++)
        printf("%d ", list[i]);
}
#endif