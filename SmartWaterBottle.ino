#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <DHT.h>

#define in1 D0
#define in2 D1
#define in3 D2
#define in4 D3
#define servo D5
#define DHTPIN 12  // Define the pin where your DHT sensor is connected
#define DHTTYPE DHT11  // Set the type of the DHT sensor

Servo myservo;
int buttonState;
int button2State;
int button3state;
float temperature;
float humidity;

char ssid[] = "Kunalm30s";
char pass[] = "11032004";
char auth[] = "pvXY1dfS_LgP7O3x4LMRad1tbv7-HCw3";

#define BLYNK_TEMPLATE_ID "TMPL3MVVQ4ZZy"
#define BLYNK_TEMPLATE_NAME "smart water bottle"
#define BLYNK_AUTH_TOKEN "pvXY1dfS_LgP7O3x4LMRad1tbv7-HCw3"

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  myservo.attach(servo);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  dht.begin();
}

BLYNK_WRITE(V1) {
  buttonState = param.asInt();
}

BLYNK_WRITE(V2) {
  button2State = param.asInt();
}

BLYNK_WRITE(V3) {
  button3state = param.asInt();
}

void fan_und_cold_hot() {
  if (buttonState == 1) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(200);
    Serial.println("Im Here");
  } else if (buttonState == 0) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(200);
  }
  if (button2State == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(200);
    Serial.println("Im Here");
  } else if (button2State == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(200);
  }
  if (button3state == 1) {
    myservo.write(180);
    delay(800);
    myservo.write(0);
    delay(800);
  } else {
    myservo.write(0);
  }
}

void readDHTSensor() {
  temperature = dht.readTemperature();
}

void loop() {
  Blynk.run();
  fan_und_cold_hot();
  readDHTSensor();
  Blynk.virtualWrite(V4, temperature);
}
