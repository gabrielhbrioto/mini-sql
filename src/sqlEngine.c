#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/utils.h"

void mini_sql_init() {

    char *command = NULL;
    printf("mini_sql=# ");
    read_command(&command);

    while(strcmp(strtrim(command), "exit")) {

        printf("mini_sql=# ");
        read_command(&command);
        if(command_ended(command))
            printf("Command: %s\n", command);

    }

    free(command);
}
