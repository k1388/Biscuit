#pragma once
#define LIST_CREATE_NODE (struct list_node*)malloc(sizeof(struct list_node))
#define BIT(x) (1 << (x))

/// <summary>
/// 声明了链表节点中存放哪种数据
/// </summary>
typedef enum data_class
{
    TextureSEC =    BIT(1) | BIT(0),
    FontSec =       BIT(2) | BIT(0),
    SpriteSec =     BIT(3) | BIT(0),
    UISec =         BIT(4) | BIT(0),
    UnnamedSec =    BIT(5) | BIT(0),
    KEY =           BIT(6),
    VALUE =         BIT(7),
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
    struct list_node*   head, 
    void*               data,
    data_class          dataKind
);

int list_delete(
    struct list_node*    head, 
    void*               _data
);

int list_delete_if(
    struct list_node*    head, 
    int                 (*func)(void* data)
);

void list_print(
    struct list_node*    head
);

void list_delete_all(
    struct list_node*    head
);

int list_find(
    struct list_node*    head, 
    void*               _data
);

int list_find_if(
    struct list_node*    head, 
    int                 (*func)(void* data)
);

int list_get_next(
    struct list_node*   node,
    void**             _data,
    data_class*         kind
);

int list_get_prev(
    struct list_node*   node,
    void**             _data,
    data_class*         kind
);

