# Library for Keeloq device in Microchip microcontrollers PIC series

## **Disclaimer**

**All information is provided for educational purposes only. Follow these instructions at your own risk. Neither the authors nor their employer are responsible for any direct or consequential damage or loss arising from any person or organization acting or failing to act on the basis of information contained in this page.**

## Introduction

This repository is a library for an undocumented crypto device contained in various microcontrollers PIC (Microchip Technology). A PIC microcontroller impliments [Keeloq block cipher](https://en.wikipedia.org/wiki/KeeLoq) using a undocumented internal device. This page will give information how this device works.

## Background

Several microcontrollers have a embedded crypto device. Their datasheets indicate a module on the data bus:

![Screenshot_19 1](https://github.com/y0v1737/keeloq-pic-microchip/assets/128224033/021fde53-c235-4493-a00c-c4b72de661fd)

The datasheet contains the registers that relate to this device:

![Screenshot_21](https://github.com/y0v1737/keeloq-pic-microchip/assets/128224033/75050b42-e47d-4f61-9617-24575d68eb11)

Register description doesn't have enougth information for using the Keeloq device. There are known only a few bits (GO_nDONE & ENC_nDEC) of the CRCON (crypto control) register. Keeloq a well-known block cipher where the input must be data and a key. The data block size is 32 bits, and the key length is 64 bits. The following describes how to use these five registers. How to download plaintext for encryption. How to download ciphertext for decryption.

## Registers description

Registers CRCON (crypto control register) contains two undocumented bits CRREG0 & CRREG1. They are responsible for the mode of operation of the registers CRDATAx.

|CRREG1   |CRREG0   | MODE  | DESCRIPTION  | 
|---|---|---|---|
|0|0|DATA_MODE |In this mode, plaintext or ciphertext (32 bits) is written to the registers CRDATAx. |
|0|1|MAGIC_MODE|In this mode, byte 0x42 is written to the registers CRDATA0. Unknown operation.  |
|1|0|KEY_H_MODE|In this mode, most significant part of key is written to the registers CRDATAx.  |
|1|1|KEY_L_MODE|In this mode, least significant part of key is written to the registers CRDATAx. |

|GO/nDONE   | DESCRIPTION  | 
|---|---|
|0|Process finished |
|1|Start process Keeloq encrypt or decrypt  |

|ENC/nDEC   | DESCRIPTION  | 
|---|---|
|0|Decrypt mode |
|1|Encrypt mode |

**To use the Keeloq:**
* Set the DATA_MODE in CRCON, load data into CRDATAx.
* Set the MAGIC_MODE in CRCON, load 0x42 into CRDATA0 (optional).
* Set the KEY_H_MODE in CRCON, load most significant part of key into CRDATAx.
* Set the KEY_L_MODE in CRCON, load least significant part of key into CRDATAx.
* Set the encrypt or decrypt mode in CRCON.
* Start process in CRCON.
* Wait until the process is completed.
* Set the DATA_MODE in CRCON, before read result of operation in CRDATAx.

***NOTE:*** CRDATA0 for MSB, CRDATA3 for LSB

## Supported microcontrollers

* PIC12F635 (Cryptographic module)
* PIC16F636 (Cryptographic module)
* PIC16F639 (Keeloq module)

In datasheets Keeloq device can be called differently: Cryptographic module OR Keeloq module

## Usage library

Add the header *#include "keeloq_pic.h"* into your PIC project and then you may use keeloq_decrypt & keeloq_encrypt.
```
#include <stdint.h>
#include "keeloq_pic.h"

void main(void) {
    uint8_t key[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    uint8_t plaintext[]  = {0x12, 0x34, 0x56, 0x78};
    uint8_t ciphertext[] = {0x66, 0x8d, 0x9e, 0x8c};
    uint8_t ct[4] = {0};
    uint8_t pt[4] = {0};    
    
    keeloq_encrypt(key, plaintext, ct); 
    // ct[4] = {0x66, 0x8d, 0x9e, 0x8c};    
    keeloq_decrypt(key, pt, ciphertext);
    // pt[4]  = {0x12, 0x34, 0x56, 0x78};
        
    return;
}

```

# License

Copyright (c) 2023 Yury Vasin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
