#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/errorMessages.h"
#include "../headers/automaton.h"

#define KEYWORDS_NUM 27

/// @brief vetor de palavras reservadas
const char *keywords[KEYWORDS_NUM] = {
    "SELECT",
    "FROM",
    "WHERE",
    "CREATE",
    "TABLE",
    "NOT",
    "NULL",
    "PRIMARY",
    "KEY",
    "INT",
    "VARCHAR",
    "DECIMAL",
    "DATE",
    "BOOLEAN",
    "DROP",
    "INSERT",
    "INTO",
    "VALUES",
    "DELETE",
    "SHOW",
    "DATABASES",
    "USE",
    "TABLES",
    "DESCRIBE",
    "AND",
    "OR",
    "NOT"
};

/// @brief percorre o vetor checando se o token pertence à lista de palavras reservadas
/// @param token_class - string usada para salvar a token_class do token
/// @param token - string que contém o token
/// @return retorna verdadeiro se o teken é uma palavra reservada ou falso caso contrário
char is_keyword(char *token_class, const char *token) {

    for (int i = 0; i < KEYWORDS_NUM; i++) {

        if (!strcmp(token, keywords[i])) {

            //mudar isso para dar um "to_upper()" na palavra e verificar se está na lista de palavras reservadas
            strcpy(token_class, "<");
            strcat(token_class, keywords[(i%2 ? i-1 : i)]);
            strcat(token_class, ">");
            return true;

        }
    }
    
    return false;

}

/// @brief verifica se o caractere c pertence a uma token_class de caracteres a serem desprezados
/// @param c - caractere lido do código fonte
/// @return retoena verdadeiro se o caractere c for um dos caracteres a serem desprezados e falso caso contrário
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


/// @brief função que implementa as transições do autômato, se nenhuma transição é encontrada, o código é interrompido
/// @param s - estado corrente do autômato
/// @param c - último caractere lido do código fonte
/// @param source_file - ponteiro para o arquivo de código fonte
/// @return retorna o próximo estado baseado no estado corrente e no último caractere lido do código fonte
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

        //consome espaços em branco, tabulações e quebras de linha 
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

        //se identificar o fim do comentário avança para o estado 2, 
        if(c == '-')
            return 19;

    }

    if(s == 3) {

        //enquanto forem identificados letras ou dígitos ou '_' ele mantém o autômato no estado 3
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

    TRANSITION_ERRROR
    exit(-1);//encerra o programa

}

/// @brief verifica se o estado s faz parte do conjunto de estados finais
/// @param s - estado corrente do autômato
/// @return retorna verdadeiro se s é estado final e falso caso contrário
char is_final_state(char s) {

    if(s == 21 ||
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

/// @brief função que define a token_class do token
/// @param token_class - string usada para armazenar a token_class do token
/// @param s - estado corrente do autômato
/// @param token - string contendo o token 
/// @param source_file - ponteiro para o arquivo de código fonte
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

        //case 22 
        default:
            strcpy(token_class, "<LEXICAL_ERROR_2>");//ERRO_LEXICO_3 indica caracateres que não pertencem ao alfabeto da linguagem (SyntaxError: Unexpected token ILLEGAL)
            break;

    }
}

/// @brief função que implementa o autômato
/// @param token - string onde será salvo o token lido do código fonte
/// @param token_class - string onde será salvo a token_class do token processado
/// @param source_file - ponteiro para o arquivo de código fonte
/// @return retorna verdadeiro se chegou ao fim do arquivo e falso caso contrário
void automaton(char **token, char *token_class, char *command) {

    char c = 0, s = 0;
    strcpy(*token, "");
    strcpy(token_class, "");

    //processa a cadeia até encontrar o fim do arquivo ou até atingir um estado final
    while (!is_final_state(s)) {

        c = *token;
        s = transition(s,c);

        // se c, faz parte do alfabeto da linguagem, adiciona o caractere c à cadeia do token
        if((s != 4 && s != 17 && !ignore_char(c, command)) || (s == 2 && c == ' ')){

            *token = realloc(*token, (strlen(*token)+2)*sizeof(char));
                if(*token == NULL) {//imprime uma mensagem de erro caso a alocação falhe
                MEMORY_ALOCATION_ERRROR
                exit(-1);//encerra o programa 
            }
            strncat(*token, &c, 1);

        }
        
    }

    define_token_class(token_class, s, *token);

}