//#include <FastLED.h>
//#include <EEPROM.h>
#define LED_PIN     7
#define b1   2
#define b2   3
#define b3   4
#define b4   5
#define b5   6
//#define NUM_LEDS    20

int bS1 = 0;
int bS2 = 0;
int bS3 = 0;
int bS4 = 0;
int bS5 = 0;

//CRGB leds[NUM_LEDS];

void setup() {
//  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
//  FastLED.setBrightness(1);
//  pinMode(LED_PIN,OUTPUT);
  pinMode(b1,INPUT_PULLUP);
  pinMode(b2,INPUT_PULLUP);
  pinMode(b3,INPUT_PULLUP);
  pinMode(b4,INPUT_PULLUP);
  pinMode(b5,INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() {
  bS1 = digitalRead(b1);
  bS2 = digitalRead(b2);
  bS3 = digitalRead(b3);
  bS4 = digitalRead(b4);
  bS5 = digitalRead(b5);
//  Serial.println(bS1);
//  Serial.println(bS2);
//  Serial.println(bS3);
//  Serial.println(bS4);
//  Serial.println(bS5);
  if(bS1 == 0){ Serial.println(F("yes1")); }
  if(bS2 == 0){ Serial.println("yes2"); }
  if(bS3 == 0){ Serial.println("yes3"); }
  if(bS4 == 0){ Serial.println("yes4"); }
  if(bS5 == 0){ Serial.println("yes5"); }
  delay(1000);
  //Serial.println("New");
}

  if(bS1 == 0){
    for (int i = 0; i <= 19; i++){
      leds[i] = CRGB ( 0, 0, 255);
      FastLED.show();
      delay(40);
    }
    for (int i = 19; i >= 0; i--){
      leds[i] = CRGB ( 255, 0, 0);
      FastLED.show();
      delay(40);
    }
      //digitalWrite(LED_PIN,HIGH);
      //Serial.println("PUSHED");
