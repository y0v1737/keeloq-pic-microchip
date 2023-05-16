#include <stdint.h>
#include "keeloq_pic.h"

uint8_t keeloq_set_key(const uint8_t* key){
    CRCON = MAGIC_MODE;
    CRDATA0 = 0x42; 

    CRCON = KEY_H_MODE;    
    CRDATA0 = key[7];  
    CRDATA1 = key[6]; 
    CRDATA2 = key[5]; 
    CRDATA3 = key[4]; 

    CRCON = KEY_L_MODE;            
    CRDATA0 = key[3];  
    CRDATA1 = key[2]; 
    CRDATA2 = key[1]; 
    CRDATA3 = key[0];  

    return 1;
}

uint8_t keeloq_decrypt(const uint8_t* key, uint8_t* plaintext, const uint8_t* ciphertext){
    CRCON = DATA_MODE;    
    CRDATA0 = ciphertext[3];  
    CRDATA1 = ciphertext[2]; 
    CRDATA2 = ciphertext[1]; 
    CRDATA3 = ciphertext[0];
    
    keeloq_set_key(key);

    CRCON_bits.ENC_DEC = 0; // set decrypt mode
    CRCON_bits.GO_nDONE = 1; // start process
    
    while(CRCON_bits.GO_nDONE); // wait decrypt process
    
    CRCON = DATA_MODE; // end operation - update CRDATA
    
    plaintext[3] = CRDATA0;  
    plaintext[2] = CRDATA1; 
    plaintext[1] = CRDATA2; 
    plaintext[0] = CRDATA3;

    return 1;
}

uint8_t keeloq_encrypt(const uint8_t* key, const uint8_t* plaintext, uint8_t* ciphertext){
    CRCON = DATA_MODE;    
    CRDATA0 = plaintext[3];  
    CRDATA1 = plaintext[2]; 
    CRDATA2 = plaintext[1]; 
    CRDATA3 = plaintext[0];
    
    keeloq_set_key(key);
    
    CRCON_bits.ENC_DEC = 1; // set encrypt mode
    CRCON_bits.GO_nDONE = 1; // start process
    
    while(CRCON_bits.GO_nDONE); // wait encrypt process
    
    CRCON = DATA_MODE; // end operation - update CRDATA
    
    ciphertext[3] = CRDATA0;  
    ciphertext[2] = CRDATA1; 
    ciphertext[1] = CRDATA2; 
    ciphertext[0] = CRDATA3;
       
    return 1;
}