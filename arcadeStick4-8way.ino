// Arcade gate switcher v0.1 by VariableBits
// This is free to use.

#include<Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define P1Servo_PIN   3
#define P2Servo_PIN   4
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Servo joystick1Switch;
Servo joystick2Switch;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int p1servoAngle = 0;
char key = 0;
int playerButton = 11;
int p1val = 0;
int p1State = 0;    // 2 = 8 way, 1 = 4 way, 0 = 4 way diagonal
int p2State = 0;
int p1_4way_val = 40;
int p1_4Dway_val = 105;
int p1_8way_val = 92;
int p2_4way_val = 0;
int p2_4Dway_val = 45;
int p2_8way_val = 170;
int x = 0;
int minX = 0;

char message[] = "P1: 4-Way Diagonal";


void setup() {
  // put your setup code here, to run once:
  joystick1Switch.attach(P1Servo_PIN, 1000, 500);
  joystick2Switch.attach(P2Servo_PIN, 1000, 500);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x1B)) { // Replace 0x1B with address for your screen
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  display.clearDisplay();
  
  Serial.begin(19200);
  pinMode(playerButton, INPUT);     // left player
  
  // run once
  joystick1Switch.write(0);                                  //move servo to 60 deg
  delay(500);                                           //wait for 500ms

  joystick1Switch.write(p1_8way_val);            // default 8 way p1
  p1State=2;
  delay(500);

  joystick2Switch.write(0);                                  //move servo to 60 deg
  delay(500);                                           //wait for 500ms

  joystick2Switch.write(p2_8way_val);            // default 8 way p2
  p2State=2;
  delay(500);

  display.invertDisplay(false);
  display.setRotation(0);
  display.setTextWrap(false);
  x = display.width();
  minX = -12 * strlen(message);

  joystick1Switch.detach();
  joystick2Switch.detach();
  display_state();
}

void loop() {
  p1val = digitalRead(playerButton);   // read player 1
  display_state();
  if(p1val == HIGH) {
    if(p1State == 0) {
      
      Serial.print("Switching controls to 4-way\n");
      joystick1Switch.attach(P1Servo_PIN, 1000, 500);
      joystick2Switch.attach(P2Servo_PIN, 1000, 500);
      
      joystick1Switch.write(0);                                  //move servo to 60 deg
      delay(500);                                           //wait for 500ms
  
      joystick1Switch.write(p1_4way_val);
      delay(500);      
      joystick2Switch.write(0);                                  //move servo to 60 deg
      delay(500);                                           //wait for 500ms
  
      joystick2Switch.write(p2_4way_val);
      delay(500);      
      
      p1State = 1;
      p2State = 1;
      display_state();
      joystick1Switch.detach();
      joystick2Switch.detach();
    } else if(p1State == 1) {
      joystick1Switch.attach(P1Servo_PIN, 1000, 500);
      joystick2Switch.attach(P2Servo_PIN, 1000, 500);
      Serial.print("Switching controls to 8-way\n");
      joystick1Switch.write(0);                                  //move servo to 60 deg
      delay(500);                                           //wait for 500ms
      
      joystick1Switch.write(p1_8way_val);
      delay(500);

      joystick2Switch.write(0);                                  //move servo to 60 deg
      delay(500);                                           //wait for 500ms
      
      joystick2Switch.write(p2_8way_val);
      delay(500);
      
      p1State = 2;
      p2State = 2;
      display_state();      
      joystick1Switch.detach();
      joystick2Switch.detach();
    } else if (p1State == 2) {
      joystick1Switch.attach(P1Servo_PIN, 1000, 500);
      joystick2Switch.attach(P2Servo_PIN, 1000, 500);
      Serial.print("Switching controls to 4-way Diagnol\n");
      joystick1Switch.write(0);                                  //move servo to 60 deg
      delay(500);                                           //wait for 500ms
      
      joystick1Switch.write(p1_4Dway_val);
      delay(500);
      
      joystick2Switch.write(0);                                  //move servo to 60 deg
      delay(500);                                           //wait for 500ms
      
      joystick2Switch.write(p2_4Dway_val);
      delay(500);
      
      p1State = 0;
      p2State = 0;
      display_state();
      joystick1Switch.detach();
      joystick2Switch.detach();
    }
    delay(1000);
  }
}

void display_state()
{
  display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(F("VariableBits\nGate Switcher")); // Change to whatever you like.
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 28);
    if (p1State == 0)
    {
      display.setCursor(x, 28);
      display.println(F("P1: 4-Way Diagonal"));
      x = x -3;
      if(x < minX) x = display.width();
    }
    else if(p1State == 2)    
      display.println(F("P1: 8-Way"));
    else if(p1State == 1)
      display.println(F("P1: 4-Way"));
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 48);
    if (p2State == 0)
    {
      display.setCursor(x, 48);
      display.println(F("P2: 4-Way Diagonal"));
      x = x -3;
      if(x < minX) x = display.width();
    }
    else if(p2State == 2)
      display.println(F("P2: 8-Way"));
    else if(p2State == 1)
      display.println(F("P2: 4-Way"));
    display.display();

}
