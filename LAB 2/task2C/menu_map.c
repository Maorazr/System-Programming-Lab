#include <stdlib.h>

#include <stdio.h>
#include <string.h>
 
char censor(char c) {
  if(c == '!')
    return '*';
  else
    return c;
}
 
char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  for (int i = 0; i < array_length; i++){
      mapped_array[i] = (*f)(array[i]);
  }
  return mapped_array;
}


char encrypt(char c){
  if (c < 'A'  || c > 'z'){
    return(c);
  } 
  else{
    return (c + 2);
  }
}

char decrypt(char c){
  char c2 = c-2;
   if (c2 < 'A'  || c2 > 'z'){
    return(c);
  } 
  else{
    return (c2);
  }
}

char dprt(char c){
  printf("%d\n", c);
  return c;
}

char cprt(char c){
  if (c >= 'A'  && c <= 'z'){
  printf("%c\n", c);
  } else {
    printf("*\n");
  }
  return c;
}

char my_get(char c){
  char c2 = fgetc(stdin);
  return c2;
}

char quit(char c){
    if (c == 'q'){
      exit(0);
    }
    else return c;    
}


// void menu(){
//     int len = 5;
//     char *carray = (char*)(malloc(len));
//     carray[0] = '\0';
//     typedef struct fun_desc{
//         char *name;
//         char (*fun)(char);
//     }fun_desc;

//     fun_desc fun_arr[] = {{"Censor", censor},{"Encrypt", encrypt}, {"Decrypt", decrypt}, {"Print dec", dprt}, 
//                         {"Print string", cprt}, {"Get string", my_get}, {"Quit", quit}, {NULL, NULL}};

//     int count =1;
//     while(count == 1){
//     printf("Please choose a function:\n");
//     for (int i = 0; i < 7; i++){
//         printf("%d) %s\n", i, fun_arr[i].name);
//     }
//     printf("Option: ");
//     char option = fgetc(stdin);
//     fgetc(stdin);
//     if (option < '0'|| option > '6'){
//       printf("Not within bound\n");
//       exit(0);
//     } else{ 
//       printf("Within bound\n");
//       if(option == '5'){
//       scanf(carray,"%s");
//       if (strcmp(carray,"quit")== 0)
//       {
//         exit(0);
//       }
      
//     }
//     carray = map(carray, len, fun_arr[option - '0'].fun);
//     printf("DONE.\n");
//     }
//   }
// }


int main(int argc, char **argv){

}
