/*
//풀업, 풀다운을 활용한 버튼 활용
#define button 2

void setup() {
  pinMode(button, INPUT);
  Serial.begin(9600);
}

//On과 Off가 한번씩만 나오게하는 변수
char button_flag = 0;
void loop() {
  bool b = digitalRead(button);
  //버튼 활성화
  if(b){
    if(button_flag == 0){
      button_flag = 1;
      Serial.println("ON");
    }
  }
  //버튼 비활성화
  else{
    if(button_flag == 1){
      button_flag = 0;
      Serial.println("OFF");
    }
  }
  delay(10);
}
*/
//------------------------------------------------
//인터럽트 사용하기
/*
  인터럽트
  Rising : 전압 0 -> 1
  Falling : 전압 1 -> 0
  Change : Rising + Falling
*/
/*
#define button 2
void btnISR();

void setup(){
  Serial.begin(9600);
  pinMode(button, INPUT);

  attachInterrupt(0, btnISR, CHANGE);
}

char button_flag = 0;
void loop(){
  
}

unsigned long prev_micros = 0;
int diff_micros = 0;
void btnISR(){
  unsigned long curr_micros = micros();
  
  int Data = digitalRead(button);
  if(Data == 1){
    prev_micros = curr_micros;
  }
  else{
    diff_micros = curr_micros - prev_micros;
    Serial.println(diff_micros);
  }
}
*/
//------------------------------------------------
/*
  t : 측정된 시간, X : 구하고자 하는 거리
  1,000,000(us) : 340(m) = t/2(us) : X/100(cm)
  340*t/2 = 10,000*X
  X = 340*t/20,000 = 0.34*t/20 = 0.17*t/10 = 0.017*t
*/
//초음파센서 사용하기
/*#define Echo 3
#define Trig 4

void setup(){
  Serial.begin(9600);
  pinMode(Echo, INPUT);

  pinMode(Trig, OUTPUT);
  attachInterrupt(1, btnISR, CHANGE);
}

void loop(){
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  delay(1000);
}

unsigned long prev_micros = 0;
int diff_micros = 0;
float cm = 0;

void btnISR(){
  int Data = digitalRead(Echo);
  if(Data == 1){
    prev_micros = micros();
  }
  else{
    diff_micros = micros() - prev_micros;
    cm = diff_micros * 0.017;
    Serial.print(cm);
    Serial.println(" cm");
  }
}*/
//------------------------------------------------
//IRRemote 사용하기
#define Remo 2

void setup(){
  Serial.begin(9600);
  pinMode(Remo, INPUT);
  attachInterrupt(0, remoconISR, FALLING);
}

void loop(){
  
}

unsigned long prev_micros = 0;
int diff_micros = 0;
int count_remocon = 0;

void remoconISR(){
  count_remocon++;
  Serial.println(count_remocon);
}
