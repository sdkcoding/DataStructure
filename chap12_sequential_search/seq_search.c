int seq_search(int key, int low, int high)
{
	int i;
	for (i = low; i <= high; i++)
		if (list[i] == key)
			return i;  // 탐색에 성공하면 키 값의 인덱스 반환 
	return -1;    // 탐색에 실패하면 -1 반환 
}

int seq_search2(int key, int low, int high)
{
	int i;
	list[high + 1] = key;
	for (i = low; list[i] != key; i++) // 키값을 찾으면 종료  
		;
	if (i == (high + 1)) return -1;   // 탐색 실패 
	else     return i;           // 탐색 성공 
}
