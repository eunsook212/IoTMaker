/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
int led_pin = 6;
int analog_pin = A1;
int light_val;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_pin, OUTPUT);
  pinMode(analog_pin, INPUT);
  Serial.begin(9600);
  
}

// the loop function runs over and over again forever
void loop() {
                      // wait for a second
                  // wait for a second
  Serial.print("light:");

  light_val = analogRead(analog_pin);
  light_val = light_val / 4;
  Serial.println(light_val);

  if(light_val < 190) {
    digitalWrite(led_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);   
  } else {
    digitalWrite(led_pin, LOW);    // turn the LED off by making the voltage LOW
    delay(500);     
  }
}
