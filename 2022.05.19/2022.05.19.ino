//지난 주꺼 멀티태스킹으로 개조, 회로 핀 변경 요함
/*#define IR 2
#define Echo 3
#define Trig 12
#define led 13

const int COM_NUM[] = {14, 15, 16, 17}; //A0, A1, A2, A3

int Number_FND_A[10][8] = {
  {0,0,0,0,0,0,1,1},  //0
  {1,0,0,1,1,1,1,1},  //1
  {0,0,1,0,0,1,0,1},  //2
  {0,0,0,0,1,1,0,1},  //3
  {1,0,0,1,1,0,0,1},  //4
  {0,1,0,0,1,0,0,1},  //5
  {0,1,0,0,0,0,0,1},  //6
  {0,0,0,1,1,0,1,1},  //7
  {0,0,0,0,0,0,0,1},  //8
  {0,0,0,0,1,0,0,1},  //9
};
//Cathode
int Number_FND[10][8] = {
  {1,1,1,1,1,1,0,0},  //0
  {0,1,1,0,0,0,0,0},  //1
  {1,1,0,1,1,0,1,0},  //2
  {1,1,1,1,0,0,1,0},  //3
  {0,1,1,0,0,1,1,0},  //4
  {1,0,1,1,0,1,1,0},  //5
  {1,0,1,1,1,1,1,0},  //6
  {1,1,1,0,0,1,0,0},  //7
  {1,1,1,1,1,1,1,0},  //8
  {1,1,1,1,0,1,1,0},  //9
};

void SetCom(int n){
  for(int i=14; i<18; i++){
    if(n + 13 == i) digitalWrite(i, LOW);
    else digitalWrite(i, HIGH);
  }
  return;
}

unsigned long remocon_micros[50];
unsigned int diff_time[33];
int remocon_count = 0;
int data_bit[32];
byte data_byte = 0;
unsigned char number_of_hex[10] = {0x2D, 0x19, 0x31, 0xBD, 0x11, 0x39, 0xB5, 0x85, 0xA5, 0x95};
int remocon_num = 0;

unsigned long prev_micros = 0;
int diff_micros = 0;
float cm = 0;
int ten = 0, one = 0;

void remoconISR();
void btnISR();

void setup() {
  for(int i=4; i<12; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  for(int i=0; i<4; i++){
    pinMode(COM_NUM[i], OUTPUT);
  }
  SetCom(0);

  pinMode(led, OUTPUT);

  Serial.begin(9600);
  pinMode(IR, INPUT);
  attachInterrupt(0, remoconISR, FALLING);

  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  attachInterrupt(1, btnISR, CHANGE);
}

unsigned int count_lcd = 0;
unsigned int count_lcd2 = 0;
unsigned int count_p = 0;

int count_led = 0;
int count_sec = 0;
unsigned long prev_millis_led = 0;
unsigned long duty = 0;
bool mode = true;

void loop() {
  if(count_lcd == 1000){
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
  }
  
  if(count_lcd >= 1000){
    count_lcd = 0;
    count_p++;
    if(count_p == 10){
      count_p = 0;
    }
  }

  count_lcd2 = (count_lcd % 4) + 1;

  if(count_lcd2 > 0 && count_lcd2 <= 1){
    SetCom(1);
    for(int i=0; i<8; i++){
      digitalWrite(i + 4, Number_FND[ten][i]);
    }
  }
  if(count_lcd2 > 1 && count_lcd2 <= 2){
    SetCom(2);
    for(int i=0; i<8; i++){
      digitalWrite(i + 4, Number_FND[one][i]);
    }
  }
  if(count_lcd2 > 2 && count_lcd2 <= 3){
    SetCom(3);
    for(int i=0; i<8; i++){
      digitalWrite(i + 4, Number_FND[remocon_num][i]);
    }
  }
  if(count_lcd2 > 3 && count_lcd2 <= 4){
    SetCom(4);
    for(int i=0; i<8; i++){
      digitalWrite(i + 4, Number_FND[count_p][i]);
    }
  }
  
  count_lcd++;
  //-------------------------------------------------------
  if(count_led == 10){
    count_led = 0;
    digitalWrite(led, HIGH);
  }
  else if(count_led == duty){
    digitalWrite(led, LOW);
  }
  count_led++;
  count_sec++;
  if(count_sec == 100){
    count_sec = 0;
    if(mode){
      duty++;
      if(duty == 9) mode = false;
    }
    else{
      duty--;
      if(duty == 1) mode = true;
    }
  }
  delay(1);
}

void remoconISR(){
  remocon_micros[remocon_count] = micros();

  if(remocon_count > 0){
    diff_time[remocon_count - 1] = remocon_micros[remocon_count] - remocon_micros[remocon_count - 1];
    //-----------------------------------------------------------------------------------------------
    if(diff_time[remocon_count - 1] > 12500 && diff_time[remocon_count - 1] < 14500){
      remocon_count = 1;
    }
    //-----------------------------------------------------------------------------------------------
    if(diff_time[remocon_count - 1] > 10500 && diff_time[remocon_count - 1] < 12500){
      remocon_count = -1;
      Serial.println(remocon_num);
    }
    //-----------------------------------------------------------------------------------------------
  }
  
  remocon_count++;
  if(remocon_count == 34){
    remocon_count = 0;
    //-----------------------------
    for(int i=0; i<32; i++){
      if(diff_time[i] > 1000 && diff_time[i] < 1500){
        data_bit[i] = 0;
      }
      else if(diff_time[i] > 2000 && diff_time[i] < 2500){
        data_bit[i] = 1;
      }
    }
    //-----------------------------
    for(int i=0; i<8; i++){
      data_byte >>= 1;
      
      if(data_bit[16 + i] == 1){
        data_byte |= 0x80;
      }
    }
    //Serial.println(data_byte, HEX);
    for(int i=0; i<10; i++){
      if(number_of_hex[i] == (unsigned char)data_byte){
        Serial.println(i);
        remocon_num = i;
        break;
      }
    }
  }
}

void btnISR(){
  int Data = digitalRead(Echo);
  if(Data == 1){
    prev_micros = micros();
  }
  else{
    diff_micros = micros() - prev_micros;
    cm = diff_micros * 0.017;
    
    if(cm >= 100){
      cm = 99;
    }
    Serial.print("Now : ");
    Serial.print(cm);
    Serial.println(" cm");
    ten = (int)cm / 10;
    one = (int)cm % 10;
  }
}*/

