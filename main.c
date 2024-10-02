#include <stdio.h>

#define MAX_BUFFER_SIZE 1000
#define MAX_TOKEN_LENGTH MAX_BUFFER_SIZE

enum STATE{
	STATE_START,
	STATE_IDENTIFIER,
	STATE_NUMBER,
	STATE_STRING
};

enum TokenType{
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

short int isAlpha(char ch);
short int isDigit(char ch);

int main(){
  char ch;
	int state=STATE_START;
	char buffer[MAX_BUFFER_SIZE];
	int buffer_index=0;
	
  while ((ch=getchar())!=EOF){
    switch(state){
      case STATE_START:
        if(isAlpha(ch)){
					state=STATE_IDENTIFIER;
					buffer[buffer_index++]=ch;
	   		}else if (isDigit(ch)){
					state=STATE_NUMBER;
					buffer[buffer_index++]=ch;
				}
				break;
			case STATE_IDENTIFIER:
			  break;
			case STATE_NUMBER:
			  break;
			case STATE_STRING:
			  break;
    }
  }
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

