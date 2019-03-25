#define BTSerial Serial2


void setup() {
    BTSerial.begin(115200);
}


void loop() {
    String data = BTSerial.readStringUntil('\n');

    if (data.length() > 0){
        BTSerial.println("I got this String:");
        BTSerial.println(data);
    }
}
