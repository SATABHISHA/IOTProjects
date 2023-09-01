int pin = 2;

void setup() {
  // put your setup code here, to run once:
// initialize GPIO 2 as an output.
 pinMode (pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite (pin, HIGH);
delay (1000);
digitalWrite (pin, LOW);
delay (1000);
}