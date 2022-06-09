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

//초기화
void charLCD_init(){
  Serial.println("init");
  for(int i=0; i<11; i++) pinMode(i + 4, OUTPUT);
  RS_HIGH();
  RW_LOW();
}

//명령어
void charLCD_inst(uint8_t I){
  Serial.print("instruction ");
  Serial.println(I);
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
  Serial.print("data ");
  Serial.println(D);
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

void setup(){
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
}
