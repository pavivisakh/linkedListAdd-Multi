

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CLS_SCREEN system("clear")
#define CLS_INPUT_BUFF while(getchar() != '\n')

typedef struct Node{

	struct Node *link;
	int exp;
	int coeff;
	
}Node;

void show_menu();
Node* make_node(int exp, int coeff);
void input_equation(Node **eqn[]);
void show_equations(Node* eqn[]);
void show_result(Node *res);
void revaluate_equation(Node **eqn_header);
void add_equation(Node *eqn1, Node *eqn2, Node **res);
void multiply_equation(Node *eqn1, Node *eqn2, Node **res);
void delete_equation(Node** eqn);
void sort_equation(Node **header);

int main(){
	
	Node *eqn1, *eqn2, *res;
	int option;
	char runAgain;
	
	do{
		CLS_SCREEN;
		printf("\n=======================================\n");
		show_menu();
		printf("\n=======================================\n");
		
		printf("Enter an option : ");
		scanf("%d", &option);
		
		switch(option){
		
			case 1 : input_equation( (Node **[]) {&eqn1, &eqn2} );
					 CLS_SCREEN;
					 show_equations( (Node* []) {eqn1, eqn2} );
					 add_equation(eqn1, eqn2, &res);
					 show_result(res);
					 break;
							
			case 2 : input_equation( (Node **[]) {&eqn1, &eqn2} );
					 CLS_SCREEN;
					 show_equations( (Node* []) {eqn1, eqn2} );
					 multiply_equation(eqn1, eqn2, &res);
					 show_result(res);
					 delete_equation(&eqn1);
					 delete_equation(&eqn2);
					 break;
						
			case 3 : CLS_SCREEN; 
					 exit(EXIT_SUCCESS);
			
			default: printf("Enter a valid option! :(\n");
			
		}
		
		CLS_INPUT_BUFF;
		printf("\nDo want to continue (y/n) : ");
		scanf("%c", &runAgain);
			
		delete_equation(&res);
		CLS_SCREEN;
	}while(runAgain == 'y' || runAgain == 'Y');
	
}

void show_menu(){

	printf("Enter 1 for polynomial addition.\n");
	printf("Enter 2 for polynomial multiplication.\n");
	printf("Enter 3 to exit program.\n");
	
}

Node* make_node(int exp, int coeff){

	Node *new_node = (Node*) malloc(sizeof(Node));
	if(new_node == NULL){
	
		printf("\nFailed to allocate memory! :(\n");
		printf("Closing program!\n");
		exit(EXIT_FAILURE);
	
	}
	
	new_node->link = NULL;
	new_node->exp = exp;
	new_node->coeff = coeff;
	
	return new_node;
	
}

void input_equation(Node **eqn[]){

	Node **ptr;
	int exp, coeff, n_terms;
	
	for(int en = 0; en < 2; en++){
	
		printf("\nEnter equation %d.\n", (en+1));
		//first node(header) is not used to store data.
		*eqn[en] = make_node(0, 0);
		ptr = &((*eqn[en])->link);
	
		while(true){
			
			printf("Enter how many terms : ");
			scanf("%d", &n_terms);
			
			if(n_terms <= 0)
				printf("Number of terms cannot be zero or less than zero!\n\n");
			else 
				break;
			
		}
		
		for(int i = 1; i <= n_terms; i++){
	
			printf("\nEnter term %d details. \n", i);
		
			printf("Enter exponent : ");
			scanf("%d", &exp);
		
			printf("Enter coefficient : ");
			scanf("%d", &coeff);
		
			*ptr = make_node(exp, coeff);
			ptr = &((*ptr)->link);
		
		}
	
	}
	
}

void show_equations(Node* eqn[]){
	
	Node *ptr;
	
	for(int en = 0; en < 2; en++){
	
		putchar('\n');
		printf("Equation %d \n", (en+1));
		printf("Exponent : \t");
		for(ptr = eqn[en]->link; ptr != NULL; ptr = ptr->link)
			printf("%d\t", ptr->exp);	
		putchar('\n');
	
		printf("Coefficient : \t");
		for(ptr = eqn[en]->link; ptr != NULL; ptr = ptr->link)
			printf("%d\t", ptr->coeff);
		putchar('\n');
	}
	
}

