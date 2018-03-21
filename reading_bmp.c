#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    //CHange image accordingly
    fp = fopen("./test2.bmp","rb");

    //FOR 2x2,replace w and h
    int w = 2, h = 2;//Resolution of image. this time 32x32
    int r = w*h;
    int image[r][3];//3 represents R G B column

    int i,j;

    if(fp == NULL){
        printf("File not found");
        return 0;
    }
   /*  int byte;

    for(i=0;i<54;i++) 
        byte = getc(fp);//Skipping all the bmp header . it contains first 54 bytes. 
 */
//ALTERNATIVE FOR UPPER COMMENTED code
    fseek(fp,54,SEEK_SET);
        
    for(i=0;i<h;i++){
        for(j=0;j<w;j++){

            image[j][2] = getc(fp);//BMP SAVES IN BGR Format. So assining in revrese order.[2] = B
            image[j][1] = getc(fp);//[1] = G [0] = R
            image[j][0] = getc(fp);
            //BMP IS STORED from bottom left and changing row means going up instead of down
            //So 0,0 indicates bottom left position, 1,1 means top right in 2x2 pixel
            printf("pixel %d %d : [R:%d,G:%d,B:%d]\n",i,j,image[j][0],image[j][1],image[j][2]);
        }
        fseek(fp,2,SEEK_CUR);//GETTING TWO bytes ahead because of padding (2 bytes).
    }
   
  /*  //JUST TESTING TO CREATE ANOTHER IMAGE WITH DIFFERENT VALUES
       
    ON WRITING_BMP.C
*/
    fclose(fp);
}



//SINGLE PIXEL
    /* fseek(fp,65,SEEK_SET);
        image[i][2] = getc(fp);
        image[i][1] = getc(fp);
        image[i][0] = getc(fp);
        printf("pixel %d : [R:%d,G:%d,B:%d]\n",i+1,image[i][0],image[i][1],image[i][2]); */