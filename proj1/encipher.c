#include "base64.h"
#include <stdio.h>
#include <assert.h>

char * b64encipher(char string[],int len, char key[], int klen);
static char b64Result[MAX_MSG_LENGTH];

char getFirstXBits(char byte, int x);
char getLastXBits(char byte , int x);

int main(int argc, char **argv) {
	char inputMsg[MAX_MSG_LENGTH] = "";
	//	printf("%s\n",b64encipher("A",1));
	int stri=0;
	char in;
	while(1) {
		in=getchar();
		if (feof(stdin)) break;
		inputMsg[stri++]=in;
	}
	inputMsg[stri]=0;
	assert(stri<MAX_MSG_LENGTH);

	char * result=b64encipher(inputMsg,stri, "ABC",3);
	int b64i=0;
	for(b64i=0; result[b64i]; b64i++) {
		putchar(result[b64i]);
	}
	return 0;
}

char * b64encipher(char string[],int len, char key[],int klen ) {

	/* Your code to convert the input array of chars to a base64 string goes here */
  
 
  char buffer = 0;
  char bitsLeft = 8;
  char bufferSize = 0;

  //this loop will terminate when we have a full buffer and we have used all of our bytes
  int i = 0; //the byte index
  int j = 0; //the index for b64Result
  int k = 0; //the index of the key

 

  while (bufferSize != 6 || i < len)
    {
      if (bitsLeft <= 6 && i < len){
	    buffer = getLastXBits(string[i], bitsLeft) << (6-bitsLeft);
	    bufferSize = bitsLeft;      // update the buffer size
	    i++;                       // we are now going to look at the next byte
	    if (i == len) bitsLeft = 0;
	    else bitsLeft = 8;
      }
      else {
	buffer += getFirstXBits(string[i], 6 - bufferSize); // grab as many bits as you need to fill the buffer
	     bitsLeft -= (6-bufferSize); //account for the amount of bits
	     b64Result[j++] = base64[buffer ^ key[k++]];
	     buffer = 0; 
	     bufferSize = 0;//once we create a new b64 digit, we clear the buffer
	     if (k == klen) k = 0;
      }
            
      if (bitsLeft < 6 && i == len){
	b64Result[j++] = base64[buffer ^ key[k++]];
	if (k == klen) k = 0;
	bufferSize = 6;
      }
    }
  //this will pad the end if needed
  int pI; //padding index...
  for (pI = 0; pI < 3 - len % 3; pI++){
    b64Result[j++] = base64Pad;
  }
  
  
  b64Result[j+1]=0; // Make sure result is null terminated
  
  return b64Result; 
}

// some helper functions....

// gets the first x number of bits from the left of a byte and shifts them to the right end
char getFirstXBits(char byte, int x){
   return (unsigned char)byte >> (8-x);
  
}

//gets the last x number of bits from a byte
char getLastXBits(char byte , int x){
 
  return  (byte  & ~(0xFF << x));
}

