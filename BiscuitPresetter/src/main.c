#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <io.h>
#include <string.h>
#include "iniio.h"
#include "code_gen.h"
#include "format_output.h"

#define DEBUG

const char* PROJECT_FILE_NAME = "BCProjectSettings.bp";

int _find_sec(struct list_node* head)
{
    return !(strcmp(head->data, "testSprite") && head->kind == SpriteSec);
}

int main(int argc, char *argv[])
{
    
#ifdef DEBUG
    printf("DEBUGING!\n");
    
    char* path = "D:\\aaaa\\test.ini";
    char* readonlyPath = "C:\\Users\\kanho\\OneDrive\\Desktop\\bcp.ini";
    char* tempCode = "C:\\Users\\kanho\\OneDrive\\Desktop\\tempCode.ini";
    struct list_node* list = gen_list(readonlyPath);

    o_bind_list(list);
    int stack[10];
    int stackIndex = 0;
    stack[stackIndex++] = 0;
    while (stackIndex > 0)
    {
        int cur = stack[stackIndex - 1];
        MenuItem* items = menu_table[cur].items;
        int itemCount = menu_table[cur].count;
        int index = o_menu(items, itemCount);
        if (index < 0)
        {
            continue;
        }

        MenuItem* item = &items[index];

        if (!item->callFn && item->nextMenu >= 0)
        {
            stack[stackIndex++] = item->nextMenu;
            continue;
        }

        if (item->nextMenu == -2)
        {
            if (stackIndex > 1)
            {
                --stackIndex;
            }
            continue;
        }

        if (item->callFn)
        {
            int fnret = item->callFn();
            if (fnret == -2 || fnret == 1)
            {
                --stackIndex;
            }
            else if (fnret >= 0)
            {
                stack[stackIndex++] = fnret;
            }
        }

        
    }
    
#elif
    char *projPath[200];
    int isRunning = 1;
    if(argc == 1)
    {
        int hasRightProjPath = 0;
        while (!hasRightProjPath)
        {
            printf("\033[33m输入项目路径\033[0m:\n");
            scanf("%s", projPath);

            struct stat s;
            if (stat(projPath, &s) != 0 || !(s.st_mode & S_IFDIR))
            {
                printf("\033[31m您输入的路径有误！\033[0m\n");
            }
            else
            {
                hasRightProjPath = 1;
            }
        }

        int hasCreatedProjFile = 0;
        if (access(strcat(projPath, PROJECT_FILE_NAME), 0)==0)
        {
            hasCreatedProjFile = 1;
        }
        else
        {
                
        }
    }
    while (isRunning)
    {
        //system("cls");
    }
#endif
    
    
    return 0;
}
