#include<stdio.h>
#include<stdlib.h>
  struct BitMap
{
  short Type;
  long Size;
  short Reserve1;
  short Reserve2;
  long OffBits;
  long biSize;
  long biWidth;
  long biHeight;
  short biPlanes;
  short biBitCount;
  long biCompression;
  long biSizeImage;
  long biXPelsPerMeter;
  long biYPelsPerMeter;
  long biClrUsed;
  long biClrImportant;
} Header;
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

            image[(i*h)+j][2] = getc(fp);//BMP SAVES IN BGR Format. So assining in revrese order.[2] = B
            image[(i*h)+j][1] = getc(fp);//[1] = G [0] = R
            image[(i*h)+j][0] = getc(fp);
            //BMP IS STORED from bottom left and changing row means going up instead of down
            //So 0,0 indicates bottom left position, 1,1 means top right in 2x2 pixel
            printf("pixel %d %d : [R:%d,G:%d,B:%d]\n",i,j,image[(i*h)+j][0],image[(i*h)+j][1],image[(i*h)+j][2]);
            //printf("%d %d")
        }
        fseek(fp,2,SEEK_CUR);//GETTING TWO bytes ahead because of padding (2 bytes).
    }
   
    //JUST TESTING TO CREATE ANOTHER IMAGE WITH DIFFERENT VALUES
        FILE *fq;
        fq = fopen("code_image.bmp","wb");
        rewind(fp);//File pointer goes to start
        ///COPIED FROM INTERNET TO ENTER HEADER FILES OF BMP


 
   
        memset(&Header, 0, sizeof(Header));
        
        fread(&Header.Type, 2, 1, fp);
        fread(&Header.Size, 4, 1, fp);
        fread(&Header.Reserve1, 2, 1, fp);
        fread(&Header.Reserve2, 2, 1, fp);
        fread(&Header.OffBits, 4, 1, fp);
        fread(&Header.biSize, 4, 1, fp);
        fread(&Header.biWidth, 4, 1, fp);
        fread(&Header.biHeight, 4, 1, fp);
        fread(&Header.biPlanes, 2, 1, fp);
        fread(&Header.biBitCount, 2, 1, fp);
        fread(&Header.biCompression, 4, 1, fp);
        fread(&Header.biSizeImage, 4, 1, fp);
        fread(&Header.biXPelsPerMeter, 4, 1, fp);
        fread(&Header.biYPelsPerMeter, 4, 1, fp);
        fread(&Header.biClrUsed, 4, 1, fp);
        fread(&Header.biClrImportant, 4, 1, fp);
//COPYING EVERYTHING FROM ORIGINAL HEADER FILE AND REPLACING
        fwrite(&Header.Type, 2, 1, fq);
        fwrite(&Header.Size, 4, 1, fq);
        fwrite(&Header.Reserve1, 2, 1, fq);
        fwrite(&Header.Reserve2, 2, 1, fq);
        fwrite(&Header.OffBits, 4, 1, fq);
        fwrite(&Header.biSize, 4, 1, fq);
        fwrite(&Header.biWidth, 4, 1, fq);
        fwrite(&Header.biHeight, 4, 1, fq);
        fwrite(&Header.biPlanes, 2, 1, fq);
        fwrite(&Header.biBitCount, 2, 1, fq);
        fwrite(&Header.biCompression, 4, 1, fq);
        fwrite(&Header.biSizeImage, 4, 1, fq);
        fwrite(&Header.biXPelsPerMeter, 4, 1, fq);
        fwrite(&Header.biYPelsPerMeter, 4, 1, fq);
        fwrite(&Header.biClrUsed, 4, 1, fq);
        fwrite(&Header.biClrImportant, 4, 1, fq);

        //NOW for changing some parts .. I AM GONNA CHANGE MSB INSTEAD OF LSB .. LETS SEE

        int c = 5;


        

   //END TEST

    fclose(fp);
} 



//SINGLE PIXEL
    /* fseek(fp,65,SEEK_SET);
        image[i][2] = getc(fp);
        image[i][1] = getc(fp);
        image[i][0] = getc(fp);
        printf("pixel %d : [R:%d,G:%d,B:%d]\n",i+1,image[i][0],image[i][1],image[i][2]); */