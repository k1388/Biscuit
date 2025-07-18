/*
	要导出函数或类，或在游戏项目中使用导出函数或导出类时引入此文件
*/

#pragma once

#ifdef BC_PLATFORM_WINDOWS

	#ifdef BC_DYNAMIC_LIBRARY
		#ifdef BC_BUILD_DLL
			#define BISCUIT_API __declspec(dllexport)
		#else
			#define BISCUIT_API __declspec(dllimport)
		#endif
	#else
		#define BISCUIT_API 
	#endif


#endif

#define BIT(x) (1 << (x))