#pragma once

#ifdef BC_PLATFORM_WINDOWS

		#ifdef BC_BUILD_DLL
			#define BISCUIT_API __declspec(dllexport)
		#else
			#define BISCUIT_API __declspec(dllimport)
		#endif
#else
	#error Biscuit only supports Windows!
#endif
