#include "data_struct.h"

#include <stdio.h>
#include <stdlib.h>

struct list_node* list_create(void)
{
    struct list_node* head = LIST_CREATE_NODE;
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;
    return head;
}

void list_append(struct list_node* head, void* _data)
{
    struct list_node* p = head;
    struct list_node* p1 = LIST_CREATE_NODE;

    p1->data = _data;
    p1->next = NULL;
    
    while (p->next != NULL)
    {
        p = p->next;
    }
    
    p->next = p1;
    p1->prev = p;
}

int list_delete(struct list_node* head, void* _data)
{
    struct list_node* p = head;
    
    while (p->next != NULL)
    {
        if (p->next->data == _data)
        {
            struct list_node* p1 = p->next;
            p->next = p->next->next;
            free(p1);
            return 1;
        }
    }

    return 0;
}

int list_delete_if(struct list_node* head, int (*func)(void* data))
{
    struct list_node* p = head;

    while (p->next != NULL)
    {
        if (func(p->next->data))
        {
            struct list_node* p1 = p->next;
            p->next = p->next->next;
            free(p1);
            return 1;
        }
    }
    
    return 0;
}

void list_print(struct list_node* head)
{
    struct list_node* p = head;
    size_t count = 0;
    
    printf("列表中所有的元素：\n");
    
    while (p->next != NULL)
    {
        printf("%p\n", p->next->data);
        p = p->next;
    }

    printf("共%llu项\n", count);
}

void list_delete_all(struct list_node* head)
{
    struct list_node* p1 = head;
    struct list_node* p2 = NULL;
    
    while (p1->next != NULL)
    {
        p2 = p1->next;
        free(p1);
        p1 = p2;
    }

    if (p1 != NULL)
    {
        free(p1);
    }
}

int list_find(struct list_node* head, void* _data)
{
    struct list_node* p = head;
    
    while (p->next != NULL)
    {
        if (p->next->data == _data)
        {
            return 1;
        }
    }

    return 0;
}

int list_find_if(struct list_node* head, int (*func)(void* data))
{
    struct list_node* p = head;

    while (p->next != NULL)
    {
        if (func(p->next->data))
        {
            return 1;
        }
    }
    
    return 0;
}
