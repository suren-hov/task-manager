#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/task.h"
#include "../include/file.h"
#include "../include/util.h"

int get_next_id(Task *tasks, int task_count) {
    int max_id = 0;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id > max_id) {
            max_id = tasks[i].id;
        }
    }
    return max_id + 1;
}

void bubble_sort_tasks(Task *tasks, int task_count) {
    int i, j;
    for (i = 0; i < task_count - 1; i++) {
        for (j = 0; j < task_count - i - 1; j++) {
            if (tasks[j].priority > tasks[j + 1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

void add_task(Task** tasks, int* task_count, char* title, char* description, Priority priority, struct tm due_date) {
    *tasks = (Task*)realloc(*tasks, sizeof(Task) * (*task_count + 1));
    Task new_task = {
        .id = get_next_id(*tasks, *task_count),
        .priority = priority,
        .status = PENDING,
        .due_date = due_date
    };
    strncpy(new_task.title, title, MAX_TITLE_LEN);
    strncpy(new_task.description, description, MAX_DESC_LEN);
    (*tasks)[*task_count] = new_task;
    (*task_count)++;
    save_tasks(*tasks, *task_count);
    printf("Task added successfully.\n");
}

void view_tasks(Task *tasks, int task_count) {
    if (task_count == 0) {
        printf("No tasks available.\n");
        return;
    }

    bubble_sort_tasks(tasks, task_count);

    for (int i = 0; i < task_count; i++) {
        char priority_str[10];
        switch (tasks[i].priority) {
            case HIGH: strcpy(priority_str, "High"); break;
            case MEDIUM: strcpy(priority_str, "Medium"); break;
            case LOW: strcpy(priority_str, "Low"); break;
        }

        char status_str[10];
        switch (tasks[i].status) {
            case PENDING: strcpy(status_str, "Pending"); break;
            case COMPLETED: strcpy(status_str, "Completed"); break;
            case FAILED: strcpy(status_str, "Failed"); break;
        }

        char due_date_str[20];
        strftime(due_date_str, sizeof(due_date_str), "%Y-%m-%d", &tasks[i].due_date);

        printf("%d. %s %s [%s] Due: %s Status: %s\n",
               tasks[i].id, tasks[i].title, tasks[i].description, priority_str, due_date_str, status_str);
    }
}


void update_task(Task* tasks, int task_count, int id, const char* field, char* value) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            if (strcmp(field, "title") == 0) {
                strncpy(tasks[i].title, value, sizeof(tasks[i].title) - 1);
                tasks[i].title[sizeof(tasks[i].title) - 1] = '\0';
            } else if (strcmp(field, "description") == 0) {
                strncpy(tasks[i].description, value, sizeof(tasks[i].description) - 1);
                tasks[i].description[sizeof(tasks[i].description) - 1] = '\0';
            } else if (strcmp(field, "priority") == 0) {
                tasks[i].priority = parse_priority(value);
            } else if (strcmp(field, "status") == 0) {
                tasks[i].status = parse_status(value);
            } else if (strcmp(field, "due") == 0) {
                tasks[i].due_date = parse_date(value);
            } else {
                printf("Unknown field: %s\n", field);
                return;
            }

            save_tasks(tasks, task_count);
            printf("Task updated successfully.\n");
            return;
        }
    }
    printf("Task not found.\n");
}

void delete_task(Task** tasks, int* task_count, int id) {
    for (int i = 0; i < *task_count; i++) {
        if ((*tasks)[i].id == id) {
            for (int j = i; j < *task_count - 1; j++) {
                (*tasks)[j] = (*tasks)[j + 1];
            }
            (*tasks) = (Task*)realloc(*tasks, sizeof(Task) * (*task_count - 1));
            (*task_count)--;
            save_tasks(*tasks, *task_count);
            printf("Task deleted successfully.\n");
            return;
        }
    }
    printf("Task not found.\n");
}
