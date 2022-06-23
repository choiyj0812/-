//서보모터
/*
 * 0.7ms ~ 1.5ms
 * 1.5ms ~ 2.3ms
 * 2.3ms - 0.7ms = 1.6ms
 * 50단계로 나누면 32us
 * 0.7ms : 625up, 22down
 * 2.3ms : 625up, 72down
*/
/*#define servo 7

void setup(){
  pinMode(servo, OUTPUT);
  Serial.begin(9600);
}

int count = 0;
int duty = 22;
int duty_count = 0;

void loop(){
  //파형
  if(count == 625){
    count = 0;
    digitalWrite(servo, HIGH);
  }
  else if(count == duty){
    digitalWrite(servo, LOW);
  }

  //duty 가변
  if(duty_count == 625){
    duty_count = 0;
    duty++;
    if(duty == 72) duty = 22;
  }

  count++;
  duty_count++;
  delayMicroseconds(32);
}*/

//======================================
//servo(millis() 활용)

/*void setup(){
  pinMode(servo, OUTPUT);
  Serial.begin(9600);
}

long curr_micros = 0;
long prev_micros = 0;
long curr_millis = 0;
long prev_millis_duty = 0;
int count = 0;
int duty = 22;
int duty_count = 0;

void loop(){
  //시간 측정
  curr_millis = millis();
  curr_micros = micros();
  
  //시간 추가
  if(curr_micros - prev_micros > 32){
    prev_micros = curr_micros;
    count++;

    if(count == 625){
      count = 0;
      digitalWrite(servo, HIGH);
    }
    else if(count == duty){
      digitalWrite(servo, LOW);
    }
  }

  //duty 가변
  if(curr_millis - prev_millis_duty > 20){
    prev_millis_duty = curr_millis;
    duty++;
    if(duty == 72) duty = 22;
  }
}*/

//==========================================
//초음파
/*
 * Trig에서 쏜 초음파가 Echo로 들어옴
 * 1sec : 340m = (걸린시간) : (왕복거리) / 2
 * 0.017s * (걸린시간)(us) = (거리)(cm)
 * 
 * Trig - HIGH, LOW
 * 초음파 출발
 * Echo - HIGH
 * 초음파 도착
 * Echo - LOW
*/
/*#define Echo 3
#define Trig 5

void setup(){
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  attachInterrupt(1, myISR, CHANGE);
}

unsigned long rising_time = 0, falling_time = 0;
unsigned int diff_time = 0;
int echo_data = 0, distance = 0;
bool get_distance_flag = 0;

void loop(){
  //Trig 발사
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  delay(1000);

  /*if(get_distance_flag == 1){
    get_distance_flag = 0;
    
    Serial.print(distance);
  }
}

void myISR(){
  //echo에서 시간 측정
  echo_data = digitalRead(Echo);
  if(echo_data == 1){
    rising_time = micros();
  }
  else{
    falling_time = micros();
    diff_time = falling_time - rising_time;

    distance = (int)diff_time * 0.017;
    //get_distance_flag = 1;
    Serial.print(distance);
    Serial.println(" cm");
  }
}*/

//==========================================
//초음파(millis, micros 활용)

/*#define Echo 3
#define Trig 5

void setup(){
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  attachInterrupt(1, myISR, CHANGE);
}

unsigned long rising_time = 0, falling_time = 0;
unsigned int diff_time = 0;
int echo_data = 0, distance = 0;
bool get_distance_flag = 0;

int curr_millis = 0, prev_millis = 0;

void loop(){
  curr_millis = millis();
  if(curr_millis - prev_millis > 1000){
    prev_millis = curr_millis;
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
  }
}

void myISR(){
  //echo에서 시간 측정
  echo_data = digitalRead(Echo);
  if(echo_data == 1){
    rising_time = micros();
  }
  else{
    falling_time = micros();
    diff_time = falling_time - rising_time;

    distance = (int)diff_time * 0.017;
    //get_distance_flag = 1;
    Serial.print(distance);
    Serial.println(" cm");
  }
}*/

//============================================
//ir리모컨
/*
 * ir수신기 : 왼쪽부터 OUT, GND, VCC
 * Lead code : LOW상태-9ms, HIGH상태-4.5ms
 * Falling을 인식
 * custom code : 0x01
 * custom code : 0xFE
 * data code : 0x02
 * data code : 0xFD
 * code : 32개(custom+data) + 2개(Lead)
 * LCD 명령어 : (8비트 : 30, 30, 30, 38, 06, 0C, 80, 01), (4비트 : 30, 30, 30, 28 / 28, 06, 0C, 80, 01)
 */

void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(0, remoconISR, FALLING);
}

int count = 0;
unsigned long micros_time[50];
unsigned long diff_time[34];
unsigned int lead_code_time = 0;
bool data_bit[32];
unsigned char remocon_data = 0;

void loop(){
  
}

void remoconISR(){
  //Lead code
  micros_time[count] = micros();
  if(count > 0){
    diff_time[count - 1] = micros_time[count] - micros_time[count - 1];
    if(diff_time[count - 1] > 13000 && diff_time[count - 1] < 14000){
      count = 1;
    }
    if(diff_time[count - 1] > 11000 && diff_time[count - 1] < 12000){
      count = -1;
      Serial.println("Repeat");
    }
  }
  
  //IR신호 찾기(34개)
  if(count == 34){
    for(int i=0; i<32; i++){
      if(diff_time[i + 1] > 1000 && diff_time[i + 1] < 1500){
        data_bit[i] = 1;
      }
      else if(diff_time[i + 1] > 2000 && diff_time[i + 1] < 2500){
        data_bit[i] = 0;
      }
    }
    
    for(int i=0; i<32; i++){
      /*Serial.print(data_bit[i]);
      Serial.println();*/
      for(int i=0; i<8; i++){
        remocon_data <<= 1;

        if(data_bit[24 + i] == 1){
          remocon_data |= 0x01;
        }
      }
      Serial.println(remocon_data, HEX);
    }
    count = 0;
    //Serial.println("remocon start");
  }
  count++;
}

//=========================================
//matrix button
/*
 * 저항 : 4.9K / 10K
 * Col4~1, ROW1~4
 */
