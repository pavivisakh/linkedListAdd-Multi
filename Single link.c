
/*
 * Program implementing various Single Linked List Operations.  
 * 1 Insertion
 * 2 Deletion
 * 3 Searching
 * 4 Sorting
 * 5 Mergeing
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define CLS_INPUT_BUFF while(getchar() != '\n')
#define CLS_SCREEN system("clear")
#define MAIN_PROCESS 1
#define SUB_PROCESS 2

bool CREATED_LIST = false;


typedef struct Node{
	
	struct Node *link;
	int data;
	
}Node;


//function prototypes
void show_menu();
Node* make_node(int data);
void delete_complete_list(Node **header);
void create_list_and_input_node(Node **header, int PROCESS_TYPE);
void show_complete_list(Node **header);
void insert_at_beginning(Node **header);
void insert_before_node(Node **header);
void insert_at_end(Node **header);
void delete_from_beginning(Node **header);
void delete_by_data(Node **header);
void delete_from_end(Node **header);
Node* search_key(Node **header);
void sort_list(Node **header);
void merge_list(Node **header);


int main(){
	
	Node *header = NULL;
	int option;
	
	char choice;
	
	do{
		
		show_menu();
		
		printf("\nEnter an option : ");
		scanf("%d", &option);
		
		switch(option){
			
			case 1: create_list_and_input_node(&header, MAIN_PROCESS);
					break;
					
			case 2: show_complete_list(&header);
					break;
					
			case 3: insert_at_beginning(&header);
					break;
					
			case 4: insert_before_node(&header);
					break;
					
			case 5: insert_at_end(&header);
					break;
					
			case 6: delete_from_beginning(&header);
					break;
			
			case 7: delete_by_data(&header);
					break;
					
			case 8: delete_from_end(&header);
					break;
					
			case 9: (void) search_key(&header);
					break;
					
			case 10: sort_list(&header);
					 break;
					 
			case 11: merge_list(&header);
					 break;
					 
			case 12: CLS_SCREEN; 
					 exit(EXIT_SUCCESS);
					
			default: printf("Enter a valid option!\n");
			
		}
		
		CLS_INPUT_BUFF;
		printf("\nDo you want to continue (y/n) : ");
		scanf("%c", &choice);
		
	}while(choice == 'y' || choice == 'Y');
	
	CLS_SCREEN;
	return EXIT_SUCCESS;
	
}


void show_menu(){

	CLS_SCREEN;

	printf("\n===============================================\n");
	printf("Enter 1 to create new list and input nodes.\n");
	printf("Enter 2 to show complete list.\n");
	printf("Enter 3 to insert node at beginning.\n");
	printf("Enter 4 to insert node before data. \n");
	printf("Enter 5 to insert node at end. \n");
	printf("Enter 6 to delete node from beginning. \n");
	printf("Enter 7 to delete node by data. \n");
	printf("Enter 8 to delete node from end. \n");
	printf("Enter 9 to search key in list. \n");  
	printf("Enter 10 to sort list. \n");
	printf("Enter 11 to merge list. \n");
	printf("Enter 12 to exit program. \n");
	printf("===============================================\n");
	
}


Node* make_node(int data){

	Node *new_node = (Node*) malloc(sizeof(Node));
	
	if(new_node == NULL){
	
		printf("Failed to allocate memory for node! :( \n");
		exit(EXIT_FAILURE);
	
	}
	
	new_node->link = NULL;
	new_node->data = data;
	
	return new_node;
	
}


void delete_complete_list(Node **header){

	Node *waste_node;
	Node *next_node = *header;
	while(next_node != NULL){
	
		waste_node = next_node;
		next_node = next_node->link;
		
		free(waste_node);
		
	}
	
	*header = NULL;
	
}


void create_list_and_input_node(Node **header, int PROCESS_TYPE){

	Node **next_node_link;
	int n_nodes, data;
	char choice;
	
	if(CREATED_LIST == true && (*header)->link != NULL && PROCESS_TYPE == MAIN_PROCESS){
	
		CLS_INPUT_BUFF;
		printf("List already created do you want to override it (y/n) : ");
		scanf("%c", &choice);
		
		if(choice == 'n') return;
		
		delete_complete_list(header);
		
	}else if(CREATED_LIST == true && (*header)->link == NULL){
	
		free(*header);
		*header = NULL;
		
	}
	
	if(PROCESS_TYPE == MAIN_PROCESS)
		CREATED_LIST = true;
	
	while(true){
		
		printf("\nEnter how many nodes to create : ");
		scanf("%d", &n_nodes);
	
		if(n_nodes <= 0) 
			printf("Number of nodes cannot be or less than zero!\n");
		else break;
			
	}
	
	
	//first node is unused!.
	*header = make_node(0);
	next_node_link = &((*header)->link);
	
	
	for(int i = 1; i <= n_nodes; i++){
	
		printf("Enter data for node %d : ", i);
		scanf("%d", &data);
		
		*next_node_link = make_node(data);
		next_node_link = &((*next_node_link)->link);
		
	}
	
	if(PROCESS_TYPE == MAIN_PROCESS)
		printf("Successfully created list! :) \n");
	
}


void show_complete_list(Node **header){
	
	if(*header == NULL){
	
		printf("Please create a list! \n");
		return;
	
	}else if ((*header)->link == NULL){
	
		printf("No nodes in list to display! \n");
		return;
		
	}
	
	Node **next_node = &((*header)->link);
	
	for(int i = 1; *next_node != NULL; next_node = &((*next_node)->link), i++)
		printf("NODE %d = %d\n", i, (*next_node)->data);
	
}


void insert_at_beginning(Node **header){
	
	Node *new_node;
	int data;
	
	if(*header == NULL){
	
		printf("Please create list! \n");
		printf("Insertion failed! :( \n");
		return;
		
	}
	
	printf("Enter data to insert : ");
	scanf("%d", &data);
	
	new_node = make_node(data);

	new_node->link = (*header)->link;
	(*header)->link = new_node;
	
	printf("Successfully wrote! :) \n");
	
}


void insert_before_node(Node **header){

	if(*header == NULL){
	
		printf("Please create list! \n");
		printf("Insertion failed! :( \n");
		return;
		
	}

	int key, data;
	
	printf("Enter a key : ");
	scanf("%d", &key);
	
	Node **next_node = &((*header)->link);
	for(; *next_node != NULL; next_node = &((*next_node)->link)){
	
		if((*next_node)->data == key){
			
			printf("Enter data to insert : ");
			scanf("%d", &data);
	
			Node *new_node = make_node(data);
	
			new_node->link = *next_node;
			*next_node = new_node;
	
			printf("Successfully wrote! :) \n");
			
			return;
			
		}
	
	}
	
	printf("Key ' %d ' not found in any nodes in list!\n", key);
	printf("Insertion failed! :( \n");
	return;
		
}


void insert_at_end(Node **header){
	
	if(*header == NULL){
	
		printf("Please create list! \n");
		printf("Insertion failed! :( \n");
		return;
		
	}
	
	Node **next_node = &((*header)->link);
	int data;
	
	printf("Enter data to insert : ");
	scanf("%d", &data);
	
	for(; *next_node != NULL; next_node = &((*next_node)->link));
	
	*next_node = make_node(data);
	
	printf("Successfully wrote! :) \n");
	
}


void delete_from_beginning(Node **header){

	if(*header == NULL){
	
		printf("Please create list! \n");
		printf("Deletion failed! :( \n");
		return;
		
	}else if((*header)->link == NULL){
	
		printf("No nodes in list to delete! \n");
		printf("Deletion failed! :( \n");
		return;
		
	}

	Node *waste_node = (*header)->link;
	(*header)->link = waste_node->link;
	free(waste_node);
	
	printf("Successfully deleted :) \n");
	
}


void delete_by_data(Node **header){

	if(*header == NULL){
	
		printf("Please create list! \n");
		printf("Deletion failed! :( \n");
		return;
		
	}else if((*header)->link == NULL){
	
		printf("No nodes in list to delete! \n");
		printf("Deletion failed! :( \n");
		return;
		
	}


	bool found_data = false;
	Node **next_node = &((*header)->link);
	int data;
	
	printf("Enter data to delete : ");
	scanf("%d", &data);
	
	for(; *next_node != NULL; next_node = &((*next_node)->link)){
		
		if((*next_node)->data == data){
		
			found_data = true;
			break;
			
		}
		
	}
	
	if(found_data == false){
	
		printf("Data ' %d ' not found in any nodes in list!\n", data);
		printf("Deletion failed! :( \n");
		
		return;
		
	}
	
	Node *waste_node = *next_node;
	*next_node = (*next_node)->link;
	
	free(waste_node);
	
	printf("Successfully deleted :) \n");
	
}


void delete_from_end(Node **header){
	
	if(*header == NULL){
	
		printf("Please create list! \n");
		printf("Deletion failed! :( \n");
		return;
		
	}else if((*header)->link == NULL){
	
		printf("No nodes in list to delete! \n");
		printf("Deletion failed! :( \n");
		return;
		
	}
	
	
	Node **next_node = header;
	Node *waste_node;
	
	if((*header)->link == NULL){
	
		printf("No nodes in list! \n");
		printf("Deletion failed :( \n");
		return;
		
	}
	
	for(; *next_node != NULL; next_node = &((*next_node)->link)){
	
		if((*next_node)->link->link == NULL)
			break;
		
	}
	
	waste_node = (*next_node)->link;
	(*next_node)->link = NULL;
	free(waste_node);
	
	printf("Successfully deleted! :) \n");
	
}


//searching using linear search.
Node* search_key(Node **header){

	if(*header == NULL){
	
		printf("Please create list! \n");
		printf("Searching failed! :( \n");
		return NULL;
		
	}else if((*header)->link == NULL){
	
		printf("No nodes in list to search! \n");
		printf("Searching failed! :( \n");
		return NULL;
	}


	Node **next_node = &((*header)->link);
	int key;
	
	printf("Enter a key to search : ");
	scanf("%d", &key);
	
	
	for(int i = 1; *next_node != NULL; next_node = &((*next_node)->link), i++){
	
		if((*next_node)->data == key){
		
			printf("Key ' %d ' found in list! :) \n", key);
			printf("Key ' %d ' found in node %d \n", key, i);
			return *next_node;
			
		}
		
	}
	
	printf("Key ' %d ' not found in any nodes in list! :( \n", key);
	return NULL;
	
}


//sorting using bubble sort.
void sort_list(Node **header){
	
	if(*header == NULL){
	
		printf("Please create list! \n");
		printf("Sorting failed! :( \n");
		return;
		
	}else if((*header)->link == NULL){
	
		printf("No nodes in list to sort! \n");
		printf("Sorting failed! :( \n");
		return;
	}

	Node **i_node = &((*header)->link);
	Node **starting_node = &((*header)->link);
	Node **j_node = starting_node;
	int temp; 
	
	i_node = &((*i_node)->link);
	
	for(; *i_node != NULL; i_node = &((*i_node)->link)){
	
		for(; *j_node != NULL; j_node = &((*j_node)->link)){
		
			if((*j_node)->link!= NULL){
				
				if((*j_node)->data > (*j_node)->link->data){
					
					temp = (*j_node)->data;
					(*j_node)->data = (*j_node)->link->data;
					(*j_node)->link->data = temp;
					
				}
				
			}else{
			
				break;
				
			}
			
		}
		
		j_node = starting_node;
		
	}
	
	printf("Successfully sorted! :) \n");
	
}


void merge_list(Node **header){
	
	if(*header == NULL){
	
		printf("Please create list! \n");
		printf("Merging failed! :( \n");
		return;
		
	}
	
	Node **next_node = header;
	Node *new_list_header;
	
	create_list_and_input_node(&new_list_header, SUB_PROCESS);
	
	for(; *next_node != NULL; next_node = &((*next_node)->link));
	
	*next_node = new_list_header->link;
	free(new_list_header);
	
	printf("Successfully merged! :) \n");
	
}
