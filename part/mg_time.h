#ifndef MG_TIME_H
#define MG_TIME_H

static const char *month_names[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Convert month to the month number. Return -1 on error, or month number
int month_number_to_month_name(const char *s);

// Parse date-time string, and return the corresponding time_t value
time_t parse_date_string(const char *s);

#endif /* MG_TIME_H */
