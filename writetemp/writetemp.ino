/* Code to display a given temperature
 *
 * Reads in the temperature from the Serial Monitor and shows that number
 * on the LED display. The range of temperatures that can be shown are -99 to 99.
 * The top-left LED indicates if the temperature is positive or negative; if that
 * LED is on, then the temperature displayed is negative. A sad face will be shown
 * on the LED display for temperatures above 99 or below -99.
 * *
 * == Setting up the Serial Monitor ==
 * The Serial Monitor must be configured (bottom-right corner of the screen) as:
 *   - Newline (for the line ending)
 *   - Baud rate 115200
 *
 * ENGR 40M
 * February 2020
 */

// Arrays of pin numbers. Fill these in with the pins to which you connected
// your anode (+) wires and cathode (-) wires.
const byte ANODE_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

void setup() {
  // Configure all anode (+) and cathode (-) wires to outputs
  // Turn "off" all the LEDs
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
    
    digitalWrite(ANODE_PINS[i], HIGH); 
    digitalWrite(CATHODE_PINS[i], HIGH);
  }

  // Initialize serial communication
  // (to be read by Serial Monitor on your computer)
  Serial.begin(115200);
  Serial.setTimeout(100);
}

/* Function: display
 * -----------------
 * Runs through one multiplexing cycle of the LEDs, controlling which LEDs are
 * on.
 *
 * During this function, LEDs that should be on will be turned on momentarily,
 * one row at a time. When this function returns, all the LEDs will be off
 * again, so it needs to be called continuously for LEDs to be on.
 */
void display(byte pattern[8][8]) {
  // Pseudocode for this display function:
  //   for each anode (+/row) wire
  //     for each cathode (-/column) wire
  //       look up in pattern whether this LED should be on or off
  //       if LED should be on, activate cathode (-) wire, else deactivate it
  //     end for
  //     activate anode (+) wire
  //     wait a short time (hint: try delayMicroseconds())
  //     deactivate anode (+) wire
  //   end for

  for(byte i = 0; i < 8; i++){
    for(byte j = 0; j < 8; j++){
      if(pattern[i][j]){
        digitalWrite(CATHODE_PINS[j], LOW);
      } else{
        digitalWrite(CATHODE_PINS[j], HIGH);
      }
    }
    
    digitalWrite(ANODE_PINS[i], LOW);
    delayMicroseconds(100);
    digitalWrite(ANODE_PINS[i], HIGH);
  }
}

/* Function: handleOverHundred
 * -----------------
 * Creates the sad face pattern to show on the LED display when the absolute 
 * value of the temperature is greater than or equal to a hundred
 */
void handleOverHundred(byte (& pattern) [8][8]) {
    static byte newAddition[8][8] = {
                    {0,0,0,0,0,0,0,0},
                    {0,0,1,0,0,1,0,0},
                    {0,0,1,0,0,1,0,0},
                    {0,0,1,0,0,1,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,1,1,1,1,0,0},
                    {0,1,0,0,0,0,1,0},
                    {1,0,0,0,0,0,0,1} };
    for (byte i = 0; i < 8; i++) {
      for (byte j = 0; j < 8; j++) {
        pattern[i][j] = newAddition[i][j];
      }
    }
}

/* Function: placeFirstNumberInPattern
 * -----------------
 * Copies the matrix for one digit (newAddition) into the appropriate spot on the
 * pattern for the LED display, specifically the first spot or the tens place
 */
void placeFirstNumberInPattern(byte newAddition[8][4], byte (& pattern) [8][8]) {
    for (byte i = 0; i < 8; i++) {
      for (byte j = 0; j < 4; j++) {
        pattern[i][j] = newAddition[i][j];
      }
    }
}

/* Function: placeSecondNumberInPattern
 * -----------------
 * Copies the matrix for one digit (newAddition) into the appropriate spot on the
 * pattern for the LED display, specifically the second spot or the ones place
 */
void placeSecondNumberInPattern(byte newAddition[8][4], byte (& pattern) [8][8]) {
    for (byte i = 0; i < 8; i++) {
      for (byte j = 4; j < 8; j++) {
        pattern[i][j] = newAddition[i][j-4];
      }
    }
}

/* Function: placeNumberInPattern
 * -----------------
 * Depending on the value of the first boolean, call the appropriate function to copy the 
 * matrix for one digit (newAddition) into the appropriate spot on the pattern for the LED display 
 */
