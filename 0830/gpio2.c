#include <stdio.h>
#include <wiringPi.h>

#define LED 0

int count = 0;
int duty = 0;
int count_duty = 0;

int main(){
	printf("Raspberry Pi blink\n");
	wiringPiSetup();
	pinMode(LED, OUTPUT);

	for(;;){
		//digitalWrite(LED, HIGH);
		//delay(500);
		//digitalWrite(LED, LOW);
		//delay(500);
		if(count == 100){
			count = 0;
			digitalWrite(LED, HIGH);
		}
		else if(count == duty){
			digitalWrite(LED, LOW);
		}

		//----------------------------------

		if(count_duty == 100){
			count_duty = 0;
			duty++;
			if(duty == 99) duty = 0;
		}

		count++;
		count_duty++;
		delayMicroseconds(100);
	}
	return 0;
}
