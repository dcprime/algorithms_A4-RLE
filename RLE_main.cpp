/************************ RLE_main.cpp ************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "RLE.h"

void main(int argc, char *argv[]) {

    FILE *fp;
    FILE *fp2;
    float compressLen, decompressLen, testLen;
    int fsize, fsize2, i;
    char file1[10] = { "RLE.cpp" };
    char file2[80] = { "C:/Algorithms code/Assignment 4/Compression_RLE/Debug/Compression_RLE.exe" };

    // Buffer to test successful compression
    char testBuf1[BUFFER_LENGTH] = { "Goooooooood joooooooob duuuude!" };
    
    // Buffer to test unsuccessful compression
    char testBuf2[BUFFER_LENGTH] = { "Why won't this compress well?!!" };

    // Buffer to store compressed test strings
    char compressed1[BUFFER_LENGTH] = { NULL };

    // Buffer to store decompressed test strings
    char decompressed[BUFFER_LENGTH] = { NULL };

    // open file 1
    if (fopen_s(&fp, file1, "r") != 0) {
        printf("Error opening file1. Check path and filename.");
    }

    // get file1 length in bytes
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);

    // calloc buffer to hold contents of file 1
    char* testBuf3;
    testBuf3 = (char *)calloc(fsize, sizeof(char));

    // read file 1
    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < fsize; i++) {
        testBuf3[i] = fgetc(fp);

    }
    testBuf3[i - 1] = '\0'; // end the character array

    // calloc buffer to hold compressed contents of file 1
    char* compressed2;
    compressed2 = (char *)calloc(fsize, sizeof(char));
    
    // open file 2 (C:\Algorithms code\Assignment 4\Compression_RLE\Debug\Compression_RLE.exe)
    if (fopen_s(&fp2, file2, "rb") != 0) {
        printf("Error opening file2. Check path and filename.");
    }

    // get file2 length in bytes
    fseek(fp2, 0, SEEK_END);
    fsize2 = ftell(fp2);

    // calloc buffer to hold contents of file 2
    char* testBuf4;
    testBuf4 = (char *)calloc(fsize2+1, sizeof(char));

    // read file 2
    fseek(fp2, 0, SEEK_SET);
    fread(testBuf4, 1, fsize2, fp2);

    // calloc buffer to hold compressed contents of file 2
    char* compressed3;
    compressed3 = (char *)calloc(fsize2, sizeof(char));

    fclose(fp);
    fclose(fp2);

    // ------------------- Output Checking -------------------- //

    testLen = (float)strlen(testBuf1)+1;
    compressLen = (float)RLEncode(testBuf1, BUFFER_LENGTH, compressed1, BUFFER_LENGTH);

    printf("Uncompressed string: %s\n", testBuf1);
    printf("Compressed string: %s\n", compressed1);
    printf("Uncompressed string of length %.0f was compressed to length %.0f\n", testLen, compressLen);
    printf("Compression factor: %.3f\n\n", compressLen/testLen);

    testLen = (float)strlen(compressed1)+1;
    decompressLen = (float)(RLDecode(compressed1, strlen(compressed1), decompressed, BUFFER_LENGTH)) + 1;

    printf("Ccompressed string: %s\n", compressed1);
    printf("Decompressed string: %s\n", decompressed);
    printf("Compressed string of length %.0f was decompressed to length %.0f\n", testLen, decompressLen);
    printf("Decompression factor: %.3f\n\n", decompressLen / testLen);

    testLen = (float)strlen(testBuf2)+1;
    compressLen = (float)RLEncode(testBuf2, BUFFER_LENGTH, compressed1, BUFFER_LENGTH);

    printf("Uncompressed string: %s\n", testBuf2);
    printf("Compressed string: %s\n", compressed1);
    printf("Uncompressed string of length %.0f was compressed to length %.0f\n", testLen, compressLen);
    printf("Compression factor: %.3f\n\n", compressLen / testLen);

    // print results of file 1 compression
    testLen = (float)strlen(testBuf3);
    compressLen = (float)RLEncode(testBuf3, fsize, compressed2, fsize);

    printf("Compressing %s ...\n", file1);
    printf("Uncompressed file of size %.0f bytes was compressed to size %.0f bytes\n", testLen, compressLen);
    printf("Compression factor: %.3f\n\n", compressLen / testLen);

    // print results of file 2 compression
    testLen = (float)fsize2;
    compressLen = (float)RLEncode(testBuf4, fsize2, compressed3, fsize2);

    printf("Compressing %s ...\n", file2);
    printf("Uncompressed file of size %.0f bytes was compressed to size %.0f bytes\n", testLen, compressLen);
    printf("Compression factor: %.3f\n\n", compressLen / testLen);

    // free all calloc'd buffers
    free(testBuf3);
    free(testBuf4);
    free(compressed2);
    free(compressed3);

    system("pause");
}