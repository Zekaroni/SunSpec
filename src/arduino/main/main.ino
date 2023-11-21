void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    if (incomingByte == 0x0D)
    {
     Serial.print("\n"); 
    } else
    {
      Serial.print(incomingByte);
    };
  }
}
