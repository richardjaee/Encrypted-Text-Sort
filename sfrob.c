
#include <stdio.h>
#include <stdlib.h>

int frobcmp (char const  *a, char const *b){
  while (*a != ' ' && *b != ' '){ //runs loop until either a or b is a space
    char c1 = *a ^ 42;
    char c2 = *b ^ 42;
    if ((c1) < (c2)){ //a < b
      return -1;
    }
    if ((c1) > (c2)){ //a > b
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
  return frobcmp(*(char const **)a, *(char const **)b); //calls frobcmp and compares a and b
}



int main(){
char **wordarr = (char**)malloc(sizeof(char*)); //uses malloc to create the 2d array
char *word =  (char*)malloc(sizeof(char)); //uses malloc to create an array

int cell = 0;
int row = 0;

int c = 0;
while(c != EOF){
    c = getchar();

    if (c != ' ' && c != EOF){ //not the end of the word
        word = realloc(word, sizeof(char)*(cell+1));
        word[cell] = c;
        cell++; //increments the index
    }
    else{ //end of the word
        word = realloc(word, sizeof(char) * (cell +1));
        word[cell] = ' '; //put a space at the end of the word
        cell = 0; //reset cell to 0

        wordarr = realloc(wordarr, sizeof(char*)*(row+1));
        wordarr[row] = word; //adds the word to the wordarray
        row++;
        char* temp = (char*)malloc(sizeof(char)); //temp array
        word = temp; //makes word empty
    }
} //end while loop

 qsort(wordarr, row, sizeof(char *), compare);

    for (int i = 0; i < row; i++){
        for (int k = 0 ;; k++){
          if (wordarr[i][k]==' '){
              break;
          }
            putchar(wordarr[i][k]);

        }
        putchar(' ');
        free(wordarr[i]);
    }
    free(wordarr);
    free(word);
    exit(0);
}


