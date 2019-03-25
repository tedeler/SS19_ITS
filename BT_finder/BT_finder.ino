#define BTSerial Serial2

String sendcmd(String cmd, bool debuginfo=false) {
    String result;
    if (debuginfo) {
        Serial.print("Command: ");
        Serial.println(cmd);
    }
    BTSerial.print(cmd);
    delay(400);
    while(BTSerial.available()) {
        result += (char) BTSerial.read();
        delay(10);
    }
    if (debuginfo) {
        Serial.print("   Result: ");
        Serial.println(result);
    }
    return result;
}

unsigned long getHC06BaudrateById(int baudid) {
    const unsigned long baudrates[] = {1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
    return baudrates[baudid-1];
}

int getHC06BaudId(unsigned long baudrate) {
    for(int i=1; i<=8; i++){
        if (getHC06BaudrateById(i) == baudrate)
            return i;
    }
    return getHC06BaudrateById(9600);
}

bool probeHC06(int baudid) {
    unsigned long baudrate = getHC06BaudrateById(baudid);
    
    Serial.print("Probing HC-06 Module with ");
    Serial.print(baudrate);
    Serial.print(" BAUD ... ");

    BTSerial.begin(baudrate); 
    String result = sendcmd("AT");
    if(result == "OK") {
        Serial.println("[OK]");
        return true;
    } else {
        Serial.println("[FAILED]");
        return false;
    }
}

bool setHC06Baud(unsigned long baudrate) {
    int baudid = getHC06BaudId(baudrate);
    
    String cmd = "AT+BAUD";
    cmd += baudid;
    delay(500);
    sendcmd(cmd, true);
    delay(500);
    return probeHC06(baudid);
}

bool initBluetooth(unsigned long baudrate) {
    for(int i=1; i<=8; i++){
        if( probeHC06(i) )
            return setHC06Baud( baudrate );
    }
    
    return false;
}

void setPinCode(String pin) {
    Serial.println("Setting pin to " + pin);
    Serial.println("    BT-Modules response:");
    Serial.println("    " + sendcmd("AT+PIN"+pin));
}

void setName(String name) {
    Serial.println("Setting name to " + name);
    Serial.println("    BT-Modules response:");
    Serial.println("    " + sendcmd("AT+NAME"+name));
}

void getVersion() {
    Serial.println("BT-Modules Version:");
    Serial.println("    " + sendcmd("AT+VERSION"));
}

void setup() {
    Serial.begin(9600);       //monitor
    initBluetooth(115200);

    getVersion();
    setName("CoolHAW");
    setPinCode("5643");
}

void loop(){
}   //one-shot - nothing here

