#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/errorMessages.h"
#include "../headers/automaton.h"

#define KEYWORDS_NUM 65

/// @brief reserved words of the SQL language
const char *keywords[KEYWORDS_NUM] = {
    "SELECT",
    "FROM",
    "WHERE",
    "GROUP",
    "BY",
    "HAVING",
    "ORDER",
    "ASC",
    "DESC",
    "LIMIT",
    "OFFSET",
    "INSERT",
    "INTO",
    "VALUES",
    "UPDATE",
    "SET",
    "DELETE",
    "CREATE",
    "TABLE",
    "INDEX",
    "DATABASE",
    "USER",
    "IDENTIFIED",
    "DROP",
    "ALTER",
    "ADD",
    "COLUMN",
    "MODIFY",
    "RENAME",
    "TO",
    "CONSTRAINT",
    "UNIQUE",
    "PRIMARY",
    "KEY",
    "FOREIGN",
    "REFERENCES",
    "CHECK",
    "DEFAULT",
    "ON",
    "DELETE",
    "UPDATE",
    "CASCADE",
    "SET",
    "NULL",
    "NO",
    "ACTION",
    "CURRENT_DATE",
    "CURRENT_TIMESTAMP",
    "CURRENT_DATETIME",
    "CURRENT_TIME",
    "CURRENT_YEAR",
    "SHOW",
    "DATABASES",
    "TABLES",
    "USE",
    "DESCRIBE",
    "AS",
    "MAX",
    "MIN",
    "AVG",
    "COUNT",
    "SUM",
    "ABS",
    "NOW",
    "CURDATE",
    "BETWEEN",
    "IN",
    "LIKE",
    "AND",
    "OR",
    "NOT"
};

/// @brief iterates through the array checking if the token belongs to the list of reserved words
/// @param token_class - string used to save the token_class of the token
/// @param token - string that contains the token
/// @return returns true if the token is a reserved word or false otherwise
char is_keyword(char *token_class, const char *token) {

    for (int i = 0; i < KEYWORDS_NUM; i++) {

        if (!strcmp(token, keywords[i])) {

            // change this to perform a "to_upper()" on the word and check if it is in the list of reserved words
            strcpy(token_class, "<");
            strcat(token_class, keywords[(i%2 ? i-1 : i)]);
            strcat(token_class, ">");
            return true;

        }
    }
    
    return false;

}

/// @brief checks if the character c belongs to a token_class of characters to be ignored
/// @param c character read from the source code
/// @return returns true if the character c is one of the characters to be ignored and false otherwise
char ignore_char(char c, int *command) {

    if(c == '\n') {

        (*command)++;
        //printf("%d\n", *command);
        return true;

    }

    if(c == ' ' || c == '\r' || c == '\t' || c == ' ')
        return true;

    return false;

}

/// @brief function that implements the transitions of the automaton, if no transition is found, the code is interrupted
/// @param s - current state of the automaton
/// @param c - last character read from the source code
/// @param source_file - pointer to the source code file
/// @return returns the next state based on the current state and the last character read from the source code
char transition(const char s, const char c) {

    if(s == 0) {

        if(c == ';')
            return 21;

        if(isdigit(c))
            return 16;

        if(c == ')')
            return 15;
        
        if(c == '(')
            return 14;
        
        if(c == '*')
            return 13;

        if(c == '<')
            return 9;
        
        if(c == '>')
            return 6;
        
        if(c == ',')
            return 5;

        if(isalpha(c) || c == '_')
            return 3;

        if(c == '-')
            return 1;

        if(c == '\'')
            return 22;

        // consumes whitespace, tabs, and line breaks
        if(c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == ' ') 
            return 0;   
        
        return 20;

    }

    if(s == 1) {

        if(c == '-')
            return 2;

    }

    if(s == 2) {

        if(c == '-')
            return 18;

        return 2;

    }

    if(s == 18) {

        // if it identifies the end of the comment, it advances to state 2
        if(c == '-')
            return 19;

    }

    if(s == 3) {

        // while letters, digits, or '_' are identified, it keeps the automaton in state 3
        if(isalnum(c) || c == '_')
            return 3;

        //fseek(source_file, -1, SEEK_CUR);
        return 4;
        
    }

    if(s == 16) {

        if(isdigit(c))
            return 16;

        //fseek(source_file, -1, SEEK_CUR);
        return 17;
    }

    if(s == 9) {
        
        if(c == '=')
            return 11;
        
        if(c == '>')
            return 12;
        
        //fseek(source_file, -1, SEEK_CUR);
        return 10;

    }

    if(s == 6) {

        if(c == '=')
            return 8;

        //fseek(source_file, -1, SEEK_CUR);
        return 7;

    }   

    if(s == 22) {

        if( isalnum(c) || c == '_' || c == ' ')
            return 23;

        if(c == '\'')
            return 24;

        //fseek(source_file, -1, SEEK_CUR);
        NOT_ALLOWED_CHAR

    }   

    if(s == 23) {

        if(c == '\'')
            return 24;

        //fseek(source_file, -1, SEEK_CUR);
        return 23;

    }   

    TRANSITION_ERRROR
    exit(-1);// terminates the program

}

