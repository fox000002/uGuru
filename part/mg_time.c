#include "mg_defs.h"

#include "mg_time.h"


// Convert month to the month number. Return -1 on error, or month number
int month_number_to_month_name(const char *s)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(month_names); i++)
	{
		if (!strcmp(s, month_names[i]))
		{
			return (int) i;
		}
	}
	return -1;
}

// Parse date-time string, and return the corresponding time_t value
time_t parse_date_string(const char *s)
{
  time_t current_time;
  struct tm tm, *tmp;
  char mon[32];
  int sec, min, hour, mday, month, year;

  (void) memset(&tm, 0, sizeof(tm));
  sec = min = hour = mday = month = year = 0;

  if (((sscanf(s, "%d/%3s/%d %d:%d:%d",
            &mday, mon, &year, &hour, &min, &sec) == 6) ||
        (sscanf(s, "%d %3s %d %d:%d:%d",
                &mday, mon, &year, &hour, &min, &sec) == 6) ||
        (sscanf(s, "%*3s, %d %3s %d %d:%d:%d",
                &mday, mon, &year, &hour, &min, &sec) == 6) ||
        (sscanf(s, "%d-%3s-%d %d:%d:%d",
                &mday, mon, &year, &hour, &min, &sec) == 6)) &&
      (month = month_number_to_month_name(mon)) != -1) {
    tm.tm_mday = mday;
    tm.tm_mon = month;
    tm.tm_year = year;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;
  }

  if (tm.tm_year > 1900) {
    tm.tm_year -= 1900;
  } else if (tm.tm_year < 70) {
    tm.tm_year += 100;
  }

  // Set Daylight Saving Time field
  current_time = time(NULL);
  tmp = localtime(&current_time);
  tm.tm_isdst = tmp->tm_isdst;

  return mktime(&tm);
}

