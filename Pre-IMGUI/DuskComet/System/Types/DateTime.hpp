#ifndef DUSKCOMET_SYSTEM_TYPES_DATETIME__HPP
#define DUSKCOMET_SYSTEM_TYPES_DATETIME__HPP

#include <chrono>
#include <ctime>

namespace dc
{

	enum class Months
	{
		JANUARY   = 0,
		FEBRUARY  = 1,
		MARCH     = 2,
		APRIL     = 3,
		MAY       = 4,
		JUNE      = 5,
		JULY      = 6,
		AUGUST    = 7,
		SEPTEMBER = 8,
		OCTOBER   = 9,
		NOVEMBER  = 10,
		DECEMBER  = 11
	};

	struct DateTime
	{
	private:
		uint64_t timestamp;
	public:
		/// <summary>
		/// Sets the current second of the minute
		/// </summary>
		/// <param name="second">: Value will be clamped between 0 - 59</param>
		void setSecondOfTheMinute(const uint8_t& second);
		/// <summary>
		/// Second of the minute
		/// </summary>
		/// <returns>Value clamped between 0 - 59</returns>
		uint8_t getSecondOfTheMinute();


		/// <summary>
		/// Sets the current minute of the hour
		/// </summary>
		/// <param name="minute">: Value will be clamped between 0 - 59</param>
		void setMinuteOfTheHour(const uint8_t& minute);
		/// <summary>
		/// Minute of the hour
		/// </summary>
		/// <returns>Value clamped between 0 - 59</returns>
		uint8_t getMinuteOfTheHour();


		/// <summary>
		/// Sets the current hour of the day
		/// </summary>
		/// <param name="minute">: Value will be clamped between 0 - 23</param>
		void setHourOfTheDay(const uint8_t& hour);
		/// <summary>
		/// Hour of the day
		/// </summary>
		/// <returns>Value clamped between 0 - 23</returns>
		uint8_t getHourOfTheDay();

		/// <summary>
		/// Sets the current day of the month
		/// </summary>
		/// <param name="day">: Value clamped between 0 and the number of days in this month</param>
		void setDayOfTheMonth(const uint8_t& day);
		/// <summary>
		/// Day of the Month
		/// </summary>
		/// <returns>Value clamped between 0 and the number of days in this month</returns>
		uint8_t getDayOfTheMonth();

		/// <summary>
		/// Set the month of the year
		/// </summary>
		/// <param name="month"></param>
		void setMonthOfTheYear(const uint8_t& month);
		/// <summary>
		/// Get the month of the year
		/// </summary>
		/// <returns></returns>
		uint8_t getMonthOfTheYear();





		/// <summary>
		/// Is the year a leap year
		/// </summary>
		/// <param name="year"></param>
		/// <returns></returns>
		static bool isYearLeapYear(const uint32_t& year);

		/// <summary>
		/// How many days are in this month
		/// </summary>
		/// <param name="month"></param>
		/// <returns></returns>
		static uint8_t getDaysInMonth(const uint8_t& month, const uint32_t& year);
	};
}

#endif // !DUSKCOMET_SYSTEM_TYPES_DATETIME__HPP
