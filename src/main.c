#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/task.h"
#include "../include/file.h"
#include "../include/util.h"

void print_usage() {
    printf("Usage:\n");
    printf("  taskmanager add --title <title> --desc <description> --priority <high|medium|low> --due <YYYY-MM-DD>\n");
    printf("  taskmanager view --all\n");
    printf("  taskmanager update --id <id> --field <title|description|priority|status|due> --value <valid_input>\n");
    printf("  taskmanager delete --id <id>\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;
    }

    Task* tasks = NULL;
    int task_count = 0;
    load_tasks(&tasks, &task_count);

    if (strcmp(argv[1], "add") == 0) {
        if (argc != 10) {
            printf("Not correct count of arguments");
            print_usage();
            return EXIT_FAILURE;
        }

        char *title = NULL;
        char *description = NULL;
        Priority priority = HIGH;
        struct tm due_date = {0};

        for (int i = 2; i < argc; i += 2) {
            if (strcmp(argv[i], "--title") == 0) {
                title = argv[i + 1];
            } else if (strcmp(argv[i], "--desc") == 0) {
                description = argv[i + 1];
            } else if (strcmp(argv[i], "--priority") == 0) {
                priority = parse_priority(argv[i + 1]);
            } else if (strcmp(argv[i], "--due") == 0) {
                due_date = parse_date(argv[i + 1]);
            } else {
                print_usage();
                return EXIT_FAILURE;
            }
        }

        if (title == NULL || description == NULL) {
            print_usage();
            return EXIT_FAILURE;
        }

        add_task(&tasks, &task_count, title, description, priority, due_date);

    } else if (strcmp(argv[1], "view") == 0) {
        if (argc != 3 || strcmp(argv[2], "--all") != 0) {
            print_usage();
            return EXIT_FAILURE;
        }
        view_tasks(tasks, task_count);

    } else if (strcmp(argv[1], "update") == 0) {
        if (argc != 8) {
            print_usage();
            return EXIT_FAILURE;
        }
        
        char *field = NULL;
        char *value = NULL;
        int id;

        for (int i = 2; i < argc; i += 2) {
            if (strcmp(argv[i], "--id") == 0) {
                id = atoi(argv[i + 1]);
            } else if (strcmp(argv[i], "--field") == 0) {
                field = argv[i + 1];
            } else if (strcmp(argv[i], "--value") == 0) {
                value = argv[i + 1];
            } else {
                print_usage();
                return EXIT_FAILURE;
            }
        }

        update_task(tasks, task_count, id, field, value);

    } else if (strcmp(argv[1], "delete") == 0) {
        if (argc != 4) {
            print_usage();
            return EXIT_FAILURE;
        }

        int id = atoi(argv[3]);
        delete_task(&tasks, &task_count, id);

    } else {
        print_usage();
        return EXIT_FAILURE;
    }

    free(tasks);
    return EXIT_SUCCESS;
}
