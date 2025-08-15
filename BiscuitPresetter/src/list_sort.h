#include "iniio.h"
#include "data_struct.h"

void list_sort(struct list_node *head)
{
    struct list_node *p = head;

    // 将材质和字体置前
    while (p->next->kind != data_class::FontSec && p->next != NULL)
    {
        p = p->next;
    }
    struct list_node *tmp = head->next;
    head->next = p->next;
    p->next->next->next = tmp;
    
    p = head;
    while (p->next->kind != data_class::TextureSEC && p->next != NULL)
    {
        p = p->next;
    }
    struct list_node *tmp = head->next;
    head->next = p->next;
    p->next->next->next = tmp;
}