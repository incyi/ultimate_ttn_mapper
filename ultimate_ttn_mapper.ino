/*******************************************************************************
 * ttn-mapper-gps
 *
 * Send TTN packets with GPS payload for tracking via ttnmapper.org
 *
 * This code runs on an Adafruit Feather M4 Express with: 
 * - Adafruit LoRa Featherwing
 * - Adafruit GPS FeatherWing
 * - status displayed on  OLED FeatherWing
 *
 *******************************************************************************/

/**
 * Ultimate TTN Mapper with Adafruit Feather M4 Express
 * Pinout: https://learn.adafruit.com/assets/78438
 * 
 * Adafruit Quad Featherwing http://adafru.it/4254
 * Adafruit OLED Featherwing  http://adafru.it/2900
 * Adafruit GPS Featherwing http://adafru.it/3133
 * Adafruit LoRa Radio FeatherWing RadioFruit http://adafru.it/3231
 * 
 * Used libraries:
 * Adafruit_SSD1306
 * Adafruit_GFX
 * Adafruit_NeoPixel
 * 
 * Used board support packages:
 */
 
#include <lmic.h>
#include "OLED_Display.h"
#include "gps.h"
#include "pins.h"

#include <SPI.h>
#include <Wire.h>

// include the Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// NeoPixel
Adafruit_NeoPixel neopixels(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Display
OLED_Display display = OLED_Display();

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

bool toggle = false;
int i = 0;

// Init radio
extern osjob_t init_lora_job;
extern void init_lora (osjob_t* j);

// Update the display every seccond
const uint8_t update_display_interval = 1;
static osjob_t update_display_job;
static void update_display(osjob_t* j)
{
  // Update screen
  display.update();
  // Reschedule
  os_setTimedCallback(&update_display_job,
                      os_getTime() + sec2osticks(update_display_interval),
                      update_display);
}

void setup() {
  // Display splash screen
  display.init();
  delay(1000);

  // initialize the scheduler
  os_init();

  // initialize GPS
  gps_init();
  delay(2000);

  // OLED Feathewing buttons
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_C_PIN, INPUT_PULLUP);

  // NeoPixels
  delay(200); // magic delay
  neopixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  delay(200); // magic delay
  neopixels.clear();
  neopixels.setPixelColor(0, neopixels.Color(20, 20, 20));
  neopixels.setBrightness(30);
  neopixels.show();

  // Schedule jobs
  // Display updates
  os_setCallback(&update_display_job, update_display);
  // Initialize radio
  os_setCallback(&init_lora_job, init_lora);

  Serial.print("End of setup");
}

void loop() {
  // Run the scheduler
  os_runloop_once();

  if(!digitalRead(BUTTON_A_PIN)) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Menu A");  
    display.display();  
  }
  if(!digitalRead(BUTTON_B_PIN)) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Menu B");  
    display.display();
  }
  if(!digitalRead(BUTTON_C_PIN)) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Menu C");
    display.display();
  }
  toggle = true;
  digitalWrite(REDLED_PIN, toggle);    // turn the LED on by making the voltage HIGH
  if( i > 5) {
    toggle != toggle;
    digitalWrite(REDLED_PIN, toggle);    // turn the LED on/off by making the voltage HIGH/LOW
    i = 0 ;  
  }
  i++;
}
