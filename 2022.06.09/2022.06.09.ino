// LCD 제어(I2C X)
#include <stdarg.h>

#define RS 4
#define RW 5
#define E 6
#define D0 7

#define RS_HIGH() digitalWrite(RS, HIGH)
#define RS_LOW() digitalWrite(RS, LOW)
#define RW_HIGH() digitalWrite(RW, HIGH)
#define RW_LOW() digitalWrite(RW, LOW)
#define E_HIGH() digitalWrite(E, HIGH)
#define E_LOW() digitalWrite(E, LOW)

uint8_t charLCD_command[8] = {0x30, 0x30, 0x30, 0x38, 0x06, 0x0C, 0x80, 0x01};
uint8_t charLCD_command_4bit[9] = {0x30, 0x30, 0x30, 0x28, 0x28, 0x06, 0x0C, 0x80, 0x01};

//초기화
void charLCD_init(){
  for(int i=0; i<11; i++) pinMode(i + 4, OUTPUT);
  RS_HIGH();
  RW_LOW();
}

//명령어
void charLCD_inst(uint8_t I){
  RS_LOW();
  for(int i=0; i<8; i++){
    if(I & (0x01 << i)){
      digitalWrite(D0 + i, HIGH);
    }
    else{
      digitalWrite(D0 + i, LOW);
    }
  }
  E_HIGH();
  E_LOW();
  RS_HIGH();
  delayMicroseconds(50);
}

//출력
void charLCD_data(uint8_t D){
  for(int i=0; i<8; i++){
    if(D & (0x01 << i)){
      digitalWrite(D0 + i, HIGH);
    }
    else{
      digitalWrite(D0 + i, LOW);
    }
  }
  E_HIGH();
  E_LOW();
  delayMicroseconds(50);
}

//문자열 출력
void charLCD_string(char *str){
  int str_len = strlen(str);
  for(int i=0; i<str_len; i++){
    charLCD_data(str[i]);
  }
}

//커서 위치 설정
void charLCD_cursor_set(int line, int col){
  if(col > 0 && col <= 16){
    if(line == 1) charLCD_inst(0x80 + col - 1);
    else if(line == 2) charLCD_inst(0xC0 + col - 1);
  }
}

//문자열 출력(=printf())
void _printf(char *format, ...){
  char buf[512];
  va_list arglist;

  va_start(arglist, format);
  vsprintf(buf, format, arglist);
  va_end(arglist);
  charLCD_string(buf);
}

//4bit 명령어
void charLCD_inst_4bit(uint8_t I){
  RS_LOW();
  for(int i=4; i<8; i++){
    if(I & (0x01 << i)){
      digitalWrite(D0 + i, HIGH);
    }
    else{
      digitalWrite(D0 + i, LOW);
    }
  }
  E_HIGH();
  E_LOW();
  RS_HIGH();
  delayMicroseconds(50);
}

//4bit 명령어
void charLCD_inst_4bit_mode(uint8_t I){
  uint8_t high_byte = I & 0xF0;
  uint8_t low_byte = (I & 0x0F) << 4;
  charLCD_inst_4bit(high_byte);
  charLCD_inst_4bit(low_byte);
}

//4bit 출력
void charLCD_data_4bit(uint8_t D){
  for(int i=4; i<8; i++){
    if(D & (0x01 << i)){
      digitalWrite(D0 + i, HIGH);
    }
    else{
      digitalWrite(D0 + i, LOW);
    }
  }
  E_HIGH();
  E_LOW();
  delayMicroseconds(50);
}

//4bit 출력
void charLCD_data_4bit_mode(uint8_t D){
  uint8_t high_byte = D & 0xF0;
  uint8_t low_byte = (D & 0x0F) << 4;
  charLCD_data_4bit(high_byte);
  charLCD_data_4bit(low_byte);
}

//4bit 문자열 출력
void charLCD_string_4bit(char *str){
  int str_len = strlen(str);
  for(int i=0; i<str_len; i++){
    charLCD_data_4bit_mode(str[i]);
  }
}

//4bit 커서 위치 설정
void charLCD_cursor_set_4bit(int line, int col){
  if(col > 0 && col <= 16){
    if(line == 1) charLCD_inst_4bit_mode(0x80 + col - 1);
    else if(line == 2) charLCD_inst_4bit_mode(0xC0 + col - 1);
  }
}

//4bit 문자열 출력(=printf())
void _printf_4bit(char *format, ...){
  char buf[512];
  va_list arglist;

  va_start(arglist, format);
  vsprintf(buf, format, arglist);
  va_end(arglist);
  charLCD_string_4bit(buf);
}

//==========================================
//LCD 숫자

/*void setup(){
  Serial.begin(9600);

  charLCD_init();
  for(int i=0; i<8; i++){
    charLCD_inst(charLCD_command[i]);
  }
  delay(2);
}

void loop(){
  //charLCD_data(0x31);
  //delay(1000);
  for(int i=0; i<10; i++){
    charLCD_data(0x30 + i);
    delay(1000);
  }
}*/

//=========================================
//LCD 문자열

/*void setup(){
  Serial.begin(9600);

  charLCD_init();
  for(int i=0; i<8; i++){
    charLCD_inst(charLCD_command[i]);
  }
  delay(2);

  charLCD_cursor_set(2, 3);
  charLCD_string("hello, world!");
}

void loop(){
  
}*/

//=========================================
//printf 연동

