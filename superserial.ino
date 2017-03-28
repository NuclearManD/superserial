// I would use interrupts but I speciffically want to use these pins.
#define RX 6
#define TX 9
// wrt is defined for the test transmitter
#define wrt
void setup() {
  // put your setup code here, to run once:
  pinMode(RX,INPUT);
  pinMode(TX,OUTPUT);
  digitalWrite(TX,HIGH);  // setup serial - Don't start by transmitting!
  #ifdef wrt
  delay(15);
  write('t');
  write('e');
  write('s');
  write('t');
  #else
  Serial.begin(19200);
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
  #ifndef wrt
  Serial.write(wait_read());
  #endif
}
void write(byte x){
  // Initiate transfer
  digitalWrite(TX,LOW);
  for(byte i=0;i<8;i++){
    while(digitalRead(RX));
    digitalWrite(TX, 1&(x>>i));
    while(!digitalRead(RX));
  }
  // end transfer
  digitalWrite(TX,HIGH);
}
byte wait_read(){
  byte x=0;
  // Wait for a transfer
  // (indicated by a low RX)
  while(digitalRead(RX));
  for(byte i=0;i<8;i++){
    digitalWrite(TX, LOW);
    delayMicroseconds(1);
    digitalWrite(TX, HIGH);
    x|=(digitalRead(RX)&1)<<i;
  }
  // no need to end transfer - TX is already HIGH
  return x;
}

