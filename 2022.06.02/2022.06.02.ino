//LCD 제어(I2C)
#define SCL 19
#define SDA 18
#define add 0x3F

#define SCL_HIGH() digitalWrite(SCL, HIGH);
#define SCL_LOW() digitalWrite(SCL, LOW);
#define SDA_HIGH() digitalWrite(SDA, HIGH);
#define SDA_LOW() digitalWrite(SDA, LOW);

void pcf8574(unsigned char d);
void Init();
void Start();
void Address(unsigned char a);
int Ack();
void Stop();

void setup() {
  Serial.begin(9600);
  Init();
}

void loop() {
  pcf8574(0x08);
  delay(1000);
  pcf8574(0x00);
  delay(1000);
}

void pcf8574(unsigned char d){
  Start();
  Address(add << 1);
  int ack_slave = Ack();
  Address(d);
  int ack_data = Ack();
  Stop();
}

void Init(){
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  SCL_HIGH();
  SDA_HIGH();
}

void Start(){
  SCL_HIGH();
  SDA_HIGH();
  delayMicroseconds(10);
  SDA_LOW();
  delayMicroseconds(10);
  SCL_LOW();
  delayMicroseconds(10);
}

void Address(unsigned char a){
  for(int i=0; i<8; i++){
    if(a & (0x80 >> i)){
      SDA_HIGH();
    }
    else SDA_LOW();
    delayMicroseconds(10);
    
    SCL_HIGH();
    delayMicroseconds(10);
    SCL_LOW();
    delayMicroseconds(10);
  }
}

int Ack(){
  pinMode(SDA, INPUT);
  SDA_LOW();
  SCL_HIGH();
  delayMicroseconds(10);

  int ack = digitalRead(SDA);
  SCL_LOW();
  pinMode(SDA, OUTPUT);
  //Serial.println(ack);
  return ack;
}

void Stop(){
  SDA_LOW();
  delayMicroseconds(10);
  SCL_HIGH();
  delayMicroseconds(10);
  SDA_HIGH();
  delayMicroseconds(10);
}
