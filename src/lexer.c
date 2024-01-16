#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


lexer_T* init_lexer(char* contents){
  lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
  lexer->contents = contents;
  lexer->i = 0;
  lexer->c = contents[lexer->i];
  // array of the content of the lexer
  
  return lexer;
}
// iterate through the line of code
void lexer_advance(lexer_T* lexer){
  if(lexer-> c != '\0' && lexer->i < strlen(lexer->contents)){
    lexer->i += 1;
    lexer->c = lexer->contents[lexer->i];
  }
}
// if white space is encountered skip and just continue with detecting lexers
void lexer_skip_whitespace(lexer_T* lexer){
  while(lexer->c == ' ' || lexer->c == 10){
    lexer_advance(lexer);
  }
}


token_T* lexer_get_next_token(lexer_T* lexer){
  while(lexer->c != '\0' && lexer->i < strlen(lexer->contents)){
    if(lexer->c == ' ' || lexer->c == 10){
      lexer_skip_whitespace(lexer);
    }
    if(isalnum(lexer->c)){
      return lexer_collect_id(lexer);
    }
    if(lexer->c == '"'){
      return lexer_collect_string(lexer);
    }
    switch (lexer->c)
    {
      case '=': 
        lexer_advance(lexer);
        if (lexer->c == '*'){
          lexer_advance(lexer);
          return init_token(TOKEN_MULTIPLY_ASSIGN, "*=");
        } else if(lexer->c == '/'){
          lexer_advance(lexer);
          return init_token(TOKEN_DIVIDE_ASSIGN, "/=");
        } else if (lexer->c == '%')
        {
          lexer_advance(lexer);
          return init_token(TOKEN_MODULO_ASSIGN, "%=");
        } else if (lexer->c == '+')
        { 
          lexer_advance(lexer);
          return init_token(TOKEN_ADD_ASSIGN, "+=");
        } else if (lexer->c == '-')
        {
          lexer_advance(lexer);
          return init_token(TOKEN_SUBTRACT_ASSIGN, "-=");
        } else {
          return init_token(TOKEN_EQUALS, "=");
        }

      case '+':
        lexer_advance(lexer);
        if (lexer->c == '+'){
          lexer_advance(lexer);
          return init_token(TOKEN_INCREMENT, "++");
        } else {
          return init_token(TOKEN_PLUS, "+");
        } 
      case '-':
        lexer_advance(lexer);
        if (lexer->c == '-'){
          lexer_advance(lexer);
          return init_token(TOKEN_DECREMENT, "--");
        } else {
          return init_token(TOKEN_SUBTRACT, "-");
        } 
      case '*':
        lexer_advance(lexer);
        return init_token(TOKEN_MULTIPLY, "*");
      case '/':
        lexer_advance(lexer);
        return init_token(TOKEN_DIVIDE, "/");
      case '%':
        lexer_advance(lexer);
        return init_token(TOKEN_MODULO, "%");
      case '!':
        lexer_advance(lexer);
        return init_token(TOKEN_NOT, "!");
        
      case ';': return lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer))); break;
      case '(': return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer))); break;
      case ')': return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer))); break;
      case '{': return lexer_advance_with_token(lexer, init_token(TOKEN_LBRACE, lexer_get_current_char_as_string(lexer))); break;
      case '}': return lexer_advance_with_token(lexer, init_token(TOKEN_RBRACE, lexer_get_current_char_as_string(lexer))); break;
      case ',': return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer))); break;

    }  
  }
}

token_T* lexer_collect_string(lexer_T* lexer){
  lexer_advance(lexer);
  
  char* value = calloc(1, sizeof(char));
  value[0] = '\0';

  while(lexer->c != '"'){
    char* s = lexer_get_current_char_as_string(lexer);
    value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
    strcat(value, s);

    lexer_advance(lexer);
  }
  lexer_advance(lexer);
  return init_token(TOKEN_STRING, value);
}


token_T* lexer_collect_id(lexer_T* lexer){
  char* value = calloc(1, sizeof(char));
  value[0] = '\0';

  while(isalnum(lexer->c) || lexer->c == '_'){
    char* s = lexer_get_current_char_as_string(lexer);
    value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
    strcat(value, s);

    lexer_advance(lexer);
  }
  int token_type;

  if (strcmp(value, "int") == 0){
    token_type = TOKEN_INT_KEYWORD;
  } else if (strcmp(value, "str") == 0){
    token_type = TOKEN_STR_KEYWORD;
  } else if(strcmp(value, "float") == 0){
    token_type = TOKEN_FLOAT_KEYWORD;
  } else if (strcmp(value, "double") == 0 )
  {
    token_type = TOKEN_DOUBLE_KEYWORD;
  } else if (strcmp(value, "decimal") == 0)
  {
    token_type = TOKEN_DECIMAL_KEYWORD;
  } else {
    token_type = TOKEN_ID;
  }
  
  // lexer_advance(lexer);
  
  return init_token(token_type, value);
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token){
  lexer_advance(lexer);
  return token;
}

char* lexer_get_current_char_as_string(lexer_T* lexer){
  char* str = calloc(2, sizeof(char));
  str[0] = lexer->c;
  str[1] = '\0';

  return str;
}




