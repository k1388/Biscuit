#pragma once
#include <stdio.h>
#include "data_struct.h"

static struct list_node* list = NULL;
static char progPath[512];
static char secName[100];
static char keyName[100];
static int choice = 0;
static void (*update_files_callback)(void)  = NULL;
static void (*update_ini_callback)(void)  = NULL;

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
void o_bind_progPath(char* path)
{
    strcpy(progPath, path);
}
void o_bind_callback(void (*_callback)(void))
{
    update_files_callback = _callback;
}
void o_bind_ini_callback(void (*_callback)(void))
{
    update_ini_callback = _callback;
}

void o_refresh_elements_menu(struct list_node* head);

static int o_manage_all_elements_callback(void);
static int o_sprite_detail_callback(void);
static int o_ui_detail_callback(void);
static int o_sprite_prop_change_callback(void);
static int o_ui_prop_change_callback(void);
static int o_create_sprite_callback(void);
static int o_create_ui_callback(void);
static int o_gen_code_callback(void);
static int o_sprite_delete_callback(void);
static int o_ui_delete_callback(void);
static int o_reselect_path_callback(void);
static int o_save_ini_callback(void);
static int o_create_texture_callback(void);
static int o_create_font_callback(void);
static int o_texture_detail_callback(void);
static int o_font_detail_callback(void);
static int o_texture_prop_change_callback(void);
static int o_font_prop_change_callback(void);
static int o_texture_delete_callback(void);
static int o_font_delete_callback(void);

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
    {2, "生成项目Sandbox", o_gen_code_callback, 0},
    {3, "重新选择项目地址", o_reselect_path_callback, 0},
    {4, "保存更改到配置文件", o_save_ini_callback, 0},
};

// menu 1
static const MenuItem element_menu[] =
{
    {1, "管理所有元素", o_manage_all_elements_callback, 2},
    {2, "创建一个Sprite", o_create_sprite_callback, 1},
    {3, "创建一个UI元素", NULL, 3},
    {4, "创建一个Texture", o_create_texture_callback, 1},
    {5, "创建一个Font", o_create_font_callback, 1},
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
    {1, "创建 Button", o_create_ui_callback, 0},
    {2, "创建 Label", o_create_ui_callback, 0},
    {3, "创建 ProgressBar", o_create_ui_callback, 0},
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
    {-1, "删除此Sprite", o_sprite_delete_callback, 3},
    {0, "返回上一页", NULL, -2},
};

// menu 5
static MenuItem ui_management_menu[512] =
{
    {1, UI_TYPE, o_ui_prop_change_callback, 5},
    {2, UI_POS_X, o_ui_prop_change_callback, 5},
    {3, UI_POS_Y, o_ui_prop_change_callback, 5},
    {4, UI_WIDTH, o_ui_prop_change_callback, 5},
    {5, UI_HEIGHT, o_ui_prop_change_callback, 5},
    {6, UI_SCALE, o_ui_prop_change_callback, 5},
    {7, UI_BUTTON_LABEL, o_ui_prop_change_callback, 5},
    {8, UI_BUTTON_FONT, o_ui_prop_change_callback, 5},
    {9, UI_BUTTON_FONT_SIZE, o_ui_prop_change_callback, 5},
    {10, UI_BUTTON_COLOR, o_ui_prop_change_callback, 5},
    {11, UI_LABEL_FONT, o_ui_prop_change_callback, 5},
    {12, UI_LABEL_FONT_SIZE, o_ui_prop_change_callback, 5},
    {13, UI_LABEL_COLOR, o_ui_prop_change_callback, 5},
    {-1, "删除此UI控件", o_ui_delete_callback, 5},
    {0, "返回上一页", NULL, -2},
    
};

// menu 6
static MenuItem texture_detail_menu[] =
{
    {1, "更改Texture路径", o_texture_prop_change_callback, 6},
    {-1, "删除此UI控件", o_texture_delete_callback, 6},
    {0, "返回上一页", NULL, -2},
};

// menu 7
static MenuItem font_detail_menu[] =
{
    {1, "更改Font路径", o_font_prop_change_callback, 6},
    {-1, "删除此UI控件", o_ui_delete_callback, 6},
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
    [4] = { sprite_management_menu, 11},
    [5] = { ui_management_menu,15},
    [6] = { texture_detail_menu, sizeof(texture_detail_menu)/sizeof(texture_detail_menu[0])},
    [7] = { font_detail_menu, sizeof(font_detail_menu)/sizeof(font_detail_menu[0])},
};

