// I would use interrupts but I speciffically want to use these pins.
#define RX 6
#define TX 9
// wrt is defined for the test transmitter
//#define wrt
void setup() {
  pinMode(RX,INPUT);
  pinMode(TX,OUTPUT);
  digitalWrite(TX,HIGH);  // setup serial - Don't start by transmitting!
  #ifndef wrt
  Serial.begin(19200);
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
  #ifndef wrt
  Serial.write(wait_read());
  #endif
}
long ls=0;
void write(byte x){
  // Initiate transfer
  while(ls+10>micros());
  digitalWrite(TX,LOW);
  ls=micros();
  byte i=0;
  while(ls+200>micros()){
    while(digitalRead(RX));
    while(!digitalRead(RX));
    digitalWrite(TX, 1&(x>>i));
    i++;
    ls=micros();
  }
  // end transfer
  digitalWrite(TX,HIGH);
  ls=micros();
}
byte wait_read(){
  byte x=0;
  // Wait for a transfer
  // (indicated by a low RX)
  while(digitalRead(RX));
  for(byte i=0;i<8;i++){
    delayMicroseconds(20);
    digitalWrite(TX, LOW);
    delayMicroseconds(20);
    x|=(digitalRead(RX)&1)<<i;
    digitalWrite(TX, HIGH);
  }
  // no need to end transfer - TX is already HIGH
  return x;
}

