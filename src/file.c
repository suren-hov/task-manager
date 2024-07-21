#include <stdio.h>
#include <stdlib.h>
#include "../include/file.h"

#define FILENAME "tasks.dat"

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
    fclose(file);
}
