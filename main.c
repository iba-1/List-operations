/*
 * llwmf.c
 *
 *  Created on: Feb 13, 2016
 *      Author: Dario
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

//STRUCT LIST DEFINITION


typedef struct list
{
	int value;
	struct list* next_ptr;
}tylist;

//FUNCTION PROTOTYPES

tylist init(tylist**);
void insert_at_beg(tylist**, int);
void insert_at_end(tylist**, int);
bool delete_at_beg(tylist**);
bool delete_at_end(tylist**);
void mid_insert(tylist**, int);
void mid_delete(tylist**);
bool search_list(tylist**, int);
void visit_list(tylist**);
void ord_insert(tylist**, int);
void action(int, tylist**);
int choicer();
void seq_sort(tylist **);
/*int get_dimension(tylist *);
int get_value(tylist *ptrptr, int);
void swap(tylist ** ptrptr, int ,int);*/

//MAIN FUNCT

int main()
{

	tylist *ptrptr;
	ptrptr = NULL;
	printf("\nI'm going to initialize the list now\n");
	action(choicer(), &ptrptr);
	return 0;
}

//FUNCTION DECLARATIONS

tylist init(tylist** ptrptr)
{
	*ptrptr = NULL;
	return **ptrptr;
}

void insert_at_beg(tylist** ptrptr, int value)
{
	if(*ptrptr != NULL)								//Fanno la stessa cosa in pratica
	{
		tylist* tmp_ptr;
		tmp_ptr = *ptrptr;
		*ptrptr = (tylist*)malloc(sizeof(tylist));
		(*ptrptr)->value = value;
		(*ptrptr)->next_ptr = tmp_ptr;
	}
	else
	{
		*ptrptr = (tylist*)malloc(sizeof(tylist));
		(*ptrptr)->value = value;
		(*ptrptr)->next_ptr = NULL;
	}
}

void insert_at_end(tylist** ptrptr, int value)
{
	if(*ptrptr != NULL)
	{
		while(*ptrptr != NULL)
		{
			ptrptr = &((*ptrptr)->next_ptr);
		}
		insert_at_beg(ptrptr, value);
	}
	else
	{
		printf("\nList is empty, will insert %d at beginning\n", value);
		insert_at_beg(ptrptr, value);
	}
}

bool delete_at_beg(tylist** ptrptr)
{
	if(*ptrptr == NULL)
	{
		printf("\nList is empty, there's no value to delete\n");
		return false;
	}
	else
	{
		tylist * tmp_ptr;
		tmp_ptr = *ptrptr;
		(*ptrptr) = (*ptrptr)->next_ptr;
		printf("\nYou are going to cancel %d from the list\n"
				"\n%d has been deleted\n", tmp_ptr->value, tmp_ptr->value);
		return true;
	}
}

bool delete_at_end(tylist** ptrptr)
{
	if(*ptrptr == NULL)
	{
		printf("\nList is empty, there's no value to delete\n");
		return false;
	}
	else if((*ptrptr)->next_ptr == NULL)
	{
		printf("\nThere were only two value on the list, one it's %d and you are going to cancel it\n", (*ptrptr)->value);
		free(*ptrptr);
		*ptrptr = NULL;
		return true;
	}
	else if(*ptrptr != NULL)
	{
		while((*ptrptr)->next_ptr->next_ptr != NULL)
		{
			ptrptr = &((*ptrptr)->next_ptr);
		}
		tylist* tmp_ptr;
		tmp_ptr = (*ptrptr)->next_ptr;
		printf("\nYou are going to delete %d\n", tmp_ptr->value);
		(*ptrptr)->next_ptr = NULL;
		free(tmp_ptr);
		return true;
	}
	else
	{
		printf("\nThere's something wrong!\n");
		return false;
	}
}

