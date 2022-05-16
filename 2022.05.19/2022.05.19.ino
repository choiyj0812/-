//지난 주꺼 멀티태스킹으로 개조, 회로 핀 변경 요함
#define IR 2
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
  switch(n){
    case 0:
      digitalWrite(14, HIGH);
      digitalWrite(15, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(17, HIGH);
      break;
    case 1:
      digitalWrite(14, LOW);
      digitalWrite(15, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(17, HIGH);
      break;
    case 2:
      digitalWrite(14, HIGH);
      digitalWrite(15, LOW);
      digitalWrite(16, HIGH);
      digitalWrite(17, HIGH);
      break;
    case 3:
      digitalWrite(14, HIGH);
      digitalWrite(15, HIGH);
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      break;
    case 4:
      digitalWrite(14, HIGH);
      digitalWrite(15, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(17, LOW);
      break;
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

unsigned long curr_millis = 0;
unsigned long prev_millis1 = 0;
unsigned long prev_millis2 = 0;
unsigned long prev_millis3 = 0;
unsigned long prev_millis4 = 0;
int count = 0;
int count_led = 0;
int count_sec = 0;
unsigned long prev_millis_led = 0;
unsigned long duty = 0;
bool mode = true;

void loop() {
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  delayMicroseconds(100);
  //-------------------------------------------------------
  if(count >= 100) count = 0;
  
  curr_millis = millis();

  if(prev_millis1 - curr_millis >= 1){
    prev_millis1 = curr_millis;
    SetCom(1);
    for(int i=0; i<8; i++){
      digitalWrite(i + 4, Number_FND[ten][i]);
    }
  }
  if(prev_millis2 - curr_millis >= 1){
    prev_millis2 = curr_millis;
    SetCom(2);
    for(int i=0; i<8; i++){
      digitalWrite(i + 4, Number_FND[one][i]);
    }
  }
  if(prev_millis3 - curr_millis >= 1){
    prev_millis3 = curr_millis;
    SetCom(3);
    for(int i=0; i<8; i++){
      digitalWrite(i + 4, Number_FND[remocon_num][i]);
    }
  }
  if(prev_millis4 - curr_millis >= 1){
    prev_millis4 = curr_millis;
    SetCom(4);
    for(int i=0; i<8; i++){
      digitalWrite(i + 4, Number_FND[(int)count / 10][i]);
    }
    count++;
  }
  //-------------------------------------------------------
  if(prev_millis_led - curr_millis >= 1){
    if(count_led == 10){
      prev_millis_led = curr_millis;
      count_led = 0;
      digitalWrite(led, HIGH);
    }
    else if(count_led == duty){
      digitalWrite(led, LOW);
    }
    count_led++;
    count_sec++;
  }
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
    ten = (int)cm / 10;
    one = (int)cm % 10;
  }
}
