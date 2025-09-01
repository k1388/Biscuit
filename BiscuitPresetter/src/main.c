#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <io.h>
#include <string.h>
#include <windows.h>
#include <direct.h>
#include "iniio.h"
#include "code_gen.h"
#include "format_output.h"

//#define DEBUG

const char* PROJECT_FILE_NAME = "BCProjectSettings.bp";

int _find_sec(struct list_node* head)
{
    return !(strcmp(head->data, "testSprite") && head->kind == SpriteSec);
}

#ifdef DEBUG

int main()
{
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

            if (fnret == -2)
            {
                --stackIndex;
            }
            else if (fnret >= 0)
            {
                stack[stackIndex++] = fnret;
            }
        }

        
    }
}

#else

char projPath[512] = {0};
char iniPath[512] = {0};
char sandboxCodePath[512] = {0};
FILE* inifp = NULL;
FILE* sandboxcodefp = NULL;
struct list_node* m_list = NULL;

int directory_exists(const char* path)
{
    DWORD attr = GetFileAttributesA(path);
    return (attr != INVALID_FILE_ATTRIBUTES) && (attr & FILE_ATTRIBUTE_DIRECTORY);
}

void update_files(void)
{
    strcpy(iniPath, projPath);
    strcat(iniPath, "\\");
    strcat(iniPath, PROJECT_FILE_NAME);

    char tmpPath[512] = {0};
    strcpy(tmpPath, projPath);
    if (!directory_exists(strcat(tmpPath, "\\Sandbox")))
    {
        _mkdir(tmpPath);
    }
    
    
    strcpy(sandboxCodePath, projPath);
    strcat(sandboxCodePath, "\\Sandbox\\Sandbox.cpp");
    
    FILE* inifp = fopen(iniPath, "r+");
    if (!inifp)
    {
        inifp = fopen(iniPath, "w+");
    }

    FILE* sandboxcodefp = fopen(sandboxCodePath, "r+");
    if (!sandboxcodefp)
    {
        sandboxcodefp = fopen(sandboxCodePath, "w+");
    }

    m_list = gen_list(iniPath);

    o_bind_list(m_list);
    o_bind_progPath(sandboxCodePath);
}

void update_ini(void)
{
    char tmp[512] = {0};
    strcpy(tmp, projPath);
    strcat(tmp, "\\BCProjectSettings.bp");
    list_cover_origin_file(list, tmp);
}

int main(int argc, char *argv[])
{

    if (argc == 2)
    {
        strcpy(projPath, argv[1]);
    }
    else
    {
        printf("请输入项目目录:\n");
        scanf("%s", projPath);
    }
    o_bind_callback(update_files);
    o_bind_ini_callback(update_ini);
    update_files();
    
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

            if (fnret == -2)
            {
                --stackIndex;
            }
            else if (fnret >= 0)
            {
                stack[stackIndex++] = fnret;
            }
        }

        
    }
    
    return 0;
}

#endif
