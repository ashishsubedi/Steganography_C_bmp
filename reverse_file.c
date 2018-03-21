#include<stdio.h>

int main(){
    FILE *f1,*f2;
    char c;
    int total;
    f1 = fopen("text.txt","r");
    if(f1 == NULL){
        printf("ERROR OPENING FILE>.....");
        return 0;
    }
    f2 = fopen("reversed.txt","w");

    fseek(f1,-1,SEEK_END);
    total = ftell(f1) + 1;//Adding 1 for string terminator
    printf("%d",total);

    fseek(f1,-1,SEEK_END);
    while(total){
        c = fgetc(f1);
        fputc(c,f2);
        fseek(f1,-2,SEEK_CUR);
        total--;
    }
    fclose(f1);
    fclose(f2);

}