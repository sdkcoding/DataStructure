#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY_SIZE	10	// Ž��Ű�� �ִ����  
#define TABLE_SIZE	13	// �ؽ� ���̺��� ũ��=�Ҽ� 

typedef struct				
{   
	char key[KEY_SIZE];	
    // �ٸ� �ʿ��� �ʵ�� 
} element;

element hash_table[TABLE_SIZE];		// �ؽ� ���̺� 

// ���ڷ� �� Ž��Ű�� ���ڷ� ��ȯ
int transform1(char *key)
{
	int number=0;
	// ������ ���� ��� ��� �ڿ��� ����
	while(*key){
		//printf("%d ", *key);
		number += *key++;
	}
	//printf("%d\n", number);
	return number;
}

int transform(char *key)
{
	int number=0;
	while(*key)
		number = 31*number + *key++;
	return number;
} 

// ���� �Լ��� ����� �ؽ� �Լ�
int hash_function(char *key)
{
	// Ű�� �ڿ����� ��ȯ�� ���� ���̺��� ũ��� ������ �������� ��ȯ
	return transform1(key) % TABLE_SIZE;
} 

// ���� �Լ��� ����� �ؽ� �Լ�
int hash_function2(char *key)
{
	// Ű�� �ڿ����� ��ȯ�� ���� ���̺��� ũ��� ������ �������� ��ȯ
	return 5-transform1(key) % TABLE_SIZE;
} 

void init_table(element ht[])
{
	int i;
	for(i=0;i<TABLE_SIZE;i++){
		ht[i].key[0]=NULL;
	}
}

#define empty(item) (strlen(item.key)==0)
#define equal(item1, item2) (!strcmp(item1.key,item2.key))

// ���� ������� �̿��Ͽ� ���̺� Ű�� �����ϰ�, 
// ���̺��� ���� �� ���� ����     
void hash_lp_add( element item, element ht[] )
{ 
   int i, hash_value;
   hash_value = i = hash_function( item.key ) ;
   //printf("hash_address=%d\n", i);
   while(!empty(ht[i])){
      if(equal(item, ht[i])){
	     fprintf(stderr, "Ž��Ű�� �ߺ��Ǿ����ϴ�\n");
		 exit(1);
	  }
      i = (i+1) % TABLE_SIZE;
      if(i == hash_value){  
		 fprintf(stderr, "���̺��� ����á���ϴ�\n");
	     exit(1);
      }
   }
   ht[i]=item;
}

// ���� ������� �̿��Ͽ� ���̺� Ű�� �����ϰ�, 
// ���̺��� ���� �� ���� ����     
void hash_qp_add( element item, element ht[] )
{ 
   int i, hash_value, inc=0;
   hash_value = i = hash_function( item.key ) ;
   //printf("hash_address=%d\n", i);
   while(!empty(ht[i])){
      if(equal(item, ht[i])){
	     fprintf(stderr, "Ž��Ű�� �ߺ��Ǿ����ϴ�\n");
		 exit(1);
	  }
	  i = (i+inc +1) % TABLE_SIZE;
      inc = inc +2;
      if(i == hash_value){  
		 fprintf(stderr, "���̺��� ����á���ϴ�\n");
	     exit(1);
      }
   }
   ht[i]=item;
}

// ���� ������� �̿��Ͽ� ���̺� Ű�� �����ϰ�, 
// ���̺��� ���� �� ���� ����     
void hash_dh_add( element item, element ht[] )
{ 
   int i, hash_value, inc;
   hash_value = i = hash_function( item.key ) ;
   inc = hash_function2( item.key ) ;
   //printf("hash_address=%d\n", i);
   while(!empty(ht[i])){
      if(equal(item, ht[i])){
	     fprintf(stderr, "Ž��Ű�� �ߺ��Ǿ����ϴ�\n");
		 exit(1);
	  }
	  i = (i+inc) % TABLE_SIZE;
      if(i == hash_value){  
		 fprintf(stderr, "���̺��� ����á���ϴ�\n");
	     exit(1);
      }
   }
   ht[i]=item;
}


// ����������� �̿��Ͽ� ���̺� ����� Ű�� Ž��
void hash_lp_search(element item, element ht[])
{
   int i, hash_value;
   hash_value = i = hash_function(item.key);
   while(!empty(ht[i]))
   {  
      if(equal(item,ht[i])){
		fprintf(stderr, "Ž������: ��ġ = %d\n",i);
		return;
	  }
      i = (i+1) % TABLE_SIZE;
      if(i == hash_value){  
		fprintf(stderr, "ã�� ���� ���̺� ����\n");
		return;
      }
   }
   fprintf(stderr, "ã�� ���� ���̺� ����\n");
}

// �ؽ� ���̺��� ������ ���
void hash_lp_print(element ht[])
{
	int i;
	for(i=0;i<TABLE_SIZE;i++)
		printf("[%d]	%s\n", i, ht[i].key); 
}

// �ؽ� ���̺��� ����� ���� 
main()
{
	element tmp;
	int op;
	while(1){
		printf("���ϴ� ������ �Է��Ͻÿ�(0=�Է�, 1=Ž��, 2=����)=");
		scanf("%d",&op);
		if( op == 2 ) break;
		printf("Ű�� �Է��Ͻÿ�=");
		scanf("%s",tmp.key);
		if( op == 0 ){
			hash_qp_add(tmp, hash_table);
		}
		else if( op == 1 ){
			hash_lp_search(tmp, hash_table);
		}
		hash_lp_print(hash_table);
	}
}