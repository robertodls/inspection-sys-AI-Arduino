// Include a WebUSB library for a camera
#include <WebUSB.h>

// Create a WebUSB instance with the target URL for communication
WebUSB WebUSBSerial(1 /* https:// */, "webusb.github.io/arduino/demos/rgb");

// Rename Serial to WebUSBSerial for ease of use
#define Serial WebUSBSerial

// Define pin assignments for components
#define banda 8
#define caja_buena 7
#define caja_mala 4
#define estado_robot 2

// Variables to store robot state, color information, and color index
int estado;
int color[3];
int colorIndex;

void setup() {
  // Wait until WebUSB connection is established
  while (!Serial) {
    ;
  }
  // Initialize serial communication and set pin modes
  Serial.begin(9600);
  pinMode(banda, OUTPUT);
  pinMode(caja_buena, OUTPUT);
  pinMode(caja_mala, OUTPUT);
  pinMode(estado_robot, INPUT);
  Serial.flush();
  // Reset color index
  colorIndex = 0;
}

void loop() {
  // Read the state of the robot
  estado = digitalRead(estado_robot);

  // Check for incoming serial data
  if (Serial && Serial.available()) {
    // Read color information into the color array
    color[colorIndex++] = Serial.read();

    // Check if a complete color code is received
    if (colorIndex == 1) {
      // Take action based on the received color and robot state
      if (color[0] == 1 && estado == LOW) {
        // Activate the conveyor belt for the good box
        delay(200);
        digitalWrite(banda, LOW);
        digitalWrite(caja_mala, LOW);
        digitalWrite(caja_buena, HIGH);
        delay(500);
      }
      else if (color[0] == 2 && estado == LOW) {
        // Activate the conveyor belt for the bad box
        delay(200);
        digitalWrite(banda, LOW);
        digitalWrite(caja_buena, LOW);
        digitalWrite(caja_mala, HIGH);
        delay(500);
      }

      // Clear any remaining serial data
      while (Serial.available()) {
        int throwaway = Serial.read();
      }

      // Reset color index for the next color code
      Serial.flush();
      colorIndex = 0;
    }
  }
  else if (estado == LOW) {
    // Activate the conveyor belt if the robot is in a ready state
    digitalWrite(caja_buena, LOW);
    digitalWrite(caja_mala, LOW);
    digitalWrite(banda, HIGH);
  }
}
