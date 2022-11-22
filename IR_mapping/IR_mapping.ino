#include <IRremote.h>

const int receive_pin=2;// initializing a pin
IRrecv irrecv(receive_pin); //pulling in values from the initialized pin
decode_results results; // declaring a variable

void setup() {
    Serial.begin(9600); 
    irrecv.enableIRIn();
}
void loop() {
    if (irrecv.decode(&results)){     //setting up an empty loop to keep putting in hexadecimal values into the serial monitor
        Serial.println(results.value,HEX);
        irrecv.resume();  
    }
}