/// @brief checks if the state s is part of the set of final states
/// @param s - current state of the automaton
/// @return returns true if s is a final state and false otherwise
char is_final_state(char s) {

    if(s == 24 ||
       s == 21 ||
       s == 20 ||
       s == 19 ||
       s == 17 ||
       s == 15 ||
       s == 14 ||
       s == 13 ||
       s == 12 ||
       s == 11 ||
       s == 10 ||
       s == 8 ||
       s == 7 ||
       s == 5 ||
       s == 4)
        return true;

    return false;

}
/// @brief function that defines the token_class of the token
/// @param token_class - string used to store the token_class of the token
/// @param s - current state of the automaton
/// @param token - string containing the token
/// @param source_file - pointer to the source code file
void define_token_class(char *token_class, const char s, char *token) {

    switch (s) {

        case 4:
            if(!is_keyword(token_class, token))
                strcpy(token_class, "<identifier>");
            break;

        case 5:
            strcpy(token_class, "<comma>");
            break;

        case 7:
            strcpy(token_class, "<greater_symb>");
            break;

        case 8:
            strcpy(token_class, "<greater_eq_symb>");
            break;

        case 10:
            strcpy(token_class, "<minor_symb>");
            break;

        case 11:
            strcpy(token_class, "<minor_eq_symb>");
            break;

        case 12:
            strcpy(token_class, "<diff_symb>");
            break;

        case 13:
            strcpy(token_class, "<asterisk>");
            break;

        case 14:
            strcpy(token_class, "<left_parenthesis>");
            break;

        case 15:
            strcpy(token_class, "<rigth_parenthesis>");
            break;

        case 17:
            strcpy(token_class, "<number>");
            break;

        case 19:
            strcpy(token_class, "<comment>");
            break;

        case 21:
            strcpy(token_class, "<semicolon>");
            break;

        case 20:
            strcpy(token_class, "<LEXICAL_ERROR_1>");
            break;
        
        case 24:
            strcpy(token_class, "<value>");
            break;
 
        default:
            strcpy(token_class, "<LEXICAL_ERROR_2>");//LEXICAL_ERROR_2 indicates characters that do not belong to the language alphabet (SyntaxError: Unexpected token ILLEGAL)
            break;

    }
}

/// @brief function that implements the automaton
/// @param token - string where the token read from the source code will be saved
/// @param token_class - string where the token_class of the processed token will be saved
/// @param source_file - pointer to the source code file
/// @return returns true if it reached the end of the file and false otherwise
void automaton(char **token, char *token_class, char *command) {

    char c = 0, s = 0;
    strcpy(*token, "");
    strcpy(token_class, "");

    // processes the string until it finds the end of the file or reaches a final state
    while (!is_final_state(s)) {

        c = *token;
        s = transition(s,c);

        // if c is part of the language alphabet, adds the character c to the token string
        if((s != 4 && s != 17 && !ignore_char(c, command)) || (s == 2 && c == ' ')){

            *token = realloc(*token, (strlen(*token)+2)*sizeof(char));
                if(*token == NULL) {// prints an error message if allocation fails
                MEMORY_ALOCATION_ERRROR
                exit(-1);// terminates the program 
            }
            strncat(*token, &c, 1);

        }
        
    }

    define_token_class(token_class, s, *token);

}
