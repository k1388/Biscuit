#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define UI_ELEMENTS "UIElements"
#define SPRITE_ELEMENTS "SpriteElements"
#define SPRITES(str) "Sprite:" #str
#define UI(str) "UI:" #str

#define S_POS_X "positionX"
#define S_POS_Y "positionY"
#define S_SCALE "scale"
#define S_ROTATE "rotate"
#define S_ORIGIN_PIC "originPic"
#define S_OTHER_PIC(str) "otherPic" #str
#define S_VISIBLE "visible"
#define S_SCRIPT_PATH "scriptPath"

#define UI_POS_X "positionX"
#define UI_POS_Y "positionY"
#define UI_WIDTH "width"
#define UI_HEIGHT "height"
#define UI_SCALE "scale"
#define UI_BUTTON_LABEL "buttonLabel"
#define UI_BUTTON_FONT "buttonFont"
#define UI_BUTTON_FONT_SIZE "buttonFontSize"
#define UI_BUTTON_COLOR "buttonColor"
#define UI_LABEL_FONT "labelFont"
#define UI_LABEL_FONT_SIZE "labelFontSize"
#define UI_LABEL_COLOR "labelFontColor"

#define FONT(str) "Font:" #str
#define FONT_PATH "path"

#define TEXTURE(str) "Texture:" #str
#define TEXTURE_PATH "path"


char* SEC_NAMES[] = {
    "Sprite:", "UI:", UI_ELEMENTS, SPRITE_ELEMENTS, "Font:", "Texture:"
};

char* KEY_NAMES[] = {
    S_POS_X, S_POS_Y, S_SCALE, S_ROTATE, S_ORIGIN_PIC, "otherPic:", S_VISIBLE, S_SCRIPT_PATH
    
}

//const char* LOCAL_TEMP_FILE = "./temp/iniTemp.ini";

/// <summary>
/// 读取一个结构为.ini规范的文件
/// </summary>
/// <param name="filePath">文件路径</param>
/// <param name="section">段名称</param>
/// <param name="key">键名称</param>
/// <param name="value">值缓冲</param>
/// <returns>找到目标返回非0</returns>
int ini_read(
    char*       filePath,
    char*       section,
    char*       key,
    char**      value
);

/// <summary>
/// 写入一个结构为.ini规范的文件
/// </summary>
/// <param name="filePath">文件路径</param>
/// <param name="section">段名称</param>
/// <param name="key">键名称</param>
/// <param name="value">写入的值</param>
/// <returns>找到目标返回非0</returns>
int ini_write(
    char*       filePath,
    char*       section,
    char*       key,
    char*       value
);