void placeNumberInPattern(byte newAddition[8][4], bool first, byte (& pattern) [8][8]) {
  if (first) {
    placeFirstNumberInPattern(newAddition, pattern);
  }
  else {
    placeSecondNumberInPattern(newAddition, pattern);
  }
}

/* Function: getPattern
 * -----------------
 * Get and place the correct manually-created pattern for the digit that we want to show
 * on the LED display
 */
void getPattern(byte digit, bool first, byte (& pattern) [8][8]) {
  if (digit == 0) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {1,1,1,1},
                    {1,0,0,1},
                    {1,0,0,1},
                    {1,0,0,1},
                    {1,0,0,1},
                    {1,0,0,1},
                    {1,1,1,1} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  else if (digit == 1) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {0,0,1,0},
                    {0,1,1,0},
                    {1,0,1,0},
                    {0,0,1,0},
                    {0,0,1,0},
                    {0,0,1,0},
                    {1,1,1,1} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  else if (digit == 2) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {1,1,1,1},
                    {0,0,0,1},
                    {0,0,0,1},
                    {1,1,1,1},
                    {1,0,0,0},
                    {1,0,0,0},
                    {1,1,1,1} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  else if (digit == 3) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {1,1,1,1},
                    {0,0,0,1},
                    {0,0,0,1},
                    {1,1,1,1},
                    {0,0,0,1},
                    {0,0,0,1},
                    {1,1,1,1} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  else if (digit == 4) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {1,0,1,0},
                    {1,0,1,0},
                    {1,0,1,0},
                    {1,1,1,1},
                    {0,0,1,0},
                    {0,0,1,0},
                    {0,0,1,0} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  else if (digit == 5) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {1,1,1,1},
                    {1,0,0,0},
                    {1,0,0,0},
                    {1,1,1,1},
                    {0,0,0,1},
                    {0,0,0,1},
                    {1,1,1,1} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  else if (digit == 6) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {1,0,0,0},
                    {1,0,0,0},
                    {1,0,0,0},
                    {1,1,1,1},
                    {1,0,0,1},
                    {1,0,0,1},
                    {1,1,1,1} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  else if (digit == 7) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {1,1,1,1},
                    {1,0,0,1},
                    {0,0,0,1},
                    {0,0,0,1},
                    {0,0,0,1},
                    {0,0,0,1},
                    {0,0,0,1} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  else if (digit == 8) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {1,1,1,1},
                    {1,0,0,1},
                    {1,0,0,1},
                    {1,1,1,1},
                    {1,0,0,1},
                    {1,0,0,1},
                    {1,1,1,1} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  else if (digit == 9) {
    static byte newAddition[8][4] = {
                    {0,0,0,0},
                    {1,1,1,1},
                    {1,0,0,1},
                    {1,0,0,1},
                    {1,1,1,1},
                    {0,0,0,1},
                    {0,0,0,1},
                    {0,0,0,1} };
    placeNumberInPattern(newAddition, first, pattern);
  }
  // Check that the correct pattern is printed
  for (byte i = 0; i < 8; i++) {
    for (byte j = 0; j < 8; j++) {
      Serial.print(pattern[i][j]);
    }
  }
}

void loop() {
  // use 'static' so that it retains its value between successive calls of loop()
  static byte ledOn[8][8];

  int temp = 0;
  int tens_val = 0;
  int ones_val = 0;
  static char message[60];

  if (Serial.available()) {
    // Parse the values from the serial string
    temp = Serial.parseInt();

    // Check for input validity
    if (Serial.read() != '\n') {
      Serial.println("invalid input - check that line ending is set to \"Newline\"; input must be one number");
      return;
    }

    // Print a message to Serial Monitor to state what the input was
    sprintf(message, "A weather of %d degrees was inputted.", temp);
    Serial.println(message);
    
    if (temp >= 100 || temp <= -100) {
      // Handle the case where the inputted temperature is greater than or equal to 100
      // or less than or equal to -100
      handleOverHundred(ledOn);
    }
    else {
      // Otherwise get the numbers and patterns that should be in the tens and ones spots
      tens_val = abs(temp) / 10;
      ones_val = abs(temp) % 10;
      getPattern(tens_val, true, ledOn);
      getPattern(ones_val, false, ledOn);
      // Turn on the indictor LED (top-left corner) if the temperature is negative
      if (temp < 0) {
        ledOn[0][0] = 1;
      }
    }
  }

  // Display the final pattern on the LED display
   display(ledOn);
}