//-----------------------------------------------------------------
//도트매트릭스 제어
#define sec 1
#define sec2 100

int Array[10][8]= {
  {0x00, 0x38, 0x44, 0x4C, 0x54, 0x64, 0x44, 0x38}, //0
  {0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7C}, //1
  {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7C}, //2
  {0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38}, //3
  {0x00, 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x08}, //4
  {0x00, 0x7C, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38}, //5
  {0x00, 0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38}, //6
  {0x00, 0x7C, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20}, //7
  {0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38}, //8
  {0x00, 0x38, 0x44, 0x44, 0x3C, 0x04, 0x44, 0x38}  //9
};

//행 설정
void SetRow(int n){
  for(int i=11; i<19; i++){
    if(n + 10 == i) digitalWrite(i, HIGH);
    else digitalWrite(i, LOW);
  }
}

//열 설정
void SetCol(int n){
  for(int i=0; i<8; i++){
    int a = n % 2;
    n /= 2;
    if(a == 1) digitalWrite(10 - i, LOW);
    else digitalWrite(10 - i, HIGH);
  }
}

//-----------------------------------------------------------------
//0~9 출력

/*void setup(){
  for(int i=0; i<16; i++){
    pinMode(i + 3, OUTPUT);
  }
}

void loop(){
  for(int i=0; i<10; i++){  //숫자 반복
    for(int j=0; j<sec2; j++){  //숫자 출력시간 제어
      for(int k=0; k<8; k++){ //한 숫자의 행,열 출력
        SetRow(0);
        SetCol(Array[i][k]);
        SetRow(k + 1);
        delay(sec);
      }
    }
  }
}*/

//-----------------------------------------------------------------
//IRremote 연동
#define IR 2

unsigned long remocon_micros[50];
unsigned int diff_time[33];
int remocon_count = 0;
int data_bit[32];
byte data_byte = 0;
unsigned char number_of_hex[10] = {0x2D, 0x19, 0x31, 0xBD, 0x11, 0x39, 0xB5, 0x85, 0xA5, 0x95};
int remocon_num = 0;

void setup(){
  Serial.begin(9600);
  pinMode(IR, INPUT);
  attachInterrupt(0, remoconISR, FALLING);
  for(int i=0; i<16; i++){
    pinMode(i + 3, OUTPUT);
  }
}

void loop(){
  for(int j=0; j<sec2; j++){  //숫자 출력시간 제어
    for(int k=0; k<8; k++){ //한 숫자의 행,열 출력
      SetRow(0);
      SetCol(Array[remocon_num][k]);
      SetRow(k + 1);
      delay(sec);
    }
  }
}

void remoconISR(){
  remocon_micros[remocon_count] = micros();

  if(remocon_count > 0){
    diff_time[remocon_count - 1] = remocon_micros[remocon_count] - remocon_micros[remocon_count - 1];
    //-----------------------------------------------------------------------------------------------
    if(diff_time[remocon_count - 1] > 12500 && diff_time[remocon_count - 1] < 14500){
      remocon_count = 1;
    }
    //-----------------------------------------------------------------------------------------------
    if(diff_time[remocon_count - 1] > 10500 && diff_time[remocon_count - 1] < 12500){
      remocon_count = -1;
      Serial.println(remocon_num);
    }
    //-----------------------------------------------------------------------------------------------
  }
  
  remocon_count++;
  if(remocon_count == 34){
    remocon_count = 0;
    //-----------------------------
    for(int i=0; i<32; i++){
      if(diff_time[i] > 1000 && diff_time[i] < 1500){
        data_bit[i] = 0;
      }
      else if(diff_time[i] > 2000 && diff_time[i] < 2500){
        data_bit[i] = 1;
      }
    }
    //-----------------------------
    for(int i=0; i<8; i++){
      data_byte >>= 1;
      
      if(data_bit[16 + i] == 1){
        data_byte |= 0x80;
      }
    }
    //Serial.println(data_byte, HEX);
    for(int i=0; i<10; i++){
      if(number_of_hex[i] == (unsigned char)data_byte){
        Serial.println(i);
        remocon_num = i;
        break;
      }
    }
  }
}
