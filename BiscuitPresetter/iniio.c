#include "iniio.h"

int ini_read(char* filePath, char* section, char* key, char** value)
{
    FILE* fp = fopen(filePath, "r+");
    
    if (fp == NULL)
    {
        return 0;
    }

    char ch = fgetc(fp);
    while (ch != EOF)
    {
        char secBuf[100] = {0};
        size_t secBufLen = 0;
        
        if (ch == '[')
        {
            ch = fgetc(fp);
            while (ch != ']')
            {
                secBuf[secBufLen++] = ch;
                ch = fgetc(fp);
            }
            ch = fgetc(fp);  
            if (!strcmp(section, secBuf))
            {
                while (ch != ']' && ch != EOF)
                {
                    char keyBuf[100] = {0};
                    size_t keyBufLen = 0;
                    ch = fgetc(fp);
                    while (ch != '=')
                    {
                        if (ch == EOF)
                        {
                            return 0;
                        }
                        keyBuf[keyBufLen++] = ch;
                        ch = fgetc(fp);
                    }
                
                    if (!strcmp(key, keyBuf))
                    {
                        if (ch == EOF)
                        {
                            return 0;
                        }
                        // 返回key对应的value
                        char valBuf[100] = {0};
                        size_t valBufLen = 0;
                        ch = fgetc(fp);
                        while (ch != '\n' && ch != EOF)
                        {
                            valBuf[valBufLen++] = ch;
                            ch = fgetc(fp);
                        }
                        strcpy(value, valBuf);
                        return 1;
                    }
                    else
                    {
                        fscanf(fp, "%*[^\n]%*c");
                        continue;
                    }
                }
            }
            else
            {
                continue;
                //fscanf(fp, "%*[^\n]%*c");
            }
        }

        ch = fgetc(fp);
    }

    return 0;
}
