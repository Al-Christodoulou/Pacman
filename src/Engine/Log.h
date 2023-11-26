#pragma once
#include <fstream>

// default behavior
#ifdef _DEBUG
#define LOG_ENABLED
#endif

class Log
{
private:
	static std::ofstream m_log;

public:
	template <typename T>
	inline friend static std::ostream& operator<<([[maybe_unused]] const Log& log,
												[[maybe_unused]] const T& t)
	{
		return
#ifdef LOG_ENABLED
			log.m_log << t;
#else
			m_log;
#endif
	}

	inline static std::ostream& flush()
	{
		return
#ifdef LOG_ENABLED
			m_log.flush();
#else
			m_log;
#endif
	}
};