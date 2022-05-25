//IRremote 활용2(모드 설정, LED PWM)
#define IR 2
#define LED 19

void remoconISR();
void First();
void Second();
void Others();

unsigned long remocon_micros[50];
unsigned int diff_time[33];
int remocon_count = 0;
int data_bit[32];
byte data_byte = 0;
unsigned char number_of_hex[10] = {0x2D, 0x19, 0x31, 0xBD, 0x11, 0x39, 0xB5, 0x85, 0xA5, 0x95};
int remocon_num = 0;

int count = 0;
int count_sec = 0;
int duty = 0;
bool mode = true;

void setup(){
  Serial.begin(9600);
  pinMode(IR, INPUT);
  attachInterrupt(0, remoconISR, FALLING);
  for(int i=0; i<16; i++){
    pinMode(i + 3, OUTPUT);
  }
  pinMode(LED, OUTPUT);
}

int function = 0;

int count_dot = 0;
int count_dot2 = 0;
int print_num = 0;
int row = 1, col = 0;

void loop(){
  if(function != remocon_num) function = remocon_num;

  SetRow(0);
  if(function == 1) First();
  if(function == 2) Second();
  if(function == 3) digitalWrite(LED, HIGH);
  if(function == 4) digitalWrite(LED, LOW);
  if(function >= 5){
    Others();
    SetRow(0);
  }
  
  count++;
  count_sec++;
  count_dot++;
  count_dot2++;
  delayMicroseconds(100);
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

//0~9까지 출력하는 함수
void First(){
  if(count_dot == sec2 * 80){
    count_dot = 0;
    print_num++;
    if(print_num == 10){
      print_num = 0;
    }
  }
  if(count_dot2 == 10){
    count_dot2 = 0;
    SetRow(0);
    SetCol(Array[print_num][col]);
    SetRow(row);
    row++;
    col++;
    if(row >= 9) row = 1;
    if(col >= 8) col = 0;
  }
}

//LED 밝기 조절하는 함수
void Second(){
  if(count == 100) {
    count = 0;
    digitalWrite(LED, HIGH);
  }
  else if(count == duty) digitalWrite(LED, LOW);

  if(count_sec == 1000){
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

void Others(){
  for(int k=0; k<8; k++){
    SetRow(0);
    SetCol(Array[remocon_num][k]);
    SetRow(k + 1);
    delay(sec);
  }
}
