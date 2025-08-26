#pragma once
#include <stdio.h>
#include "data_struct.h"

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

void o_p_mainmenu(char* projPath)
{
    system("cls");
    int maxLen = _o_get_width(projPath) + 10;
    o_p_stars(maxLen);
    printf("\t\t主菜单\n");
    printf("项目地址：%s\n", projPath);
    o_p_line(maxLen);
    printf("1.浏览和设置项目元素\n");
    printf("2.生成项目Sandbox\n");
    printf("3.重新选择项目地址\n");
    o_p_stars(maxLen);
    printf("请选择：\n");
}

void o_p_elements()
{
    system("cls");
    o_p_stars(16);
    printf("1.管理所有元素\n");
    printf("2.创建一个Sprite\n");
    printf("3.创建一个UI元素\n");
    printf("0.返回上一页\n");
    o_p_stars(16);
    printf("请选择：\n");
}

int _o_find_uiType(struct list_node* node)
{
    return !strcmp((char*)node->data, UI_TYPE) && node->kind == KEY;
}

void o_p_all_lements(struct list_node* head)
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

void o_p_showDetails(struct list_node* node)
{
    system("cls");
    o_p_stars(30);
    printf("\t%s的属性\n");
    int count = 0;
    struct list_node* p = node;
    while (p->next != NULL && p->next->kind | (KEY|VALUE))
    {
        if (p->next->kind == KEY)
        {
            char* props[] = {
                S_COLLISION, S_POS_X, S_POS_Y, S_ROTATE, S_SCALE, S_VISIBLE, S_ORIGIN_PIC
            };
            for (int i = 0; i < 7; ++i)
            {
                printf("%d.%s:%s\t", ++count, props[i], p->next->next->data);
            }
        }
        p = p->next;
    }
    printf("0.返回上一页\n");
    printf("a.删除\n");
    o_p_stars(30);
    printf("请输入：\n");
}

void o_p_showProp(char* gameobj, struct list_node* keyNode)
{
    system("cls");
    o_p_stars(30);
    printf("\t%s的%s属性\n", gameobj, keyNode->data);
    printf("1.修改\n");
    printf("0.返回上一页\n");
    o_p_stars(30);
}

