#include<stdio.h>
#include<stdlib.h>

struct node{
 int coeff;
 int expo;
 struct node*link;
};


struct node * createNode(struct node*head,int coeff,int expo){
    struct node*newNode=(struct node*)malloc(sizeof (struct node));
if(newNode == NULL){
 printf("Memory allocation failed..\n");
 exit(1);

}
 newNode->coeff = coeff;
 newNode->expo = expo;
 newNode->link=NULL;

 if(head == NULL){
 head = newNode;
}
else{
  struct node* current = head;
  while (current->link != NULL){
    current = current->link;
   }
  current->link = newNode;
}

  return head;

}

void traverseNode(struct node* head){
  if (head == NULL){
    printf("Cannot traverse..\n");
    exit(1);
   }
   else{
        struct node* current= head;
        while(current != NULL){
         printf("%d\t",current->coeff);
 	current = current->link;
   }
	printf("\n");
	current = head;
	while(current != NULL){
	printf("%d\t",current->expo);
	current = current->link;
 	}
     }
  }

  // adding linked list...

  struct node* addLinkedList(struct node*head1 , struct node*head2){
	struct node* resHead = NULL;
	struct node* current1 = head1;
	struct node* current2 = head2;
 	while(current1 != NULL && current2 !=NULL){
	   if(current2->expo > current2-> expo){
	     resHead = createNode(resHead,current1->coeff,current1->expo);
	     current1 = current1->link;
 	   }
	   else if (current1->expo <current2->expo){
	     resHead = createNode(resHead,current2->coeff,current2->expo);
	     current1 = current2->link;
	   }
	   else{
	     int coeffSum = current1->coeff + current2->coeff;
	     if(coeffSum != 0){
		resHead = createNode(resHead,coeffSum,current1->expo);
		   }
	    current1 = current1->link;
	    current2 = current2->link;
	  }
     }

     while (current1 != NULL) {
	resHead = createNode(resHead, current1->coeff,current1->expo);
	current1= current1->link;
     }

     while (current2 != NULL) {
	resHead = createNode(resHead, current2->coeff,current2->expo);
	current2= current2->link;
     }
     current1 = resHead;
     while(current1 !=NULL){
 	current2 = current1->link;
 	while(current2 = current1->link){
	  if(current1->expo == current2->expo){
	     current1->coeff = current1->coeff + current2->coeff;
	     struct node* duplicate = current2;
	     current1->link = current2->link;
	     free(duplicate);
	     current2 = current1->link;
           }
	   else{
	     current2 = current2->link;
	       }
	    }
	     current1 = current1->link;
     }
     return resHead;
 }

//multiplying linked list....

  struct node* multiplyLinkedList(struct node* head1, struct node* head2){
    if(head1 == NULL|| head2 ==NULL){
	printf("Multiplication is not possible,exiting program..");
	exit(1);
    }	
	struct node* current1 = head1;
	struct node* current2 = head2;
	struct node*resHead = NULL;

	while(current1 != NULL){
	    current2 = head2;
	    while(current2 != NULL){
		int coeffMulti = current1->coeff*current2->coeff;
		int expoSum = current1->expo + current2->expo;
		resHead = createNode(resHead,coeffMulti,expoSum);
		current2 = current2->link;
 	}
    }


// adding the resulting terms of the polynomial.....


    current1 = resHead;
    while(current1 !=NULL){
	current2 = current1->link;
	while(current2 !=NULL){
	  if(current1->expo == current2->expo){
		current1->coeff = current1->coeff + current2->coeff;
		struct node* duplicate = current2;
		current1->link = current2->link;
		free(duplicate);
		current2 = current1->link;
	   }
	   else{
	}
	current1 = current1->link;
    }

    return resHead;
}




   int main(){
	int coeff,expo,length1,length2,operation;
	struct node* head1 = NULL;
	struct node* head2 = NULL;
	struct node* resHead = NULL;
	char choice;

	do{

		printf("Enter your choice, 1 for addition and 2 for multiplication:");
		scanf("%d",&operation);

		printf("Enter the length of the first linked list:");
		scanf("%d",&length1);

		printf("Enter the length of the second linked list:");
		scanf("%d",&length2);

		printf("Enter the values of first linked list....\n");
		for(int i=0;i<length1;i++){
		   printf("Enter the coefficient of the node%d:",i+1);
		   scanf("%d",&coeff); 
		   printf("Enter the exponent of the node%d:",i+1);
		   scanf("%d",&expo);

		   head1 = createNode(head1,coeff,expo);
		}
		
		printf("Enter the values of second linked list....\n");
		for(int i=0;i<length2;i++){
		   printf("Enter the coefficient of the node%d:",i+1);
		   scanf("%d",&coeff); 
		   printf("Enter the exponent of the node%d:",i+1);
		   scanf("%d",&expo);

		   head2 = createNode(head2,coeff,expo);
		}


		if(operation == 1){
		    resHead = addLinkedList(head1,head2);
		    printf("The first linked list is...\n");
		    traverseNode(head1);
 		    printf("\n");
		   
		    printf("The second linked list is...\n");
		    traverseNode(head2);
 		    printf("\n");

		    printf("The sum of the linked list is...\n");
		    traverseNode(resHead);
 		    printf("\n");
		}

		else if(operation == 2){
		    resHead = addLinkedList(head1,head2);
		    printf("The first linked list is...\n");
		    traverseNode(head1);
 		    printf("\n");
		   
		    printf("The second linked list is...\n");
		    traverseNode(head2);
 		    printf("\n");

		    printf("The product of the linked list is...\n");
		    traverseNode(resHead);
 		    printf("\n");
		}

		else{
		    printf("Enter a valid choice...\n");
		}
		
		printf("Do you want to continue?y/n:");
		scanf("%s",&choice);
		head1 = NULL;
		head2 = NULL;
		resHead = NULL;

		}

		while(choice != 'n');




	
   }










































































































































































