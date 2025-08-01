// 注意在每个.cpp文件第一行添加本头文件
#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <functional>
#include <memory>
#include <vector>
#include <array>
#include <Glad/glad.h>


#ifdef BC_DEBUG

#include "Biscuit/Log.h"

#endif // BC_DEBUG



#ifdef BC_PLATFORM_WINDOWS
#include <Windows.h>
#endif // BC_PLATFORM_WINDOWS
