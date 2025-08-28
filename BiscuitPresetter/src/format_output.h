#pragma once
#include <stdio.h>
#include "data_struct.h"

struct list_node* list = NULL;
char secName[100];
char keyName[100];
int choice = 0;

void o_bind_list(struct list_node* _list)
{
    list = _list;
}
void o_bind_sec(char* name)
{
    strcpy(secName, name);    
}
void o_bind_key(char* name)
{
    strcpy(keyName, name);
}

void o_refresh_elements_menu(struct list_node* head);
int o_manage_all_elements_callback(void);
int o_sprite_detail_callback(void);
int o_ui_detail_callback(void);
int o_sprite_prop_change_callback(void);
typedef struct
{
    int             id;          
    const char      *text;    
    int             (*callFn)(void);
    int             nextMenu;    
}MenuItem;

// menu 0
static const MenuItem main_menu[] =
{
    {1, "浏览和设置项目元素", NULL, 1},
    {2, "生成项目Sandbox", NULL, 0},
    {3, "重新选择项目地址", NULL, 0}
};

// menu 1
static const MenuItem element_menu[] =
{
    {1, "管理所有元素", o_manage_all_elements_callback, 2},
    {2, "创建一个Sprite", NULL, 1},
    {3, "创建一个UI元素", NULL, 3},
    {0, "返回上一页", NULL, -2}
};

// menu 2
static MenuItem all_elements_menu[512] =
{
    {0, "返回上一页", NULL, 0}
};
int all_elements_menu_count = 0;

// menu 3
static MenuItem ui_type_menu[] =
{
    {1, "创建 Button", NULL, 0},
    {2, "创建 Label", NULL, 0},
    {3, "创建 Prograss Bar", NULL, 0},
    {0, "返回上一页", NULL, -2}
};

// menu 4
static MenuItem sprite_management_menu[512] =
{
    {1, S_POS_X, o_sprite_prop_change_callback, 4},
    {2, S_POS_Y, o_sprite_prop_change_callback, 4},
    {3, S_SCALE, o_sprite_prop_change_callback, 4},
    {4, S_ROTATE, o_sprite_prop_change_callback, 4},
    {5, S_ORIGIN_PIC, o_sprite_prop_change_callback, 4},
    {6, "otherPic(未完成)", o_sprite_prop_change_callback, 4},
    {7, S_VISIBLE, o_sprite_prop_change_callback, 4},
    {8, S_SCRIPT_PATH, o_sprite_prop_change_callback, 4},
    {9, S_COLLISION, o_sprite_prop_change_callback, 4},
    {0, "返回上一页", NULL, -2},
};

// menu 5
static MenuItem ui_management_menu[512] =
{
    {1, UI_TYPE, NULL, 0},
    {2, UI_POS_X, NULL, 0},
    {3, UI_POS_Y, NULL, 0},
    {4, UI_WIDTH, NULL, 0},
    {5, UI_HEIGHT, NULL, 0},
    {6, UI_SCALE, NULL, 0},
    {7, UI_BUTTON_LABEL, NULL, 0},
    {8, UI_BUTTON_FONT, NULL, 0},
    {9, UI_BUTTON_FONT_SIZE, NULL, 0},
    {10, UI_BUTTON_COLOR, NULL, 0},
    {11, UI_LABEL_FONT, NULL, 0},
    {12, UI_LABEL_FONT_SIZE, NULL, 0},
    {13, UI_LABEL_COLOR, NULL, 0},
    {0, "返回上一页", NULL, -2},
    
};



static struct
{
    const MenuItem *items;
    int             count;
}
menu_table[] =
{
    [0] = { main_menu,  sizeof(main_menu)/sizeof(main_menu[0]) },
    [1] = { element_menu,  sizeof(element_menu)/sizeof(element_menu[0]) },
    [2] = { all_elements_menu, sizeof(all_elements_menu)/sizeof(all_elements_menu[0]) },
    [3] = { ui_type_menu,  sizeof(ui_type_menu)/sizeof(ui_type_menu[0]) },
    [4] = { sprite_management_menu, 10},
    [5] = { ui_management_menu,14}
};

int _o_sti(char* str)
{
    int len = strlen(str);
    int res = 0;
    for (int i = 0; i < len; ++i)
    {
        res *= 10;
        res += str[i] - '0';
    }
    return res;
}

int _o_get_width(char* v)
{
    char buf[512];
    sprintf(buf, "%s", v);
    return strlen(buf);
}

void o_p_stars(int num)
{
    for (int i = 0; i < num; ++i)
    {
        printf("*");
    }
    printf("\n");
}

void o_p_line(int lenth)
{
    for (int i = 0; i < lenth; ++i)
    {
        printf("-");
    }
    printf("\n");
}

