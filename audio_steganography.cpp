//Thomas Jarrell MSIM 695 Final ODU Main Campus

// Standard libraries
#include <iostream> /* Enable iostream*/
#include <stdio.h> /* This header file defines the I/O functions */
#include <stdlib.h> /* include standard dfeinitions like exit() */
#include <math.h> /* this includes math functions*/
#include <conio.h> /* This is for user input/output*/


#define FALSE 0
#define TRUE 1


// The main function has always access to the programs.
// argc = counter; argv = array of strings
int main(int argc, char **argv){

    // Initialize variables
		FILE *fpIna;
		FILE *fpInb;

		FILE *fpimagea;	//This is the target file (PPM) that will be modified.
		FILE *fpimageb;	//This is the input (PGM) file that will be embedded into imagea.
		FILE *fpimaged;
		char *stringa;
		char *stringb;
		char c;
		int l;
		int imageasize, imagebsize;
		int highVal;
		int doneReading = FALSE;
		int numberOfRowsa, numberOfColumnsa, numberOfBandsa;
		int numberOfRowsb, numberOfColumnsb, numberOfBandsb;
		int totalPixelsa;
		int totalPixelsb;
		int imagesizea, imagesizeb;
		int i, j;
		int iOff;
		int cnt;
		int bnd;
		int input, output;
		unsigned char *imaged;			//Output file
		int ipOff;						
		int b0, b1, b2, b3, b4, b5, b6, b7;
		unsigned char *imagea;			//Input and output file
		unsigned char *imageb;			//Input file
		unsigned char bitarraya[8];
		unsigned char bitarrayb[8];
		int b;				//Bit tracker
	  // The read program is invoked by: readimage targetfile inputfile outputfile.
      // Program requires at least 3 arguments:
      // 1. "call program"
      // 2. "input pgm"
      // 3. "output pgm"; the histogram will be written to this outfile file
      if (argc < 3) {
            fprintf(stderr,"Usage: readimage output-file-name inputb-file-name\n");
            exit(0);
      }
      fpIna = fopen(argv[1],"rb");   // argv[1] contains the filename
      if (fpIna == NULL) {
            fprintf(stderr,"%s either cannot be read or does not exist\n", argv[1]);
            exit(-1);
      }
      stringa = (char *) calloc(256,1);  // initialized dynamic memory allocation
      while (!doneReading && (c = (char) fgetc(fpIna)) != '\0')
            switch(c) {
        case 'P':
              c = (char) getc(fpIna);
              switch(c) {
        case '2':
              numberOfBandsa = 1;
              /* ppmType = PPMASCII; */
              break;
        case '3':
              numberOfBandsa = 3;
              /* ppmType = PPMASCII; */
              break;
        case '5':
              numberOfBandsa = 1;
              /* ppmType = PPMGRAY; */
              break;
        case '6':
              numberOfBandsa = 3;
              /* ppmType = PPMRAW; */
              break;
              }
              c = (char) getc(fpIna);
              if (c != 0x0A) {
                    ungetc(c,fpIna);
              }
              else {
                    ungetc(c,fpIna);
                    fgets(stringa,256,fpIna);
              }
              break;
        case '#':
              fgets(stringa,256,fpIna);
              break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
              ungetc(c,fpIna);
              fscanf(fpIna,"%d %d %d", &numberOfColumnsa, &numberOfRowsa, &highVal);
              doneReading = TRUE;
              fgetc(fpIna);
              break;
      }

      // De-allocate memory
      free(stringa);

      // Allocate this many number of bytes to the image.
      totalPixelsa = numberOfRowsa*numberOfColumnsa*numberOfBandsa;
    
	  //Read and store the file imagea 

      // Reads from the specified pointer; 1 byte, # of pixels, and file pointer
      
      //fpIna = fopen(argv[1],"rb");
      imagea = (unsigned char *) malloc(totalPixelsa);
      l = fread(imagea,1,totalPixelsa,fpIna);  //stores the image data into imagea
      fprintf(stderr,"fread returned %d bytes\n", l);
      
	  doneReading = FALSE;

	  //Load the second image called imageb, this is the input image.

	  fpInb = fopen(argv[2],"rb");   // argv[2] contains the filename
      if (fpInb == NULL) {
            fprintf(stderr,"%s either cannot be read or does not exist\n", argv[2]);
            exit(-1);
      }
      stringb = (char *) calloc(256,1);  // initialized dynamic memory allocation
      while (!doneReading && (c = (char) fgetc(fpInb)) != '\0')
            switch(c) {
        case 'P':
              c = (char) getc(fpInb);
              switch(c) {
        case '2':
              numberOfBandsb = 1;
              /* ppmType = PPMASCII; */
              break;
        case '3':
              numberOfBandsb = 3;
              /* ppmType = PPMASCII; */
              break;
        case '5':
              numberOfBandsb = 1;
              /* ppmType = PPMGRAY; */
              break;
        case '6':
              numberOfBandsb = 3;
              /* ppmType = PPMRAW; */
              break;
              }
              c = (char) getc(fpInb);
              if (c != 0x0A) {
                    ungetc(c,fpInb);
              }
              else {
                    ungetc(c,fpInb);
                    fgets(stringb,256,fpInb);
              }
              break;
        case '#':
              fgets(stringb,256,fpInb);
              break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
              ungetc(c,fpInb);
              fscanf(fpInb,"%d %d %d", &numberOfColumnsb, &numberOfRowsb, &highVal);
              doneReading = TRUE;
              fgetc(fpInb);
              break;
      }

      // De-allocate memory
      free(stringb);

      // Allocate this many number of bytes to the image.
      totalPixelsb = numberOfRowsb*numberOfColumnsb*numberOfBandsb;
      
//Read and store the file imageb 

      // Reads from the specified pointer; 1 byte, # of pixels, and file pointer
      //fpInb = fopen(argv[2],"rb");
      imageb = (unsigned char *) malloc(totalPixelsb);
      l = fread(imageb,1,totalPixelsb,fpInb);
      fprintf(stderr,"fread returned %d bytes\n", l);


//********Conduct test to fit imageb (total pixels) into imagea, 
// if okay, then output the size of image B rows and columns.

	imagesizea=totalPixelsa*2;
	imagesizeb=totalPixelsb*6;
		if(imagesizeb>imagesizea){
			fprintf(stderr,"%s is too large to fit the target image\n",argv[2]);
			exit(-1);}
		fprintf(stderr,"%s embedded image is %d columns and %d rows\n",argv[2], numberOfColumnsb, numberOfRowsb);
		
	  		
// Read a band of original file into a floating point array named imaged 
		for (bnd = 0; bnd < numberOfBandsa; bnd++) {
			for (i = 0; i < numberOfRowsa; i++) {
					iOff = i*numberOfColumnsa*numberOfBandsa;
					ipOff = i*numberOfColumnsa;
					l = 0;
					for (j = bnd; j < numberOfColumnsa*numberOfBandsa; j+=numberOfBandsa) {
							imaged[ipOff+l] = imagea[iOff+j];    
							l++;}
					}
		}

      		
//Read a band of original file into a floating point array named imaged 
		for (bnd = 0; bnd < numberOfBandsb; bnd++) {
			for (i = 0; i < numberOfRowsb; i++) {
					iOff = i*numberOfColumnsb*numberOfBandsb;
					ipOff = i*numberOfColumnsb;
					l = 0;
					for (j = bnd; j < numberOfColumnsb*numberOfBandsb; j+=numberOfBandsb) {
							imaged[ipOff+l] = imageb[iOff+j];
							l++;}
					}
		}
//Read bit data for imageb by band, insert imagea bit fields into imageb bit b1 and b0.  
//This will insert imagea bits b7-b2 in the three bands for the same pixel position.

			l = 0;	//Set imagea to the begining.
			i = 0;	//Set imageb to the begining.
	        //for (l=0; l<totalPixelsa; l++){
				if (numberOfBandsa==0){
					for(i=0;i<totalPixelsb; i++){
						b7=(imageb[l]&0x80 ? 1 : 0);	//imageb b7 data
						b6=(imageb[l]&0x40 ? 1 : 0);	//imageb b6 data
						b5=(imagea[l]&0x20 ? 1 : 0);
						b4=(imagea[l]&0x10 ? 1 : 0);
						b3=(imagea[l]&0x08 ? 1 : 0);
						b2=(imagea[l]&0x04 ? 1 : 0);
						b1=(imagea[i]&0x02 ? 1 : 0);	
						b0=(imagea[i]&0x01 ? 1 : 0);	
						imagea[l]=b7*128+b6*64+b5*32+b4*16+b3*8+b2*4+b1*2+b0*1;}
					l++;	//Advance imagea
				}

				if (numberOfBandsa==1){
					//for(i=0;i<totalPixelsb; i++){
						b7=(imageb[l]&0x20 ? 1 : 0);	//imageb b5 data
						b6=(imageb[l]&0x10 ? 1 : 0);	//imageb b4 data
						b5=(imagea[l]&0x20 ? 1 : 0);
						b4=(imagea[l]&0x10 ? 1 : 0);
						b3=(imagea[l]&0x08 ? 1 : 0);
						b2=(imagea[l]&0x04 ? 1 : 0);
						b1=(imagea[i]&0x02 ? 1 : 0);	
						b0=(imagea[i]&0x01 ? 1 : 0);	
						imagea[l]=b7*128+b6*64+b5*32+b4*16+b3*8+b2*4+b1*2+b0*1;}
					l++;	//Advance imagea
				}

				if (numberOfBandsa==2){
					//for(i=0;i<totalPixelsb; i++){
						b7=(imageb[l]&0x08 ? 1 : 0);	//imageb b3 data
						b6=(imageb[l]&0x04 ? 1 : 0);	//imageb b2 data
						b5=(imagea[l]&0x20 ? 1 : 0);
						b4=(imagea[l]&0x10 ? 1 : 0);
						b3=(imagea[l]&0x08 ? 1 : 0);
						b2=(imagea[l]&0x04 ? 1 : 0);
						b1=(imagea[i]&0x02 ? 1 : 0);	
						b0=(imagea[i]&0x01 ? 1 : 0);	
						imagea[l]=b7*128+b6*64+b5*32+b4*16+b3*8+b2*4+b1*2+b0*1;}
					l++;	//Advance imagea
					i++;	//Advance imagea
				}
				//l++;
			}

