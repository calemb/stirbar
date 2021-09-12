# include <LiquidCrystal.h>

const uint8_t c8pin = 5;
const uint8_t c4pin = 4;
const uint8_t c2pin = 3;
const uint8_t c1pin = 2;

// Setup LCD screen
const int rs = 13, en = 12, d4 = 11, d5 = 8, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void WritePWM(int value){ // Writes pwm value to pin 9

  if (value < 3){
    value = 3;  
  }
  
  OCR1A = value*320/100;
  }

int ReadPWM(){ // Reads pwm from pin 10
    return 12500000/pulseIn(10, HIGH);
  }

int getVal(){
  int val = 0;
  if (digitalRead(c8pin) == HIGH){
    val = val + 8;
    }
  if (digitalRead(c4pin) == HIGH){
    val = val + 4;
    }
  if (digitalRead(c2pin) == HIGH){
    val = val + 2;
    }
  if (digitalRead(c1pin) == HIGH){
    val = val + 1;
    }

   if (val == 0){
      return 1;
    }
   
   return val;
  }

void setup() {
  // Encoder
  pinMode(c8pin, INPUT);
  pinMode(c4pin, INPUT);
  pinMode(c2pin, INPUT);
  pinMode(c1pin, INPUT);
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // Undo default configuration
  TCCR1A = 0;
  TCCR1B = 0;

  // Reset timer
  TCNT1 = 0;

  // Set timer. Source: https://forum.arduino.cc/t/arduino-uno-25khz-pwm/608666
  TCCR1A = _BV(COM1A1)
          | _BV(COM1B1)
          | _BV(WGM11);
  TCCR1B = _BV(WGM13)
          | _BV(CS10);
  ICR1 = 320;

  // Set pins
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);

  // Turn on screen
  lcd.begin(16, 2);
}

void loop() {

  lcd.clear();

  int new_rpm = getVal();
  int new_rpm_scaled = new_rpm*100/16;
  lcd.setCursor(0,0);
  lcd.print(new_rpm);

  WritePWM(new_rpm_scaled);
  lcd.setCursor(0,1);
  lcd.print(ReadPWM());
  
  delay(200);
  }