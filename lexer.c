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
        case '"':
            return stringLiteral();
        default:
            if(isAlpha(c))
                return identifierLiteral(c);
            else if(isDigit(c))
                return numberLiteral(c);

            return makeToken(ERROR, "Unexpected character", NULL);
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

struct Token* stringLiteral()
{
    char *str = (char *)malloc(1);
    str[0] = '\0';

    while(peek() != '"' && !isAtEnd())
    {
        size_t len = strlen(str);
        str = (char *)realloc(str, len + 2);
        str[len] = peek();
        str[len + 1] = '\0';
        advance();
    }

    //ERROR
    if (isAtEnd())
        return makeToken(ERROR,"Unterminated string.",NULL);

    advance();
    return makeToken(STRING_LITERAL, str, NULL);
}


struct Token* identifierLiteral(char c)
{
    char *lexeme = (char *)malloc(2);
    lexeme[0] = c;
    lexeme[1] = '\0';

    while(isAlpha(peek()) || isDigit(peek()))
    {
        size_t len = strlen(lexeme);
        lexeme = (char *)realloc(lexeme, len + 2);
        lexeme[len] = peek();
        lexeme[len + 1] = '\0';
        advance();
    }

    if(strcmp(lexeme, "class") == 0)
        return makeToken(CLASS, "class", NULL);
    if(strcmp(lexeme, "endclass") == 0)
        return makeToken(END_CLASS, "endclass", NULL);
    if(strcmp(lexeme, "if") == 0)
        return makeToken(IF, "if", NULL);
    if(strcmp(lexeme, "else") == 0)
        return makeToken(ELSE, "else", NULL);
    if(strcmp(lexeme, "elseif") == 0)
        return makeToken(ELSEIF, "elseif", NULL);
    if(strcmp(lexeme, "endif") == 0)
        return makeToken(END_IF, "endif", NULL);
    if(strcmp(lexeme, "function") == 0)
        return makeToken(FUNCTION, "function", NULL);
    if(strcmp(lexeme, "endfunction") == 0)
        return makeToken(END_FUNCTION, "endfunction", NULL);
    if(strcmp(lexeme, "for") == 0)
        return makeToken(FOR, "for", NULL);
    if(strcmp(lexeme, "endfor") == 0)
        return makeToken(END_FOR, "endfor", NULL);
    if(strcmp(lexeme, "while") == 0)
        return makeToken(WHILE, "while", NULL);
    if(strcmp(lexeme, "endwhile") == 0)
        return makeToken(END_WHILE, "endwhile", NULL);
    if(strcmp(lexeme, "var") == 0)
        return makeToken(VAR, "var", NULL);
    if(strcmp(lexeme, "true") == 0)
        return makeToken(TRUE, "true", NULL);
    if(strcmp(lexeme, "false") == 0)
        return makeToken(FALSE, "false", NULL);


    return makeToken(IDENTIFIER, lexeme, NULL);
}


struct Token* numberLiteral(char c)
{
    return makeToken(EQUAL, NULL ,NULL);
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
                if(peekNext() == '/')
                {
                    while(peek() != '\n' && !isAtEnd())
                        advance();
                    skipWhiteSpace();
                }
                else if (peekNext() == '*')
                {
                    while(!(peek() == '*' && peekNext() == '/') && !isAtEnd())
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
    if(isAtEnd() || lexer->source[lexer->position] != c)
        return 0;

    lexer->position++;
    return 1;
}


int isAtEnd()
{
    return lexer->position == strlen(lexer->source);
}


int isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

int isDigit(char c)
{
    return c >= '0' && c <= '9';
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