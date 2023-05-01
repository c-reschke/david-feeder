#include <Arduino.h>
#include <Servo.h>

#define TO_FEED D7
#define LED D0
#define LED_0 D3
#define SERVO D4

const long interval = 1000;
unsigned long current_time = millis();
unsigned long last_trigger = 0;
boolean timer_on = false;
Servo servo;

void feed()
{
  int qtd = 1;
  for (int i = 0; i < qtd; i++)
  {
    for (int z = 0; z < 10; z++)
    {

      servo.write(0);
      delay(1000);
      servo.write(90);
      delay(1000);
    }
  }
}

void led()
{
  Serial.println("led INIT");

  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
  Serial.println("led FIM");
}

IRAM_ATTR void inter()
{
  Serial.println("Motion was detected");
  digitalWrite(LED_0, HIGH);
  timer_on = true;
  last_trigger = millis();
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(TO_FEED, INPUT_PULLUP);
  servo.attach(SERVO, 430, 2590);

  servo.write(0);
  digitalWrite(LED, LOW);
  attachInterrupt(digitalPinToInterrupt(TO_FEED), inter, RISING);
}

void loop()
{
  current_time = millis();
  if (timer_on && (current_time - last_trigger > interval))
  {
    Serial.println("Motion has stopped");
    digitalWrite(LED_0, LOW);
    timer_on = false;
  }
}