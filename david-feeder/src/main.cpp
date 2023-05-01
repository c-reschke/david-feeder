#include <Arduino.h>
#include <Servo.h>
#include <MQTT.h>
#include <ESP8266WiFi.h>

void myDataCb(String &topic, String &data);
void myPublishedCb();
void myDisconnectedCb();
void myConnectedCb();

#define CLIENT_ID "rZYRpEtoMx"

// create MQTT object
MQTT myMqtt(CLIENT_ID, "broker.hivemq.com", 1883);

//
const char *ssid = "cmd.exe";
const char *password = "rsk90000";

#define TO_FEED D7
#define LED D0
#define LED_0 D3
#define SERVO D4

const long interval = 1000;
unsigned long current_time = millis();
unsigned long last_trigger = 0;
boolean timer_on = false;
Servo servo;
String mqttData;

void feed(int qtd)
{

  String topic("/");
  topic += CLIENT_ID;
  topic += "/value";

  mqttData = "0";

  if (WiFi.status() == WL_CONNECTED)
  {
    myMqtt.publish(topic, mqttData);
  }
  for (int i = 0; i < qtd; i++)
  {
    for (int z = 0; z < 2; z++)
    {
      servo.write(0);
      delay(500);
      servo.write(90);
      delay(500);
    }
  }

  mqttData = "1";
  if (WiFi.status() == WL_CONNECTED)
  {
    myMqtt.publish(topic, mqttData);
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
  digitalWrite(LED_0, HIGH);
  feed(2);
  digitalWrite(LED_0, LOW);
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

  delay(1000);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Connecting to MQTT server");

  // setup callbacks
  myMqtt.onConnected(myConnectedCb);
  myMqtt.onDisconnected(myDisconnectedCb);
  myMqtt.onPublished(myPublishedCb);
  myMqtt.onData(myDataCb);

  Serial.println("connect mqtt...");
  myMqtt.connect();

  delay(10);
}

void loop()
{
}

/*
 *
 */
void myConnectedCb()
{
  Serial.println("connected to MQTT server");
}

void myDisconnectedCb()
{
  Serial.println("disconnected. try to reconnect...");
  delay(500);
  myMqtt.connect();
}

void myPublishedCb()
{
  Serial.println("published.");
}

void myDataCb(String &topic, String &data)
{

  Serial.print(topic);
  Serial.print(": ");
  Serial.println(data);
}
