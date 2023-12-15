
 /*
 * 
 * IMPLEMENTATION OF POLYNOMIAL USING ARRAY.
 * 
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Macro to clear input buffer.
#define CLS_INPUT_BUFF while(getchar() != '\n')

//Macro to clear output screen.
#define CLS_SCREEN system("clear")



//Structure to store polynomial.
//Array of structure is used to store terms of equation.
typedef struct{

	int exp;
	int coeff;
	
}Poly;


//functions prototypes.
void input_equation(Poly eqn[], int eqn_len);
void show_equation(Poly eqn[], int eqn_len);
void sort_equation(Poly eqn[], int eqn_len);
void delete_duplicate_terms(Poly eqn[], int position, int eqn_len);
void revalidate_equation(Poly eqn[], int *eqn_len);
void add_missing_terms(Poly res[], int *res_len, Poly eqn[], int eqn_len);
int add_equation(Poly eqn1[], Poly eqn2[], Poly res[], int eqn1_len, int eqn2_len);


int main(){
	
	
	int eqn1_len, eqn2_len, res_len;
	Poly *eqn1, *eqn2, *res;
	char runAgain;
	
	do{
		
		printf("Enter the number of terms in equation one : ");
		scanf("%d", &eqn1_len);
	
		//allocating memory to store equation one.
		eqn1 = (Poly*) calloc(eqn1_len, sizeof(Poly));
		if(eqn1 == NULL){
	
			printf("Failed to allocate memory :(\n");
			printf("CLOSING PROGRAM\n");
			exit(EXIT_FAILURE);
		
		}
		
		input_equation(eqn1, eqn1_len);
	
		CLS_SCREEN;
		
		printf("\n====================================================================\n");
		printf("Equation One : \n");
		show_equation(eqn1, eqn1_len);
		printf("\n====================================================================\n");
	
		sort_equation(eqn1, eqn1_len);
		revalidate_equation(eqn1, &eqn1_len);
	

		printf("Enter the number of terms in equation two : ");
		scanf("%d", &eqn2_len);
	
		//allocating memory to store equation two
		eqn2 = (Poly*) calloc(eqn2_len, sizeof(Poly));
		if(eqn2 == NULL){
	
			printf("Failed to allocate memory :(\n");
			printf("CLOSING PROGRAM\n");
			exit(EXIT_FAILURE);
		
		}
	
		input_equation(eqn2, eqn2_len);
	
		CLS_SCREEN;
		
		
		printf("\n====================================================================\n");
		printf("Equation Two : \n");
		show_equation(eqn2, eqn2_len);
		printf("\n====================================================================\n");
	
		sort_equation(eqn2, eqn2_len);
		revalidate_equation(eqn2, &eqn2_len);
	
		
		//allocating memory to store result of addtion operation.
		res = (Poly*) calloc( (eqn1_len + eqn2_len), sizeof(Poly));
		if(res == NULL){
	
			printf("Failed to allocate memory :(\n");
			printf("CLOSING PROGRAM\n");
			exit(EXIT_FAILURE);
		
		}
		
		//clearing input buffer.
		CLS_INPUT_BUFF;
		printf("Press enter key to continue\n");
		getchar();
		
		CLS_SCREEN;
		
		printf("\n====================================================================\n");
		printf("Equation One in formatted form : \n");
		show_equation(eqn1, eqn1_len);
		printf("\n====================================================================\n");
		
		
		printf("\n====================================================================\n");
		printf("Equation Two in formatted form : \n");
		show_equation(eqn2, eqn2_len);
		printf("\n====================================================================\n");
		
	
		if(eqn1_len > eqn2_len){
	
			res_len = add_equation(eqn1, eqn2, res, eqn1_len, eqn2_len);
	
		}else{
		
			res_len = add_equation(eqn2, eqn1, res, eqn2_len, eqn1_len);
	
		}	
	
	
		printf("\n====================================================================\n");
		printf("Result : \n");
		show_equation(res, res_len);
		printf("\n====================================================================\n");
	
	
		//freeing allocated memory.
		free(eqn1);
		free(eqn2);
		free(res);
		
		
		//prompt asking to run this program again.
		printf("\nDo you want run again (y/n) : ");
		scanf("%c", &runAgain);
		
		CLS_SCREEN;
	
	}while(runAgain == 'y' || runAgain == 'Y');
	
	
	
	return EXIT_SUCCESS;
	
}


//Function to input equations.
void input_equation(Poly eqn[], int eqn_len){
	
	int i;
	putchar('\n');
	for(i = 0; i < eqn_len; i++){
	
		printf("Enter term %d : \n", (i+1));
		
		printf("Enter exponent of term %d : ", (i+1));
		scanf("%d", &eqn[i].exp);
		
		printf("Enter coefficient of term %d : ", (i+1));
		scanf("%d", &eqn[i].coeff);
				
	}
	putchar('\n');
	
	
}

//Function to display equation.
void show_equation(Poly eqn[], int eqn_len){
	
	int i;
	
	putchar('\n');
	printf("Exponent : ");
	for(i = 0; i < eqn_len; i++){
		
			printf("\t%-3d", eqn[i].exp);
		
	}
	
	putchar('\n');
	printf("Coefficient : ");
	for(i = 0; i < eqn_len; i++){
	
			printf("\t%-3d", eqn[i].coeff);
		
	}
	
	putchar('\n');
	
}


//Arranging equation in decending exponent order (bubble sort used). 
void sort_equation(Poly eqn[], int eqn_len){
	
	Poly temp_term;
	int i;
	int j;
		
	for(i = 1; i < eqn_len; i++){
			
		for(j = 0; j < (eqn_len - i); j++){
					
			if(eqn[j].exp < eqn[j+1].exp){
						
				temp_term.exp = eqn[j].exp;
				temp_term.coeff = eqn[j].coeff;
								
				eqn[j].exp = eqn[j+1].exp;
				eqn[j].coeff = eqn[j+1].coeff;
							
				eqn[j+1].exp = temp_term.exp;
				eqn[j+1].coeff = temp_term.coeff;
						
			}
							
		}
					
	}
	
}


//Function to delete same exponent terms from equation.
void delete_duplicate_term(Poly eqn[], int position, int eqn_len){
	
	int i;
	
	for(i = position; i < eqn_len; i++){
		
		eqn[i].exp = eqn[i+1].exp;
		eqn[i].coeff = eqn[i+1].coeff;
				
	}
	
}


//Function to sum up same exponent terms in equation and remove same exponent terms from equation,
//Thus reducing length of equation.
//Making equation more readable.
void revalidate_equation(Poly eqn[], int *eqn_len){
	
	
	int i, j, exp, eqn_new_len = *eqn_len;
	int coeff_sum;
	
	for(i = 0; i < eqn_new_len; i++){
	
		exp = eqn[i].exp;
		coeff_sum = eqn[i].coeff;
		j = (i+1);
		
		while(j < eqn_new_len){
			
			if(eqn[j].exp == exp){
				
				coeff_sum = coeff_sum + eqn[j].coeff;
				delete_duplicate_term(eqn, j, eqn_new_len);
				eqn_new_len--;
				
			}else{
			
				j++;
			
			}
			
		}
		
		eqn[i].coeff = coeff_sum;
		
	}
	
	*eqn_len = eqn_new_len;
	
}


//Function to add terms missed during addition of equations, changes length of resulting equation.
void add_missing_terms(Poly res[], int *res_len, Poly eqn[], int eqn_len){
	
	 
	bool same_term = false;
	int i;
	int j;
	int new_res_len = *res_len;
		
	for(i = 0; i < eqn_len; i++){
			
		for(j = 0; j < *res_len; j++){
				
			if(eqn[i].exp != res[j].exp){
							
				same_term = false;
				continue;
								
			}else{
						
				same_term = true;
				break;
			
			}
						
		}
				
		if(same_term == false){
					
			res[new_res_len].exp = eqn[i].exp;
			res[new_res_len].coeff = eqn[i].coeff;
			new_res_len++;
			
		}
			
	}
	
	*res_len = new_res_len;
	
}


//Main function to perform addition operation.
int add_equation(Poly eqn1[], Poly eqn2[], Poly res[], int eqn1_len, int eqn2_len){
	
	
	int i = 0, j = 0;
	int res_len = eqn1_len;
	
	
	for(i = 0; i < eqn1_len; i++){
			
		for(j = 0; j < eqn2_len; j++){
				
			if(eqn1[i].exp == eqn2[j].exp){
						
				res[i].exp = eqn1[i].exp;
				res[i].coeff = (eqn1[i].coeff + eqn2[j].coeff);
				break;
							
			}else{
				
				res[i].exp = eqn1[i].exp;
				res[i].coeff = eqn1[i].coeff;
				
			}
						
		}
							
	}
	
	
	add_missing_terms(res, &res_len, eqn2, eqn2_len);
	revalidate_equation(res, &res_len);
	sort_equation(res, res_len);
	
	return res_len;

		
}
