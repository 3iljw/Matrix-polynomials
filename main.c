#include<stdio.h>
#include<stdlib.h>

struct list{
	int coef;
	int expon;
	struct list *next;
};
typedef struct list node;
typedef node *link;

void createpoly( link *ptr);  	// 建立多項式
link add( link poly1, link poly2); 	 // 兩多項式相加
link mul( link poly1 , link poly2 ); // 多項式的乖法
int compare( int , int );  // 比較兩多項式的指數大小
void attach( int , int , link *ptr);  // 將一個節點附加在串列的結尾
void printfresult( link ); // printf 多項式運算的結果
link freelist( link temp ); // 釋放空間

int main(){
	link poly1 = NULL;  // intially there are no nodes
	link poly2 = NULL;
	link answer = NULL;  // 放置多項式的運算結果
	link temp;
	printf( "請輸入兩個多項式  \n");
	printf( "please input first polynomial :\n" ); // 第一個多項式
	createpoly(&poly1);
	printf( "please input second polynomial :\n" );  // 第二個多項式
	createpoly(&poly2);
	printf( "兩多項式的乘法運算結果\n" );
    answer = mul( poly1 , poly2 );
	printfresult( answer );
}

void createpoly( link *ptr){
	link head=NULL;  // pointer to head
	link current;    // pointer to current

	int coef , expon ;
	int sign = 1 ;
	char token ;

	do{
		scanf( "%d", &coef );   // 係數
		getchar();              //  ^
		scanf( "%d", &expon );  // 指數
		scanf( "%c", &token );  // 正負號

		if( !head ){  // 如head為NULL時
			head =( node *)malloc( sizeof ( node ));  //creat node
			head->coef = coef * sign; // place 係數值 in node
			head->expon = expon;      // place 指數值 in node
			head->next = NULL;        // node does not link to another node

		}
		else{
			current = head; // 指到串列之首
			while( current->next !=NULL ){ // 此while是在找串列的最後一個節點 就是current->next 為 NULL時
				current = current->next;
			}
			current->next = (node *)malloc( sizeof( node)); // 在串列最後再creat一個node
			current->next->coef = coef * sign ;  // place 係數值 in node
			current->next->expon = expon;        // place 指數值 in node
			current->next->next = NULL;	         // node does not link to another node
		}

        // 判定下一項的正負號
		if( token == '+')  // 正
			sign = 1;
		else if( token == '-')  // 負
			sign = -1;

	}while( token != '\n');  // 當token為enter時就結束while

	*ptr = head;  // head assign 給*sptr 指到串列之首

}

// 多項式的加法
link add( link poly1, link poly2){
	link front , rear, temp;
	int sum;
	rear = ( node *)malloc( sizeof( node ));  //creat node
	front = rear;


	while( poly1, poly2 )
		switch( compare( poly1->expon, poly2->expon )){

		case -1:  // poly1->expon 小於 poly2->expon
			attach( poly2->coef, poly2->expon, &rear);
			poly2 = poly2->next;
			break;

		case 0:  // poly1->expon 等於 poly2->expon
			sum = poly1->coef + poly2->coef ;
			if( sum )
				attach( sum, poly1->expon, &rear);
			poly1 = poly1->next;
			poly2 = poly2->next;
			break;

		case 1:  // poly1->expon 大於 poly2->expon
			attach( poly1->coef, poly1->expon, &rear);
			poly1 = poly1->next;
			break;
	}

	/*copy rest of list head1 and then head2*/
	for( ; poly1 ; poly1 = poly1->next)
		attach( poly1->coef, poly1->expon, &rear);
	for( ; poly2 ; poly2 = poly2->next)
		attach( poly2->coef, poly2->expon, &rear);
	rear->next = NULL;

	/* delete extra initial node */
	temp = front;
	front = front->next;
	free( temp );
	return front;
}

// 多項式的乘法
link mul( link poly1, link poly2){
	link temp = NULL , sum = NULL;
	link first;
	int coef , expon;

	first = poly1;
	while( poly2 != NULL){
		while( poly1 != NULL){
			coef = ( poly1->coef ) * ( poly2->coef );
			expon = ( poly1->expon ) * ( poly2->expon );
			attach( coef, expon, &temp );  // 將一個節點附加在串列的結尾
			poly1 = poly1->next;  // poly1 下一個節點
		}
		sum = add( temp , sum );
		poly2 = poly2->next;
		poly1 = first;  // poly1 回到最首項
		temp = freelist( temp );  // 釋回節點串列空間
	}
	return sum;

}

// 比較poly1 和poly2 的指數的大小
int compare( int a, int b){
	if( a < b)       return -1;
    else if( a > b)  return 1;
	else             return 0;
}

// 將一個節點附加在串列的結尾
void attach( int coefficient , int exponent, link *ptr){
	/* creat a new node with coef = coefficient and expon = exponent,
	   attach it to the node pointed to by sptr,
	   sptr is updated to point to this new node*/

	link  temp;
	temp = ( node *)malloc( sizeof( node ));  //creat node
	temp->coef = coefficient ;
	temp->expon = exponent ;
	ptr->next = temp;
	ptr = temp;
}

// 把運算之後的多項式printf出來
void printfresult( link node ){
	while( node != NULL ){
		if( node->coef > 0 ){  // 係數為正時
			printf( "+%d^%d", node->coef, node->expon);
		}
		else{    // 係數為負時
			printf( "%d^%d", node->coef, node->expon);
		}
		node = node->next; // 到下一個node
	}
	printf( "\n" );

}

// 釋回節點串列空間
link freelist( link head ){
	link temp;

	while(temp != NULL){
		temp = head->next;
		free(head);
		head = temp;
	}

	head = NULL;
	return head;
}

