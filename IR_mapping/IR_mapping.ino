#include <IRremote.h>

const int receive_pin=2;
IRrecv irrecv(receive_pin);
decode_results results;

void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn();
}
void loop() {
    if (irrecv.decode(&results)){
        Serial.println(results.value,HEX);
        irrecv.resume();  
    }
}
