#ifndef __SYSTEM_DATETIME_HPP__
#define __SYSTEM_DATETIME_HPP__

#include <System/TimeSpan.hpp>

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace System
{
	class DateTime
	{
	public:
		DateTime()
			: m_time(0)
		{

		}

		DateTime(int year)
			: DateTime(year, 0)
		{

		}

		DateTime(int year, int month)
			: DateTime(year, month, 0)
		{

		}

		DateTime(int year, int month, int day)
			: DateTime(year, month, day, 0)
		{

		}

		DateTime(int year, int month, int day, int hour)
			: DateTime(year, month, day, hour, 0)
		{

		}

		DateTime(int year, int month, int day, int hour, int minute)
			: DateTime(year, month, day, hour, minute, 0)
		{

		}

		DateTime(int year, int month, int day, int hour, int minute, int second)
			: DateTime(year, month, day, hour, minute, second, 0)
		{

		}

		DateTime(int year, int month, int day, int hour, int minute, int second, int milliseconds)
			: m_time(0)
		{
			const int leapYears = ((year - 1972) + 1) / 4;
			
			m_time = leapYears * Days2Ms(366) + (year - 1970 - leapYears) * Days2Ms(365);
			m_time += Days2Ms(DaysTillMonth(year, month));
			m_time += Days2Ms(day > 0 ? day - 1 : 0);
			m_time += Hours2Ms(hour > 0 ? hour - 1 : 0);
			m_time += Minutes2Ms(minute > 0 ? minute - 1 : 0);
			m_time += Seconds2Ms(second > 0 ? second - 1 : 0);
			m_time += milliseconds;
		}

		DateTime(const DateTime& rhs)
		{
			m_time = rhs.m_time;
		}

		DateTime& operator=(const DateTime& rhs)
		{
			m_time = rhs.m_time;

			return *this;
		}

		static DateTime UtcNow()
		{
			return DateTime(
				static_cast<uint64_t>(
					std::chrono::time_point_cast<std::chrono::milliseconds>(
						std::chrono::system_clock::now()
						).time_since_epoch().count()
				)
			);
		}

		int getDay() const
		{
			return 0;
		}

		int getMont() const
		{
			return 0;
		}

		int getYear() const
		{
			return m_time / Years2Ms(1) + 1970ull;
		}

		int getHour() const
		{
			return 0;
		}

		int getMinute() const
		{
			return 0;
		}

		int getSecond() const
		{
			return 0;
		}

		uint64_t getUnixTimestamp() const
		{
			return m_time / 1000ull;
		}

		bool operator<(const DateTime& rhs) const
		{
			return m_time < rhs.m_time;
		}

		bool operator<=(const DateTime& rhs) const
		{
			return m_time <= rhs.m_time;
		}

		bool operator>(const DateTime& rhs) const
		{
			return m_time > rhs.m_time;
		}

		bool operator>=(const DateTime& rhs) const
		{
			return m_time >= rhs.m_time;
		}

		bool operator==(const DateTime& rhs) const
		{
			return m_time == rhs.m_time;
		}

		DateTime operator +=(const TimeSpan& span) const
		{
			return this->Add(span);
		}

		DateTime operator -= (const TimeSpan& span) const
		{
			return this->Subtract(span);
		}

		DateTime Add(const TimeSpan& span) const
		{
			return DateTime(m_time + static_cast<uint64_t>(span.GetTotalMilliseconds()));
		}

		DateTime Subtract(const TimeSpan& span) const
		{
			return DateTime(m_time - static_cast<uint64_t>(span.GetTotalMilliseconds()));
		}

		DateTime AddYears(int years) const
		{
			return DateTime(m_time + Years2Ms(years));
		}

		DateTime AddMonths(int months) const
		{
			return DateTime(); // Implement
		}

		std::string ToString(const std::string& format = std::string()) const
		{
			std::stringstream ss;

			ss << std::setfill('0')
				<< std::setw(2) << this->getDay() << "/"
				<< std::setw(2) << this->getHour() << "/"
				<< std::setw(2) << this->getMinute() << "/"
				<< std::setw(4) << this->getSecond() << " ";

			return ss.str();
		}

		// Statics
		static constexpr bool IsLeapYear(int year)
		{
			return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
		}

		static constexpr int DaysInMonth(int year, int month)
		{
			constexpr int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

			return (month == 2 && IsLeapYear(year))
				? 29
				: daysPerMonth[(month - 1) % 12];
		}

		static constexpr int DaysTillMonth(int year, int month)
		{
			constexpr int daysTillMonthLeap[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
			constexpr int daysTillMonth[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

			return IsLeapYear(year)
				? daysTillMonthLeap[(month - 1) % 12]
				: daysTillMonth[(month - 1) % 12];
		}

		static constexpr uint64_t Years2Ms(uint64_t years)
		{
			return Days2Ms(years * static_cast<uint64_t>(365));
		}

		static constexpr uint64_t Days2Ms(uint64_t days)
		{
			return Hours2Ms(days * static_cast<uint64_t>(24));
		}

		static constexpr uint64_t Hours2Ms(uint64_t hours)
		{
			return Minutes2Ms(hours * static_cast<uint64_t>(60));
		}

		static constexpr uint64_t Minutes2Ms(uint64_t minutes)
		{
			return Seconds2Ms(minutes * static_cast<uint64_t>(60));
		}

		static constexpr uint64_t Seconds2Ms(uint64_t seconds)
		{
			return (seconds * static_cast<uint64_t>(1000));
		}

	private:
		DateTime(uint64_t time)
			: m_time(time)
		{

		}

	private:
		uint64_t m_time;
	};
}

#endif // __SYSTEM_DATETIME_HPP__
