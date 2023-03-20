#include "./include/FileHandler.h"

#include <stdio.h>
#include <unistd.h>

char *read_file(const char *fileName){
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;
    
    if (!file){ //null check
        return NULL;
    }
    
    fseek(file, 0L, SEEK_END); //goes to the end of the file
    long int res = ftell(file); //get's the size of the texxt file
    rewind(file); //goes to the beginning of the file
    
    code = malloc(res); //reserves space for the text based on the bytes of the text file
    
    while ((c = fgetc(file)) != EOF){
        code[n++] = (char) c; //sets string code(str) to the value of the text file char by char
        //probably not the best solution....
    }
    code = realloc(code, (n + 1) * sizeof(char));
    n+=1;
    // don't forget to terminate with the null character
    code[n] = '\0';        
    
    return code;
}

int file_exists(char *file_name){
    if( access( file_name, F_OK ) == 0 ) {
        return 1;
    }
    return 0;
}

void file_flush(char *file_name){
    fopen(file_name, "w");    
}

void file_write(char *file_name, char *frmt, char *content){
    
   int num;
   FILE *fptr;

    if(!file_exists(file_name)){
        fptr = fopen(file_name, "w");    
    }else{
        fptr = fopen(file_name,"a");
    }

    if(!fptr){
      printf("\nCouldn't Open File!");   
      exit(1);             
    }

   fprintf(fptr,"%s",content);
   fclose(fptr);
}
