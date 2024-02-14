#include "lexer.h"


Lexer* lexer_init(char *text) {
    Lexer *lexer = malloc(sizeof(Lexer));
    lexer->text = text;
    lexer->position = 0;
    lexer->current_char = lexer->text[lexer->position];
    return lexer;
}

void lexer_advance(Lexer *lexer) {
    lexer->position++;
    if (lexer->position > strlen(lexer->text) - 1) {
        lexer->current_char = '\0';
    } else {
        lexer->current_char = lexer->text[lexer->position];
    }
}

void lexer_skip_whitespace(Lexer *lexer) {
    while (lexer->current_char != '\0' && isspace(lexer->current_char)) {
        lexer_advance(lexer);
    }
}


Token* lexer_get_next_token(Lexer *lexer) {
    while (lexer->current_char != '\0') {
        if (isspace(lexer->current_char)) {
            lexer_skip_whitespace(lexer);
            continue;
        }

        if (isdigit(lexer->current_char)) {
            char str_value[20] = "";
            while (lexer->current_char != '\0' && isdigit(lexer->current_char)) {
                strncat(str_value, &(lexer->current_char), 1);
                lexer_advance(lexer);
            }
            Token *token = malloc(sizeof(Token));
            token->type = INTEGER;
            token->value = strdup(str_value);
            return token;
        }

        switch (lexer->current_char) {
            case '+':
                lexer_advance(lexer);
                Token *token_plus = malloc(sizeof(Token));
                token_plus->type = PLUS;
                token_plus->value = strdup("+");
                return token_plus;
            case '-':
                lexer_advance(lexer);
                Token *token_minus = malloc(sizeof(Token));
                token_minus->type = MINUS;
                token_minus->value = strdup("-");
                return token_minus;
            case '*':
                lexer_advance(lexer);
                Token *token_multiply = malloc(sizeof(Token));
                token_multiply->type = MULTIPLY;
                token_multiply->value = strdup("*");
                return token_multiply;
            case '/':
                lexer_advance(lexer);
                Token *token_divide = malloc(sizeof(Token));
                token_divide->type = DIVIDE;
                token_divide->value = strdup("/");
                return token_divide;
            case '(':
                lexer_advance(lexer);
                Token *token_lparen = malloc(sizeof(Token));
                token_lparen->type = OPEN_PAREN;
                token_lparen->value = strdup("(");
                return token_lparen;
            case ')':
                lexer_advance(lexer);
                Token *token_rparen = malloc(sizeof(Token));
                token_rparen->type = CLOSE_PAREN;
                token_rparen->value = strdup(")");
                return token_rparen;
            case '<':
                lexer_advance(lexer);
                Token *token_less_than = malloc(sizeof(Token));
                token_less_than->type = LESS;
                token_less_than->value = strdup("<");
                return token_less_than;
            case '>':
                lexer_advance(lexer);
                Token *token_greater_than = malloc(sizeof(Token));
                token_greater_than->type = GREAT;
                token_greater_than->value = strdup(">");
                return token_greater_than;
            case ';':
                lexer_advance(lexer);
                Token *token_semicolon = malloc(sizeof(Token));
                token_semicolon->type = SEMI_COLON;
                token_semicolon->value = strdup(";");
                return token_semicolon;
            case ':':
                lexer_advance(lexer);
                Token *token_colon = malloc(sizeof(Token));
                token_colon->type = COLON;
                token_colon->value = strdup(";");
                return token_colon;
             default:
                if (isalpha(lexer->current_char)) {
                    char str_value[20] = "";
                    while (lexer->current_char != '\0' && (isalnum(lexer->current_char) || lexer->current_char == '_')) {
                        strncat(str_value, &(lexer->current_char), 1);
                        lexer_advance(lexer);
                    }

                    Token *token = malloc(sizeof(Token));
                    if (strcmp(str_value, "if") == 0) {
                        token->type = IF;
                    } else if (strcmp(str_value, "elseif") == 0) {
                        token->type = ELSEIF;
                    } else if (strcmp(str_value, "else") == 0) {
                        token->type = ELSE;
                    } else if (strcmp(str_value, "function") == 0) {
                        token->type = FUNCTION;
                    } else if (strcmp(str_value, "class") == 0) {
                        token->type = CLASS;
                    } else if (strcmp(str_value, "endclass") == 0) {
                        token->type = END_CLASS;
                    } else if (strcmp(str_value, "for") == 0) {
                        token->type = FOR;
                    } else if (strcmp(str_value, "endfor") == 0) {
                        token->type = END_FOR;
                    } else {
                        token->type = IDENTIFIER;
                    }
                    token->value = strdup(str_value);
                    return token;
                } else {
                    printf("hata");
                }
        }
    }

    Token *token = malloc(sizeof(Token));
    token->type = EOF_TOKEN;
    token->value = NULL;
    return token;
}

void free_token(Token *token) {
    free(token->value);
    free(token);
}