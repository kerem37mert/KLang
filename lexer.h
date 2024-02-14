

enum {
    INTEGER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    LESS,
    GREAT,
    DOT,
    COMMA,
    SEMI_COLON,
    COLON,

    IDENTIFIER,

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

    EOF_TOKEN
};

typedef struct {
    int type;
    char *value;
} Token;

typedef struct {
    char *text;
    int position;
    char current_char;
} Lexer;

Lexer* lexer_init(char *text);

Lexer* lexer_init(char *text);

void lexer_skip_whitespace(Lexer *lexer);

Token* lexer_get_next_token(Lexer *lexer);