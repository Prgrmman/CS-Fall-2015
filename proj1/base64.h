#ifndef base64_h
#define base64_h

#include <string.h>
#define MAX_MSG_LENGTH 1024

const char base64[]=
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char base64Pad='=';

char b64Index(char in) {
	char *fnd=strchr(base64,in);
	if (fnd) return fnd-base64;
	return strlen(base64);
}
#endif