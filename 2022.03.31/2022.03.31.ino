#define led 13

int count = 0;
int count_sec = 0;
int duty = 0;

void setup() {
  pinMode(led, OUTPUT); //출력
}

void loop() {
  if(count == 10) {
    count = 0;
    digitalWrite(led, HIGH);
  }
  else if(count == duty) digitalWrite(led, LOW);

  if(count_sec == 100){
    count_sec = 0;
    duty++;
    if(duty == 9) duty = 1;
  }
  
  count++;
  count_sec++;
  delay(1);
}
