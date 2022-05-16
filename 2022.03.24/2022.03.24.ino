//change resistance + LED

#define led 13
int count = 0;
int count_sec = 0;
int duty = 0;
bool mode = true;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  if(count == 10) {
    count = 0;
    digitalWrite(led, HIGH);
  }
  else if(count == duty) digitalWrite(led, LOW);

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
  
  count++;
  count_sec++;
  delay(1);
}
