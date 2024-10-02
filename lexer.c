#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1000
#define MAX_TOKEN_LENGTH MAX_BUFFER_SIZE

//todo I don't want to spend time to create a HashSet for this, so, array's performance is enough
char *keywords[]={"int","void","public"};
char *operators[]={"+","-","*","/","%%","="};
char *punctuations[]={"(",")","[","]","{","}",";"};

enum STATE{
	STATE_START,
	STATE_IDENTIFIER,
	STATE_NUMBER,
	STATE_STRING
};

enum TokenType{
  EMPTY,
  KEYWORD, 
  IDENTIFIER, 
  NUMBER, 
  STRING, 
  OPERATOR, 
  PUNCTUATION, 
  EOF_TOKEN
};

struct Token {
    enum TokenType type;
    char value[MAX_TOKEN_LENGTH];
};

struct Token tokens[MAX_TOKEN_LENGTH];

short int isAlpha(char ch);
short int isDigit(char ch);
short int canFind(char** array, char* toFind);
short int isIdentifierChar(char ch);
short int isPunctuation(char ch);
short int isOperators(char ch);
int prettyPrint(struct Token tokens[],int size);

int main(int argc, char *argv[]){
  printf("Lexer start...\n");
  if(argc<2){
    printf("ERROR: no arg\n");
    exit(1);
  }
  if(argc>2){
    printf("ERROR: too much args\n");
    exit(1);
  }
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("ERROR: Error opening file\n");
    exit(1);
  }
  printf("Lexer start parse file...\n");

  char ch;
	int state=STATE_START;
	char buffer[MAX_BUFFER_SIZE];
	int buffer_index=0;
  int token_index=0;
	
  while ((ch=fgetc(file))!=EOF){
    switch(state){
      case STATE_START:
        if(isAlpha(ch)){
					state=STATE_IDENTIFIER;
					buffer[buffer_index++]=ch;
	   		}else if (isDigit(ch)){
					state=STATE_NUMBER;
					buffer[buffer_index++]=ch;
				}else if (isPunctuation(ch)){
          struct Token token;
          token.type=PUNCTUATION;
          token.value[0]=ch;
          token.value[1]='\0';
          tokens[token_index++]=token;
        }else if(' '==ch){
          continue;
        }else if(isOperators(ch)){
          struct Token token;
          token.type=OPERATOR;
          token.value[0]=ch;
          token.value[1]='\0';
          tokens[token_index++]=token;
        }
				break;
			case STATE_IDENTIFIER:
        //todo no operator check, must space before operator
        if(' '==ch){
          struct Token token;
          if(canFind(keywords,buffer)){
            token.type=KEYWORD;
          }else{
            token.type=IDENTIFIER;
          }
          strcpy(token.value,buffer);
          buffer_index=0;
          memset(buffer, 0, sizeof(buffer));
          state=STATE_START;
          tokens[token_index++]=token;
        }else if(isIdentifierChar(ch)){
          buffer[buffer_index++]=ch;
        }else{
          printf("ERROR: parse identifier");
          exit(1);
        }
			  break;
			case STATE_NUMBER:
        if(' '==ch){
          struct Token token;
          token.type=NUMBER;
          strcpy(token.value,buffer);
          buffer_index=0;
          memset(buffer,0,sizeof(buffer));
          state=STATE_START;
          tokens[token_index++]=token;
        }else if(isDigit(ch)){
          buffer[buffer_index++]=ch;
        }else{
          printf("ERROR: parse identifier");
          exit(1);
        }
			  break;
			case STATE_STRING:
        //todo
			  break;
      default:
        break;
    }
  }
  printf("file is compiled\n");
  prettyPrint(tokens,MAX_TOKEN_LENGTH);
  return 0;
}

short int isAlpha(char ch){
	if('a'<=ch && ch <='z'){
		return 1;
	}else if('A'<=ch && ch<='Z'){
		return 1;
  }else{
		return 0;
	}
}

short int isDigit(char ch){
  if('0'<=ch && ch <='9'){
    return 1;
  }
  return 0;
}

short int canFind(char** array, char* toFind) {
  if (array == NULL) {
    return 0;
  }
  for (int i = 0; i <= sizeof(array)/sizeof(toFind); i++) {
    if(!strcmp(array[i],toFind)){
      return 1;
    }
  }
  return 0;
}

short int isIdentifierChar(char ch){
  if(isDigit(ch)||isAlpha(ch)||'_'==ch){
    return 1;
  }else {
    return 0;
  }
}

short int isPunctuation(char ch){
  for(int i=0;i<sizeof(punctuations)/sizeof(punctuations[0]);i++){
    if(punctuations[i][0]==ch){
      return 1;
    }
  }
  return 0;
}

short int isOperators(char ch){
  for(int i=0;i<sizeof(operators)/sizeof(operators[0]);i++){
    if(operators[i][0]==ch){
      return 1;
    }
  }
  return 0;
}

int prettyPrint(struct Token tokens[],int size){
  for(int i=0;i<size;i++){
    if(tokens[i].type==EMPTY){
      return 1;
    }
    printf("token index:%d, type: %d, value: %s\n", i, tokens[i].type, tokens[i].value);
  }
  return 1;
}
