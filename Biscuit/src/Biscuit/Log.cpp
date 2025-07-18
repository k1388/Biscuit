#include "pch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Biscuit
{
	/// <summary>
	/// 引擎内部使用的Logger
	/// </summary>
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	/// <summary>
	/// 游戏项目使用的Logger
	/// </summary>
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	/// <summary>
	/// 初始化两个Logger，并设定各自的输出格式
	/// </summary>
	void Log::Init()
	{
		spdlog::set_pattern("%^[%l][%T]%n: %v %$");

		s_CoreLogger = spdlog::stdout_color_mt("BISCUIT");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stderr_color_mt("GAME");
		s_ClientLogger->set_level(spdlog::level::trace);

	}

}
