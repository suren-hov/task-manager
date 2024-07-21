#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/util.h"

Priority parse_priority(char *priority_str) {
    if (strcmp(priority_str, "high") == 0) return HIGH;
    if (strcmp(priority_str, "medium") == 0) return MEDIUM;
    if (strcmp(priority_str, "low") == 0) return LOW;
    fprintf(stderr, "Invalid priority: %s\n", priority_str);
    exit(EXIT_FAILURE);
}

Status parse_status(char *status_str) {
    if (strcmp(status_str, "pending") == 0) return PENDING;
    if (strcmp(status_str, "completed") == 0) return COMPLETED;
    if (strcmp(status_str, "failed") == 0) return FAILED;
    fprintf(stderr, "Invalid status: %s\n", status_str);
    exit(EXIT_FAILURE);
}

int validate_date(struct tm time) {

    if (time.tm_year < 2024) return 0;
    if (time.tm_mon < 1 || time.tm_mon > 12) return 0;
    if (time.tm_mday < 1 || time.tm_mday > 31) return 0;

    return 1;
}

struct tm parse_date(char *date_str) {
    struct tm tm = {0};
    if (sscanf(date_str, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday) != 3) {
        fprintf(stderr, "Invalid date format: %s\n", date_str);
        exit(EXIT_FAILURE);
    }

    if (validate_date(tm) == 0){
        printf("Invlaid Date\n");
        exit(EXIT_FAILURE);
    }

    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    return tm;
}
