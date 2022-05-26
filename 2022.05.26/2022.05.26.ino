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

//-------------------------------------------------------------------------------------------------

//IRremote 활용2(모드 설정, LED PWM)
/*#define IR 2
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
  if(function != remocon_num) {
    function = remocon_num;
    SetRow(0);
    digitalWrite(LED, LOW);
  }

  SetRow(0);
  if(function == 1) First();
  if(function == 2) Second();
  if(function == 3) digitalWrite(LED, HIGH);
  if(function == 4) digitalWrite(LED, LOW);
  if(function >= 5) Others();
  
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
}*/

//-------------------------------------------------------------------------------------------------

//수업용
#define IR 2
#define LED 19

void setup(){
  Serial.begin(9600);
  for(int i=0; i<16; i++){
    pinMode(i + 3, OUTPUT);
  }

  for(int i=0; i<8; i++){
    digitalWrite(i + 3, HIGH);  //column off
    digitalWrite(i + 11, LOW);  //row off
  }

  pinMode(LED, OUTPUT);

  pinMode(IR, INPUT);
  attachInterrupt(0, remoconISR, FALLING);
}

unsigned long curr_millis = 0;
unsigned long prev_millis = 0;
unsigned long dot_millis = 0;

unsigned long curr_micros = 0;
unsigned long prev_micros = 0;
unsigned long led_millis = 0;

int count_pwm = 0;
int duty = 0;
bool mode = false;

int line_num = 0;
int num = 0;
int command = 0;
unsigned char value[8] = {0x23, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned long remocon_micros[50];
unsigned int diff_time[33];
int remocon_count = 0;
int data_bit[32];
byte data_byte = 0;
unsigned char number_of_hex[10] = {0x2D, 0x19, 0x31, 0xBD, 0x11, 0x39, 0xB5, 0x85, 0xA5, 0x95};
int remocon_num = 0;

void loop(){
  curr_millis = millis();
  curr_micros = micros();
  
  if(command != remocon_num){
    command = remocon_num;
    digitalWrite(LED, LOW);
    all_row_off();
  }
  
  if(command == 0) First();
  else if(command == 1) Second();
  else Others();
}

void all_row_off(){
  for(int i=0; i<8; i++){
    digitalWrite(i + 11, LOW);  //row off
  }
}

void one_line_value(unsigned char Data){
  for(int i=0; i<8; i++){
    if(Data & (0x80 >> i)){
      digitalWrite(i + 3, LOW);
    }
    else{
      digitalWrite(i + 3, HIGH);
    }
  }
}

void one_line_on(int line_num){
  digitalWrite(11 + line_num, HIGH);
}

void dot_matrix_function(){
  all_row_off();
  one_line_value(Array[num][line_num]);
  one_line_on(line_num);
  
  line_num++;
  if(line_num == 8) line_num = 0;
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

void First(){
  if(curr_millis - prev_millis >= 1){
    prev_millis = curr_millis;
    
    dot_matrix_function();
  }
  if(curr_millis - dot_millis >= 500){
    dot_millis = curr_millis;
    
    num++;
    if(num == 10) num = 0;
  }
}

void Second(){
  if(curr_micros - prev_micros >= 100){
    prev_micros = curr_micros;

    if(count_pwm == 100) {
      count_pwm = 0;
      digitalWrite(LED, HIGH);
    }
    else if(count_pwm == duty) digitalWrite(LED, LOW);
    count_pwm++;
  }
  if(curr_millis - led_millis >= 10){
    led_millis = curr_millis;
    
    duty++;
    if(duty == 99) duty = 1;
  }

  Others();
}

void Others(){
  all_row_off();
  one_line_value(Array[remocon_num][line_num]);
  one_line_on(line_num);
  
  line_num++;
  if(line_num == 8) line_num = 0;
}
