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
    
    eeprom_write(0x40, pt[0]);
    eeprom_write(0x44, pt[1]);
    eeprom_write(0x48, pt[2]);
    eeprom_write(0x4C, pt[3]); 
    
    eeprom_write(0x50, ct[0]);
    eeprom_write(0x54, ct[1]);
    eeprom_write(0x58, ct[2]);
    eeprom_write(0x5C, ct[3]); 
    
    return;
}
