void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Board is alive!");
  delay(1000);
}