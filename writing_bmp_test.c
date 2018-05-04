#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#include<string.h>
//#include"hiding.c"

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

struct v5BITMAPINFO{

  short        bV5RedMask;
  short        bV5GreenMask;
  short        bV5BlueMask;
  short        bV5AlphaMask;
  short        bV5CSType;
  CIEXYZTRIPLE bV5Endpoints;
  short        bV5GammaRed;
  short        bV5GammaGreen;
  short        bV5GammaBlue;
  short        bV5Intent;
  short        bV5ProfileData;
  short        bV5ProfileSize;
  short        bV5Reserved;
}v5Header;
int main(){
    FILE *fp;
    //CHange image accordingly
    fp = fopen("./32.bmp","rb");
    FILE *fq;
        fq = fopen("image.bmp","wb");

    //FOR 2x2,replace w and h
  /*   int w =32, h =32;//Resolution of image. this time 32x32
    int r = w*h*4;b
    int image[r][4];//3 represents R G B column
*/
    int i,j;

    if(fp == NULL){
        printf("File not found");
        return 0;
    }

        fread(&Header.Type, 2, 1, fp);//2 equivalent to sizeof(Header.Type)
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
        if(Header.biSize == 124){
            fread(&v5Header.bV5RedMask, 4, 1, fp);
            fread(&v5Header.bV5GreenMask, 4, 1, fp);
            fread(&v5Header.bV5BlueMask, 4, 1, fp);
            fread(&v5Header.bV5AlphaMask, 4, 1, fp);
            fread(&v5Header.bV5CSType, 4, 1, fp);
            fread(&v5Header.bV5Endpoints, sizeof(v5Header.bV5Endpoints), 1, fp);
            fread(&v5Header.bV5GammaRed, 4, 1, fp);
            fread(&v5Header.bV5GammaGreen, 4, 1, fp);
            fread(&v5Header.bV5GammaBlue, 4, 1, fp);
            fread(&v5Header.bV5Intent, 4, 1, fp);
            fread(&v5Header.bV5ProfileData, 4, 1, fp);
            fread(&v5Header.bV5ProfileSize, 4, 1, fp);
            fread(&v5Header.bV5Reserved, 4, 1, fp);

        }


        printf("%d\n",Header.Type);
        printf("%ld\n",Header.Size);
        printf("%ld\n",Header.Reserve1);
        printf("%ld\n",Header.Reserve2);
        printf("%ld\n",Header.OffBits);
        printf("%ld\n",Header.biSize);
        printf("%ld\n",Header.biWidth);
        printf("%ld\n",Header.biHeight);
        printf("%ld\n",Header.biPlanes);
        printf("%ld\n",Header.biBitCount);
        printf("%ld\n",Header.biCompression);
        printf("%ld\n",Header.biSizeImage);
        printf("%ld\n",Header.biXPelsPerMeter);
        printf("%ld\n",Header.biYPelsPerMeter);
        printf("%ld\n",Header.biClrUsed);
        printf("%ld\n",Header.biClrImportant);
        if(Header.biSize == 124){
            printf("%ld\n",v5Header.bV5RedMask);
            printf("%ld\n",v5Header.bV5GreenMask);
            printf("%ld\n",v5Header.bV5BlueMask);
            printf("%ld\n",v5Header.bV5AlphaMask);
            printf("%ld\n",v5Header.bV5CSType);
            printf("%ld\n",v5Header.bV5Endpoints.ciexyzRed);
            printf("%ld\n",v5Header.bV5Endpoints.ciexyzGreen);
            printf("%ld\n",v5Header.bV5Endpoints.ciexyzBlue);
            printf("%ld\n",v5Header.bV5GammaRed);
            printf("%ld\n",v5Header.bV5GammaGreen);
            printf("%ld\n",v5Header.bV5GammaBlue);
            printf("%ld\n",v5Header.bV5Intent);
            printf("Workingtill now\n");
            printf("%ld\n",v5Header.bV5ProfileData);
            printf("%ld\n",v5Header.bV5ProfileSize);
            printf("%ld\n",v5Header.bV5Reserved);


            printf("NOT WORKING??");
            printf("%d",ftell(fp));
            printf("Workingtill now\n");
        }

   /*  int byte;

    for(i=0;i<54;i++)
        byte = getc(fp);//Skipping all the bmp header . it contains first 54 bytes.

 */
//
   int w =(int) Header.biWidth, h =(int) Header.biHeight;//Resolution of image. this time 32x32
    int r = (int)Header.biSizeImage;
    int pad = w%4;

   // int image[r][4];//3 represents R G B column
   unsigned char * image = (unsigned  char * )calloc(r*4,sizeof(unsigned char));

//ALTERNATIVE FOR UPPER COMMENTED code
//NO NEED FOR THIS AS IT IS ALREADY
   // rewind(fp);
    printf(" Header: %ld",Header.OffBits);
    //fseek(fp,(int)Header.OffBits,SEEK_SET);
    printf("\n%ld %ld %d",ftell(fp),ftell(fq),r);
    //fseek(fp,54,SEEK_SET);


    for(i=0;i<h;i++){
        for(j=0;j<w;j++){
            printf("j is : %d and w is %d\n",j,w);

           // image[(i*h)+j][2] = getc(fp);//BMP SAVES IN BGR Format. So assining in revrese order.[2] = B
            *(image + ((i*h)+j)*i+2) = getc(fp);
           // image[(i*h)+j][1] = getc(fp);//[1] = G [0] = R
            *(image + ((i*h)+j)*i+1) = getc(fp);
           // image[(i*h)+j][0] = getc(fp);
            *(image + ((i*h)+j)*i+0) = getc(fp);
            printf("HERE?");
            if(Header.biBitCount == 32){
                //image[(i*h)+j][3] = getc(fp);
                *(image + ((i*h)+j)*i+3) = getc(fp);
            }


            printf("Image %d,%d : R:%d G:%d B:%d A:%d  %d  \n",i,j,*(image + ((i*h)+j)*i+0),*(image + ((i*h)+j)*i+1),*(image + ((i*h)+j)*i+2),*(image + ((i*h)+j)*i+3),i*h+j);
            //BMP IS STORED from bottom left and changing row means going up instead of down
            //So 0,0 indicates bottom left position, 1,1 means top right in 2x2 pixel
    //  printf("pixel %d %d : [R:%d,G:%d,B:%d]\n",i,j,image[(i*h)+j][0],image[(i*h)+j][1],image[(i*h)+j][2]);

        }
        // printf("Outside j is : %d and w %d\n",j,w);
        //fseek(fp,0,SEEK_CUR);//GETTING TWO bytes ahead because of padding (2 bytes).
    }

    //JUST TESTING TO CREATE ANOTHER IMAGE WITH DIFFERENT VALUES


        ///COPIED FROM INTERNET TO ENTER HEADER FILES OF BMP

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


       // memset(&Header, 0, sizeof(Header));


      // int c = 5;
      // fseek(fq,54,SEEK_SET);
//offbits tells where pixel start from so

       // fseek(fq,(int)Header.OffBits,SEEK_SET);
        fseek(fq,54,SEEK_SET);
        int R,G,B,A;
        R=G=B=A=0;

        for(i=0;i<h;i++){
            for(j=0;j<w;j++){



            //TODO: GET BIT OF CURRENT IMAGE AND CHANGE IT


                // R =  image[(i*h)+j][0];
                R = *(image + ((i*h)+j)*i+0);
                // G =  image[(i*h)+j][1];
                G = *(image + ((i*h)+j)*i+1);
                // B =  image[(i*h)+j][2];
                B = *(image + ((i*h)+j)*i+2);
                 if(Header.biBitCount == 32){
                //    A = image[(i*h)+j][3];
                    A = *(image + ((i*h)+j)*i+3);
                }

                 R = R - R%2;// Makes LSB 0??? THis works because if odd, 2^0 is 1, if even 2^0 = 0. So
                 B = B - B%2;//If odd, remainder is 1, and subtracts it. Else does nothing
                G = G - G%2;

                //hiding test character
               /*  char c = 'a';
                int hide = 1;
                for(int i=0;i<8;i++){

                    int data = c & hide;//returns 1
                } */

                putc(B,fq);
                putc(G,fq);
                putc(R,fq);
                if(Header.biBitCount == 32){
                   putc(A,fq);
                }

               // printf("Image %d,%d : R:%d G:%d B:%d   %d  \n",i,j,image[(i*h+j)][0],image[(i*h+j)][1],image[(i*h+j)][2],i*h+j);

                //printf("%d, %d R: %d G: %d B:%d\n\n",i,j,R,G,B);

                //TODO: MOVE/seek padding value forward to get to another pixel data
            }

            





        }



   //END TEST


    fclose(fp);
    fclose(fq);
    system("pause");
}



//SINGLE PIXEL
    /* fseek(fp,65,SEEK_SET);
        image[i][2] = getc(fp);
        image[i][1] = getc(fp);
        image[i][0] = getc(fp);
        printf("pixel %d : [R:%d,G:%d,B:%d]\n",i+1,image[i][0],image[i][1],image[i][2]); */
//
//TODO: Yes.. How to put bit inside??
/*
    use binary or(|) with 00...1 making only last value valid. and put that in the bit. then right shift the bit and continue
 */
