/**
 * Upeksharathy - Zen like driving.
 *
 * All right reservered - Tiny Magiq
 * support@tinymagiq.com
 */
#include <Grove_LED_Bar.h>

int ir1=9;
int ir2=10;
int ir3=11;
int ir4=6;;
int ir5=7;
int indicator_switch=2;
int indicator_led=13;
int status_flag=0;
int ir1_status,ir2_status,ir3_status,ir4_status,ir5_status,indicator_switch_status;
int buzzer=5;
int buzzer_state=0;
int pre_status_flag=0;
int switch_value=0;
int switch_control=0;
Grove_LED_Bar bar(3,2, 0);  // Clock pin, Data pin, Orientation

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("Started");

	pinMode(ir1,INPUT);
	pinMode(ir2,INPUT);
	pinMode(ir3,INPUT);
	pinMode(ir4,INPUT);
	pinMode(ir5,INPUT);
	pinMode(indicator_switch,INPUT);
	pinMode(indicator_led,OUTPUT);
	pinMode(buzzer,OUTPUT);

	bar.begin();
}

void loop() {
	// put your main code here, to run repeatedly:
	ir1_status=digitalRead(ir1);
	ir2_status=digitalRead(ir2);
	ir3_status=digitalRead(ir3);
	ir4_status=digitalRead(ir4);
	ir5_status=digitalRead(ir5);
	switch_value=analogRead(A0);
	if(switch_value<100) {
		switch_control=1;
	} else {
		switch_control=0;
	}

	Serial.print("A:");
	Serial.print(ir1_status);
	Serial.print("     B:");
	Serial.print(ir2_status);
	Serial.print("     C:");
	Serial.print(ir3_status);
	Serial.print("     D:");
	Serial.print(ir4_status);
	Serial.print("     E:");
	Serial.println(ir5_status);
	indicator_switch_status=digitalRead(indicator_switch);

	if(switch_control==0) {
		if(ir1_status==LOW) {
			status_flag=1;
		} else if(ir2_status==LOW) {
			status_flag=2;
		} else if(ir3_status==LOW) {
			status_flag=3;
		} else if(ir4_status==LOW) {
			status_flag=4;
		} else if(ir5_status==LOW) {
			status_flag=5;
		}

		switch(status_flag) {
			case 1:
				if(pre_status_flag==2) {
					digitalWrite(buzzer,LOW);
					Serial.println("Good driving");   
					bar.setLevel(2);
				}
				break;
			case 2:
				Serial.println("Stage2");
				bar.setLevel(4);
				if(buzzer_state==3) {
					digitalWrite(buzzer,LOW);
					Serial.println("Stage_cleared");
				}
				break;
			case 3:
				buzzer_state=1;
				bar.setLevel(6);
				Serial.println("Stage3");
				digitalWrite(buzzer,HIGH);
				delay(200);
				digitalWrite(buzzer,LOW);
				break;
			case 4:
				bar.setLevel(8);
				Serial.println("Stage4");
				buzzer_state=2;
				digitalWrite(buzzer,HIGH);
				delay(500);
				digitalWrite(buzzer,LOW);
				delay(200);
				break;
			case 5:
				bar.setLevel(10);
				Serial.println("Stage5");
				buzzer_state=3;
				digitalWrite(buzzer,HIGH);
				break;
		}

		pre_status_flag=status_flag;
	} else {
		Serial.println("indicating...");
		bar.setLevel(0);
		digitalWrite(indicator_led,HIGH);
		delay(400);
		digitalWrite(indicator_led,LOW);
		delay(390);
		pre_status_flag=0;
		status_flag=0;
	}
	delay(10);
}
