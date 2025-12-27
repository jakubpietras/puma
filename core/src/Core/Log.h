#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
#include <fmt/ostream.h>
#include <kbmath.h>

namespace kb
{
	class Log
	{
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

	std::ostream& operator<<(std::ostream& os, const kbm::Vec3& v);
	std::ostream& operator<<(std::ostream& os, const kbm::Vec4& v);
	std::ostream& operator<<(std::ostream& os, const kbm::Mat4& mat);
	std::ostream& operator<<(std::ostream& os, const kbm::Quat& q);
}

namespace fmt {
	template <> struct formatter<kbm::Vec3> : ostream_formatter {};
	template <> struct formatter<kbm::Vec4> : ostream_formatter {};
	template <> struct formatter<kbm::Mat4> : ostream_formatter {};
	template <> struct formatter<kbm::Quat> : ostream_formatter {};
}

#define	P_TRACE(...) ::kb::Log::GetLogger()->trace(__VA_ARGS__)
#define P_INFO(...) ::kb::Log::GetLogger()->info(__VA_ARGS__)
#define P_WARN(...) ::kb::Log::GetLogger()->warn(__VA_ARGS__)
#define P_ERROR(...) ::kb::Log::GetLogger()->error(__VA_ARGS__)
#define P_FATAL(...) ::kb::Log::GetLogger()->fatal(__VA_ARGS__)