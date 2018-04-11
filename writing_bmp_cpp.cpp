#include "stdafx.h"
#include<iostream>
#include<fstream>

typedef unsigned char BYTE;
using namespace std;

struct BitMap{

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
};
void readHeaderFile(ifstream& fp,struct BitMap& Header){

    fp.read((char*)&Header.Type,sizeof Header.Type);
    fp.read((char*)&Header.Size,sizeof Header.Size);
    fp.read((char*)&Header.Reserve1,sizeof Header.Reserve1);
    fp.read((char*)&Header.Reserve2,sizeof Header.Reserve2);
    fp.read((char*)&Header.OffBits,sizeof Header.OffBits);
    fp.read((char*)&Header.biSize,sizeof Header.biSize);
    fp.read((char*)&Header.biWidth,sizeof Header.biWidth);
    fp.read((char*)&Header.biHeight,sizeof Header.biHeight);
    fp.read((char*)&Header.biPlanes,sizeof Header.biPlanes);
    fp.read((char*)&Header.biBitCount,sizeof Header.biBitCount);
    fp.read((char*)&Header.biCompression,sizeof Header.biCompression);
    fp.read((char*)&Header.biSizeImage,sizeof Header.biSizeImage);
    fp.read((char*)&Header.biXPelsPerMeter,sizeof Header.biXPelsPerMeter);
    fp.read((char*)&Header.biYPelsPerMeter,sizeof Header.biYPelsPerMeter);
    fp.read((char*)&Header.biClrUsed,sizeof Header.biClrUsed);
    fp.read((char*)&Header.biClrImportant,sizeof Header.biClrImportant);

}
//YOU CAN READ LIKE THIS AS WELL>> I FOUND IT NOW AS WELL.. HECK YEAH

//THIS WORKS BUT SOMEWHERE THERE IS A HOLE IN BYTE SO PREFERRED IS READING BYTE BY BYTE AS BEFORE
void readHeaderFileCompletely(ifstream& fp,struct BitMap& Header){
    fp.read((char*)&Header,sizeof Header);
}

void writeFileHeaderCompletely(ofstream&fq,struct BitMap& Header){
    fq.write((char *)&Header,sizeof Header);
}
void printHeader(struct BitMap Header ){

    cout<<Header.Type<<endl;
    cout<<Header.Size<<endl;
    cout<<Header.Reserve1<<endl;
    cout<<Header.Reserve2<<endl;
    cout<<Header.OffBits<<endl;
    cout<<Header.biSize<<endl;
    cout<<Header.biWidth<<endl;
    cout<<Header.biHeight<<endl;
    cout<<Header.biPlanes<<endl;
    cout<<Header.biBitCount<<endl;
    cout<<Header.biCompression<<endl;
    cout<<Header.biSizeImage<<endl;
    cout<<Header.biXPelsPerMeter<<endl;
    cout<<Header.biYPelsPerMeter<<endl;
    cout<<Header.biClrUsed<<endl;
    cout<<Header.biClrImportant<<endl;
}

void writeFileHeader(ofstream& fq,BitMap& Header){
    fq.write((char*)&Header.Type,sizeof Header.Type);
    fq.write((char*)&Header.Size,sizeof Header.Size);
    fq.write((char*)&Header.Reserve1,sizeof Header.Reserve1);
    fq.write((char*)&Header.Reserve2,sizeof Header.Reserve2);
    fq.write((char*)&Header.OffBits,sizeof Header.OffBits);
    fq.write((char*)&Header.biSize,sizeof Header.biSize);
    fq.write((char*)&Header.biWidth,sizeof Header.biWidth);
    fq.write((char*)&Header.biHeight,sizeof Header.biHeight);
    fq.write((char*)&Header.biPlanes,sizeof Header.biPlanes);
    fq.write((char*)&Header.biBitCount,sizeof Header.biBitCount);
    fq.write((char*)&Header.biCompression,sizeof Header.biCompression);
    fq.write((char*)&Header.biSizeImage,sizeof Header.biSizeImage);
    fq.write((char*)&Header.biXPelsPerMeter,sizeof Header.biXPelsPerMeter);
    fq.write((char*)&Header.biYPelsPerMeter,sizeof Header.biYPelsPerMeter);
    fq.write((char*)&Header.biClrUsed,sizeof Header.biClrUsed);
    fq.write((char*)&Header.biClrImportant,sizeof Header.biClrImportant);
}
int main(){
    ifstream fp;
    fp.open("./sword.bmp",ios::binary);
    if(!fp.is_open()){
        cout<<"FILE NOT FOUND. ERROR. GET HELP, NOW"<<endl;
        return -1;
    }
    ofstream fq("image.bmp",ios::binary);
    struct BitMap Header;
    long w,h,imageSize;
    BYTE pixel;

    readHeaderFile(fp,Header);
    printHeader(Header);
    writeFileHeader(fq,Header);

    w = Header.biWidth; h = Header.biHeight;
    imageSize = Header.biSizeImage;

    long image[imageSize][4];
    



    fp.close();
    fq.close();
    return 0;
}

