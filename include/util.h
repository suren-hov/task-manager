#ifndef UTIL_H
#define UTIL_H

#include "task.h"

Priority parse_priority(char *priority_str);
Status parse_status(char *status_str);
struct tm parse_date(char *date_str);
int validate_date(struct tm);

#endif // UTIL_H
