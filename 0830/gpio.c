#include <stdio.h>
#include <wiringPi.h>

#define LED 0

int main(){
	printf("Raspberry Pi blink\n");
	wiringPiSetup();
	pinMode(LED, OUTPUT);

	for(;;){
		digitalWrite(LED, HIGH);
		delay(500);
		digitalWrite(LED, LOW);
		delay(500);
	}
	return 0;
}
