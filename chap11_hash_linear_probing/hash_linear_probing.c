#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY_SIZE	10	// 탐색키의 최대길이  
#define TABLE_SIZE	13	// 해싱 테이블의 크기=소수 

typedef struct				
{   
	char key[KEY_SIZE];	
    // 다른 필요한 필드들 
} element;

element hash_table[TABLE_SIZE];		// 해싱 테이블 

// 문자로 된 탐색키를 숫자로 변환
int transform1(char *key)
{
	int number=0;
	// 간단한 덧셈 방식 사용 자연수 생성
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

// 제산 함수를 사용한 해싱 함수
int hash_function(char *key)
{
	// 키를 자연수로 변환한 다음 테이블의 크기로 나누어 나머지를 반환
	return transform1(key) % TABLE_SIZE;
} 

// 제산 함수를 사용한 해싱 함수
int hash_function2(char *key)
{
	// 키를 자연수로 변환한 다음 테이블의 크기로 나누어 나머지를 반환
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

// 선형 조사법을 이용하여 테이블에 키를 삽입하고, 
// 테이블이 가득 찬 경우는 종료     
void hash_lp_add( element item, element ht[] )
{ 
   int i, hash_value;
   hash_value = i = hash_function( item.key ) ;
   //printf("hash_address=%d\n", i);
   while(!empty(ht[i])){
      if(equal(item, ht[i])){
	     fprintf(stderr, "탐색키가 중복되었습니다\n");
		 exit(1);
	  }
      i = (i+1) % TABLE_SIZE;
      if(i == hash_value){  
		 fprintf(stderr, "테이블이 가득찼습니다\n");
	     exit(1);
      }
   }
   ht[i]=item;
}

// 선형 조사법을 이용하여 테이블에 키를 삽입하고, 
// 테이블이 가득 찬 경우는 종료     
void hash_qp_add( element item, element ht[] )
{ 
   int i, hash_value, inc=0;
   hash_value = i = hash_function( item.key ) ;
   //printf("hash_address=%d\n", i);
   while(!empty(ht[i])){
      if(equal(item, ht[i])){
	     fprintf(stderr, "탐색키가 중복되었습니다\n");
		 exit(1);
	  }
	  i = (i+inc +1) % TABLE_SIZE;
      inc = inc +2;
      if(i == hash_value){  
		 fprintf(stderr, "테이블이 가득찼습니다\n");
	     exit(1);
      }
   }
   ht[i]=item;
}

// 선형 조사법을 이용하여 테이블에 키를 삽입하고, 
// 테이블이 가득 찬 경우는 종료     
void hash_dh_add( element item, element ht[] )
{ 
   int i, hash_value, inc;
   hash_value = i = hash_function( item.key ) ;
   inc = hash_function2( item.key ) ;
   //printf("hash_address=%d\n", i);
   while(!empty(ht[i])){
      if(equal(item, ht[i])){
	     fprintf(stderr, "탐색키가 중복되었습니다\n");
		 exit(1);
	  }
	  i = (i+inc) % TABLE_SIZE;
      if(i == hash_value){  
		 fprintf(stderr, "테이블이 가득찼습니다\n");
	     exit(1);
      }
   }
   ht[i]=item;
}


// 선형조사법을 이용하여 테이블에 저장된 키를 탐색
void hash_lp_search(element item, element ht[])
{
   int i, hash_value;
   hash_value = i = hash_function(item.key);
   while(!empty(ht[i]))
   {  
      if(equal(item,ht[i])){
		fprintf(stderr, "탐색성공: 위치 = %d\n",i);
		return;
	  }
      i = (i+1) % TABLE_SIZE;
      if(i == hash_value){  
		fprintf(stderr, "찾는 값이 테이블에 없음\n");
		return;
      }
   }
   fprintf(stderr, "찾는 값이 테이블에 없음\n");
}

// 해싱 테이블의 내용을 출력
void hash_lp_print(element ht[])
{
	int i;
	for(i=0;i<TABLE_SIZE;i++)
		printf("[%d]	%s\n", i, ht[i].key); 
}

// 해싱 테이블을 사용한 예제 
main()
{
	element tmp;
	int op;
	while(1){
		printf("원하는 연산을 입력하시오(0=입력, 1=탐색, 2=종료)=");
		scanf("%d",&op);
		if( op == 2 ) break;
		printf("키를 입력하시오=");
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