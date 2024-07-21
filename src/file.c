#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/file.h"

#define FILENAME "tasks.dat"

void check_and_update_task_status(Task* tasks, int task_count) {
    time_t now = time(NULL);
    for (int i = 0; i < task_count; i++) {
          time_t time = mktime(&tasks[i].due_date);

        if (difftime(time, now) < -86399.999999 && (tasks[i].status != 1)) {
            tasks[i].status = 2;
        }
        printf("%f\n", difftime(time, now));
    }
}

void save_tasks(Task* tasks, int task_count) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fwrite(&task_count, sizeof(int), 1, file);
    fwrite(tasks, sizeof(Task), task_count, file);
    fclose(file);
}

void load_tasks(Task** tasks, int* task_count) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        *tasks = NULL;
        *task_count = 0;
        return;
    }
    
    fread(task_count, sizeof(int), 1, file);
    *tasks = (Task*)malloc(sizeof(Task) * (*task_count));
    fread(*tasks, sizeof(Task), *task_count, file);

    check_and_update_task_status(*tasks, *task_count);

    fclose(file);
}
