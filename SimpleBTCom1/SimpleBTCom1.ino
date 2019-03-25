String Nachricht;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Nachricht = "";
}

void loop() {
    if (Serial.available() > 0) {
        char thisChar = Serial.read();
    
        if (thisChar == 0x0A)
        {
            Serial.println("Nachricht: " + Nachricht);
            return;
        }

        Nachricht += thisChar;
    }
}
