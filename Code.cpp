#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------- DHT22 ----------------
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ---------------- PINS ----------------
#define SOIL_PIN A0
#define RELAY_PIN 13      // ACTIVE-LOW relay
#define BUZZER_PIN 6
#define LED_PIN 5
#define TRIG_PIN 8
#define ECHO_PIN 9

// ---------------- SOIL CALIBRATION ----
#define DRY_VALUE 820
#define WET_VALUE 380

// ---------------- THRESHOLDS ----------
#define MOISTURE_THRESHOLD 60   // % below this → watering
#define TANK_LOW_LEVEL 12       // cm (tank empty limit)

// ---------------- BUZZER NOTES --------
#define BEAT 200
#define DO 262
#define RE 294
#define MI 330

bool pumpState = false;

// -------------------------------------

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(RELAY_PIN, HIGH);   // Pump OFF (ACTIVE LOW)

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not detected");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 28);
  display.println("System Ready");
  display.display();
  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  // ---- DHT ERROR CHECK ----
  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT Sensor Error");
    return;
  }

  // ---- SOIL MOISTURE ----
  int soilRaw = analogRead(SOIL_PIN);
  int moisture = map(soilRaw, DRY_VALUE, WET_VALUE, 0, 100);
  moisture = constrain(moisture, 0, 100);

  // ---- TANK LEVEL ----
  float tankLevel = getWaterLevel();

  // ---------------- SERIAL OUTPUT ----------------
  Serial.println("----- SYSTEM STATUS -----");
  Serial.print("Temperature : "); Serial.print(temp); Serial.println(" C");
  Serial.print("Humidity    : "); Serial.print(hum);  Serial.println(" %");
  Serial.print("Soil Moist. : "); Serial.print(moisture); Serial.println(" %");
  Serial.print("Tank Level  : "); Serial.print(tankLevel); Serial.println(" cm");
  Serial.println("--------------------------");

  // ---------------- OLED DISPLAY ----------------
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("T: "); display.print(temp); display.println(" C");
  display.print("H: "); display.print(hum); display.println(" %");

  display.setCursor(0, 24);
  display.print("Soil: "); display.print(moisture); display.println(" %");

  display.setCursor(0, 40);
  display.print("Pump: ");
  display.println(pumpState ? "ON" : "OFF");

  display.setCursor(64, 40);
  display.print("Tank:");
  display.print(tankLevel);

  display.display();

  // ---------------- TANK WARNING LED -------------
  digitalWrite(LED_PIN, tankLevel < TANK_LOW_LEVEL ? HIGH : LOW);

  // ---------------- WATERING LOGIC ---------------
  if (moisture < MOISTURE_THRESHOLD && tankLevel > TANK_LOW_LEVEL) {
    digitalWrite(RELAY_PIN, LOW);   // Pump ON
    if (!pumpState) {
      playDryTune();
      pumpState = true;
    }
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Pump OFF
    if (pumpState) {
      playWetTune();
      pumpState = false;
    }
  }

  delay(2000);
}

// ---------------- ULTRASONIC -------------------
float getWaterLevel() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;

  return duration * 0.034 / 2;
}

// ---------------- BUZZER -----------------------
void playDryTune() {
  tone(BUZZER_PIN, DO, BEAT);
  delay(BEAT);
  tone(BUZZER_PIN, RE, BEAT);
  delay(BEAT);
  tone(BUZZER_PIN, MI, BEAT);
  delay(BEAT);
  noTone(BUZZER_PIN);
}

void playWetTune() {
  tone(BUZZER_PIN, MI, BEAT);
  delay(BEAT);
  tone(BUZZER_PIN, RE, BEAT);
  delay(BEAT);
  tone(BUZZER_PIN, DO, BEAT);
  delay(BEAT);
  noTone(BUZZER_PIN);
}