////Build the bit arrays for imagea and imageb.
////			bitarraya[0]=(imagea[i]&0x01 ? 1 : 0);
////			bitarraya[1]=(imagea[i]&0x02 ? 1 : 0);
////			bitarraya[2]=(imagea[i]&0x04 ? 1 : 0);
////			bitarraya[3]=(imagea[i]&0x08 ? 1 : 0);
////			bitarraya[4]=(imagea[i]&0x10 ? 1 : 0);
////			bitarraya[5]=(imagea[i]&0x20 ? 1 : 0);
////			bitarraya[6]=(imagea[i]&0x40 ? 1 : 0);
////			bitarraya[7]=(imagea[i]&0x80 ? 1 : 0);
////		
////			bitarrayb[0]=(imageb[l]&0x01 ? 1 : 0);
////			bitarrayb[1]=(imageb[l]&0x02 ? 1 : 0);
////			bitarrayb[2]=(imageb[l]&0x04 ? 1 : 0);
////			bitarrayb[3]=(imageb[l]&0x08 ? 1 : 0);
////			bitarrayb[4]=(imageb[l]&0x10 ? 1 : 0);
////			bitarrayb[5]=(imageb[l]&0x20 ? 1 : 0);
////			bitarrayb[6]=(imageb[l]&0x40 ? 1 : 0);
////			bitarrayb[7]=(imageb[l]&0x80 ? 1 : 0);
//			
//            
//            //imageb[l]&0x01 = imagea[i]&0x04;
//			//imageb[l]&0x02 = imagea[i]&0x08;
//			//imageb[l+1]&0x01 = imagea[i]&0x10;
//			//imageb[l+1]&0x02 = imagea[i]&0x20;
//			//imageb[l+2]&0x01 = imagea[i]&0x40;
//			//imageb[l+2]&0x02 = imagea[i]&0x80;
//			//
//            //l += 3;
//            //}										//Is the bracket needed?
//
//
////********The process here is to read imagea bits starting with 0,0 and write them across Band 0 bits starting with position b0
////then b0 and then b1.  Continue the process for bands 1 and 2 as needed.
//
//			
//		//	cnt=0;
//		//		for(b=0; b<8; b+=2);
//		//	cnt++;
//		//		if(cnt==2){
//		//			cnt=0;
//		//			l=l+1;
//		//		}
//		


//*********************************************************
//now print 

fpimagea = fopen(argv[3],"wb");  //keep

//Write the image header
fprintf(fpimagea,"P%d\n%d %d\n255\n",numberOfBandsa>1?6:5,numberOfColumnsa, numberOfRowsa); 

fwrite(imagea,1,totalPixelsa,fpimagea);

exit(0);
}

