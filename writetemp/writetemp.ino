/* LED array test code
 *
 * Reads (x,y) co-ordinates from the Serial Monitor and toggles the state of
 * the LED at that co-ordinate. The co-ordinates are specified as "x y", e.g.
 * "1 2", followed by a newline. Invalid co-ordinates are rejected.
 *
 * You need to fill in all the places marked TODO.
 *
 * == Setting up the Serial Monitor ==
 * The Serial Monitor must be configured (bottom-right corner of the screen) as:
 *   - Newline (for the line ending)
 *   - Baud rate 115200
 *
 * ENGR 40M
 * July 2018
 */

// Arrays of pin numbers. Fill these in with the pins to which you connected
// your anode (+) wires and cathode (-) wires.
const byte ANODE_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

void setup() {
  // TODO: configure all anode (+) and cathode (-) wires to outputs
  // TODO: turn "off" all the LEDs
  // Hint: You did the same thing in everylight.ino.
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
  // TODO: You need to fill in this function.
  // Here's some suggested pseudocode:
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

void placeFirstNumberInPattern(byte newAddition[8][4], byte (& pattern) [8][8]) {
    for (byte i = 0; i < 8; i++) {
      for (byte j = 0; j < 4; j++) {
        pattern[i][j] = newAddition[i][j];
      }
    }
}

void placeSecondNumberInPattern(byte newAddition[8][4], byte (& pattern) [8][8]) {
    for (byte i = 0; i < 8; i++) {
      for (byte j = 4; j < 8; j++) {
        pattern[i][j] = newAddition[i][j-4];
      }
    }
}

void placeNumberInPattern(byte newAddition[8][4], bool first, byte (& pattern) [8][8]) {
  if (first) {
    placeFirstNumberInPattern(newAddition, pattern);
  }
  else {
    placeSecondNumberInPattern(newAddition, pattern);
  }
}

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

    // Print to Serial Monitor to give feedback about input
    sprintf(message, "A weather of %d degrees F was inputted.", temp);
    Serial.println(message);

    Serial.println(temp);
    if (temp >= 100 || temp <= -100) {
      handleOverHundred(ledOn);
      Serial.println("HERE");
    }
    else {
      tens_val = abs(temp) / 10;
      ones_val = abs(temp) % 10;
      Serial.println(tens_val);
      Serial.println(ones_val);
      getPattern(tens_val, true, ledOn);
      getPattern(ones_val, false, ledOn);
      if (temp < 0) {
        ledOn[0][0] = 1;
        Serial.println("NEG");
      }
    }
  }

  // This function gets called every loop
   display(ledOn);
}
