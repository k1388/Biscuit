#include "data_struct.h"

#include <stdio.h>
#include <stdlib.h>

#include "iniio.h"

struct list_node* list_create(void)
{
    struct list_node* head = LIST_CREATE_NODE;
    head->next = NULL;
    head->prev = NULL;
    head->data = NULL;
    return head;
}

void list_append(struct list_node* head, void* _data, data_class dataKind)
{
    struct list_node* p = head;
    struct list_node* p1 = LIST_CREATE_NODE;

    p1->data = _data;
    p1->kind = dataKind;
    p1->next = NULL;
    
    while (p->next != NULL)
    {
        p = p->next;
    }
    
    p->next = p1;
    p1->prev = p;
}

void list_append_node(struct list_node* head, struct list_node* node)
{
    struct list_node* p = head;
    struct list_node* p1 = node;
    
    while (p->next != NULL)
    {
        p = p->next;
    }
    
    p->next = p1;
    p1->prev = p;
    p1->next = NULL;
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
    
    printf("列表中所有的元素：");
    
    while (p->next != NULL)
    {
        switch (p->next->kind)
        {
        case SpriteSec:
        case FontSec:
        case UISec:
        case UnnamedSec:
        case TextureSEC:
            printf("\nsec:");
            break;
        case VALUE:
            printf("--------val:");
            break;
        case KEY:
            printf("----key:");
            break;
        }
        printf(" %s\n", (char*)p->next->data);
        p = p->next;
        count++;
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

struct list_node* list_find_if(struct list_node* head, int (*func)(void* data))
{
    struct list_node* p = head;

    while (p && p->next != NULL)
    {
        if (func(p->next))
        {
            return p->next;
        }
        p = p->next;
    }
    
    return NULL;
}

int list_get_next(struct list_node* node, void** _data, data_class* kind)
{
    if (node->next == NULL)
    {
        return 0;
    }
    *_data = node->next->data;
    *kind = node->next->kind;
    return 1;
}

int list_get_prev(struct list_node* node, void** _data, data_class* kind)
{
    if (node->prev == NULL)
    {
        return 0;
    }
    *_data = node->prev->data;
    *kind = node->prev->kind;
    return 1;
}

void list_cover_origin_file(struct list_node* head, char* filePath)
{
    struct list_node* p = head;
    FILE* fp = fopen(filePath, "w");
    while (p->next != NULL)
    {
        if (p && p->next && p->next->kind == SpriteSec)
        {
            char secName[128] = "Sprite:";
            strcat(secName, p->next->data);
            p = p->next;
            while (p && p->next && p->next->kind & (KEY|VALUE))
            {
                char* keys[] = {
                    S_COLLISION, S_POS_X, S_POS_Y, S_ROTATE, S_SCALE, S_VISIBLE, S_ORIGIN_PIC
                };
                if (p->next->kind == KEY)
                {
                    for (int i = 0; i < 7; ++i)
                    {
                        if (!strcmp(keys[i], p->next->data))
                        {
                            ini_write_inplace(filePath, secName, keys[i], p->next->next->data);
                        }
                    }
                }
                p = p->next;
            }
        }

        if (p && p->next && p->next->kind == UISec)
        {
            char secName[128] = "UI:";
            strcat(secName, p->next->data);
            p = p->next;
            while (p && p->next && p->next->kind & (KEY|VALUE))
            {
                char* keys[] =
                {
                    UI_POS_X, UI_POS_Y, UI_WIDTH, UI_HEIGHT,UI_BUTTON_LABEL,
                    UI_BUTTON_FONT, UI_BUTTON_FONT_SIZE, UI_BUTTON_COLOR, UI_LABEL_FONT,UI_LABEL_FONT_SIZE,
                    UI_TYPE
                };
                if (p && p->next && p->next->kind == KEY)
                {
                    for (int i = 0; i < 11; ++i)
                    {
                        if (!strcmp(keys[i], p->next->data))
                        {
                            ini_write_inplace(filePath, secName, keys[i], p->next->next->data);
                        }
                    }
                }
                p = p->next;
            }
        }

        if (p && p->next && p->next->kind == FontSec)
        {
            char secName[128] = "Font:";
            strcat(secName, p->next->data);
            ini_write_inplace(filePath, secName, FONT_PATH, p->next->next->next->data);
            p = p->next;
        }

        if (p && p->next && p->next->kind == TextureSEC)
        {
            char secName[128] = "Texture:";
            strcat(secName, p->next->data);
            ini_write_inplace(filePath, secName, TEXTURE_PATH, p->next->next->next->data);
            p = p->next;
        }

        p = p->next;
    }
}

void list_del_sec(struct list_node* secNode)
{
    struct list_node* p = secNode;
    struct list_node* p1 = secNode;
    p = p->next;
    while (p && p->next && p->next->kind & (KEY|VALUE))
    {
        p1 = p->next;
        free(p);
        p = p1;
    }
    p1 = p;
    p = p->next;
    secNode->prev->next = p;
    free(secNode);
    free(p1);
}