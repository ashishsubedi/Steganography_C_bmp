#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    fp = fopen("./test.bmp","rb");
    int image[4][3];
    int i;

    if(fp == NULL){
        printf("File not found");
        return 0;
    }
    int byte;

    fseek(fp,61,SEEK_SET);
        image[i][2] = getc(fp);
        image[i][1] = getc(fp);
        image[i][0] = getc(fp);
        printf("pixel %d : [B:%d,G:%d,R:%d]\n",i+1,image[i][0],image[i][1],image[i][2]);
/*     for(i=0;i<54;i++) 
        byte = getc(fp); 
    for(i=0;i<100;i++){
        image[i][2] = getc(fp);
        image[i][1] = getc(fp);
        image[i][0] = getc(fp);
        printf("pixel %d : [%d,%d,%d]\n",i+1,image[i][0],image[i][1],image[i][2]);
    } */
   

    fclose(fp);
}