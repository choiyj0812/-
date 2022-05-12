#define IR 2
#define led 13
#define Echo 3
#define Trig A1
#define First A5
#define Second A4
#define Third 12
#define Fourth A0
//Anode
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

void SetCom(int Com_num){
  switch(Com_num){
    case 1:
      digitalWrite(First, LOW);
      digitalWrite(Second, HIGH);
      digitalWrite(Third, HIGH);
      digitalWrite(Fourth, HIGH);
      break;
    case 2:
      digitalWrite(First, HIGH);
      digitalWrite(Second, LOW);
      digitalWrite(Third, HIGH);
      digitalWrite(Fourth, HIGH);
      break;
    case 3:
      digitalWrite(First, HIGH);
      digitalWrite(Second, HIGH);
      digitalWrite(Third, LOW);
      digitalWrite(Fourth, HIGH);
      break;
    case 4:
      digitalWrite(First, HIGH);
      digitalWrite(Second, HIGH);
      digitalWrite(Third, HIGH);
      digitalWrite(Fourth, LOW);
      break;
    case 0:
      digitalWrite(First, HIGH);
      digitalWrite(Second, HIGH);
      digitalWrite(Third, HIGH);
      digitalWrite(Fourth, HIGH);
      break;
  }
  return;
}

//-------------------------------------

//4digit 7segment + COMport controll

/*void setup(){
  pinMode(First, OUTPUT);
  pinMode(Second, OUTPUT);
  pinMode(Third, OUTPUT);
  pinMode(Fourth, OUTPUT);
  SetCom(0);
  for(int i=0; i<8; i++){
    pinMode(i + 4, OUTPUT);
    digitalWrite(i + 4, LOW);
  }
}

void loop(){
  for(int k=0; k<10; k++){
    for(int l=0; l<250; l++){
      for(int i=1; i<5; i++){
        SetCom(i);
        for(int j=0; j<8; j++){
          digitalWrite(j + 4, Number_FND[i][j]);
        }
        delay(1);
      }
    }
    delay(1);
  }
}*/

//-----------------------------------------------------------

//4digit 7segment + COMport controll
//Fourth Position : Count 0~9

/*void setup(){
  pinMode(First, OUTPUT);
  pinMode(Second, OUTPUT);
  pinMode(Third, OUTPUT);
  pinMode(Fourth, OUTPUT);
  SetCom(0);
  for(int i=0; i<8; i++){
    pinMode(i + 4, OUTPUT);
    digitalWrite(i + 4, LOW);
  }
}

void loop(){
  for(int k=0; k<10; k++){
    for(int l=0; l<250; l++){
      for(int i=1; i<4; i++){
        SetCom(i);
        for(int j=0; j<8; j++){
          digitalWrite(j + 4, Number_FND[i][j]);
        }
        delay(1);
      }
      
      SetCom(4);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[k][i]);
      }
      delay(1);
    }
    delay(1);
  }
}*/

//-----------------------------------------------------------

//4digit 7segment + COMport controll
//Third Position : IRremote
//Fourth Position : Count 0~9
/*
unsigned long remocon_micros[50];
unsigned int diff_time[33];
int remocon_count = 0;
int data_bit[32];
byte data_byte = 0;
unsigned char number_of_hex[10] = {0x2D, 0x19, 0x31, 0xBD, 0x11, 0x39, 0xB5, 0x85, 0xA5, 0x95};
int remocon_num = 0;

void setup(){
  pinMode(First, OUTPUT);
  pinMode(Second, OUTPUT);
  pinMode(Third, OUTPUT);
  pinMode(Fourth, OUTPUT);
  SetCom(0);
  for(int i=0; i<8; i++){
    pinMode(i + 4, OUTPUT);
    digitalWrite(i + 4, LOW);
  }

  Serial.begin(9600);
  pinMode(IR, INPUT);
  attachInterrupt(0, remoconISR, FALLING);
}

void loop(){
  for(int k=0; k<10; k++){
    for(int l=0; l<250; l++){
      for(int i=1; i<3; i++){
        SetCom(i);
        for(int j=0; j<8; j++){
          digitalWrite(j + 4, Number_FND[i][j]);
        }
        delay(1);
      }

      SetCom(3);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[remocon_num][i]);
      }
      delay(1);
      
      SetCom(4);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[k][i]);
      }
      delay(1);
    }
    delay(1);
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
      //Serial.println(remocon_num);
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
}*/

//-----------------------------------------------------------

//4digit 7segment + COMport controll
//First & Second Position : UltraSonic
//Third Position : IRremote
//Fourth Position : Count 0~9

/*unsigned long remocon_micros[50];
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

void setup(){
  pinMode(First, OUTPUT);
  pinMode(Second, OUTPUT);
  pinMode(Third, OUTPUT);
  pinMode(Fourth, OUTPUT);
  SetCom(0);
  for(int i=0; i<8; i++){
    pinMode(i + 4, OUTPUT);
    digitalWrite(i + 4, LOW);
  }

  Serial.begin(9600);
  pinMode(IR, INPUT);
  attachInterrupt(0, remoconISR, FALLING);

  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  attachInterrupt(1, btnISR, CHANGE);
}

void loop(){
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  delayMicroseconds(100);
  
  for(int k=0; k<10; k++){
    for(int l=0; l<100; l++){
      SetCom(1);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[ten][i]);
      }
      delay(1);
      
      SetCom(2);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[one][i]);
      }
      delay(1);
      
      SetCom(3);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[remocon_num][i]);
      }
      delay(1);
      
      SetCom(4);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[k][i]);
      }
      delay(1);
    }
    delay(1);
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
}*/

//-----------------------------------------------------------

//4digit 7segment + COMport controll + LED controll
//First & Second Position : UltraSonic
//Third Position : IRremote
//Fourth Position : Count 0~9

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

int count = 0;
int count_sec = 0;
int duty = 0;
bool mode = true;

void setup(){
  pinMode(First, OUTPUT);
  pinMode(Second, OUTPUT);
  pinMode(Third, OUTPUT);
  pinMode(Fourth, OUTPUT);
  SetCom(0);
  for(int i=0; i<8; i++){
    pinMode(i + 4, OUTPUT);
    digitalWrite(i + 4, LOW);
  }

  pinMode(led, OUTPUT);

  Serial.begin(9600);
  pinMode(IR, INPUT);
  attachInterrupt(0, remoconISR, FALLING);

  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  attachInterrupt(1, btnISR, CHANGE);
}

void loop(){
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  delayMicroseconds(100);
  
  for(int k=0; k<10; k++){
    for(int l=0; l<100; l++){
      SetCom(1);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[ten][i]);
      }
      delay(1);
      
      SetCom(2);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[one][i]);
      }
      delay(1);
      
      SetCom(3);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[remocon_num][i]);
      }
      delay(1);
      
      SetCom(4);
      for(int i=0; i<8; i++){
        digitalWrite(i + 4, Number_FND[k][i]);
      }
      delay(1);
    }
    delay(1);
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
