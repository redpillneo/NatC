#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT{
  enum{
    // keywords
    TOKEN_INT_KEYWORD,
    TOKEN_STR_KEYWORD,
    TOKEN_FLOAT_KEYWORD, 
    TOKEN_DOUBLE_KEYWORD,
    TOKEN_DECIMAL_KEYWORD,
    TOKEN_ID,

    TOKEN_EQUALS,
    TOKEN_MULTIPLY_ASSIGN,
    TOKEN_DIVIDE_ASSIGN,
    TOKEN_MODULO_ASSIGN,
    TOKEN_ADD_ASSIGN,
    TOKEN_SUBTRACT_ASSIGN,
    TOKEN_PLUS,
    TOKEN_SUBTRACT,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_MODULO,
    TOKEN_INCREMENT,
    TOKEN_DECREMENT,
    TOKEN_NOT,        

    TOKEN_STRING,
    TOKEN_SEMI,
    TOKEN_LPAREN,
    TOKEN_RPAREN, 
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_COMMA,
    TOKEN_EOF
  } type;
  
  char* value;
} token_T;

token_T* init_token(int type, char* value);



#endif
