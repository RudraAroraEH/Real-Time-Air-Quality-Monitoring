#define BLYNK_TEMPLATE_ID "Your Blynk Template id"
#define BLYNK_TEMPLATE_NAME "Air Quality Monitoring"
#define BLYNK_AUTH_TOKEN "Your Blynk Auth Token"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = ""; // Replace with your Wi-Fi name
char pass[] = ""; // Replace with your Wi-Fi password

BlynkTimer timer;

int gas = A0;
int sensorThreshold = 100;
#define BUZZER_PIN D5 // Buzzer connected to GPIO D5

#define DHTPIN D4 // DHT11 connected to GPIO D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celsius
  int gasValue = analogRead(gas);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, gasValue);

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C | Humidity: ");
  Serial.print(h);
  Serial.print("% | Gas Value: ");
  Serial.println(gasValue);

  // Trigger Blynk event for high pollution
  if (gasValue > 600) {
    Blynk.logEvent("pollution_alert", "Bad Air Quality Detected!");
  }

  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(t);
  display.print(" C");
  display.setCursor(0, 10);
  display.print("Humidity: ");
  display.print(h);
  display.print(" %");
  display.setCursor(0, 20);
  display.print("Gas: ");
  display.print(gasValue);

  if (gasValue > 600) {
    display.setCursor(0, 30);
    display.print("Air Quality: Bad");
    digitalWrite(BUZZER_PIN, HIGH); // Activate buzzer
  } else {
    display.setCursor(0, 30);
    display.print("Air Quality: Good");
    digitalWrite(BUZZER_PIN, LOW); // Deactivate buzzer
  }
  display.display();
}

void setup() {
  Serial.begin(115200);

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Initialize DHT sensor
  dht.begin();

  // Initialize OLED display
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  // Initialize Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Welcome message on OLED
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.print("Air Quality Monitoring");
  display.display();
  delay(2000);
  display.clearDisplay();

  // Set up periodic sensor reading
  timer.setInterval(30000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
