#include "base64.h"
#include <stdio.h>
#include <assert.h>

char * b64decipher(char b64[],int len, char key[], int klen);
static char stringResult[MAX_MSG_LENGTH];



int main(int argc, char **argv) {
 
 
  //char * test = b64decipher("VGhpcyBpcyBhIHRlc3Qgb2YgbXkgZGVjb2Rlci4=",40);
  //  printf("%s\n",test);

        char inputMsg[MAX_MSG_LENGTH] = "";
	int b64i=0;
	char in;
	while(1) {
		in=getchar();
		if (feof(stdin)) break;
		inputMsg[b64i++]=in;
	}
	assert(b64i<MAX_MSG_LENGTH);

	char * result=b64decipher(inputMsg,b64i, "ABC",3);
	int stri=0;
	for(stri=0; result[stri]; stri++) {
		putchar(result[stri]);
	}
	return 0;
}

char * b64decipher(char b64[],int len, char key[], int klen) {

  /* Your code to convert base 64 to an array of chars goes here */
  
  int i = 0; // index for b64 numbers 
  int j = 0; // index for array of chars
  int k = 0; // index for the key
  
  long int mask = 0xFF;
  long int buffer = 0; // we load b64 numbers in here and play with them
  // this long int gives us 32 bits to work with...I think.


  // we will only consider at most 24 bits at a time
    
  // we want to consider 4 b64 numbers together as much as possible

  //  printf("the length of the string is %d\n", len);
  while ( i < (len -3))
    {
      // printf("considering i %d through %d\n", i, i+3);
      // load the buffer
      int shift;
      for (shift = 6; 24 - shift >= 0; shift += 6){
	if (b64[i] == '='){
	  i+=4;
	  //	  printf("i is poop %c\n", b64[i]);
	  continue;
	}
      
	buffer += (b64Index(b64[i] ^ key[k++])) << (24 - shift);
	i++;
	// 	printf("i is %d\n", i);
      }
      //unload the buffer
      //now we need to mask stuff.
      for (shift = 0; shift <= 16; shift += 8){
	stringResult[j++] = (buffer & (mask << (16-shift))) >> (16-shift);
      }
      buffer = 0;
      if (k == klen) klen = 0;
    }
  // we now have to options: there are 3 
     
      
      

  
  
  stringResult[j+1]=0; // Make sure result is null terminated
  return stringResult;
	
}






// some helper functions....

// gets the first x number of bits from the left of a byte and shifts them to the right end
