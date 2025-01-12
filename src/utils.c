#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/errorMessages.h"

char *strtrim(char *str){

    while(*str == ' ')
        str++;

    char *end = str + strlen(str)-1;

    while(*end == ' ' || *end == '\n')
        end--;

    *(end+1) = '\0';

    return str;

}

int command_ended(char* command) {

    strtrim(command);
    int command_index = 0;
    while (command[command_index++] != '\0');
    return command[command_index-2] == ';';

}

void read_command(char** command) {

    int command_length = 0;     

    if((*command == NULL) || (*command != NULL && command_ended(*command))) { 

        free(*command);
        *command = NULL;

    }else {
    
        command_length = strlen(*command);  
        command_length++;
        (*command)[command_length-1] = ' ';

    }
    
    char c = 0;

    do{

        command_length++;
        *command = realloc(*command, (command_length)*sizeof(char));
        if (*command == NULL) {

            perror(MEMORY_ALOCATION_ERRROR); 
            exit(1);

        }
        c = (char) getchar();
        (*command)[command_length-1] = c;
        
    } while(c != '\n' && c != '\r' && c != '\377');

    *command = realloc(*command, (command_length)*sizeof(char));
    if (*command == NULL) {

        perror(MEMORY_ALOCATION_ERRROR); 
        exit(1);

    }
    (*command)[command_length-1]  = '\0';
    strtrim(*command);

}

char* strsplit(char **str, const char delimiter, int advance_ptr){

    if(advance_ptr)
        while(*((*str)++) != '\0');
    
    int str_index = 0;
    while ((*str)[str_index] != delimiter && (*str)[str_index++] != '\0');
        //str_index++;

    (*str)[str_index] = '\0';

    return *str;

}