int o_menu(MenuItem* menu, int count)
{
    system("cls");
    o_p_stars(30);
    for (int i = 0; i < count; ++i)
    {
        printf("%d.%s\n", menu[i].id, menu[i].text);
    }
    o_p_stars(30);
    printf("请选择：");
    char ans[16];
    scanf("%s", ans);
    int sel = _o_sti(ans);

    for (int i = 0; i < count; ++i)
    {
        if (menu[i].id == sel)
        {
            choice = i;
            return i;
        }
    }
    choice = -1;
    return -1;
}

int _o_find_uiType(struct list_node* node)
{
    return !strcmp((char*)node->data, UI_TYPE) && node->kind == KEY;
}

void o_p_all_elements(struct list_node* head)
{
    system("cls");
    o_p_stars(30);
    int count = 0;
    struct list_node* p = head;
    while (p->next != NULL)
    {
        if (p->next->kind == SpriteSec)
        {
            printf("%d.Sprite:%s\n", ++count, p->next->data);
        }
        if (p->next->kind == UISec)
        {
            struct list_node* node = list_find_if(p->next, _o_find_uiType);
            char* type;
            char* types[] = {UI_TYPE_BUTTON, UI_TYPE_LABEL, UI_TYPE_PROGRESSBAR};
            for (int i = 0; i < 3; ++i)
            {
                if (!strcmp(node->next->data, types[i]))
                {
                    printf("%d.%s:%s\n", ++count, types[i],p->next->data);
                }
            }
        }
        p = p->next;
    }
    printf("0.返回上一页\n");
    o_p_stars(30);
    printf("请输入：\n");
}

void o_refresh_elements_menu(struct list_node* head)
{
    int count = 0;
    struct list_node* p = head;
    while (p && p->next != NULL)
    {
        if (p->next->kind == SpriteSec)
        {
            // 这边有内存泄漏问题 --8.28
            char* buf = malloc(sizeof(char) * 64);
            strcpy(buf, "Sprite:");
            strcat(buf, p->next->data);
            all_elements_menu[count].id = count + 1;
            all_elements_menu[count].text = buf;
            all_elements_menu[count].callFn = o_sprite_detail_callback;
            all_elements_menu[count].nextMenu = 4;
            count++;
            p = p->next;
            continue;
        }
        if (p->next->kind == UISec)
        {
            struct list_node* node = list_find_if(p->next, _o_find_uiType);
            char* type;
            char* types[] = {UI_TYPE_BUTTON, UI_TYPE_LABEL, UI_TYPE_PROGRESSBAR};
            for (int i = 0; i < 3; ++i)
            {
                if (!strcmp(node->next->data, types[i]))
                {
                    //printf("%d.%s:%s\n", ++count, types[i],p->next->data);
                    char* buf = malloc(sizeof(char) * 64);
                    strcpy(buf, types[i]);
                    strcat(buf, ":");
                    strcat(buf, p->next->data);
                    all_elements_menu[count].id = count + 1;
                    all_elements_menu[count].text = buf;
                    all_elements_menu[count].callFn = o_ui_detail_callback;
                    all_elements_menu[count].nextMenu = 5;
                    count++;
                    p = p->next;
                    continue;
                }
            }
        }
        p = p->next;
    }
    all_elements_menu[count].id = 0;
    all_elements_menu[count].text = "返回上一页";
    all_elements_menu[count].callFn = NULL;
    all_elements_menu[count].nextMenu = -2;
    count++;
    all_elements_menu_count = count;
}

int o_manage_all_elements_callback()
{
    o_refresh_elements_menu(list);
    menu_table[2].count = all_elements_menu_count;
    return 2;
}

int o_sprite_detail_callback(void)
{
    const char *colon = strchr(all_elements_menu[choice].text, ':');
    if (colon && *(colon + 1))
        strcpy(secName, colon + 1);
    else
        strcpy(secName, all_elements_menu[choice].text);
    return 4;   
}

int o_ui_detail_callback(void)
{
    const char *colon = strchr(all_elements_menu[choice].text, ':');
    if (colon && *(colon + 1))
        strcpy(secName, colon + 1);
    else
        strcpy(secName, all_elements_menu[choice].text);
    return 5;   
}

int o_find_sprite_sec(struct list_node* node)
{
    return node->kind == SpriteSec && !(strcmp(node->data, secName));
}

int o_sprite_prop_change_callback(void)
{
    strcpy(keyName, all_elements_menu[choice].text);
    printf("%s---%s\n", secName, keyName);
    struct list_node* node = list_find_if(list, o_find_sprite_sec);
    int isDefined = 0;
    struct list_node* theKeyNode = NULL;
    while (node && node->next && node->next->kind & (KEY|VALUE))
    {
        if (node->next->kind == KEY && strcmp(node->next->data, keyName))
        {
            isDefined = 1;
            theKeyNode = node->next;
            break;
        }
        node = node->next;
    }
    if (!isDefined)
    {
        printf("%s的%s属性:\n默认\n", secName, keyName);
    }
    printf("%s的%s属性:\n%s\n", secName, theKeyNode->data, theKeyNode->next->data);
    char ans[512] = {0};
    scanf("%s", ans);
    return 4;
}