#ifndef __LIST_H__
#define __LIST_H__

struct node {
    int value;
    struct node *next; 
};

void list_append(int *val, struct node **head);

void list_sort(struct node **head);

void list_print(struct node *list);

void list_clear(struct node *list);

#endif // __LIST_H__
