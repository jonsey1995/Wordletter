#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

int main() {
   char c;
   FILE *myfile;
   myfile = fopen("words.txt", "r");
   if (!myfile) {
      puts("file not found");
      return 1;
   }
   while ( (c = getc(myfile))!=EOF ) { // this will keep going it reaches null character
      putchar(c);
   }
   fclose(myfile);
   return 0;
}
