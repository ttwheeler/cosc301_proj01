#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_append(int *val, struct node **head)
{
	struct node *new_node = malloc(sizeof(struct node));
        new_node->value = *val;
	new_node->next = *head;
	*head = new_node;
}

void list_sort(struct node **head) 
{ 
  if(*head==NULL)//Test for an empty list
  {
    return;
  }
  int tmp;
  struct node *new_node = *head;
  struct node *second_node = new_node->next;
  for(; new_node->next !=NULL; new_node= new_node->next)
  {
      	for(second_node = new_node->next; second_node != NULL; second_node= second_node->next)
	{
      		if (new_node->value>second_node->value)
		{
			tmp = new_node->value;
			new_node->value = second_node->value; 
			second_node->value = tmp; 
		}
      	}
  }
}

void list_print( struct node *list)
{
    if(list==NULL)
    {
        printf("\nList was empty!\n");
        return;
    }
    list_sort(&list);//Sort the list before we print it
    int i = 0;
    printf("\n*** List Contents Begin ***\n");
    while (list != NULL)
    {
        printf("List item %d: %d\n", i++, list->value);
        list = list->next;
    }
    printf("*** List Contents End ***\n");
}

void list_clear(struct node *list)
{
    while (list != NULL)
    {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

