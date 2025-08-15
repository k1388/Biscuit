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
    //fscanf(fp, "%*[^\n]", line);
    while (fgets(line, sizeof line, fp))
    {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0)
        {
            continue;
        }
        if (line[0] == '[')
        {
            char* lineBuf = malloc(64 * sizeof(char));
            int secIndex = 1;
            while (line[secIndex] != ']')
            {
                lineBuf[secIndex - 1] = line[secIndex];
                secIndex++;
            }
            lineBuf[secIndex - 1] = '\0';
            data_class dc[6] = {SpriteSec, UISec, UnnamedSec, UnnamedSec, FontSec, TextureSEC};
            char* secType = malloc(64 * sizeof(char));
            int typeIndex = 0;
            while (lineBuf[typeIndex] != ':')
            {
                if (lineBuf[typeIndex] == '\0')
                {
                    break;
                }
                secType[typeIndex] = lineBuf[typeIndex];
                typeIndex++;
            }
            secType[typeIndex] = '\0';
            for (int i = 0; i < 6; i++)
            {
                char* SEC_NAMES[] = {
                    "Sprite", "UI", UI_ELEMENTS, SPRITE_ELEMENTS, "Font", "Texture"
                };

                if (!strcmp(SEC_NAMES[i], secType))
                {
                    if (dc[i] == UnnamedSec)
                    {
                        list_append(head, lineBuf, UnnamedSec);
                        break;
                    }
                    else
                    {
                        char* secName = malloc(64 * sizeof(char));
                        int typeIndex = 0;
                        while (lineBuf[typeIndex] != ':')
                        {
                            //secType[typeIndex] = lineBuf[typeIndex];
                            typeIndex++;
                        }
                        typeIndex++;
                        int nameIndex = 0;
                        while (lineBuf[typeIndex] != '\n' && lineBuf[typeIndex] != '\0')
                        {
                            secName[nameIndex++] = lineBuf[typeIndex];
                            typeIndex++;
                        }
                        secName[nameIndex] = '\0';
                        list_append(head, secName, dc[i]);
                        break;
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
            lineBuf[keyIndex] = '\0';
            list_append(head, lineBuf, KEY);

            keyIndex++;
            char* valueBuf = malloc(512 * sizeof(char));
            int valueIndex = 0;
            while (line[valueIndex] > 0)
            {
                valueBuf[valueIndex] = line[keyIndex];
                valueIndex++;
                keyIndex++;
            }
            valueBuf[valueIndex] = '\0';
            list_append(head, valueBuf, VALUE);
        }
        //fscanf(fp, "%1023[^\n]%*c", line);
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
        if (p->next->kind == SpriteSec)
        {
            fprintf(fp, "std::shared_ptr<Sprite> %s;\n", (char*)p->next->data);
            sprites[spriteCount] = (char*)p->next->data;
            spriteCount++;
        }
        p = p->next;
    }

    //查找所有UI
    while (p->next != NULL)
    {
        if (p->next->kind == SpriteSec)
        {
            sprites[spriteCount] = (char*)p->next->data;
            char cl[100] = {0};
            
            p = p->next;
            while (p->next->next != NULL && strcmp(p->next->data, UI_TYPE))
            {
                p = p->next;
            }
            char* t = (char*)p->next->next->data;
            fprintf(fp, "std::shared_ptr<BCUI::%s> %s;\n", t, sprites[spriteCount]);
            spriteCount++;
            p = p->next;
        }
    }
    
    //生成OnInit()方法
    fprintf(fp, "\n\tvoid OnInit() override\n{\n");
    while (p->next != NULL)
    {
        if (p->next->kind == FontSec)
        {
            fprintf(fp, "LoadFontFromFile(%s, %s);\n", (char*)p->next->next->data, (char*)p->next->data);
            fonts[fontsCount] = (char*)p->next->next->data;
            fontsCount++;
        }
        else if (p->next->kind == TextureSEC)
        {
            fprintf(fp, "LoadTextureFromFile(%s, %s);\n", (char*)p->next->next->data, (char*)p->next->data);
            textures[texturesCount] = (char*)p->next->next->data;
            texturesCount++;
        }
        else if (p->next->kind == SpriteSec)
        {
            char* spriteName = (char*)p->next->data;
            p = p->next;
            while (strcmp(p->next->data, S_ORIGIN_PIC) && p->next != NULL)
            {
                p = p->next;
            }
            char* texName = (char*)p->next->data;
            fprintf(fp, "%s = make_shared<Sprite>(%s);\n", spriteName, texName);
        }
        
        
        
        p = p->next;

        
    }
}