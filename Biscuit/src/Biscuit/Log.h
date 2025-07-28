#pragma once

#include "pch.h"
#include "spdlog/spdlog.h"

namespace Biscuit
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// 引擎内部调用
#define BC_CORE_INFO(...)	::Biscuit::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BC_CORE_WARN(...)	::Biscuit::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BC_CORE_TRACE(...)	::Biscuit::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BC_CORE_FATAL(...)	::Biscuit::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define BC_CORE_ERROR(...)	::Biscuit::Log::GetCoreLogger()->error(__VA_ARGS__)

// 游戏开发调用
#define BC_INFO(...)		::Biscuit::Log::GetClientLogger()->info(__VA_ARGS__)
#define BC_WARN(...)		::Biscuit::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BC_TRACE(...)		::Biscuit::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BC_FATAL(...)		::Biscuit::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define BC_ERROR(...)		::Biscuit::Log::GetClientLogger()->error(__VA_ARGS__)

