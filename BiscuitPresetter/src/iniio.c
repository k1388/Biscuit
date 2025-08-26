#include "iniio.h"
#define MAX_LINE_LENGTH 256
#define MAX_SECTION_LENGTH 64
#define MAX_KEY_LENGTH 64
#include <stdbool.h>


void trim_string(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

int ini_write_inplace(char *filename, char *section, char *key, char *value) {
    if (!filename || !section || !key || !value) {
        return -1;
    }
    
    FILE *original_file = fopen(filename, "r");
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        if (original_file) fclose(original_file);
        return -2;
    }
    char line[MAX_LINE_LENGTH];
    char current_section[MAX_SECTION_LENGTH] = {0};
    bool section_found = false;
    bool key_found = false;
    bool section_exists = false;
    bool in_target_section = false;
    bool key_added = false;
    
    // 处理已有文件内容
    if (original_file) {
        while (fgets(line, sizeof(line), original_file)) {
            char trimmed_line[MAX_LINE_LENGTH];
            strcpy(trimmed_line, line);
            trim_string(trimmed_line);
            
            // 处理节
            if (trimmed_line[0] == '[') {
                // 如果在目标节中且键未找到，现在添加键值对
                if (in_target_section && !key_found && !key_added) {
                    fprintf(temp_file, "%s=%s\n", key, value);
                    key_found = true;
                    key_added = true;
                }
                char *end_bracket = strchr(trimmed_line, ']');
                if (end_bracket) {
                    *end_bracket = '\0';
                    strncpy(current_section, trimmed_line + 1, sizeof(current_section) - 1);
                    current_section[sizeof(current_section) - 1] = '\0';
                    // 检查是否找到目标节
                    if (strcmp(current_section, section) == 0) {
                        section_found = true;
                        section_exists = true;
                        in_target_section = true;
                    } else {
                        section_found = false;
                        in_target_section = false;
                    }
                }
                // 写入节行
                fputs(line, temp_file);
                continue;
            }
            
            // 处理键值对（只在目标节中）
            if (in_target_section && trimmed_line[0] != ';' && trimmed_line[0] != '#' && 
                strchr(trimmed_line, '=')) {
                char *equals = strchr(trimmed_line, '=');
                *equals = '\0';
                
                char current_key[MAX_KEY_LENGTH];
                strncpy(current_key, trimmed_line, sizeof(current_key) - 1);
                current_key[sizeof(current_key) - 1] = '\0';
                trim_string(current_key);
                
                if (strcmp(current_key, key) == 0) {
                    // 找到键，修改值
                    fprintf(temp_file, "%s=%s\n", key, value);
                    key_found = true;
                    key_added = true;
                    continue;
                }
                
                // 恢复等号以便写入原行
                *equals = '=';
            }
            // 写入原行
            fputs(line, temp_file);
        }
        fclose(original_file);
        // 如果目标节是最后一个节且键未找到，现在添加键值对
        if (in_target_section && !key_found && !key_added) {
            fprintf(temp_file, "%s=%s\n", key, value);
            key_found = true;
            key_added = true;
        }
    }
    
    // 如果节不存在，添加新节和键值对
    if (!section_exists) {
        // 确保文件末尾有空行（如果不是空文件）
        if (original_file) {
            // 检查临时文件是否已经有内容
            long pos = ftell(temp_file);
            if (pos > 0) {
                fprintf(temp_file, "\n");
            }
        }
        fprintf(temp_file, "[%s]\n", section);
        fprintf(temp_file, "%s=%s\n", key, value);
    }
    
    // 将临时文件内容写回原文件
    rewind(temp_file);
    original_file = fopen(filename, "w");
    if (!original_file) {
        fclose(temp_file);
        return -3; // 无法打开原文件进行写入
    }
    
    while (fgets(line, sizeof(line), temp_file)) {
        fputs(line, original_file);
    }
    
    fclose(original_file);
    fclose(temp_file);
    
    return 0; // 成功
}
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

// static char* trim_right(char* s)
// {
//     if (!s || !*s) return s;
//     char* p = s + strlen(s) - 1;
//     while (p >= s && isspace((unsigned char)*p)) *p-- = '\0';
//     return s;
// }
//
// int ini_write(char* filePath, char* section, char* key, char* value)
// {
//     FILE* fp = fopen(filePath, "r+");
//     if (!fp)
//     {
//         fp = fopen(filePath, "w");
//         if (!fp) return 0;
//         fprintf(fp, "[%s]\n%s=%s\n", section, key, value);
//         fclose(fp);
//         return 1;
//     }
//     
//     fseek(fp, 0, SEEK_END);
//     long fsize = ftell(fp);
//     fseek(fp, 0, SEEK_SET);
//
//     char* buf = (char*)malloc(fsize + 1024);
//     if (!buf) { fclose(fp); return 0; }
//
//     size_t bufLen = fread(buf, 1, fsize, fp);
//     buf[bufLen] = '\0';
//     
//     char* lines[10000];
//     int lineCount = 0;
//     
//     char* line = strtok(buf, "\n");
//     while (line && lineCount < 10000)
//     {
//         lines[lineCount++] = line;
//         line = strtok(NULL, "\n");
//     }
//
//     int foundSection = 0;
//     int foundKey     = 0;
//     int insertAfter  = -1;   
//     int secStart     = -1; 
//     
//     for (int i = 0; i < lineCount; ++i)
//     {
//         char* l = lines[i];
//         while (*l && isspace((unsigned char)*l)) ++l;
//
//         if (*l == '[')
//         {
//             if (foundSection)
//             {
//                 insertAfter = i;
//                 break;
//             }
//
//             char secBuf[100] = {0};
//             sscanf(l, "[%99[^]]", secBuf);
//             trim_right(secBuf);
//             if (strcmp(section, secBuf) == 0)
//             {
//                 foundSection = 1;
//                 secStart = i;
//             }
//             continue;
//         }
//
//         if (!foundSection) continue;
//         
//         char keyBuf[100] = {0};
//         char* eq = strchr(l, '=');
//         if (eq)
//         {
//             strncpy(keyBuf, l, eq - l);
//             keyBuf[eq - l] = '\0';
//             trim_right(keyBuf);
//             if (strcmp(key, keyBuf) == 0)
//             {
//                 foundKey = 1;
//                 sprintf(l, "%s=%s", key, value);
//                 break;
//             }
//         }
//     }
//
//     if (!foundSection)
//     {
//         sprintf(buf + bufLen, "\n[%s]\n%s=%s\n", section, key, value);
//         bufLen = strlen(buf);
//     }
//     else if (foundSection && !foundKey)
//     {
//         if (insertAfter == -1)
//             insertAfter = lineCount;
//         
//         char* pos = buf;
//         for (int i = 0; i < insertAfter; ++i)
//             pos += strlen(lines[i]) + 1;
//         
//         int tailLen = bufLen - (pos - buf);
//         memmove(pos + strlen(key) + strlen(value) + 2, pos, tailLen);
//         
//         sprintf(pos, "\n%s=%s\n", key, value);
//         bufLen += strlen(key) + strlen(value) + 1;
//     }
//     
//     freopen(filePath, "w", fp);
//     if (!fp) { free(buf); return 0; }
//     fwrite(buf, 1, bufLen, fp);
//     fclose(fp);
//     free(buf);
//     return 1;
// }