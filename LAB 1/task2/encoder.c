

#include <stdio.h>
#include <string.h>



int enc1a(){
	FILE *in = stdin;
	fprintf(in , "\n");
	char ch;
	while(( ch = fgetc(in)) != EOF){
		if( ch > 64 && ch < 91){
			printf("%c", '.');
		} 	
		else printf("%c",ch);
	}
    return 0;
}

int enc1b (){
    int count = 0;
    char ch;

    FILE* in = stdin;
    FILE* err = stderr;
    fprintf(in, "\n");
    while ((ch = fgetc(in)) != EOF)
    {
        if (ch > 64 && ch < 91)
        {
            count++;
            fprintf(err,"%d %d\n", ch, '.');
            ch = '.';
        }
        else {
            fprintf(err, "%d %d\n", ch, ch);
        }
        if (ch == '\n'){
            fprintf(err, "the number of letters: %d\n", count);
        }
        printf("%c", ch);
    }
    return 0;
} 


int enc1c(char sign, char value){
    FILE* in = stdin;
    char ch1;
    char ch;
    int val;
    int count = 0;

    if (value > 64 && value < 71)
    {
        val = value - 55;
    } else if(value > 47 && value < 58) {
        val = value - 48;
    } else {
        printf("key character out of range %d \n", value);
        return 0;
    }
    if (sign == '+')
    {   
        while ((ch = fgetc(in)) != EOF)
        {
            if (count == 0){
                ch1 = ch;
                count++;
            }   if (ch != '\n')
            {
                printf("%c", ch);
            }
                for (int i = 0; i < val && ch == '\n'; i++){
                fputc(ch1, stdout);
                }
                if(ch == '\n'){
                count = 0;
                printf("%c", '\n');
                ch = "";
                }
            }
            
        }    
     else if (sign == '-'){
        while((ch = fgetc(in)) != EOF){
            count++;
            if (count > val)
            {
                printf("%c", ch);
            }
            if (ch == '\n')
            {
                count = 0;
            }
        }
     }
    return 0;
}


int enc1d(char *str, char **argv , int var){
    FILE *input = fopen(str,"r");
    if(input == NULL){
        printf("File dosent exist");
        exit(0);
    }
    char value;
    char ch1;
    char ch;
    int val;
    char sign;
    int count = 0;
    if (strncmp(argv[1], "+e",2) == 0){
             sign = '+';
             value = argv[1][2];
        } 
    else if(strncmp(argv[1], "-e",2) == 0){
            sign = '-';
            value = argv[1][2];
          }
    if (value > 64 && value < 71)
    {
        val = value - 55;
    } else if(value > 47 && value < 58) {
        val = value - 48;
    } else {
        printf("key character out of range %d \n", value);
        return 0;
    }
    if (sign == '+')
    {   
        while ((ch = fgetc(input)) != EOF)
        {
            if (count == 0){
                ch1 = ch;
                count++;
            }   if (ch != '\n')
            {
                printf("%c", ch);
            }
                for (int i = 0; i < val && ch == '\n'; i++){
                fputc(ch1, stdout);
                }
                if(ch == '\n'){
                count = 0;
                printf("%c", '\n');
                ch = "";
                }
            }
            
        }    
     else if (sign == '-'){
        while((ch = fgetc(input)) != EOF){
            count++;
            if (count > val)
            {
                printf("%c", ch);
            }
            if (ch == '\n')
            {
                count = 0;
            }
        }
     }

}


int enc2(char *str, char **argv){
FILE *output = fopen(str,"w");
    if(output == NULL){
        printf("File dosent exist");
        exit(0);
    }
    FILE* in = stdin;
    char value;
    char ch1;
    char ch;
    int val;
    char sign;
    int count = 0;
    if (strncmp(argv[1], "+e",2) == 0){
             sign = '+';
             value = argv[1][2];
        } 
    else if(strncmp(argv[1], "-e",2) == 0){
            sign = '-';
            value = argv[1][2];
          }

    if (value > 64 && value < 71)
    {
        val = value - 55;
    } else if(value > 47 && value < 58) {
        val = value - 48;
    } else {
        printf("key character out of range %d \n", value);
        return 0;
    }
    if (sign == '+')
    {   
        while ((ch = fgetc(in)) != EOF)
        {
            if (count == 0){
                ch1 = ch;
                count++;
            }   if (ch != '\n')
            {
                fputc(ch, output);
            }
                for (int i = 0; i < val && ch == '\n'; i++){
                fputc(ch1, output);
                }
                if(ch == '\n'){
                count = 0;
                printf("%c", '\n');
                ch = "";
                }
            }
            
        }    
     else if (sign == '-'){
        while((ch = fgetc(in)) != EOF){
            count++;
            if (count > val)
            {
                fputc(ch, output);
            }
            if (ch == '\n')
            {
                count = 0;
            }
        }
     }
    return 0;

}


int main(int argc, char **argv){

    if(argc > 2){
    for (int i = 0; i < argc; i++){
        if(strncmp(argv[i], "-i",2) == 0){
            char *str = argv[i] +2;
            enc1d(str, argv, argc);
        } else if(strncmp(argv[i], "-o",2) == 0){
            char *str = argv[i] +2;
            enc2(str, argv);
        }
    }
    } else{

    if (argc == 1)
    {
        enc1a();
    } else {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-D") == 0)
            {
                enc1b();
            } 
            else
            { 
                if (strncmp(argv[i], "+e",2) == 0) 
                {
                    char sign = '+';
                    char value = argv[i][2];
                    enc1c(sign,value);
                } 
                else if(strncmp(argv[i], "-e",2) == 0)
                {
                    char sign = '-';
                    char value = argv[i][2];
                    enc1c(sign,value);
                }
            }  

        }
        
    }
    }
}
