#include "code_gen.h"

#include <stdio.h>
#include <stdlib.h>

struct list_node* gen_list(char* presetPath)
{
    struct list_node* head = list_create();

    FILE* fp = fopen(presetPath, "r");
    if (fp == NULL)
    {
        return NULL;
    }
    
    char line[1024] = {0};
    fscanf(fp, "%*[^\n]");
    
    while (fgetc(fp) != EOF)
    {
        if (line[0] == '[')
        {
            char* lineBuf = malloc(64 * sizeof(char));
            int secIndex = 1;
            while (line[secIndex] != ']')
            {
                lineBuf[secIndex] = line[secIndex];
                secIndex++;
            }
            data_class dc[6] = {SpriteSec, UISec, UnnamedSec, UnnamedSec, FontSec, TextureSEC};
            for (int i = 0; i < 6; i++)
            {
                if (!strcmp(SEC_NAMES[i], lineBuf))
                {
                    if (dc[i] == UnnamedSec)
                    {
                        list_append(head, lineBuf, UnnamedSec);
                    }
                    else
                    {
                        char* secType = malloc(64 * sizeof(char));
                        char* secName = malloc(64 * sizeof(char));
                        int typeIndex = 0;
                        while (lineBuf[typeIndex] != ':')
                        {
                            //secType[typeIndex] = lineBuf[typeIndex];
                            typeIndex++;
                        }
                        int nameIndex = 0;
                        while (lineBuf[typeIndex] != '\n' && lineBuf[typeIndex] != '\0')
                        {
                            secName[nameIndex++] = lineBuf[typeIndex];
                            typeIndex++;
                        }
                        list_append(head, secName, dc[i]);
                    }
                    
                }
            }
            
        }
        else
        {
            char* lineBuf = malloc(512 * sizeof(char));
            int keyIndex = 0;
            while (line[keyIndex] != '=')
            {
                lineBuf[keyIndex] = line[keyIndex];
                keyIndex++;
            }
            list_append(head, lineBuf, data_class::KEY);

            int valueIndex = keyIndex + 1;
            while (line[valueIndex] > 0)
            {
                lineBuf[valueIndex] = line[valueIndex];
                valueIndex++;
            }
            list_append(head, lineBuf, data_class::VALUE);
        }
    }
    
    return head;
}

int gen_sandbox(struct list_node* head, char* programPath)
{
    char* sprites[1000];
    char* uis[1000];
    char* textures[1000];
    char* fonts[1000];
    int spriteCount = 0;
    int texturesCount = 0;
    int fontsCount = 0;
    int uisCount = 0;
    
    FILE* fp = fopen(programPath, "r");
    struct list_node* p = head;

    //查找所有Sprite
    while (p->next != NULL)
    {
        if (p->next->kind == data_class::SpriteSec)
        {
            fprintf(fp, "std::shared_ptr<Sprite> %s;\n", (char*)p->next->data);
            sprites[spriteCount] = (char*)p->next->data;
            spriteCount++;
            p = p->next;
        }
    }

    //查找所有UI
    while (p->next != NULL)
    {
        // if (p->next->kind == data_class::SpriteSec)
        // {
        //     fprintf(fp, "std::shared_ptr<> %s;\n", (char*)p->next->data);
        //     sprites[spriteCount] = (char*)p->next->data;
        //     spriteCount++;
        //     p = p->next;
        // }
    }
    
    //生成OnInit()方法
    fprintf(fp, "\n\tvoid OnInit() override\n{\n");
    while (p->next != NULL)
    {
        if (p->next->kind == data_class::FontSec)
        {
            fprintf(fp, "LoadFontFromFile(%s, %s);\n", (char*)p->next->next->data, (char*)p->next->data);
            fonts[fontsCount] = (char*)p->next->next->data;
            fontsCount++;
            p = p->next->next;
        }
        else if (p->next->kind == data_class::TextureSEC)
        {
            fprintf(fp, "LoadTextureFromFile(%s, %s);\n", (char*)p->next->next->data, (char*)p->next->data);
            textures[texturesCount] = (char*)p->next->next->data;
            texturesCount++;
            p = p->next->next;
        }

        else if (p->next->kind == data_class::SpriteSec)
        {
            
        }
    }
}