static int o_sti(char* str)
{
    int len = strlen(str);
    int negtive = 0;
    if (str[0] == '-')
    {
        negtive = 1;
    }
    int res = 0;
    for (int i = negtive ? 1 : 0; i < len; ++i)
    {
        res *= 10;
        res += str[i] - '0';
    }
    return negtive ? -res : res;
}

static int o_get_width(char* v)
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
    int sel = o_sti(ans);

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

int o_find_uiType(struct list_node* node)
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
            struct list_node* node = list_find_if(p->next, o_find_uiType);
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
        if (p->next->kind == TextureSEC)
        {
            char* buf = malloc(sizeof(char) * 64);
            strcpy(buf, "Texture:");
            strcat(buf, p->next->data);
            all_elements_menu[count].id = count + 1;
            all_elements_menu[count].text = buf;
            all_elements_menu[count].callFn = o_texture_detail_callback;
            all_elements_menu[count].nextMenu = 4;
            count++;
            p = p->next;
            continue;
        }
        if (p->next->kind == FontSec)
        {
            char* buf = malloc(sizeof(char) * 64);
            strcpy(buf, "Font:");
            strcat(buf, p->next->data);
            all_elements_menu[count].id = count + 1;
            all_elements_menu[count].text = buf;
            all_elements_menu[count].callFn = o_font_detail_callback;
            all_elements_menu[count].nextMenu = 4;
            count++;
            p = p->next;
            continue;
        }
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
            struct list_node* node = list_find_if(p->next, o_find_uiType);
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

int o_find_ui_sec(struct list_node* node)
{
    return node->kind == UISec && !(strcmp(node->data, secName));
}

int o_sprite_prop_change_callback(void)
{
    strcpy(keyName, sprite_management_menu[choice].text);
    o_p_line(30);
    struct list_node* node = list_find_if(list, o_find_sprite_sec);
    //list_print(node);
    int isDefined = 0;
    struct list_node* theKeyNode = NULL;
    while (node && node->next && node->next->kind & (KEY|VALUE))
    {
        if (node->next->kind == KEY && !strcmp(node->next->data, keyName))
        {
            isDefined = 1;
            theKeyNode = node->next;
            break;
        }
        node = node->next;
    }
    // 这边有内存泄漏问题
    char* ans = malloc(sizeof(char) * 512);
    if (!isDefined)
    {
        printf("%s的 %s 属性(输入00返回):\n默认\n", secName, keyName);
        scanf("%s", ans);
        if (strcmp(ans, "00"))
        {
            struct list_node* n1 = malloc(sizeof(struct list_node));
            struct list_node* n2 = malloc(sizeof(struct list_node));
            n1->kind = KEY;
            //strcpy(n1->data, keyName);
            n1->data = keyName;
            n2->kind = VALUE;
            //strcpy(n1->data, ans);
            n2->data = ans;
            n1->next = n2;
            n2->prev = n1;
            n1->prev = node;
            n2->next = node->next;
            node->next = n1;
        }
    }
    else
    {
        printf("%s的 %s 属性(输入00返回):\n%s\n", secName, theKeyNode->data, theKeyNode->next->data);
        char ans[512] = {0};
        scanf("%s", ans);
        if (strcmp(ans, "00"))
        {
            theKeyNode->next->data = ans;
        }
    }
    //free(ans);
    return -1;
}

int o_ui_prop_change_callback(void)
{
    strcpy(keyName, ui_management_menu[choice].text);
    o_p_line(30);
    struct list_node* node = list_find_if(list, o_find_ui_sec);
    int isDefined = 0;
    struct list_node* theKeyNode = NULL;
    while (node && node->next && node->next->kind & (KEY|VALUE))
    {
        if (node->next->kind == KEY && !strcmp(node->next->data, keyName))
        {
            isDefined = 1;
            theKeyNode = node->next;
            break;
        }
        node = node->next;
    }
    // 这边有内存泄漏问题
    char* ans = malloc(sizeof(char) * 512);
    if (!isDefined)
    {
        printf("%s的 %s 属性(输入00返回):\n默认\n", secName, keyName);
        scanf("%s", ans);
        if (strcmp(ans, "00"))
        {
            struct list_node* n1 = malloc(sizeof(struct list_node));
            struct list_node* n2 = malloc(sizeof(struct list_node));
            n1->kind = KEY;
            //strcpy(n1->data, keyName);
            n1->data = keyName;
            n2->kind = VALUE;
            //strcpy(n1->data, ans);
            n2->data = ans;
            n1->next = n2;
            n2->prev = n1;
            n1->prev = node;
            n2->next = node->next;
            node->next = n1;
        }
    }
    else
    {
        printf("%s的 %s 属性(输入00返回):\n%s\n", secName, theKeyNode->data, theKeyNode->next->data);
        char ans[512] = {0};
        scanf("%s", ans);
        if (strcmp(ans, "00"))
        {
            theKeyNode->next->data = ans;
        }
    }
    //free(ans);
    return -1;
}

