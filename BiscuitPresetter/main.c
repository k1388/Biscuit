#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <io.h>
#include <string.h>
#include "iniio.h"

#define  DEBUG

const char* PROJECT_FILE_NAME = "BCProjectSettings.bp";

int main(int argc, char *argv[])
{
    
#ifdef DEBUG
    printf("DEBUGING!\n");
    char* path = "C:\\Users\\kanho\\OneDrive\\Desktop\\test.ini";
    char value[109];
    if (ini_read(path, "Test1", "abc", &value))
    {
        printf("%s\n", value);
    }
    else
    {
        printf("notfound\n");
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
