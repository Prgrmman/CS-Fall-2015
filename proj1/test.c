
#include <stdio.h>
#include "base64.h"

char * b64encode(char string[],int len);
static char b64Result[MAX_MSG_LENGTH];

char getFirstXBits(char byte, int x);
char getLastXBits(char byte , int x);

int main (char argc, char ** argv)
{
 
        char * string = "ABC";	
	char * result = b64encode("ABCB", 4);
	int  i;
	for (i = 0; i < 6; i++)
	  printf("%d\n", result[i]);


	char test = getLastXBits(0xD2,4);
	if (test == 0x02)
	  printf("Yay\n");
	return 0;
}

char * b64encode(char string[],int len) {

	/* Your code to convert the input array of chars to a base64 string goes here */
  
  /* this buffer will only hold 6 bits of a time, taking the form 00xxxxxxb where  x can be any bit*/
  char buffer = 0;
  char bitsLeft = 8; //this represents how many bits we can take from the current byte ( string[i])
  char bufferSize = 0; //represents the number of bits in the buffer

  //this loop will terminate when we have a full buffer and we have used all of our bytes
  int i = 0; //the byte index
  int j = 0; //the index for b64Result
  while (bufferSize != 6 || i < len)
    {
      printf("\niteration summary:\n");
      printf("bitsleft = %d\n",bitsLeft);
     
      //if we have don't have enough bits from the current byte to make a new b64 digit...
      // and we still have more bytes left to use...
      if (bitsLeft <= 6 && i < len){
	    buffer = getLastXBits(string[i], bitsLeft) << (6-bitsLeft); // shove the remaining bits to the right
	    printf("using the last %d bits(s) from byte %d\n", (bitsLeft), i);
	    bufferSize = bitsLeft;      // update the buffer size
	    i++;                       // we are now going to look at the next byte
	    if (i == len) bitsLeft = 0;
	    else bitsLeft = 8;
	    printf("%d bits left in byte %d\n",bitsLeft,i);
	          
       }
      else {
	     buffer += getFirstXBits(string[i], 6 - bufferSize); // grab as many bits as you need to fill the buffer
	     bitsLeft -= (6-bufferSize); //account for the amount of bits
	     printf("used %d bits in byte %d\n",(6-bufferSize), i);
	     printf("#bits left from byte %d is %d\n",i,bitsLeft);
	     printf("Number created is %d at j = %d\n", buffer,j);
	     b64Result[j++] = buffer;
	     buffer = 0; 
	     bufferSize = 0;//once we create a new b64 digit, we clear the buffer
       }
      
      //we need to handle the case we are out bytes to use, and we have a buffer that still isn't full. So pad with 0s
      if (bitsLeft < 6 && i == len){
	printf("Special code was activated i = %d\n", i);
	b64Result[j++] = buffer;
	bufferSize = 6;
      }
	   
      
	
      
    }
 
	
	


	b64Result[j+1]=0; // Make sure result is null terminated
	printf("j ended up being %d\n",j);
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




