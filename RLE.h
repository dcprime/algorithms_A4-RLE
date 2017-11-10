#pragma once

/* RLE.h: Header file for RLE functions and definitions */

/******************* define constants  ********************/

#define BUFFER_LENGTH 32
#define FALSE 0

/************************ definitions ***************************/

enum EorD { ENCODE, DECODE};

/******************** function prototypes ***********************/

// Encode buffer using RLE compression
int RLEncode(char iBuf[], int iInLen, char oBuf[], int iOutMax);

// Decode buffer created using RLE compression
int RLDecode(char iBuf[], int iInLen, char oBuf[], int iOutMax);

// Write compressed data to the output buffer using RLE compression
int emit(char input_char, int count, char oBuf[], int out);

// Write uncompressed data to the output buffer using RLE decompression
int emit2(char output_char, int count, char oBuf[], int out);

// Count number of successive letters in a section of the buffer
int count_successive(char iBuf[], int i, int coding);