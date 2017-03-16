#ifndef DATE_H_
#define DATE_H_

#include <ostream>
#include <sstream>
#include <time.h>
#include <vector>

/** @brief A date class that stores one date if the date follows the rules of a correct date */

class Date
{
private:
	int year, month, day;
	int hour, minute, second;
public:
	// Constructor and destructor
	/** @brief Builds a date, verifying if the date follows the rules, if not
	 * throws an exception
	 * @param year Year of the date
	 * @param month Month of the date
	 * @param day Day of the date
	 * @param hour Hour of the date
	 * @param minute Minute of the date
	 * @param second Second of the date */
	Date(int year, int month, int day, int hour, int minute, int second);
	/** @brief Builds a date, using the system time and verifying if
	* the date follows the rules, if not throws an exception
	* @param time Number of seconds since 1 January 2000 00h00m00s */
	Date(time_t &time);
	/** @brief Destroys the date */
	~Date() {}

	// Get methods
	/** @brief Method to get the year of the date */
	int getYear() const;
	/** @brief Method to get the month of the date */
	int getMonth() const;
	/** @brief Method to get the day of the date */
	int getDay() const;
	/** @brief Method to get the hour of the date */
	int getHour() const;
	/** @brief Method to get the minute of the date */
	int getMinute() const;
	/** @brief Method to get the second of the date */
	int getSecond() const;

	/** @brief Method to compare if a date is lower than other
	 * @param d Right hand side date
	 * @return True if date is lower than d
	 * @return False if date isn't lower than d */
	bool operator<(const Date &d) const;

	bool operator>(const Date &d) const;

	bool operator==(const Date &d) const;

	// Exception classes
	/** @brief An exception class that is thrown if an invalid date is attempted
	 * to create */
	class InvalidDate {};
};

/** @brief Method to stream a date
 * @param out Reference to the output buffer
 * @param d Pointer to the date that is to stream
 * @return Reference to the output buffer */
std::ostream& operator<< (std::ostream& out, const Date* d);

#endif
