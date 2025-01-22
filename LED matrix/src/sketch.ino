const int rowPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Row pins
const int colPins[] = {10, 11, 12, 13, A0, A1, A2, A3}; // Column pins

void setup() {
  // Initialize row and column pins
  for (int i = 0; i < 8; i++) {
    pinMode(rowPins[i], OUTPUT); 
    pinMode(colPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW); 
    digitalWrite(colPins[i], HIGH);
  }
  pinMode(A4, INPUT); // Input pin for a button or sensor (A4)
  Serial.begin(9600);
  Serial.println("Hi");
  Serial.println("Enter [M] key or [T] key on your keyboard: ");
}

void loop() {
  // Check if the button or sensor at A4 is pressed
  if (digitalRead(A4 == HIGH)) {
    char input = Serial.read();  // Read input from the serial
    if (input == 'M' || input == 'm') {
      // If user enters 'M' or 'm', display "M" pattern on the LED matrix
      
      lightUpLED(7, 0); 
      lightUpLED(7, 7);
      delay(100);    
      clearMatrix();           
      delay(100);

      lightUpLED(6, 0); 
      lightUpLED(6, 7);
      delay(100);
      clearMatrix();
      delay(100);

      lightUpLED(5, 0); 
      lightUpLED(5, 7);
      delay(100);
      clearMatrix();
      delay(100);

      lightUpLED(4, 0); 
      lightUpLED(4, 7);
      delay(100);
      clearMatrix();
      delay(100);

      lightUpLED(3, 0); 
      lightUpLED(3, 7);
      delay(100);
      clearMatrix();
      delay(100);

      lightUpLED(2, 0); 
      lightUpLED(2, 7);
      delay(100);
      clearMatrix();
      delay(100);

      lightUpLED(1, 0); 
      lightUpLED(1, 7);
      delay(100);
      clearMatrix();

      lightUpLED(0, 0); 
      lightUpLED(0, 7);
      delay(100);
      clearMatrix();

      lightUpLED(1, 1); 
      lightUpLED(1, 6);
      delay(100);
      clearMatrix();
      delay(100);

      lightUpLED(2, 2); 
      lightUpLED(2, 5);
      delay(100);
      clearMatrix();
      delay(100);

      lightUpLED(3, 3); 
      lightUpLED(3, 4);
      delay(100);
      clearMatrix();
      delay(100);

      Serial.println("M pattern is finished"); // Notify that the "M" pattern is complete
    }
  }


  if (Serial.available() > 0) {
    char input = Serial.read();  // Read input from the serial
    if (input == 'T' || input == 't') {
      // If user enters 'T' or 't', display "T" pattern on the LED matrix
      

      lightUpLED(7, 3); 
      lightUpLED(7, 4);
      delay(100);
      clearMatrix();

      lightUpLED(6, 3); 
      lightUpLED(6, 4);
      delay(100);
      clearMatrix();

      lightUpLED(5, 3); 
      lightUpLED(5, 4);
      delay(100);
      clearMatrix();

      lightUpLED(4, 3); 
      lightUpLED(4, 4);
      delay(100);
      clearMatrix();

      lightUpLED(3, 3); 
      lightUpLED(3, 4);
      delay(100);
      clearMatrix();

      lightUpLED(2, 3); 
      lightUpLED(2, 4);
      delay(100);
      clearMatrix();

      lightUpLED(6, 3); 
      lightUpLED(4, 4);
      delay(100);
      clearMatrix();
    
      lightUpLED(0, 0); 
      lightUpLED(1, 0);
      lightUpLED(0, 7); 
      lightUpLED(1, 7);
      delay(100);
      clearMatrix();


      lightUpLED(0, 1); 
      lightUpLED(1, 1);
      lightUpLED(0, 6); 
      lightUpLED(1, 6);
      delay(100);
      clearMatrix();

      lightUpLED(0, 2); 
      lightUpLED(1, 2);
      lightUpLED(0, 5); 
      lightUpLED(1, 5);
      delay(100);
      clearMatrix();

      lightUpLED(0, 3); 
      lightUpLED(1, 3);
      lightUpLED(0, 4); 
      lightUpLED(1, 4);
      delay(100);
      clearMatrix();

      Serial.println("T pattern is finished"); // Notify that the "T" pattern is complete
    }
  }
}

// Function to light up a specific LED on the matrix
void lightUpLED(int row, int col) {
  digitalWrite(rowPins[row], HIGH);   // Enable the row
  digitalWrite(colPins[col], LOW);    // Enable the column (LED on)
}

// Function to turn off all LEDs on the matrix (clear matrix)
void clearMatrix() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(rowPins[i], LOW);   // Turn off each row
    digitalWrite(colPins[i], HIGH);  // Turn off each column
  }
}
