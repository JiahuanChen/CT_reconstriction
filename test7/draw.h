#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<PshPack2.h>

using namespace std;
typedef long BOOL;
typedef long LONG;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;

typedef struct {
        WORD    bfType;
        DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfReserved2;
        DWORD   bfOffBits;
} BMPFILEHEADER_T;

struct BMPFILEHEADER_S{
        WORD    bfType;
        DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfReserved2;
        DWORD   bfOffBits;
};

typedef struct{
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
} BMPINFOHEADER_T;

void Snapshot( BYTE * pData, int width, int height,  char * filename )
{
       int size = width*height*3; // 每个像素点3个字节

       // 位图第一部分，文件信息
       BMPFILEHEADER_T bfh;
       bfh.bfType = 0X4d42;  //bm
       bfh.bfSize = size  // data size
              + sizeof( BMPFILEHEADER_T ) // first section size
              + sizeof( BMPINFOHEADER_T ) // second section size
              ;
       bfh.bfReserved1 = 0; // reserved
       bfh.bfReserved2 = 0; // reserved
       bfh.bfOffBits = bfh.bfSize - size;

 

       // 位图第二部分，数据信息
       BMPINFOHEADER_T bih;
       bih.biSize = sizeof(BMPINFOHEADER_T);
       bih.biWidth = width;
       bih.biHeight = height;
       bih.biPlanes = 1;
       bih.biBitCount = 24;
       bih.biCompression = 0;
       bih.biSizeImage = size;
       bih.biXPelsPerMeter = 0;
       bih.biYPelsPerMeter = 0;
       bih.biClrUsed = 0;
       bih.biClrImportant = 0;      

       FILE * fp = fopen( filename,"wb" );
       if( !fp ) return;

       fwrite( &bfh, 1, sizeof(BMPFILEHEADER_T), fp );

       fwrite( &bih, 1, sizeof(BMPINFOHEADER_T), fp );

       fwrite( pData, 1, size, fp );

       fclose( fp );

}


void draw(int **a)
{
       int i=0, j=0;
       struct {
              BYTE b;
              BYTE g;
              BYTE r;
       } pRGB[256][256];  // 定义位图数据

       memset( pRGB, 0, sizeof(pRGB) ); // 设置背景为黑色

       for(  i=0;i<256;i++ ){
              for( j=0;j<256;j++ ){
                     pRGB[j][i].r = a[i][j];
					 pRGB[j][i].g = a[i][j];
					 pRGB[j][i].b = a[i][j];
              }
       }

       // 生成BMP图片
       Snapshot( ( BYTE*)pRGB, 256, 256, "rgb.bmp" );
}