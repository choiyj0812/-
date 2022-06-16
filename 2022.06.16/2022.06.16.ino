/*#define NOTE_C4  1911
#define NOTE_D4 1702  
#define NOTE_E4 1516  
#define NOTE_F4 1431  
#define NOTE_G4 1275  
#define NOTE_A4 1136  
#define NOTE_B4 1012
#define NOTE_C5 956

#define buz 16
#define Speed 300

unsigned int melody[8] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
unsigned int melody2[8] = {261, 293, 329, 349, 391, 440, 493, 523};*/

//===========================================================
//piezo buzzer test

/*void setup() {
  Serial.begin(9600);
  pinMode(buz, OUTPUT);
}

void loop() {
  for(int i=0; i<8; i++){
    Serial.println(melody[i]);
    
    for(int j=0; j<250; j++){
      digitalWrite(buz, HIGH);
      delayMicroseconds(melody[i]);
      digitalWrite(buz, LOW);
      delayMicroseconds(melody[i]);
    }
  }
}*/

//===========================================================
//piezo buzzer

/*void setup() {
  Serial.begin(9600);
  pinMode(buz, OUTPUT);
}

unsigned long curr_millis = 0;
unsigned long prev_millis = 0;
unsigned long curr_micros = 0;
unsigned long prev_micros = 0;

int melody_index = 0;
char melody_flag = 0;

void loop() {
  curr_micros = micros();
  curr_millis = millis();

  //---------------------------------------------------

  if(curr_millis - prev_millis > 1000){
    prev_millis = curr_millis;

    melody_index++;
    if(melody_index == 8) melody_index = 0;
  }

  //---------------------------------------------------
  
  if(curr_micros - prev_micros > melody[melody_index]){
    prev_micros = curr_micros;

    if(melody_flag == 0){
      melody_flag = 1;
      digitalWrite(buz, HIGH);
    }
    else{
      melody_flag = 0;
      digitalWrite(buz, LOW);
    }
  }
}*/

//===========================================================
//school bell

/*unsigned int School_Bell[24] = {NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4,
                                NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4,
                                NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4,
                                NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_C4};
unsigned int School_rhythm[24] = {Speed, Speed, Speed, Speed, Speed, Speed, (Speed * 2),
                                  Speed, Speed, Speed, Speed, (Speed * 3),
                                  Speed, Speed, Speed, Speed, Speed, Speed, (Speed * 2),
                                  Speed, Speed, Speed, Speed, (Speed * 3)};

void setup() {
  Serial.begin(9600);
  pinMode(buz, OUTPUT);
}

unsigned long curr_millis = 0;
unsigned long prev_millis = 0;
unsigned long prev_millis_750ms = 0;
unsigned long curr_micros = 0;
unsigned long prev_micros = 0;

int melody_index = 0;
char melody_flag = 0;
char melody_on = 1;

void loop() {
  curr_micros = micros();
  curr_millis = millis();

  //---------------------------------------------------
  if(curr_millis - prev_millis > (School_rhythm[melody_index] / 2) * 3){
    prev_millis = curr_millis;

    melody_index++;
    if(melody_index == 24) melody_index = 0;

    melody_on = 1;
    prev_micros = micros();
    prev_millis_750ms = curr_millis;
  }
  //---------------------------------------------------
  if(melody_on == 1){
    if(curr_millis - prev_millis_750ms > School_rhythm[melody_index]){
      prev_millis_750ms = curr_millis;
  
      melody_on = 0;
    }
  }
  //---------------------------------------------------
  if(melody_on == 1){
    if(curr_micros - prev_micros > School_Bell[melody_index]){
      prev_micros = curr_micros;
  
      if(melody_flag == 0){
        melody_flag = 1;
        digitalWrite(buz, HIGH);
      }
      else{
        melody_flag = 0;
        digitalWrite(buz, LOW);
      }
    }
  }
}*/

//===========================================================
//button matrix

void setup(){
  Serial.begin(9600);
  for(int i=0; i<4; i++){
    pinMode(i + 7, INPUT);
    pinMode(i + 15, OUTPUT);
  }
}

char col_pin_num[4] = {15, 16, 17, 18};
char row_pin_num[4] = {7, 8, 9, 10};
char row_flag[4] = {0, 0, 0, 0};
int col_index = 0;

void loop(){
  //1. all off
  for(int i=0; i<4; i++){
    digitalWrite(col_pin_num[i], LOW);
  }

  //2. 1 col on
  digitalWrite(col_pin_num[col_index], HIGH);

  //3. row read
  for(int i=0; i<4; i++){
    int row_value = digitalRead(row_pin_num[i]);
    if(row_value == 0){
      if(row_flag[i] == 0){
        row_flag[i] = 1;
      }
    }
    else{
      if(row_flag[i] == 1){
        row_flag[i] = 0;
        Serial.println((col_index + 1) + (i * 4));
      }
    }
  }

  //col index increase
  col_index++;
  if(col_index == 4) col_index = 0;

  //4. delay
  delay(10);
}
