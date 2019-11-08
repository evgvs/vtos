#include <string.h>  

char* split (char str[], char* who, int c) 
{  
    // Returns first token  
    char *token = strtok(str, who); 

    int count=0;

    char* massiv[10];
    
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    //
    while (token != NULL) 
    { 
	massiv[count++] = token;
        token = strtok(NULL, who); 
    } 
  
    return massiv[c];
} 

//	 printf ( split ( "raz dva tri" , " ", 1 ) );

	

