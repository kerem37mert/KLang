//
// Created by Kerem on 16/02/2024.
//

#include "stdlib.h"
#include "string.h"
#include "lexer.h"

struct Token* scanTokens(char *source)
{
    lexer = (struct Lexer *) malloc(sizeof(struct Lexer));
    lexer->position = 0;
    lexer->source = source;

    //First Token
    struct Token *token = NULL;

    do
    {
        struct Token *tempToken = scanToken();

        if (token == NULL)
            token = tempToken;
        else
            getLastToken(token)->next = tempToken;

    }
    while(getLastToken(token)->type != EOF_TOKEN);

    free(lexer);
    return token;
}


struct Token* scanToken()
{
    skipWhiteSpace();

    if(isAtEnd())
        return makeToken(EOF_TOKEN, NULL, NULL);

    //character
    char c = advance();

    switch (c) {
        case '(':
            return makeToken(OPEN_PAREN, "(", NULL);
        case ')':
            return makeToken(CLOSE_PAREN, ")", NULL);
        case '[':
            return makeToken(OPEN_BRACKET, "[", NULL);
        case ']':
            return makeToken(CLOSE_BRACKET, "]", NULL);
        case '+':
            if(match('+'))
                return makeToken(PLUS_PLUS, "++", NULL);
            if(match('='))
                return makeToken(PLUS_EQUAL, "+=", NULL);
            return makeToken(PLUS, "+", NULL);
        case '-':
            if(match('-'))
                return makeToken(MINUS_MINUS, "--", NULL);
            if(match('='))
                return makeToken(MINUS_EQUAL, "-=", NULL);
            if(match('>'))
                return makeToken(ARROW, "->", NULL);
            return makeToken(MINUS, "-", NULL);
        case '*':
            if(match('*'))
                return makeToken(MULTIPLY_MULTIPLY, "**", NULL);
            if(match('='))
                return makeToken(MULTIPLY_EQUAL, "*=", NULL);
            return makeToken(MULTIPLY, "*", NULL);
        case '/':
            if(match('='))
                return makeToken(DIVIDE_EQUAL, "/=", NULL);
            return makeToken(DIVIDE, "/", NULL);
        case '%':
            return makeToken(MODULUS, "%", NULL);
        case '<':
            if(match('='))
                return makeToken(LESS_EQUAL, "<=", NULL);
            return makeToken(LESS, "<", NULL);
        case '>':
            if(match('='))
                return makeToken(GREAT_EQUAL, ">=", NULL);
            return makeToken(GREAT, "<", NULL);
        case '.':
            return makeToken(DOT, ".", NULL);
        case ',':
            return makeToken(COMMA, ",", NULL);
        case ';':
            return makeToken(SEMI_COLON, ";", NULL);
        case ':':
            return makeToken(COLON, ":", NULL);
        case '!':
            if(match('='))
                return makeToken(BANG_EQUAL, "!", NULL);
            return makeToken(BANG, "!", NULL);
        case '=':
            if(match('='))
                return makeToken(EQUAL_EQUAL, "==", NULL);
            return makeToken(EQUAL, "=", NULL);
    }
}


struct Token* makeToken(enum TokenType type, char *value, struct Token *next)
{
    struct Token *token = (struct Token *) malloc(sizeof(struct Token));
    token->type = type;
    token->value = value;
    token->next = next;

    return token;
}


struct Token* getLastToken(struct Token *token)
{
    while(token->next != NULL)
        token = token->next;

    return token;
}


void skipWhiteSpace()
{
    while(1)
    {
        char c = peek();

        switch(c)
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                advance();
                break;

            // COMMENTS LINES
            case '/':
                if (peekNext() == '/')
                {
                    while (peek() != '\n' && !isAtEnd())
                        advance();
                    skipWhiteSpace();
                }
                else if (peekNext() == '*')
                {
                    while (!(peek() == '*' && peekNext() == '/') && !isAtEnd())
                    {
                        advance();
                    }
                    lexer->position += 2;
                    skipWhiteSpace();
                }

            default:
                return;
        }
    }
}


int match(char c)
{
    if (isAtEnd() || lexer->source[lexer->position] != c)
        return 0;

    lexer->position++;
    return 1;
}


int isAtEnd()
{
    return lexer->position == strlen(lexer->source);
}


char advance()
{
    return lexer->source[lexer->position++];
}


char peek()
{
    return lexer->source[lexer->position];
}

char peekNext()
{
    if (isAtEnd())
        return '\0';
    return lexer->source[lexer->position + 1];
}