void mid_insert(tylist** ptrptr, int value)
{
	int count, i, moved_value;
	char response;
	printf("\nSpecify in which position you want to insert your value (position 0 not valid):\n");
	scanf("%d", &count);
	if(count == 1)
	{
		insert_at_beg(ptrptr, value);
	}
	else
	{
		for(i = 1; i < count;)
		{
			ptrptr = &((*ptrptr)->next_ptr);
			if(*ptrptr == NULL)
			{
				printf("\nYou've reached the end of the list, do you want to insert anyway in position %d? (Y\\N)\n", i);
				scanf(" %c", &response);
				if(response == 'Y' || response == 'y')
				{
					printf("\nI'm going to insert your value (%d) at the end of the list\n", value);
					insert_at_end(ptrptr, value);
				}
				else
				{
					printf("\nBadass\n");
				}
			}
			else
			{
				i++;
			}
		}
		moved_value = (*ptrptr)->value;
		insert_at_beg(ptrptr, value);
		printf("\nYou've inserted %d before %d", value, moved_value);
	//alla fine del for siamo nel punto giusto in cui vogliamo inserire un nuovo valore
	}
}


void mid_delete(tylist** ptrptr) //SPOSTA TUTTO INDIETRO CHE ATRIMENTI VA IN SEGFAULT, PERCHE' PUNTA A QUALCOSA OLTRE NULL
{
	int count, i;
	i = 1;
	printf("\nSpecify in which position you want to delete some value (position 0 not valid):\n");
	scanf("%d", &count);
	if(count == 1)
	{
		delete_at_beg(ptrptr);
	}
	else if(count > 1)
	{
		if((*ptrptr)->next_ptr->next_ptr == NULL)  //caso 2 elementi in lista
		{
			printf("\nYou are deleting the last element of the list (%d)\n", (*ptrptr)->next_ptr->value);
			(*ptrptr)->next_ptr = NULL;
		}
		else
		{
			while(i < count)
			{
				ptrptr = &((*ptrptr)->next_ptr);
				if((*ptrptr)->next_ptr == NULL)
				{
					i = count;
				}
				else
				{
					i++;
				}
			}
			delete_at_beg(ptrptr);
		}
	}


		/*i = 1;
		while(i < count || deleted == false)
		{
			ptrptr = &((*ptrptr)->next_ptr);
			if((*ptrptr)->next_ptr == NULL)
			{
				printf("\nYou've reached the end of the list, do you want to delete the end value (%d)?\n (Y\\N?):", (*ptrptr)->value);
				scanf(" %c", &response);
				if(response == 'Y' || response == 'y')
				{
					deleted = true;
					printf("\nYou are going to cancel %d from the list\n"
						   "\n%d has been deleted\n", (*ptrptr)->value, (*ptrptr)->value);
					*ptrptr = NULL;
				}
				else
				{
					deleted = true;
					printf("\nNope!\n");
				}

			}
			else
			{
				i++;
			}
		}
		if(deleted == false)
		{
			moved_value = (*ptrptr)->value;
			delete_at_beg(ptrptr);
			printf("\nYou've deleted %d in position %d", moved_value, count);
		}
	}*/
}


bool search_list(tylist **ptrptr, int value)
{
	char response;
	printf("\nIs this an ordered list?\nIf is ordered type Y (y will work too), otherwise type any other character: ");
	scanf(" %c", &response);

	if(response == 'Y' || response == 'y')
	{
		if((*ptrptr)->value == value)
		{
			printf("\nYour value is at the beginning of the list\n");
			return true;
		}
		else
		{
			int count = 1;
			while((*ptrptr)->value < value)
			{
				ptrptr = &((*ptrptr)->next_ptr);
				count++;
			}
			if((*ptrptr)->value == value)
			{
				printf("\nLooks like your value (%d) was in position %d\n", value, count);
				return true;
			}
			else
			{
				printf("\nLooks like your value isn't in the list, the closest one i've found is %d\n", (*ptrptr)->value);
				return false;
			}
		}
	}
	else if(response != 'Y' || response != 'y')
	{
		int count = 1;
		printf("\nSo the list isn't ordered, i'm going to look right through it\n");
		while((*ptrptr)->value != value && *ptrptr != NULL)
		{
			ptrptr = &((*ptrptr)->next_ptr);
			count++;
		}
		if((*ptrptr) == NULL)
		{
			printf("\nLooks like your value (%d) isn't in the list\n", value);
			return false;
		}
		else
		{
			printf("\nI've find your value (%d), was in position %d", value, count);
			return true;
		}
	}
	else
	{
		printf("There's some error somewhere over the rainbow");
		return false;
	}
}

