//1. servo motor
//2. joystick
//3. joystick으로 servo 제어
void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

bool flag_left = false;
bool flag_right = false;
int count = 0;
int count_20ms = 0;
int count_20ms_js = 0;
int duty = 22;

void loop(){
  if(count_20ms_js == 625){
    count_20ms_js = 0;
    int Analog = analogRead(A0);
    
    if(Analog < 400){
      if(flag_left == false){
        flag_left = true;
        Serial.println("LEFT");
        duty = 22;
      }
    }
    else if(Analog > 700){
      if(flag_right == false){
        flag_right = true;
        Serial.println("RIGHT");
        duty = 72;
      }
    }
    else if(Analog > 400 && Analog < 700){
      flag_left = false;
      flag_right = false;
      duty = 47;
    }
  }

  if(count == 625){
    count = 0;
    digitalWrite(3, HIGH);
  }
  else if(count == duty){
    digitalWrite(3, LOW);
  }
//
//  if(count_20ms == 625){
//    count_20ms = 0;
//    duty++;
//    if(duty == 72) duty = 22;
//  }

  count++;
  count_20ms++;
  count_20ms_js++;
  delayMicroseconds(32);
}
