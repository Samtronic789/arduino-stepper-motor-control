#include <Arduino.h>

// Define pins
// #define STEP_PIN 12        // Step pin of stepper driver
// #define DIR_PIN 14         // Direction pin of stepper driver
// #define ENABLE_PIN 13      // Enable pin of stepper driver
#define STEP_PIN 12
#define DIR_PIN 14
#define ENABLE_PIN 13
//#define SLOT_LIMIT_SWITCH 2
// Movement parameters
#define STEP_DELAY 50     // Microseconds between steps (lower = faster rotation)
#define STEPS_TO_MOVE 2000 // Number of steps to move

// Direction control
bool moveUpward = true;    // Direction flag: true = up, false = down

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("Stepper Motor Direction Control");
  
  // Configure pins
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  
  // Ensure motor is initially stopped
  digitalWrite(ENABLE_PIN, HIGH); // Disable driver (most drivers are active LOW)
  
  // Print instructions
  Serial.println("Send commands:");
  Serial.println("'u' - Move Up");
  Serial.println("'d' - Move Down");
  Serial.println("'s' - Stop");
}

void loop() {
  // Check for serial commands
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    if (command == 'u' || command == 'U') {
      moveUpward = true;
      Serial.println("Moving UP");
      moveMotor(STEPS_TO_MOVE, moveUpward);
      digitalWrite(ENABLE_PIN, HIGH); // Disable driver after movement
    }
    else if (command == 'd' || command == 'D') {
      moveUpward = false;
      Serial.println("Moving DOWN");
      moveMotor(STEPS_TO_MOVE, moveUpward);
      digitalWrite(ENABLE_PIN, HIGH); // Disable driver after movement
    }
    else if (command == 's' || command == 'S') {
      Serial.println("Stopping motor");
      digitalWrite(ENABLE_PIN, HIGH); // Disable driver
    }
  }
  else {
    digitalWrite(ENABLE_PIN, LOW); // Ensure driver is disabled when no command is received
  }
}

// Function to move the motor in a specified direction
void moveMotor(int steps, bool upDirection) {
  Serial.print("Moving motor ");
  Serial.print(upDirection ? "UP" : "DOWN");
  Serial.print(" for ");
  Serial.print(steps);
  Serial.println(" steps");
  
  // Enable the stepper driver
  digitalWrite(ENABLE_PIN, LOW);
  
  // Set direction pin based on desired direction
  // NOTE: You might need to invert this logic based on your motor configuration
  digitalWrite(DIR_PIN, upDirection ? HIGH : LOW);
  
  // Move the specified number of steps
  for (int i = 0; i < steps; i++) {
    // Generate a pulse on the step pin
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(STEP_DELAY);
    
    // Print progress every 100 steps
    if (i % 100 == 0) {
      Serial.print("Step: ");
      Serial.println(i);
    }
  }
  
  Serial.println("Movement complete");
}