int o_create_sprite_callback()
{
    char* keys[] = {
        S_COLLISION, S_POS_X, S_POS_Y, S_ROTATE, S_SCALE, S_VISIBLE, S_ORIGIN_PIC
    };
    char* name = malloc(sizeof(char) * 64);
    o_p_line(30);
    printf("为Sprite命名(输入00返回)\n");
    scanf("%s", name);
    if (!strcmp(name, "00"))
    {
        return -1;
    }
    struct list_node* spriteNode = malloc(sizeof(struct list_node));
    spriteNode->kind = SpriteSec;
    spriteNode->data = name;
    list_append_node(list, spriteNode);
    for (int i = 0; i < 7; ++i)
    {
        char* ans = malloc(sizeof(char) * 512);
        printf("%s的 %s 属性(输入00为默认)\n", name, keys[i]);
        scanf("%s", ans);
        if (strcmp(ans, "00"))
        {
            struct list_node* propKey = malloc(sizeof(struct list_node));
            struct list_node* propVal = malloc(sizeof(struct list_node));
            propKey->kind = KEY;
            propKey->data = keys[i];
            propVal->kind = VALUE;
            propVal->data = ans;
            list_append_node(list, propKey);
            list_append_node(list, propVal);
        }
    }
    
    return -1;
}

