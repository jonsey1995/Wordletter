#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#define MAXSTRING 100
int edit_dist(char *x, char *y);
int stringlen(char *x);
void change(char *x, char *y);
void tests(void);

int main() {
   char string1[MAXSTRING], string2[MAXSTRING];
   int i;
   printf("enter 2, 4 letter words:\n");
   scanf("%s", string1);
   scanf("\n%s", string2);
   printf("\n");

   tests();

   while (edit_dist(string1, string2) != 0) {
      printf("%s\n",string1);
      change(string1, string2);
   }
   return 0;
}

int edit_dist(char *x, char *y){
   int i,count = 0;
   char letter1, letter2;
   if(stringlen(x) == 4 && stringlen(y)  == 4){
      for (i = 0; i < 4; i++) {
         if (isalpha(*x) && isalpha(*y)) {
            letter1 = tolower(*x);
            letter2 = tolower(*y);
            if (letter1 != letter2) {
               count++;
            }
            x++;
            y++;
         }
         else {
            //point x and y back to position x[0][0]
            return -1;
         }
      }
   }
   else{
      return -1;
   }

   return count;
}
int stringlen(char *x){
   int count = 0;
   while (*x != '\0') {
      count++;
      x++;
   }
   return count;
}
void change(char *x, char *y){
   int i;
   char intermediate[MAXSTRING];
   strcpy(intermediate, x);
   for (i = 0; i < 4; i++) {
      if (x[i] != y[i]) {
         intermediate[i] = y[i];
         if(realword(intermediate)){
            x[i] = intermediate[i];
         }
         printf("%s\n", x);
      }
   }
}
void tests(void){
   /*edit_dist testing*/
   assert(edit_dist("chap", "ball") == 4);
   assert(edit_dist("chap", "chat") == 1);
   assert(edit_dist("shoe", "shop") == 1);
   assert(edit_dist("sho^", "shop") == -1);
   assert(edit_dist("shoes", "shoes") == -1);
   assert(edit_dist("shoe", "shoe") == 0);
   /*stringlen testing*/
   assert(stringlen("shoe") == 4);
   assert(stringlen("") == 0);
   assert(stringlen("  ") == 2);
   assert(stringlen("shoes") == 5);
   assert(stringlen("ghfdjsgd") == 8);
   /*change testing*/
}
