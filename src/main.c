#include <stdio.h>
#include "include/lexer.h"

int main(int agrc, char* argv[]){
  lexer_T* lexer = init_lexer(
    "int num1, num2;"
    "int sum_of_nums;"
    "str prompt, result;"
    "prompt = \"Value of num1 and num2: \";"
    "result = \"Sum of the two numbers: \";"
    "num1 = 3;"
    "num2 = 5;"
    "sum_of_nums = num1 + num2;"
    "print(prompt, num1, num2);"
    "print(result, sum_of_nums);"
  );

  token_T* token = (void*)0;
  
  while((token = lexer_get_next_token(lexer)) != (void*)0){ 
    printf("TOKEN(%d, %s)\n", token->type, token->value);
  }
  return 0;
}