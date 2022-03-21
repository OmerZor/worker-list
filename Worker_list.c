#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING 1
#define NUMBERS 0

typedef struct Worker {
	unsigned int id;
	char* name;
	double sal;
	union WorkeDate
	{
		char Ldate[6];
		unsigned int Ndate;
	}WorkeDate;
}worker;

typedef struct WorkerList
{
	worker* data;
	struct WorkerList* next;
} WorkerList;

void printList(WorkerList* head);

worker* CreateWorker();

void printWorker(worker* head, int typeD); 

WorkerList* addWorker(WorkerList* head, worker* w);

int index(WorkerList* head, long unsigned id);

WorkerList* deleteWorstWorker(WorkerList* head);

void update_worker(WorkerList* head, float percent);

WorkerList* reverse(WorkerList* head);

void freeWorkers(WorkerList* head);

void main() {
	worker* printW;
	int id = 0;
	worker* ptr;
	float perecent = 0;
	WorkerList* head = NULL;

	int checkTheNum = -1;

	while (checkTheNum != 0) {

		printf("press 1 to creat new worker: \n");

		printf("press 2 to print all workers in the list:\n");

		printf("press 3 to delete the last worker: \n");

		printf("press 4 to update the salary of all the workers: \n");

		printf("press 5 to revers the list\n");

		printf("press 6 to delet all the list \n");

		printf("press 7 to print the emploo: \n");

		printf("press 8 to print the emploo place in the salary table: \n");

		printf("press 0 to return to log out: \n");

		printf("\nyou chosen num is: ");
		scanf("%d", &checkTheNum);

		switch (checkTheNum) /*cases that the user can chose*/
		{
		case(0):
			printf(" you signed out...");
			exit(0);
		case(1):
			ptr = CreateWorker();
			head = addWorker(head, ptr);
			break;
		case(2):
			printList(head,0);
			break;
		case(3):
			head = deleteWorstWorker(head);
			break;
		case(4):
			printf("enter perecent: ");
			scanf("%f", &perecent);
			update_worker(head, perecent);
			printf("you update the emlpp salary!");
			break;
		case(5):
			head = reverse(head);
			break;
		case(6):
			freeWorkers(head);
			break;
		case(7):

			printW = head->data;
			printWorker(printW, 0);
			break;
		case(8):
			printf("enter emploo id: \n");
			scanf("%d", &id);
			int retPlace = index(head, id);
			printf("the place is: %d\n", retPlace);
			break;
		}
	}


}



worker* CreateWorker() {
	worker* ptr = (worker*)calloc(5, sizeof(worker));
	int dataType = 0;
	char tepname[100];
	if (!ptr) {
		printf("allocation faild");
		exit(-1);
	}

	printf("enter emploo id: ");
	scanf("%d", &ptr->id);

	printf("\nenter emploo name: ");
	scanf("%s", &tepname);

	int len = strlen(tepname);
	ptr->name = (char*)malloc(len * sizeof(char*)); /*allocated to the size of the name*/
	strcpy(ptr->name, tepname);

	printf("\nenter salary: ");
	scanf("%lf", &ptr->sal);

	printf("\nchose type of data to enter: 1 -string ,0-number: ");
	scanf("%d", &dataType);

	switch (dataType) {
	case(STRING): {
		printf("\nenter string data: ");
		scanf("%s", &ptr->WorkeDate.Ldate);
		break;
	}
	case(NUMBERS): {
		printf("\n enter data num: ");
		scanf("%d", &ptr->WorkeDate.Ndate);
		break;
	}
	default:
		printf("illegel choise");
		break;
	}
	return ptr;
}

void printWorker(worker* head, int typeD) {

	printf("emplo id is:%d\n", head->id);

	printf("emplo name is: %s\n", head->name);

	printf("emplo salary is: %g\n", head->sal);

	switch (typeD) {
	case(STRING):
		printf("emplo work date is: %s\n", head->WorkeDate.Ldate);
		break;

	case(NUMBERS):
		printf("emplo work data is: %d\n", head->WorkeDate.Ndate);
		break;
	}

}

WorkerList* addWorker(WorkerList* head, worker* w) {

	WorkerList* newworker = (WorkerList*)calloc(1, sizeof(WorkerList)); /*allocated the new worker*/
	if (newworker == NULL)
	{
		printf("alocation is faild");
		return NULL;
	}
	newworker->data = w;
	if (head == NULL) {  /*cheking if the list is empty*/
		head = newworker;
		return head;
	}
	if (head->data->sal < newworker->data->sal) /*cheking were to put the new worker*/
	{
		newworker->next = head;
		return newworker;
	}
	WorkerList* ptr = head->next;
	WorkerList* prev = head;
	while ((ptr && ptr->data->sal > newworker->data->sal))
	{

		ptr = ptr->next;
		prev = prev->next;

	}
	prev->next = newworker;
	newworker->next = ptr;
	return head;


}

int index(WorkerList* head, long unsigned id) {
	int counter = 1;
	WorkerList* temp = head;
	while (temp != NULL) {    /*find the place of the worker by his ID*/
		if (temp->data->id == id) {
			return counter;
		}
		counter++;
		temp = temp->next;
	}
	return -1;
}

WorkerList* deleteWorstWorker(WorkerList* head) {
	WorkerList* ptr = head;

	/*finding the lates worker and delete him*/

	if (head->next == NULL) 
	{
		free(head);
		head = NULL;
		return head;
	}
	else
		if (head == NULL)
		{
			return head;
		}
		else
		{
			while (ptr != NULL)
			{
				if (ptr->next->next == NULL)
				{
					free(ptr->next->next);
					ptr->next = NULL;
				}
				ptr = ptr->next;
			}
		}
	return head;
}

void update_worker(WorkerList* head, float percent)
{
	WorkerList* temp = head;
	
	if (temp == NULL)
	{
		printf("you dont have any emplo");
		return temp;
	}
	
	while (temp != NULL) /* runs all over the list and updates the salary*/
	{
		temp->data->sal += (temp->data->sal) * (percent / 100);
			temp = temp->next;
		

	}

}

WorkerList* reverse(WorkerList* head) {
	WorkerList* temp = head;
	WorkerList* prev = NULL;
	WorkerList* next = NULL;

	while (temp != NULL)
	{
		next = temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
	}

	return prev;



}

void freeWorkers(WorkerList* head)
{
	WorkerList* temp = head;
	while (temp != NULL)
	{
		free(temp->data);
		temp = temp->next;
	}
}

void printList(WorkerList* head)
{
	WorkerList* temp = head;

	while (temp)
	{
		printWorker(temp->data, 0);
		temp = temp->next;
		printf("\n");
	}
}



