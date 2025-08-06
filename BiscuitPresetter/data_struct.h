#pragma once
#define LIST_CREATE_NODE (struct list_node*)malloc(sizeof(struct list_node))

/// <summary>
/// 声明了链表中存放哪种数据类型
/// </summary>
typedef enum data_class
{
    STR
}data_class;

typedef struct list_node
{
    struct list_node       *prev;
    void                   *data;
    struct list_node       *next;
    data_class              kind;
}List;

struct list_node* list_create(
    void
);

void list_append(
    struct      list_node* head, 
    void*       data
);

int list_delete(
    struct      list_node* head, 
    void*       a_data
);

int list_delete_if(
    struct      list_node* head, 
    int         (*func)(void* data)
);

void list_print(
    struct      list_node* head
);

void list_delete_all(
    struct      list_node* head
);

int list_find(
    struct      list_node* head, 
    void*       a_data
);

int list_find_if(
    struct      list_node* head, 
    int         (*func)(void* data)
);