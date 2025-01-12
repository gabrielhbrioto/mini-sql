#ifndef UTILS_H
#define UTILS_H

void read_command(char** command);
char *strtrim(char *str);
char* strsplit(char **str, const char delimiter, int advance_ptr);
int command_ended(char* command);

#endif