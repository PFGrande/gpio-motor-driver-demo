// #define PCA_CHANNEL 0x06

// should I use auto increment mode so i can reduce this to just LED0???
// does it even work like that?
#define LED0_ON_L   0x06
#define LED0_ON_H   0x07
#define LED0_OFF_L  0x08
#define LED0_OFF_H  0x09

#define MODE_REGISTER_1 0x00

/* "The PRE_SCALE register can only be set
 when the SLEEP bit of MODE1 register is set to logic 1." 
 (PCA96_datasheet, 24)*/
// the value used to determine the circuit's frequency
#define PRE_SCALE_REGISTER 0xFE