void visit_list(tylist **ptrptr) //TODO L'OTTAVO VALORE INSERITO RESETTA LA FUNZIONE, RESTITUENDO GLI ULTIMI DUE VALORE ED UNO 0 AL TERZO POSTO
{
	while((*ptrptr) != NULL)
	{
		printf(" %d", (*ptrptr)->value);
		ptrptr = &((*ptrptr)->next_ptr);
	}
}

void ord_insert(tylist** ptrptr, int value)
{
	int count = 1;
	printf("\nI'm going to assume you've ordered the list\n");
	while((*ptrptr)->value < value && (*ptrptr)->next_ptr != NULL)
	{
		ptrptr = &((*ptrptr)->next_ptr);
		count++;
	}
	if((*ptrptr)->next_ptr == NULL)
	{
		ptrptr = &((*ptrptr)->next_ptr);
	}
	insert_at_beg(ptrptr, value);
	printf("\nYour value (%d) was inserted in position %d\n", value, count);

	/*if((*ptrptr)->value > value)
	{
		printf("\nLooks like your value was the smallest among all others\n");
		insert_at_beg(ptrptr, value);
	}*/

}

int choicer()
{
	int choice;
	printf("\nWhat do you want to do?\n"
				"1: Insert a value at beginning\n"
				"2: Insert a value at end\n"
				"3: Delete a value at beginning\n"
				"4: Delete a value at end\n"
				"5: Insert a value in some middle position\n"
				"6: Delete a value in some middle position\n"
				"7: Search for a value\n"
				"8: Print your list\n"
				"9: Insert a value in order\n"
				"10: Sequential sort\n"
				"0: Quit\n"
				"Type the number corresponding your choice: ");
	scanf("%d", &choice);
	return choice;
}

void action(int choice, tylist **ptrptr)
{
	switch(choice)
	{
	int value;
	case 1:
		printf("\nValue: ");
		scanf("%d", &value);
		insert_at_beg(ptrptr, value);
		action(choicer(), ptrptr);
		break;
	case 2:
		printf("\nValue: ");
		scanf("%d", &value);
		insert_at_end(ptrptr, value);
		action(choicer(), ptrptr);
		break;
	case 3:
		delete_at_beg(ptrptr);
		action(choicer(), ptrptr);
		break;
	case 4:
		delete_at_end(ptrptr);
		action(choicer(), ptrptr);
		break;
	case 5:
		printf("\nValue: ");
		scanf("%d", &value);
		mid_insert(ptrptr, value);
		action(choicer(), ptrptr);
		break;
	case 6:
		mid_delete(ptrptr);
		action(choicer(), ptrptr);
		break;
	case 7:
		printf("\nValue: ");
		scanf(" %d", &value);
		search_list(ptrptr, value);
		action(choicer(), ptrptr);
		break;
	case 8:
		visit_list(ptrptr);
		action(choicer(), ptrptr);
		break;
	case 9:
		printf("\nValue: ");
		scanf(" %d", &value);
		ord_insert(ptrptr, value);
		action(choicer(), ptrptr);
		break;
	case 10:
		seq_sort(ptrptr);
		action(choicer(), ptrptr);
		break;
	case 0:
		free(*ptrptr);
		break;
	}
}

void seq_sort(  tylist ** ptrptr ) {
	struct list ** min_ptr, * tmp, * ptr1;
// ciclo più esterno su tutti gli elementi della lista
	while( *ptrptr != NULL ) {
		min_ptr = ptrptr; // doppio puntatore al minimo iterazione corrente ptr1 = (*ptr)->next;
// ciclo interno per trovare il minimo tra gli elementi rimasti
		while( ptr1 != NULL )
		{
			if ( ptr1->value < (*min_ptr)->value )
			{
				min_ptr = &(ptr1->next_ptr);
			}
			ptr1 = ptr1->next_ptr;
		}
// scollega l'elemento con il minimo
		tmp = *min_ptr;
		min_ptr = &(*min_ptr)->next_ptr;
// collega l'elemento con il minimo corrente alla posizione di *ptr // (testa della sottolista corrente)
		tmp->next_ptr = *ptrptr;
		(*ptrptr)->next_ptr = tmp;
// avanza alla fine degli elementi ordinati
		ptrptr = &((*ptrptr)->next_ptr);
	}
}














