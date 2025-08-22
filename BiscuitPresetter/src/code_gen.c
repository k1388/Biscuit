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
    int uiCount = 0;
    
    FILE* fp = fopen(programPath, "w");
    struct list_node* p = head;

    fprintf(fp, "#include \"Biscuit.h\"\n\n");
    fprintf(fp, "using namespace Biscuit;\n\n");
    fprintf(fp, "class Sandbox : public Application\n");
    fprintf(fp, "{\n");
    fprintf(fp, "public:\n");
    fprintf(fp, "\tSandbox(const Window::WindowProps& props):Application(props){}\n\n");
    
    //查找所有Sprite
    while (p->next != NULL)
    {
        if (p->next->kind == SpriteSec)
        {
            fprintf(fp, "\tstd::shared_ptr<Sprite> %s;\n", (char*)p->next->data);
            sprites[spriteCount] = (char*)p->next->data;
            spriteCount++;
        }
        p = p->next;
    }
    
    //查找所有UI
    p = head;
    while (p->next != NULL)
    {
        if (p->next->kind == UISec)
        {
            uis[uiCount] = (char*)p->next->data;
            char cl[100] = {0};
            
            p = p->next;
            while (p->next->next != NULL && strcmp(p->next->data, UI_TYPE))
            {
                p = p->next;
            }
            if (p->next->next == NULL)
            {
                break;
            }
            char* t = (char*)p->next->next->data;
            fprintf(fp, "\tstd::shared_ptr<BCUI::%s> %s = std::make_shared<BCUI::%s>();\n", t, uis[uiCount], t);
            uiCount++;
            //p = p->next;
        }
        p = p->next;
    }
    
    //生成OnInit()方法
    fprintf(fp, "\n\tvoid OnInit() override\n\t{\n");
    fprintf(fp, "\t\tauto ui = new BCUI::BCUI();\n\n");
    p = head;
    while (p && p->next)
    {
        if (p->next->kind == FontSec)
        {
            fprintf(fp, "\t\tLoadFontFromFile(%s, %s);\n", (char*)p->next->next->data, (char*)p->next->data);
            fonts[fontsCount] = (char*)p->next->next->data;
            fontsCount++;
        }
        else if (p->next->kind == TextureSEC)
        {
            fprintf(fp, "\t\tLoadTextureFromFile(\"%s\", \"%s\");\n", (char*)p->next->next->next->data, (char*)p->next->data);
            textures[texturesCount] = (char*)p->next->next->data;
            texturesCount++;
        }
        p = p->next;
    }
    p = head;
    while (p && p->next)
    {
        struct list_node* tmp;
        if (p->next->kind == SpriteSec)
        {
            tmp = p->next;
            char* spriteName = (char*)p->next->data;
            p = p->next;
            while (p && p->next && strcmp(p->next->data, S_ORIGIN_PIC) && p->next != NULL)
            {
                p = p->next;
            }
            char* texName = (char*)p->next->next->data;
            fprintf(fp, "\t\t%s = std::make_shared<Sprite>(GetTexture(\"%s\"));\n", spriteName, texName);

            p = tmp;
            char* keys[] = {
                S_COLLISION, S_POS_X, S_POS_Y, S_ROTATE, S_SCALE, S_VISIBLE, S_ORIGIN_PIC
            };
            while (p && p->next && p->next->kind & (KEY|VALUE))
            {
                if (p->next->kind == KEY)
                {
                    if (!strcmp(p->next->data, keys[0]))
                    {
                        if (!strcmp(p->next->next->data, "false"))
                            fprintf(fp, "\t\t%s->SetCollidable(false);\n", spriteName);
                        else
                            fprintf(fp, "\t\t%s->SetCollidable(true);\n", spriteName);
                    }
                    else if (!strcmp(p->next->data, keys[1]))
                    {
                        fprintf(fp, "\t\t%s->SetPosX(%s);\n", spriteName, p->next->next->data);
                    }
                    else if (!strcmp(p->next->data, keys[2]))
                    {
                        fprintf(fp, "\t\t%s->SetPosY(%s);\n", spriteName, p->next->next->data);
                    }
                    else if (!strcmp(p->next->data, keys[3]))
                    {
                        fprintf(fp, "\t\t%s->SetRotation(%s);\n", spriteName, p->next->next->data);
                    }
                    else if (!strcmp(p->next->data, keys[4]))
                    {
                        fprintf(fp, "\t\t%s->SetScale(%s);\n", spriteName, p->next->next->data);
                    }
                    else if (!strcmp(p->next->data, keys[5]))
                    {
                        fprintf(fp, "\t\t%s->SetVisible(%s);\n", spriteName, p->next->next->data);
                    }
                }
                p = p->next;
            }
            p = p->next;
        }
        if (p && p->next && p->next->kind == UISec)
        {
            char* uiName = (char*)p->next->data;
            p = p->next;
            char* keys[] = {
                UI_POS_X, UI_POS_Y, UI_WIDTH, UI_HEIGHT,UI_BUTTON_LABEL,
                UI_BUTTON_FONT, UI_BUTTON_FONT_SIZE, UI_BUTTON_COLOR, UI_LABEL_FONT,UI_LABEL_FONT_SIZE,
                //UI_LABEL_COLOR
            };
            int bfontFlag = 0;
            char* bfontName = {0};
            char* bfontSize = {0};
            int lfontFlag = 0;
            char* lfontName = {0};
            char* lfontSize = {0};
            while (p && p->next && p->next->kind & (KEY|VALUE))
            {
                if (p->next->kind == KEY)
                {
                    if (!strcmp(p->next->data, keys[0]))
                    {
                        fprintf(fp, "\t\t%s->SetPositionX(%s);\n", uiName, p->next->next->data);
                    }
                    else if (!strcmp(p->next->data, keys[1]))
                    {
                        fprintf(fp, "\t\t%s->SetPositionY(%s);\n", uiName, p->next->next->data);
                    }
                    else if (!strcmp(p->next->data, keys[2]))
                    {
                        fprintf(fp, "\t\t%s->SetSize(Vec2(%s, %s->GetSize().Y()));\n", uiName, p->next->next->data, uiName);
                    }
                    else if (!strcmp(p->next->data, keys[3]))
                    {
                        fprintf(fp, "\t\t%s->SetSize(Vec2(%s->GetSize().Y(), %s));\n", uiName, uiName, p->next->next->data);
                    }
                    else if (!strcmp(p->next->data, keys[4]))
                    {
                        fprintf(fp, "\t\t%s->SetLabel(\"%s\");\n", uiName, p->next->next->data);
                    }
                    else if (!strcmp(p->next->data, keys[5]))
                    {
                        bfontFlag = 1;
                        bfontName = p->next->next->data;
                    }
                    else if (!strcmp(p->next->data, keys[6]))
                    {
                        bfontFlag = 1;
                        bfontSize = p->next->next->data;
                    }
                    else if (!strcmp(p->next->data, keys[7]))
                    {
                        fprintf(fp, "\t\t%s->SetColor(Vec4(\"%s\"));\n", uiName, p->next->next->data);
                    }
                    else if (!strcmp(p->next->data, keys[8]))
                    {
                        lfontFlag = 1;
                        lfontName = p->next->next->data;
                    }
                    else if (!strcmp(p->next->data, keys[9]))
                    {
                        lfontFlag = 1;
                        lfontSize = p->next->next->data;
                    }
                }
                p = p->next;
            }
            if (bfontFlag)
            {
                fprintf(fp, "\t\t%s->SetLabelFont(\"%s\", %s);\n", uiName, bfontName, bfontSize);
            }
            if (lfontFlag)
            {
                fprintf(fp, "\t\t%s->SetLabelFont(\"%s\", %s);\n", uiName, lfontName, lfontSize);
            }
        }

        
        if (p && p->next && p->next->kind == UnnamedSec)
        {
            if (!strcmp(p->next->data, SPRITE_ELEMENTS))
            {
                p = p->next;
                while (p->next != NULL && p->next->kind & (KEY|VALUE))
                {
                    if (p->next->kind == KEY)
                    {
                        fprintf(fp, "\t\tAddSprite(%s);\n", p->next->data);
                    }
                    p = p->next;
                } 
            }else if (!strcmp(p->next->data, UI_ELEMENTS))
            {
                p = p->next;
                while (p && p->next && p->next->kind & (KEY|VALUE))
                {
                    if (p->next->kind == KEY)
                    {
                        fprintf(fp, "\t\tui->Add(\"%s.get()\");\n", p->next->data);
                    }
                    p = p->next;
                }
            }
        }
        p = p->next;
    }
    
    fprintf(fp, "\t\tPushOverLay(ui);\n");
    fprintf(fp, "\t}\n");
    fprintf(fp, "};\n\n");
    fprintf(fp, "Application* Biscuit::CreateApplication()\n");
    fprintf(fp, "{\n");
    fprintf(fp, "\tWindow::WindowProps* props = new Window::WindowProps(\"Game\", 1920, 1080);\n");
    fprintf(fp, "\treturn new Sandbox(*props);\n");
    fprintf(fp, "}\n\n");
}