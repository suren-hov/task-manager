#ifndef FILE_H
#define FILE_H

#include "task.h"

void save_tasks(Task* tasks, int task_count);
void load_tasks(Task** tasks, int* task_count);
void check_and_update_task_status(Task* tasks, int task_count);

#endif // FILE_H