int o_create_ui_callback()
{
    char* type = malloc(sizeof(char) * 64);
    strcpy(type, ui_type_menu[choice].text);
    type = strchr(type, ' ') + 1;
    
    char* keys[] =
    {
        UI_POS_X, UI_POS_Y, UI_WIDTH, UI_HEIGHT,UI_BUTTON_LABEL,
        UI_BUTTON_FONT, UI_BUTTON_FONT_SIZE, UI_BUTTON_COLOR, UI_LABEL_FONT,UI_LABEL_FONT_SIZE,
    };
    int btnIndexes[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int labIndexes[] = {0, 1, 2, 3, 8, 9};
    int pragIndexes[] = {0, 1, 2, 3};
    int *indexes[] = {btnIndexes, labIndexes, pragIndexes};
    int typescounts[] = {8, 6, 4};
    int thecount = 0;
    int* theindexes = NULL;
    char* types[] =
    {
        UI_TYPE_BUTTON, UI_TYPE_LABEL, UI_TYPE_PROGRESSBAR
    };
    struct list_node* typekeyNode = malloc(sizeof(struct list_node));
    typekeyNode->kind = KEY;
    typekeyNode->data = UI_TYPE;
    struct list_node* typeNode = malloc(sizeof(struct list_node));
    typeNode->kind = VALUE;
    for (int i = 0; i < sizeof(types)/sizeof(types[0]); ++i)
    {
        if (!strcmp(type, types[i]))
        {
            thecount = typescounts[i];
            typeNode->data = types[i];
            theindexes = indexes[i];
        }
    }
    //printf("%d", thecount);
    char* name = malloc(sizeof(char) * 64);
    o_p_line(30);
    printf("为%s命名(输入00返回)\n", type);
    scanf("%s", name);
    if (!strcmp(name, "00"))
    {
        return -1;
    }
    struct list_node* spriteNode = malloc(sizeof(struct list_node));
    spriteNode->kind = UISec;
    spriteNode->data = name;
    list_append_node(list, spriteNode);
    list_append_node(list, typekeyNode);
    list_append_node(list, typeNode);
    for (int i = 0; i < thecount; ++i)
    {
        char* ans = malloc(sizeof(char) * 512);
        printf("%s的 %s 属性(输入00为默认)\n", name, keys[theindexes[i]]);
        scanf("%s", ans);
        if (strcmp(ans, "00"))
        {
            struct list_node* propKey = malloc(sizeof(struct list_node));
            struct list_node* propVal = malloc(sizeof(struct list_node));
            propKey->kind = KEY;
            propKey->data = keys[theindexes[i]];
            propVal->kind = VALUE;
            propVal->data = ans;
            list_append_node(list, propKey);
            list_append_node(list, propVal);
        }
    }
    
    return -1;
}

int o_gen_code_callback()
{
    gen_sandbox(list, progPath);
    return 0;
}

int o_sprite_delete_callback()
{
    struct list_node* secNode = list_find_if(list, o_find_sprite_sec);
    list_del_sec(secNode);
    //o_refresh_elements_menu(list);
    return 1;
}

int o_ui_delete_callback()
{
    struct list_node* secNode = list_find_if(list, o_find_ui_sec);
    list_del_sec(secNode);
    //o_refresh_elements_menu(list);
    return 1;
}

int o_reselect_path_callback()
{
    printf("请输入项目目录:\n");
    char* ans = malloc(sizeof(char) * 512);
    scanf("%s", ans);
    strcpy(progPath, ans);
    update_files_callback();
}

int o_save_ini_callback()
{
    update_ini_callback();
    update_files_callback();
    return 0;
}

int o_create_texture_callback()
{
    char* name = malloc(sizeof(char) * 64);
    o_p_line(30);
    printf("为Texture命名(输入00返回)\n");
    scanf("%s", name);
    if (!strcmp(name, "00"))
    {
        return -1;
    }
    char* ans = malloc(sizeof(char) * 512);
    printf("Texture路径:\n");
    scanf("%s", ans);
    struct list_node* secNode = malloc(sizeof(struct list_node));
    secNode->kind = TextureSEC;
    secNode->data = name;
    struct list_node* pathKeyNode = malloc(sizeof(struct list_node));
    pathKeyNode->kind = KEY;
    pathKeyNode->data = TEXTURE_PATH;
    struct list_node* pathNode = malloc(sizeof(struct list_node));
    pathNode->kind = VALUE;
    pathNode->data = ans;
    
    list_append_node(list, secNode);
    list_append_node(list, pathKeyNode);
    list_append_node(list, pathNode);
    return -1;
}

int o_create_font_callback()
{
    char* name = malloc(sizeof(char) * 64);
    o_p_line(30);
    printf("为Font命名(输入00返回)\n");
    scanf("%s", name);
    if (!strcmp(name, "00"))
    {
        return -1;
    }
    char* ans = malloc(sizeof(char) * 512);
    printf("Font路径:\n");
    scanf("%s", ans);
    struct list_node* secNode = malloc(sizeof(struct list_node));
    secNode->kind = FontSec;
    secNode->data = name;
    struct list_node* pathKeyNode = malloc(sizeof(struct list_node));
    pathKeyNode->kind = KEY;
    pathKeyNode->data = TEXTURE_PATH;
    struct list_node* pathNode = malloc(sizeof(struct list_node));
    pathNode->kind = VALUE;
    pathNode->data = ans;
    
    list_append_node(list, secNode);
    list_append_node(list, pathKeyNode);
    list_append_node(list, pathNode);
    return -1;
}

int o_texture_detail_callback(void)
{
    const char *colon = strchr(all_elements_menu[choice].text, ':');
    if (colon && *(colon + 1))
        strcpy(secName, colon + 1);
    else
        strcpy(secName, all_elements_menu[choice].text);
    return 6;   
}

int o_font_detail_callback(void)
{
    const char *colon = strchr(all_elements_menu[choice].text, ':');
    if (colon && *(colon + 1))
        strcpy(secName, colon + 1);
    else
        strcpy(secName, all_elements_menu[choice].text);
    return 7;   
}

int o_find_texture_sec(struct list_node* node)
{
    return node->kind == TextureSEC && !(strcmp(node->data, secName));
}

int o_find_font_sec(struct list_node* node)
{
    return node->kind == FontSec && !(strcmp(node->data, secName));
}

int o_texture_prop_change_callback(void){
    char* ans = malloc(sizeof(char) * 512);
    printf("更改Texture路径(输入00不更改):\n");
    scanf("%s", ans);
    if (!strcmp(ans, "00"))
    {
        return -1;
    }
    struct list_node* secNode = list_find_if(list, o_find_texture_sec);
    secNode->next->next->data = ans;
    //list_print(list);
    return -1;
}

int o_font_prop_change_callback(void)
{
    char* ans = malloc(sizeof(char) * 512);
    printf("更改Font路径(输入00不更改):\n");
    scanf("%s", ans);
    if (!strcmp(ans, "00"))
    {
        return -1;
    }
    struct list_node* secNode = list_find_if(list, o_find_font_sec);
    secNode->next->next->data = ans;
    
    return -1;
}

int o_texture_delete_callback(void)
{
    struct list_node* secNode = list_find_if(list, o_find_texture_sec);
    list_del_sec(secNode);
    //o_refresh_elements_menu(list);
    return 1;
}

int o_font_delete_callback(void)
{
    struct list_node* secNode = list_find_if(list, o_find_font_sec);
    list_del_sec(secNode);
    //o_refresh_elements_menu(list);
    return 1;
}