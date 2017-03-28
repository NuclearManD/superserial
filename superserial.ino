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
  #ifndef wrt
  Serial.begin(19200);
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
  #ifndef wrt
  Serial.write(wait_read());
  #else
  println("Yay! this worked!");
  #endif
}
long ls=0;
void write(byte x){
  // Initiate transfer
  while(ls+40>micros());
  digitalWrite(TX,LOW);
  delayMicroseconds(5);
  ls=micros();
  byte i=0;
  while(ls+500>micros()&&i<8){
    while(digitalRead(RX));
    digitalWrite(TX, 1&(x>>i));
    while(!digitalRead(RX));
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
  // be sure RX is low so no junk is received
  while(!digitalRead(RX));
  return x;
}
void println(char* x){
  for(int i=0;x[i]!=0;i++){
    write(x[i]);
  }
  write('\n');
}

