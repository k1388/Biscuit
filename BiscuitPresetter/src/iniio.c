#include "iniio.h"

int ini_read(char* filePath, char* section, char* key, char** value)
{
    FILE* fp = fopen(filePath, "r");
    
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

static char* trim_right(char* s)
{
    if (!s || !*s) return s;
    char* p = s + strlen(s) - 1;
    while (p >= s && isspace((unsigned char)*p)) *p-- = '\0';
    return s;
}

int ini_write(char* filePath, char* section, char* key, char* value)
{
    FILE* fp = fopen(filePath, "r+");
    if (!fp)
    {
        /* 文件不存在则创建 */
        fp = fopen(filePath, "w");
        if (!fp) return 0;
        fprintf(fp, "[%s]\n%s=%s\n", section, key, value);
        fclose(fp);
        return 1;
    }

    /* 先读文件大小，便于一次性分配 */
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buf = (char*)malloc(fsize + 1024); /* 多留点空间用于插入 */
    if (!buf) { fclose(fp); return 0; }

    size_t bufLen = fread(buf, 1, fsize, fp);
    buf[bufLen] = '\0';

    /* 行指针数组，最多 10000 行，够用即可 */
    char* lines[10000];
    int lineCount = 0;

    /* 按行拆分 */
    char* line = strtok(buf, "\n");
    while (line && lineCount < 10000)
    {
        lines[lineCount++] = line;
        line = strtok(NULL, "\n");
    }

    int foundSection = 0;
    int foundKey     = 0;
    int insertAfter  = -1;     /* 插入新 key 的行号 */
    int secStart     = -1;     /* section 起始行号 */

    /* 遍历行 */
    for (int i = 0; i < lineCount; ++i)
    {
        char* l = lines[i];
        while (*l && isspace((unsigned char)*l)) ++l;

        if (*l == '[')
        {
            if (foundSection)
            {
                /* 当前 section 已经结束，仍未找到 key，需要插入 */
                insertAfter = i;
                break;
            }

            char secBuf[100] = {0};
            sscanf(l, "[%99[^]]", secBuf);
            trim_right(secBuf);
            if (strcmp(section, secBuf) == 0)
            {
                foundSection = 1;
                secStart = i;
            }
            continue;
        }

        if (!foundSection) continue;

        /* 在同一 section 内找 key */
        char keyBuf[100] = {0};
        char* eq = strchr(l, '=');
        if (eq)
        {
            strncpy(keyBuf, l, eq - l);
            keyBuf[eq - l] = '\0';
            trim_right(keyBuf);
            if (strcmp(key, keyBuf) == 0)
            {
                foundKey = 1;
                sprintf(l, "%s=%s", key, value); /* 原地替换 */
                break;
            }
        }
    }

    if (!foundSection)
    {
        /* 整个文件都没有该 section，直接追加到末尾 */
        sprintf(buf + bufLen, "\n[%s]\n%s=%s\n", section, key, value);
        bufLen = strlen(buf);
    }
    else if (foundSection && !foundKey)
    {
        /* section 存在但 key 不存在，需要插入 */
        if (insertAfter == -1)
            insertAfter = lineCount; /* 插在最后 */

        /* 计算插入点偏移 */
        char* pos = buf;
        for (int i = 0; i < insertAfter; ++i)
            pos += strlen(lines[i]) + 1; /* +1 为换行符 */

        /* 剩余内容后移 */
        int tailLen = bufLen - (pos - buf);
        memmove(pos + strlen(key) + strlen(value) + 2, pos, tailLen);

        /* 写入新 key=value */
        sprintf(pos, "\n%s=%s\n", key, value);
        bufLen += strlen(key) + strlen(value) + 1; /* 1 为换行 */
    }

    /* 写回文件 */
    freopen(filePath, "w", fp);
    if (!fp) { free(buf); return 0; }
    fwrite(buf, 1, bufLen, fp);
    fclose(fp);
    free(buf);
    return 1;
}