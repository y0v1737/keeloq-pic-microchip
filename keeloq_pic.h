#define CRCON CRCON
extern volatile unsigned char           CRCON                __at(0x110);

typedef struct {
    unsigned CRREG0                 :1;
    unsigned CRREG1                 :1;
    unsigned reserve                :4;
    unsigned ENC_DEC                :1;
    unsigned GO_nDONE               :1;
}CRCON_bits_t;
extern volatile CRCON_bits_t CRCON_bits __at(0x110);

#define CRDATA0 CRDATA0
extern volatile unsigned char           CRDATA0              __at(0x111);

#define CRDATA1 CRDATA1
extern volatile unsigned char           CRDATA1              __at(0x112);

#define CRDATA2 CRDATA2
extern volatile unsigned char           CRDATA2              __at(0x113);

#define CRDATA3 CRDATA3
extern volatile unsigned char           CRDATA3              __at(0x114);

enum MODE_CRCON            
{
    DATA_MODE  = 0, // mode for load & uploadciphertext/plaintext in CRDATA 
    MAGIC_MODE = 1, // mode for load 0x42 in CRDATA0
    KEY_H_MODE = 2, // mode for load high part of key in CRDATA     
    KEY_L_MODE = 3, // mode for load low part of key in CRDATA 
};

uint8_t keeloq_set_key(const uint8_t* key);
uint8_t keeloq_decrypt(const uint8_t* key, uint8_t* plaintext, const uint8_t* ciphertext);
uint8_t keeloq_encrypt(const uint8_t* key, const uint8_t* plaintext, uint8_t* ciphertext);