/*void setup(){
  Serial.begin(9600);

  charLCD_init();
  for(int i=0; i<8; i++){
    charLCD_inst(charLCD_command[i]);
  }
  delay(2);

  charLCD_cursor_set(2, 3);
  charLCD_string("hello, world!");
  charLCD_cursor_set(1, 1);
  _printf("haha = %d", 3);
}

void loop(){
  
}*/

//=========================================
//millis 사용

/*void setup(){
  Serial.begin(9600);

  charLCD_init();
  for(int i=0; i<8; i++){
    charLCD_inst(charLCD_command[i]);
  }
  delay(2);
}

unsigned long curr = 0, prev = 0;
int count = 0;

void loop(){
  curr = millis();
  if(curr - prev > 1000){
    prev = curr;
    
    charLCD_cursor_set(1, 1);
    _printf("time=%dm%ds", count / 60, count % 60);
    count++;
  }
}*/

//=========================================
//텍스트 이동

/*void setup(){
  Serial.begin(9600);

  charLCD_init();
  for(int i=0; i<8; i++){
    charLCD_inst(charLCD_command[i]);
  }
  delay(2);
}

unsigned long curr = 0, prev = 0;
unsigned long prev_500ms = 0;
int count = 0;
int cursor_pos = 0;

void loop(){
  curr = millis();
  if(curr - prev > 1000){
    prev = curr;

    charLCD_cursor_set(1, 1);
    for(int i=0; i<16; i++) charLCD_data(' ');
    
    charLCD_cursor_set(1, 1);
    _printf("time=%dm%ds", count / 60, count % 60);
    //_printf("haha = %d", count);
    count++;
  }

  if(curr - prev_500ms > 500){
    prev_500ms = curr;

    charLCD_cursor_set(2, 1);
    for(int i=0; i<16; i++) charLCD_data(0x20);
    
    charLCD_cursor_set(2, cursor_pos + 1);
    _printf("time=%dm%ds", count / 60, count % 60);
    //_printf("haha");

    cursor_pos++;
    if(cursor_pos == 16) cursor_pos = 0;
  }
}*/

//=========================================
//전압 측정

/*void setup(){
  Serial.begin(9600);

  charLCD_init();
  for(int i=0; i<8; i++){
    charLCD_inst(charLCD_command[i]);
  }
  delay(2);
}

unsigned long curr = 0, prev = 0;
unsigned long prev_500ms = 0;
unsigned long prev_1ms = 0;
int count = 0;
int cursor_pos = 0;

void loop(){
  curr = millis();
  if(curr - prev > 1000){
    prev = curr;

    charLCD_cursor_set(1, 1);
    for(int i=0; i<16; i++) charLCD_data(' ');
    
    charLCD_cursor_set(1, 1);
    //_printf("time=%dm%ds", count / 60, count % 60);
    _printf("ha=%d", count);
    
    count++;
    if(count == 100) count = 0;
  }

  if(curr - prev_500ms > 500){
    prev_500ms = curr;

    charLCD_cursor_set(2, 1);
    for(int i=0; i<16; i++) charLCD_data(0x20);
    
    charLCD_cursor_set(2, cursor_pos + 1);
    //_printf("time=%dm%ds", count / 60, count % 60);
    _printf("haha");

    cursor_pos++;
    if(cursor_pos == 16) cursor_pos = 0;
  }

  if(curr - prev_1ms > 1000){
    prev_1ms = curr;

    int adc_value = analogRead(A5);
    float voltage = ((float)adc_value / 1023) * 5.0;
    charLCD_cursor_set(1, 7);
    _printf("V=%d", (int)voltage);
    Serial.print(voltage);
    Serial.println("v");
  }
}*/

//=========================================
//4bit LCD

void setup(){
  Serial.begin(9600);

  charLCD_init();
  for(int i=0; i<4; i++){
    charLCD_inst(charLCD_command_4bit[i]);
  }
  for(int i=4; i<9; i++){
    charLCD_inst_4bit_mode(charLCD_command_4bit[i]);
  }
  delay(2);
}

unsigned long curr = 0, prev = 0;
unsigned long prev_500ms = 0;
unsigned long prev_1ms = 0;
int count = 0;
int cursor_pos = 0;

void loop(){
  curr = millis();
  if(curr - prev > 1000){
    prev = curr;

    charLCD_cursor_set_4bit(1, 1);
    for(int i=0; i<16; i++) charLCD_data_4bit_mode(' ');
    
    charLCD_cursor_set_4bit(1, 1);
    //_printf_4bit("time=%dm%ds", count / 60, count % 60);
    _printf_4bit("ha=%d", count);
    
    count++;
    if(count == 100) count = 0;
  }

  if(curr - prev_500ms > 500){
    prev_500ms = curr;

    charLCD_cursor_set_4bit(2, 1);
    for(int i=0; i<16; i++) charLCD_data_4bit_mode(0x20);
    
    charLCD_cursor_set_4bit(2, cursor_pos + 1);
    //_printf_4bit("time=%dm%ds", count / 60, count % 60);
    _printf_4bit("haha");

    cursor_pos++;
    if(cursor_pos == 16) cursor_pos = 0;
  }

  if(curr - prev_1ms > 1000){
    prev_1ms = curr;

    int adc_value = analogRead(A5);
    float voltage = ((float)adc_value / 1023) * 5.0;
    charLCD_cursor_set_4bit(1, 7);
    _printf_4bit("V=%d", (int)voltage);
    Serial.print(voltage);
    Serial.println("v");
  }
}
