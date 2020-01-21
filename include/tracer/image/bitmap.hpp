#pragma once
#include <fstream>

#define BYTE uint8_t
#define WORD uint16_t
#define DWORD uint32_t

#define BMP_STDHEADERSIZE 7 // the standard header is 7 words long (14 bytes)
#define BMP_INFOHEADERSIZE 20 // the info header is 20 words long (40 bytes)


typedef struct tagBMPINFOHEADER {

    //field definitions
    const DWORD biSize = 2* BMP_INFOHEADERSIZE; //How many bytes long the header file is
    const DWORD biWidth; //image width
    const DWORD biHeight; // image height
    const WORD  biPlanes = 1; // how many planes, set to one
    const WORD  biBitCount = 24; //bits per color
    const DWORD biCompression= 0; //is it compressed, left at zero
    const DWORD biSizeImage;    //Compressed image size, should just be the image size
    const DWORD  biXPxlsPerMeter= 2835; //Pixels per meter? pulled from a cpp forum 
    const DWORD  biYPxlsPerMeter = 2835; // same as above
    const DWORD biClrUsed = 0; //colors used -- leave at zero
    const DWORD biClrImportant = 0; //important colors -- leave at zero

    //Array that holds the header data
    char header[2*BMP_INFOHEADERSIZE+1];

    //function to serialize the data
    void serialize()
    {
        //converts all fields of DIB header into continuous memory

        WORD* wdPtr = (WORD*)header; //pointer for words
        DWORD* dWdPtr=(DWORD*)wdPtr; //a pointer for DWORDS
        *dWdPtr = biSize; dWdPtr++;
        *dWdPtr = biWidth; dWdPtr++;
        *dWdPtr = biHeight; dWdPtr++;

        wdPtr =(WORD*) dWdPtr; //switch to a word pointer for next two fields;
        *wdPtr = biPlanes; wdPtr++;
        *wdPtr = biBitCount; wdPtr++;

        dWdPtr = (DWORD*)wdPtr; //back to DWORDS for the rest of the fields
        *dWdPtr = biCompression; dWdPtr++; 
        *dWdPtr = biSizeImage; dWdPtr++;
        *dWdPtr = biXPxlsPerMeter; dWdPtr++;
        *dWdPtr = biYPxlsPerMeter; dWdPtr++;
        *dWdPtr = biClrUsed; dWdPtr++;
        *dWdPtr = biClrImportant;
    }
    //constructor
    tagBMPINFOHEADER(int width, int height) : biWidth(width), biHeight(height), biSizeImage((DWORD)(width * height * 3))
    {
        header[2*BMP_INFOHEADERSIZE]='\0'; //put a string escape at the end
        serialize();
    }
} BMPINFOHEADER, * PBMPINFOHEADER;


typedef struct tagBMPSTANDARDHEADER
{
    //field definitions
    const WORD biSignature='MB'; //standard header calling out a bmp file
    const DWORD biFileSize; //size of the file in bytes
    const DWORD biReserved=0; //reserved 
    const DWORD biPixelOffset = 2 * (BMP_STDHEADERSIZE + BMP_INFOHEADERSIZE);//where the first pixel data is

    //Array that holds the header data
    char header[2*BMP_STDHEADERSIZE+1]; 

    //Method to serialize the data
    void serialize()
    {
        WORD* wdPtr = (WORD*) header; //make a pointer to the start of the header object
        *wdPtr = biSignature; wdPtr ++;
        //Everything else is dword so change the pointer type
        auto* dWdPtr = (DWORD*)wdPtr;
        *dWdPtr = biFileSize; dWdPtr++;
        *dWdPtr = biReserved; dWdPtr++;
        *dWdPtr = biPixelOffset;
    }

    //constructor
    tagBMPSTANDARDHEADER(int width, int height): biFileSize((DWORD)(width* height * 3 + 2*(BMP_STDHEADERSIZE+BMP_INFOHEADERSIZE)))
    {
        header[2 * BMP_STDHEADERSIZE] = '\0'; //put a string escape at the end
        serialize();
    }
    //destructor
    ~tagBMPSTANDARDHEADER()
    {
    }
} BMPSTANDARDHEADER, * PBMPSTANDARDHEADER;
