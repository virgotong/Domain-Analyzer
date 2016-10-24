#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

#define WORDS "/usr/share/dict/web2"
#define LUCKY_NUM 3

int D(char *str1){
 uint16_t c1 = 0, c2 = 0, i=0, c3 = 0;
 int size = 0, l = 0;
 FILE *fp;

 if((fp = fopen(WORDS, "r")) == NULL){
    perror("open file failed");
    return -1;
 }

 char buf[2493109];

 buf[(sizeof(buf) -1)] = 0;

 while(fgets(buf, 2493108 , fp)){
  // removing \n
  buf[strlen(buf) -1] = 0;
  l = levenshtein(str1, buf);
  if(l <= 3){
    printf("non bogon\n");
    fclose(fp);
    return 0;
  }
 }

 printf("domain might be generated by DGA\n");


 fclose(fp);

 return 0;
}

int main(int argc, char *argv[]){
  int16_t match;

  if(argc != 2){
    printf("%s str1\n", argv[0]);
    exit(0);
  }

  match = D(argv[1]);
  return 0;
}
