int seq_search(int key, int low, int high)
{
	int i;
	for (i = low; i <= high; i++)
		if (list[i] == key)
			return i;  // Ž���� �����ϸ� Ű ���� �ε��� ��ȯ 
	return -1;    // Ž���� �����ϸ� -1 ��ȯ 
}

int seq_search2(int key, int low, int high)
{
	int i;
	list[high + 1] = key;
	for (i = low; list[i] != key; i++) // Ű���� ã���� ����  
		;
	if (i == (high + 1)) return -1;   // Ž�� ���� 
	else     return i;           // Ž�� ���� 
}
