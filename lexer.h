//
// Created by Kerem on 16/02/2024.
//

#ifndef KLANG_LEXER_H
#define KLANG_LEXER_H

enum TokenType
{
    PLUS,               // +
    MINUS,              // -
    MULTIPLY,           // *
    DIVIDE,             // /
    MODULUS,            // %
    OPEN_PAREN,         // (
    CLOSE_PAREN,        // )
    OPEN_BRACKET,       // [
    CLOSE_BRACKET,      // ]
    LESS,               // <
    GREAT,              // >
    DOT,                // .
    COMMA,              // ,
    SEMI_COLON,         // ;
    COLON,              // :
    BANG,               // !
    EQUAL,              // =

    EQUAL_EQUAL,        // ==
    LESS_EQUAL,         // <=
    GREAT_EQUAL,        // >=
    BANG_EQUAL,         // !=
    ARROW,              // ->
    PLUS_EQUAL,         // +=
    MINUS_EQUAL,        // -=
    MULTIPLY_EQUAL,     // *=
    DIVIDE_EQUAL,       // /=
    PLUS_PLUS,          // ++
    MINUS_MINUS,        // --
    MULTIPLY_MULTIPLY,   // **

    STRING_LITERAL,
    IDENTIFIER,
    NUMBER_LITERAL,
    CHAR_LITERAL,

    IF,
    ELSE,
    ELSEIF,
    END_IF,
    FOR,
    END_FOR,
    CLASS,
    END_CLASS,
    FUNCTION,
    END_FUNCTION,

    ERROR,
    EOF_TOKEN
};

struct Token
{
    enum TokenType type;
    char* value;
    struct Token* next;
};

struct Lexer
{
    char* source;
    int position;
};

// GLOBAL LEXER
struct Lexer *lexer;


// FUNCTIONS
struct Token* scanTokens(char *source);

struct Token* scanToken();

struct Token* makeToken(enum TokenType type, char *value, struct Token *next);

struct Token* getLastToken(struct Token *token);

struct Token* stringLiteral();

void skipWhiteSpace();

int match(char c);

int isAtEnd();

char advance();

char peek();

char peekNext();

#endif //KLANG_LEXER_H
