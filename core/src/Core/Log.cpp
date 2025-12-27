#include "Log.h"
#include <iomanip>

namespace m = kbm;
namespace kb
{
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_Logger = spdlog::stdout_color_mt("LOG");
		s_Logger->set_level(spdlog::level::trace);
	}

	std::ostream& operator<<(std::ostream& os, const m::Vec3& v) {
		return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	}
	std::ostream& operator<<(std::ostream& os, const m::Vec4& v) {
		return os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
	}
	std::ostream& operator<<(std::ostream& os, const m::Mat4& mat) {
		os << std::fixed << std::setprecision(3);
		for (int row = 0; row < 4; ++row) {
			os << "[ ";
			for (int col = 0; col < 4; ++col) {
				os << std::setw(8) << mat(row, col);
				if (col < 3) os << ", ";
			}
			os << " ]\n";
		}
		return os;
	}
	std::ostream& operator<<(std::ostream& os, const m::Quat& q) {
		return os << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
	}
}
