#ifndef TASK_H
#define TASK_H

#include <time.h>

#define MAX_TITLE_LEN 100
#define MAX_DESC_LEN 256

typedef enum {
    HIGH,
    MEDIUM,
    LOW
} Priority;

typedef enum {
    PENDING,
    COMPLETED,
    FAILED
} Status;

typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char description[MAX_DESC_LEN];
    Priority priority;
    Status status;
    struct tm due_date;
} Task;

void add_task(Task** tasks, int* task_count, char* title, char* description, Priority priority, struct tm due_date);
void view_tasks(Task* tasks, int task_count);
void update_task(Task* tasks, int task_count, int id, Status status);
void delete_task(Task** tasks, int* task_count, int id);
int get_next_id(Task* tasks, int task_count);

#endif // TASK_H