void show_result(Node *res){

	Node *ptr;
	printf("\nResult : \n");
	printf("Exponent : \t");
	for(ptr = res->link; ptr != NULL; ptr = ptr->link)
		printf("%d\t", ptr->exp);	
	putchar('\n');
	
	printf("Coefficient : \t");
	for(ptr = res->link; ptr != NULL; ptr = ptr->link)
		printf("%d\t", ptr->coeff);
	putchar('\n');
	
}

void revaluate_equation(Node **eqn_header){

	Node **header = eqn_header;
	Node **nextNode;
	Node *wasteNode;
	int coeff_sum = 0;
	int exp;
	
	for(; *header != NULL; header = &((*header)->link)){
	
		exp = (*header)->exp;
		coeff_sum = (*header)->coeff;
		nextNode = &((*header)->link);
		
		while(*nextNode != NULL){
		
			if((*nextNode)->exp == exp){
				
				coeff_sum = coeff_sum + (*nextNode)->coeff;
				wasteNode = (*nextNode);
				*nextNode = (*nextNode)->link;
				free(wasteNode);
	
			}else{
			
				nextNode = &((*nextNode)->link);
				
			}
			
		}
	
		(*header)->coeff = coeff_sum;
			
	}
}	
	
void add_equation(Node *eqn1, Node *eqn2, Node **res){

	//merging eqn2 into eqn1.
	Node *ptr = eqn1->link;
	for(; ptr->link != NULL; ptr = ptr->link);
	ptr->link = eqn2->link;
	free(eqn2);
	
	*res = make_node(0, 0);
	(*res)->link = eqn1->link;
	free(eqn1);

	revaluate_equation(&((*res)->link));
	sort_equation(res);
}

void multiply_equation(Node *eqn1, Node *eqn2, Node **res){

	Node *ptr1, *ptr2, **ptr3;
	int exp, coeff;
	
	*res = make_node(0, 0);
	ptr3 = &( (*res)->link );
	for(ptr1 = eqn1->link; ptr1 != NULL; ptr1 = ptr1->link){
		
		for(ptr2 = eqn2->link; ptr2 != NULL; ptr2 = ptr2->link){
			
			exp = ptr1->exp + ptr2->exp;
			coeff = ptr1->coeff * ptr2->coeff;
			
			*ptr3 = make_node(exp, coeff);
			 ptr3 = &( (*ptr3)->link);
			
		}
		
	}
		
	revaluate_equation(&((*res)->link));
	sort_equation(res);
	
}

void delete_equation(Node **header){

	Node *waste_node;
	Node *next_node = *header;
	while(next_node != NULL){
	
		waste_node = next_node;
		next_node = next_node->link;
		
		free(waste_node);
		
	}
	
	*header = NULL;
	
}

void sort_equation(Node **header){
	
	Node **i_node = &((*header)->link);
	Node **starting_node = &((*header)->link);
	Node **j_node = starting_node;
	int exp, coeff; 
	
	i_node = &((*i_node)->link);
	
	for(; *i_node != NULL; i_node = &((*i_node)->link)){
	
		for(; *j_node != NULL; j_node = &((*j_node)->link)){
		
			if((*j_node)->link!= NULL){
				
				if((*j_node)->exp < (*j_node)->link->exp){
					
					exp = (*j_node)->exp;
					coeff = (*j_node)->coeff;
					
					(*j_node)->exp = (*j_node)->link->exp;
					(*j_node)->coeff = (*j_node)->link->coeff;
					
					(*j_node)->link->exp = exp;
					(*j_node)->link->coeff = coeff;
					
				}
				
			}else{
			
				break;
				
			}
			
		}
		
		j_node = starting_node;
		
	}
	
}
