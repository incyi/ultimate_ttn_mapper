 /**
  * Adafruit Feather M4 Express - Featuring ATSAMD51
  * IO Pin-out
  * ------------------ Bat, En, USB, 13, 12, 11,  10,  9,  6,  5, SCL, SDA
  * Rst, 3V, Aref, GND, A0, A1,  A2, A3, A4, A5, SCK, MO, MI, RX,  TX,  D4
  */

#define RFM95_DIO1    A0 // A0 // Radio FeatherWing pins for Cortex-M4
#define RFM95_DIO0    A1 // A1 // Radio FeatherWing pins for Cortex-M4
#define RFM95_CS      A2 // A2 // Radio FeatherWing pins for Cortex-M4
#define RFM95_RST     A3 // A3 // Radio FeatherWing pins for Cortex-M4
#define A4_PIN        A4 // A4 // Empty
#define A5_PIN        A5 // A5 // Empty
#define battery_pin   A6 // LiPo battery measurement pin

#define Pin_D4        4  // "4" // Empty
#define BUTTON_C_PIN  5  // OLED Featherwing Button C
#define BUTTON_B_PIN  6  // OLED Featherwing Button B
#define NEOPIXEL_PIN  8  // Single NeoPixel on Adafruit Feather M4 Express
#define BUTTON_A_PIN  9  // OLED Featherwing Button A
#define Pin_D10       10 // "10" // Empty
#define Pin_D11       11 // "11" // Empty
#define Pin_D12       12 // "12" // Empty
#define REDLED_PIN    13 // Red Led

#define OLED_I2C_ADDRESS 0x3C // i2c address for the OLED Featherwing Address 0x3C for 128x32
