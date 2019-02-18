#include<stdio.h>
#include<stdlib.h>

struct list{
	int coef;
	int expon;
	struct list *next;
};
typedef struct list node;
typedef node *link;

void createpoly( link *ptr);  	// �إߦh����
link add( link poly1, link poly2); 	 // ��h�����ۥ[
link mul( link poly1 , link poly2 ); // �h�������Īk
int compare( int , int );  // �����h���������Ƥj�p
void attach( int , int , link *ptr);  // �N�@�Ӹ`�I���[�b��C������
void printfresult( link ); // printf �h�����B�⪺���G
link freelist( link temp ); // ����Ŷ�

int main(){
	link poly1 = NULL;  // intially there are no nodes
	link poly2 = NULL;
	link answer = NULL;  // ��m�h�������B�⵲�G
	link temp;
	printf( "�п�J��Ӧh����  \n");
	printf( "please input first polynomial :\n" ); // �Ĥ@�Ӧh����
	createpoly(&poly1);
	printf( "please input second polynomial :\n" );  // �ĤG�Ӧh����
	createpoly(&poly2);
	printf( "��h���������k�B�⵲�G\n" );
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
		scanf( "%d", &coef );   // �Y��
		getchar();              //  ^
		scanf( "%d", &expon );  // ����
		scanf( "%c", &token );  // ���t��

		if( !head ){  // �phead��NULL��
			head =( node *)malloc( sizeof ( node ));  //creat node
			head->coef = coef * sign; // place �Y�ƭ� in node
			head->expon = expon;      // place ���ƭ� in node
			head->next = NULL;        // node does not link to another node

		}
		else{
			current = head; // �����C����
			while( current->next !=NULL ){ // ��while�O�b���C���̫�@�Ӹ`�I �N�Ocurrent->next �� NULL��
				current = current->next;
			}
			current->next = (node *)malloc( sizeof( node)); // �b��C�̫�Acreat�@��node
			current->next->coef = coef * sign ;  // place �Y�ƭ� in node
			current->next->expon = expon;        // place ���ƭ� in node
			current->next->next = NULL;	         // node does not link to another node
		}

        // �P�w�U�@�������t��
		if( token == '+')  // ��
			sign = 1;
		else if( token == '-')  // �t
			sign = -1;

	}while( token != '\n');  // ��token��enter�ɴN����while

	*ptr = head;  // head assign ��*sptr �����C����

}

// �h�������[�k
link add( link poly1, link poly2){
	link front , rear, temp;
	int sum;
	rear = ( node *)malloc( sizeof( node ));  //creat node
	front = rear;


	while( poly1, poly2 )
		switch( compare( poly1->expon, poly2->expon )){

		case -1:  // poly1->expon �p�� poly2->expon
			attach( poly2->coef, poly2->expon, &rear);
			poly2 = poly2->next;
			break;

		case 0:  // poly1->expon ���� poly2->expon
			sum = poly1->coef + poly2->coef ;
			if( sum )
				attach( sum, poly1->expon, &rear);
			poly1 = poly1->next;
			poly2 = poly2->next;
			break;

		case 1:  // poly1->expon �j�� poly2->expon
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

// �h���������k
link mul( link poly1, link poly2){
	link temp = NULL , sum = NULL;
	link first;
	int coef , expon;

	first = poly1;
	while( poly2 != NULL){
		while( poly1 != NULL){
			coef = ( poly1->coef ) * ( poly2->coef );
			expon = ( poly1->expon ) * ( poly2->expon );
			attach( coef, expon, &temp );  // �N�@�Ӹ`�I���[�b��C������
			poly1 = poly1->next;  // poly1 �U�@�Ӹ`�I
		}
		sum = add( temp , sum );
		poly2 = poly2->next;
		poly1 = first;  // poly1 �^��̭���
		temp = freelist( temp );  // ���^�`�I��C�Ŷ�
	}
	return sum;

}

// ���poly1 �Mpoly2 �����ƪ��j�p
int compare( int a, int b){
	if( a < b)       return -1;
    else if( a > b)  return 1;
	else             return 0;
}

// �N�@�Ӹ`�I���[�b��C������
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

// ��B�⤧�᪺�h����printf�X��
void printfresult( link node ){
	while( node != NULL ){
		if( node->coef > 0 ){  // �Y�Ƭ�����
			printf( "+%d^%d", node->coef, node->expon);
		}
		else{    // �Y�Ƭ��t��
			printf( "%d^%d", node->coef, node->expon);
		}
		node = node->next; // ��U�@��node
	}
	printf( "\n" );

}

// ���^�`�I��C�Ŷ�
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

