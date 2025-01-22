#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

Servo servoMotor;
LiquidCrystal_I2C lcd(0x27, 20, 4);

int pirPin = 2;          // PIR sensor pin
int potPin = A0;         // Potentiometer pin
int buzzerPin = 8;       // Buzzer pin
int pirState = LOW;      // PIR sensor state
int potValue = 0;        // Potentiometer value

// Melody notes
int melody[] = {
  NOTE_C4, NOTE_G4, NOTE_A4, NOTE_G4, 0, NOTE_B4, NOTE_C5
};

// Duration of each note
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4
};

// Custom character design for plane and bullet
byte planeChar[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100
};

byte bulletChar[8] = {
  0b00000,
  0b00100,
  0b00100, 
  0b00100, 
  0b00100, 
  0b00100, 
  0b00000,
  0b00000
};

// Custom character design for "MT" logo
byte MChar[8] = {
  0b10101,
  0b11111,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b00000
};

byte TChar[8] = {
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};

void setup() {
  pinMode(pirPin, INPUT);
  servoMotor.attach(9);  // Servo motor pin
  lcd.init();
  lcd.backlight();

  // Create custom characters
  lcd.createChar(0, planeChar);
  lcd.createChar(1, bulletChar);
  lcd.createChar(2, MChar);
  lcd.createChar(3, TChar);

  // Display MT logo
  lcd.setCursor(0, 0);
  lcd.write(2); // Display M
  lcd.write(3); // Display T
  delay(2000);
  lcd.clear();

  // Display airplane animation
  lcd.print("Playing Animation");
  playAnimation();
}

void loop() {
  // Read PIR sensor status
  int pirValue = digitalRead(pirPin);
  if (pirValue == HIGH && pirState == LOW) {
    pirState = HIGH;
    playMelody();               // Start playing music when movement is detected
  } else if (pirValue == LOW && pirState == HIGH) {
    pirState = LOW;
    noTone(buzzerPin);          // Stop music if no movement is detected
  }

  // Read potentiometer value and set servo angle
  potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, 0, 180);
  servoMotor.write(angle);
}

// Function to play melody
void playMelody() {
  for (int i = 0; i < 7; i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(buzzerPin, melody[i], noteDuration); // Play note on buzzer
    delay(300); // Short delay between notes
  }
}


// Function to display animation
void playAnimation() {
  int planePosition = 0; // Initial position of the plane
  int bulletPosition = -1; // Initial position of the bullet (-1 means no bullet on screen)

  for (int i = 0; i < 30; i++) { // Repeat the animation for 30 cycles
    lcd.clear();

    // Display the plane horizontally
    lcd.setCursor(planePosition, 1); // Position the plane on the second row
    lcd.write(0); // Show the plane character

    // Check if a bullet is currently active
    if (bulletPosition >= 0) {
      lcd.setCursor(bulletPosition, 0); // Display bullet on the first row
      lcd.write(1);                    // Show bullet character
      bulletPosition++;                // Move bullet to the right

      // If the bullet moves off the screen, deactivate it
      if (bulletPosition >= 16) {
        bulletPosition = -1; // Reset bullet
      }
    }

    // Simulate shooting a bullet
    if (i % 5 == 0 && bulletPosition == -1) { // Fire a bullet every 5th cycle if no bullet is active
      bulletPosition = planePosition + 1; // Start bullet right after the plane
    }

    // Move the plane to the next position
    planePosition++;
    if (planePosition >= 15) { // If the plane reaches the end of the screen
      planePosition = 0;       // Reset its position to the start
    }

    delay(100); 
  }

  lcd.clear();
  lcd.print("End Animation"); 
}