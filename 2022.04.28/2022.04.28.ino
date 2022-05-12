//IRremote를 통해 FND 제어
/*#define Remo 2
//Anode
int Number_FND[10][8] = {
 {0,0,0,1,0,0,0,1}, //0
 {1,1,0,1,0,1,1,1}, //1
 {0,0,1,1,0,0,1,0}, //2
 {1,0,0,1,0,0,1,0}, //3
 {1,1,0,1,0,1,0,0}, //4
 {1,0,0,1,1,0,0,0}, //5
 {0,0,0,1,1,0,0,0}, //6
 {1,1,0,1,0,0,0,1}, //7
 {0,0,0,1,0,0,0,0}, //8
 {1,0,0,1,0,0,0,0}, //9
};

void setup(){
  Serial.begin(9600);
  pinMode(Remo, INPUT);
  attachInterrupt(0, remoconISR, FALLING);
  for(int i=0; i<8; i++){
    pinMode(4 + i, OUTPUT);
    digitalWrite(4 + i, HIGH);
  }
}

void loop(){
  
}

unsigned long remocon_micros[50];
unsigned int diff_time[33];
int remocon_count = 0;
int data_bit[32];
byte data_byte = 0;
unsigned char number_of_hex[10] = {0x2D, 0x19, 0x31, 0xBD, 0x11, 0x39, 0xB5, 0x85, 0xA5, 0x95};
int remocon_num = 0;

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
        for(int n=0; n<8; n++){
          digitalWrite(n + 4, Number_FND[i][n]);
        }
        break;
      }
    }
  }
}*/

//--------------------------------------------------------

//4자리 FND 숫자 출력
//Cathode
/*int num[10][8] = {
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

void setup(){
  for(int i=2; i<10; i++){
    pinMode(i, OUTPUT);
  }
}

void loop(){
  for(int i=0; i<10; i++){
    for(int j=0; j<8; j++){
      digitalWrite(j + 2, num[i][j]);
    }
    delay(1000);
  }
}*/

//--------------------------------------------------------

//4자리 FND + IRremote 제어
#define Remo 2
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

void setup(){
  Serial.begin(9600);
  pinMode(Remo, INPUT);
  attachInterrupt(0, remoconISR, FALLING);
  for(int i=0; i<8; i++){
    pinMode(i + 4, OUTPUT);
    digitalWrite(i + 4, LOW);
  }
}

void loop(){
  
}

unsigned long remocon_micros[50];
unsigned int diff_time[33];
int remocon_count = 0;
int data_bit[32];
byte data_byte = 0;
unsigned char number_of_hex[10] = {0x2D, 0x19, 0x31, 0xBD, 0x11, 0x39, 0xB5, 0x85, 0xA5, 0x95};
int remocon_num = 0;

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
    for(int i=0; i<10; i++){
      if(number_of_hex[i] == (unsigned char)data_byte){
        Serial.println(i);
        remocon_num = i;
        for(int n=0; n<8; n++){
          digitalWrite(n + 4, Number_FND[i][n]);
        }
        break;
      }
    }
  }
}
