#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MAXCHAR 100
#define NUMWORDS 2267  //number of 4 letter words in file
#define STRLENGTH 5

int edit_dist(char *x, char *y);
void change(char *x, char *y, char fourletterwords[NUMWORDS][STRLENGTH]);
int wordsarray(char strarr[NUMWORDS][STRLENGTH]);
void tests(char fourletterwords[NUMWORDS][STRLENGTH]);

int main() {
  char string1[MAXCHAR], string2[MAXCHAR];
  int i;
  /*DICTIONARY*/
  char fourletterwords[NUMWORDS][STRLENGTH];
  wordsarray(fourletterwords);
  tests(fourletterwords);

  /*USER INPUT*/
  printf("enter 2, 4 letter words:\n");
  scanf("%s", string1);
  scanf("\n%s", string2);
  printf("\n");

  while (edit_dist(string1, string2) != 0) {
    change(string1, string2, fourletterwords);
 }


  return 0;
}

int wordsarray(char strarr[NUMWORDS][STRLENGTH]) {
  FILE *fpointer;
  char str[MAXCHAR];  //stores fgets output
  int i = 0;
  fpointer = fopen("34words.txt", "r");
  if (fpointer == NULL) {
    printf("could not open file\n");
    return(1);
  }
  /*fgets takes pointer to array where read string will be stored, max number of chars to be read,
  and file stream */

  while (fscanf(fpointer, "%s", str) == 1) {
    if (strlen(str) == 4) {
      strcpy(strarr[i], str);
      /*printf(" strarr[i] =%s str = %s\n", strarr[i], str);*/
      i++;
    }

  }
  fclose(fpointer);

}
int edit_dist(char *x, char *y){
   int i,count = 0;
   char letter1, letter2;
   if(strlen(x) == 4 && strlen(y)  == 4){
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
void tests(char fourletterwords[NUMWORDS][STRLENGTH]){
   /*edit_dist testing*/
   assert(edit_dist("chap", "ball") == 4);
   assert(edit_dist("chap", "chat") == 1);
   assert(edit_dist("shoe", "shop") == 1);
   assert(edit_dist("sho^", "shop") == -1);
   assert(edit_dist("shoes", "shoes") == -1);
   assert(edit_dist("shoe", "shoe") == 0);
   /*realword testing*/
   assert(realword(fourletterwords, "work") == 1);
   assert(realword(fourletterwords, "hgxt") == 0);
   assert(realword(fourletterwords, "wold") == 1);
   assert(realword(fourletterwords, "pake") == 0);
   assert(realword(fourletterwords, "pall") == 1);
   assert(realword(fourletterwords, "tuns") == 0);

}
void change(char *x, char *y, char fourletterwords[NUMWORDS][STRLENGTH]){
   int i;
   char intermediate[MAXCHAR];
   strcpy(intermediate, x);  //copy x into intermediate string
   for (i = 0; i < 4; i++) {
      if (x[i] != y[i]) {
         intermediate[i] = y[i];
         if(realword(fourletterwords, intermediate) == 1){
            x[i] = intermediate[i];
            printf("%s\n", x);
         }
         else if (realword(fourletterwords, intermediate) == 0) {
           intermediate[i] = x[i];
         }
      }
   }
}
int realword(char fourletterwords[NUMWORDS][STRLENGTH], char test[]) {
  int i;
  for (i = 0; i < NUMWORDS; i++) {
    if (strcmp(test, fourletterwords[i]) == 0) {
      return 1;
    }
  }
  return 0;
}
