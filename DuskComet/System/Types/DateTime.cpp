#include "DateTime.hpp"


namespace dc
{
	void DateTime::setSecondOfTheMinute(const uint8_t& second)
	{
		if (second >= 60)
		{

		}
	}
	uint8_t DateTime::getSecondOfTheMinute()
	{
		return 0;
	}


	void DateTime::setMinuteOfTheHour(const uint8_t& minute)
	{

	}
	uint8_t DateTime::getMinuteOfTheHour()
	{
		return 0;
	}


	void DateTime::setHourOfTheDay(const uint8_t& hour)
	{

	}
	uint8_t DateTime::getHourOfTheDay()
	{
		return 0;
	}


	void DateTime::setDayOfTheMonth(const uint8_t& day)
	{

	}
	uint8_t DateTime::getDayOfTheMonth()
	{
		return 0;
	}


	void DateTime::setMonthOfTheYear(const uint8_t& month)
	{

	}
	uint8_t DateTime::getMonthOfTheYear()
	{
		return 0;
	}






	bool DateTime::isYearLeapYear(const uint32_t& year)
	{
		return ((year % 4 == 0) && (year % 100 == 0) && (year % 400 == 0));
	}
	uint8_t DateTime::getDaysInMonth(const uint8_t& month, const uint32_t& year)
	{
		bool leapyear = dc::DateTime::isYearLeapYear(year);

		if (year % 2 == 0) //if the year is even?
			return 31;
		else
		{
			if (year == (uint32_t)Months::FEBRUARY)
			{
				if (leapyear)
					return 29;
				else
					return 28;
			}
			return 30;
		}
	}
}