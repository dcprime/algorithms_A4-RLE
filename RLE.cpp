/************************ RLE_.cpp ************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "RLE.h"

unsigned char cEsc = 0x1b;
int count;

int RLEncode(char iBuf[], int iInLen, char oBuf[], int iOutMax) {
    
    int out = 0;

    for (int i = 0; i < iInLen;) {
        // count number of identical successive chars in the input buffer at position i
        count = count_successive(iBuf, i, ENCODE);

        // check for overflow
        if ((count + out) > iOutMax) return(FALSE);

        // encode char(s) to output buffer, tracking output position with "out"
        out += emit(iBuf[i], count, oBuf, out);

        // set value of i (given repeated letters)
        i += count;
    }
    return(out);
}

int emit(char input_char, int count, char oBuf[], int out) {

    int total;

    if (input_char == cEsc) {
        switch (count) {
        case 1:
            // single cEsc encoding
            oBuf[out] = cEsc;
            oBuf[out + 1] = 0;
            total = 2;
            break;
        case 2:
            // double cEsc encoding
            oBuf[out] = cEsc;
            oBuf[out + 1] = 0x01;
            total = 2;
            break;
        default:
            // 3+ cEsc encoding
            oBuf[out] = cEsc;
            oBuf[out + 1] = 0x02;
            oBuf[out + 2] = count;
            total = 3;
            break;
        }
    }
    else {
        switch (count)
        {
        case 1:
            // single char encoding
            oBuf[out] = input_char;
            total = 1;
            break;
        case 2:
            // double char encoding
            oBuf[out] = input_char;
            oBuf[out + 1] = input_char;
            total = 2;
            break;
        default:
            // 3+ char encoding
            oBuf[out] = cEsc;
            oBuf[out + 1] = count;
            oBuf[out + 2] = input_char;
            total = 3;
            break;
        }
    }
    return(total);
}

int RLDecode(char iBuf[], int iInLen, char oBuf[], int iOutMax) {

    int out = 0;
    char output_char;
    int i = 0;

    for (i = 0; i < iInLen;) {

        // count number of identical successive chars in the input buffer at position i
        count = count_successive(iBuf, i, DECODE);

        // check for overflow
        if ((count + out) > iOutMax) return(0);

        // set output_char (check if cEsc is in actual message)
        if (iBuf[i] == cEsc && count < 3) output_char = cEsc;
        else if (count < 3) output_char = iBuf[i];
        else output_char = iBuf[i + 2];

        // encode char(s) to output buffer, tracking output position with "out"
        out += emit2(output_char, count, oBuf, out);

        if (count > 2) {
            i += 3;
        }
        else {
            i += count;
        }
    }
    return(out);
}


int emit2(char output_char, int count, char oBuf[], int out) {
    for (int i = 0; i < count; i++) {
        oBuf[i + out] = output_char;
    }
    return(count);
}

int count_successive(char iBuf[], int i, int coding) {
    
    int total = 1;

    switch (coding) 
    {
    case ENCODE:
        while (iBuf[i] == iBuf[i + 1]) {
            total++;
            i++;
            if (total > 255) {
                break;
            }
        }
        break;
    case DECODE:
        if (iBuf[i] == cEsc) {
            switch ((int)iBuf[i + 1]) {
            case 0:
                total = 1;
                break;
            case 1:
                total = 2;
                break;
            default:
                total = (int)iBuf[i + 1];
                break;
            }
        }
        else {
            total = 1;
        }
        break;
    }
    return (total);
}