#ifndef ERRRORMESSAGES_H
#define ERRRORMESSAGES_H

//define error messages
#define MEMORY_ALOCATION_ERRROR perror("Failed to alocate memory\n");
#define TRANSITION_ERRROR perror("mini-sql: error: transicao inexistente");

#define ERRO_LEXICO_1  perror("alex: Erro lexico na linha %d: comentário não fechado: '%s' \n", *linha-1, *token);
#define ERRO_LEXICO_2  perror("alex: Erro lexico na linha %d: caractere inválido ':', você quis dizer ':='?\n", *linha);
#define ERRO_LEXICO_3  perror("alex: Erro lexico na linha %d: caractere invalido '%s'\n", *linha, *token);
#define ERRO_SINTATICO_1(linha)  perror("alex: Erro sintatico na linha %d: código inesperado após o fim do programa\n", linha);
#define ERRO_SINTATICO_2 perror("alex: Erro sintatico na linha %d: símbolo '=' faltando\n", *linha);
#define ERRO_SINTATICO_3 perror("alex: Erro sintatico na linha %d: valor da constante faltando\n", *linha);
#define ERRO_SINTATICO_4 perror("alex: Erro sintatico na linha %d: símbolo ';' faltando\n", *linha);
#define ERRO_SINTATICO_5 perror("alex: Erro sintatico na linha %d: símbolo ':=' faltando\n", *linha);
#define ERRO_SINTATICO_6 perror("alex: Erro sintatico na linha %d: identificador faltando\n", *linha);
#define ERRO_SINTATICO_7 perror("alex: Erro sintatico na linha %d: cláusula 'END' faltando\n", *linha);
#define ERRO_SINTATICO_8 perror("alex: Erro sintatico na linha %d: cláusula 'THEN' faltando\n", *linha);
#define ERRO_SINTATICO_9 perror("alex: Erro sintatico na linha %d: cláusula 'DO' faltando\n", *linha);
#define ERRO_SINTATICO_10 perror("alex: Erro sintatico na linha %d: cláusula 'ODD' faltando\n", *linha);
#define ERRO_SINTATICO_11 perror("alex: Erro sintatico na linha %d: expressão faltando\n", *linha);
#define ERRO_SINTATICO_12 perror("alex: Erro sintatico na linha %d: símbolo ')' faltando\n", *linha);
#define ERRO_SINTATICO_13 perror("alex: Erro sintatico na linha %d: operador relacional faltando\n", *linha);
#define ERRO_SINTATICO_14 perror("alex: Erro sintatico na linha %d: condição faltando\n", *linha);
#define ERRO_SINTATICO_15 perror("alex: Erro sintatico na linha %d: 'ODD' inesperado\n", *linha);

#endif