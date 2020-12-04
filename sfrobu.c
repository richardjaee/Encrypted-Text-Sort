#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
int f = 0;

int frobcmp (char const  *a, char const *b){
  while (*a != ' ' && *b != ' '){ //runs loop until either a or b is a space
      char c1 = (*a^42);
      char c2 = (*b^42);
      if (f==1){
          c1 = toupper((unsigned char)c1);
          c2 = toupper((unsigned char)c2);
      }

      if (c1 < c2){ //a < b
      return -1;
    }
    if (c1 > c2){ //a > b
      return 1;
    }

    a++; //iterate a and b
    b++;
  }//end while loop

  //cases where a and/or b are spaces
  if (*a == ' ' && *b != ' '){ //a is a space, b is not
    return -1;
  }

  if (*a != ' ' && *b == ' '){ //a is not a space, b is space; ie a is longer than b
    return 1;
  }

  if (*a == ' ' && *b == ' '){ //space bytes are not compared to each other
    return 0;
  }
  return 0;
}

int compare(const void * a, const void * b){
  return frobcmp(*(char const **)a, *(char const **)b);
}

int main(int argc, char** argv){

  if (argc == 2){
    if (!(strcmp(argv[1], "-f"))){
        f = 1;
      }
    else{
      exit(1);
    }
  }
    struct stat fileData;
      if (fstat(STDIN_FILENO, &fileData) < 0){
        exit(1);
      }


      char*buffer;
      int buffSize = 0;
      int bytesRead = 0;
      int ch = 0;
      if (S_ISREG(fileData.st_mode)){ //if regular file
          buffSize = fileData.st_size;
        buffer = (char*)malloc(buffSize * sizeof(char)); //malloc a buffer big enough to hold entire file
        bytesRead = buffSize;
      }
      else{ //malloc an 8 KB buffer
        buffSize = 8;
        buffer = (char*)malloc(buffSize * sizeof(char));
      }
     
      int returnStatus = read(0, buffer+bytesRead, 1);
      bytesRead++;
             while (returnStatus != 0){
                 /*
                 if buffer is more than half full
                 resize buffer to 2x
                 Read STDIN into buffer, append new contents to end of current
                  Check for read errors
                 Keep a running total of number of bytes read until reaching EOF
                      */

                     if (buffSize/2 <= bytesRead){
                       buffSize *= 2;
                         buffer = realloc(buffer, sizeof(char) * buffSize);
                     }


                     returnStatus = read(0, buffer + bytesRead, 1);
                     bytesRead++;


                   }     //end while loop

                      buffer[bytesRead-1] = EOF;

                     char **wordarr = (char**)malloc(sizeof(char*)); //uses malloc to create the 2d array
                       char *word =  (char*)malloc(sizeof(char)); //uses malloc to create an array


                       int row = 0;
                       int cell = 0;
                       int c = 0;

for (int i = 0; i < bytesRead; i++){
      c = buffer[i];

      if (c!= ' ' &&c!= EOF){
          word = realloc(word, sizeof(char) * (cell+1));
          word[cell] = c;
          cell++;
      }
      else{
          word = realloc(word, sizeof(char) * (cell + 1));
          word[cell] = ' ';
          cell = 0;

          wordarr = realloc(wordarr, sizeof(char*) * (row + 1));
          wordarr[row] = word;
          row++;
          char*temp = (char*)malloc(sizeof(char));
          word = temp;

      }
  }

  qsort(wordarr, row, sizeof(char*), compare);

  for (int i = 0; i<row; i++){

    for (int k = 0; ; k++){
      if (wordarr[i][k] != ' '){
          write(1, &wordarr[i][k], 1);

      }
      else{
        break;
   }

      }

      char space = ' ';
      int returnVal = write(1, &space, 1);
        free(wordarr[i]);
    }
    free(wordarr);
    free(word);
    free(buffer);
}



