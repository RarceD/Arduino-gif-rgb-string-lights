#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <PubSubClient.h>

#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 5
#define NUMPIXELS 4
#define MQTT_USER "asd"
#define MQTT_PASSWORD "asd"

#define MQTT_TEXT "hora_de_siluetas/r"
#define MQTT_HOLA "hora_de_siluetas/hola"
#define MQTT_ADIOS "hora_de_siluetas/adios"
#define MQTT_LOVE "hora_de_siluetas/love"

#define DELAYVAL 500

const char *ssid = "RUBEN14";        // Enter your WiFi name
const char *password = "9472302440"; // Enter WiFi password
const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

bool clear_les;
WiFiClient wifiClient;
PubSubClient client(wifiClient);
Adafruit_NeoPixel pixels1(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32ClientT-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD))
    {
      Serial.println("connected");

      client.subscribe(MQTT_TEXT);
      client.subscribe(MQTT_HOLA);
      client.subscribe(MQTT_ADIOS);
      client.subscribe(MQTT_LOVE);
      for (int i = 0; i < NUMPIXELS; i++)
      {
        pixels1.setPixelColor(i, pixels1.Color(0, 253, 2));
        pixels1.show();
        delay(DELAYVAL);
      }
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  //Serial.print("channel:");
  //Serial.println(topic);
  //Serial.print("data:");
  //Serial.write(payload, length);
  //Serial.println();
  char *msg = "hora_de_siluetas/r";
  char *hola = "hora_de_siluetas/hola";
  char *adios = "hora_de_siluetas/adios";
  char *love = "hora_de_siluetas/love";
  if (clear_les) {
    clear_les = false;
    for (int i = 4; i >= 0; i--)
    {
      pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
      pixels1.show();
      delay(10);
    }
  }
  if (!strcmp(topic, msg))
  {
    int random_led = random(0, 4);
    pixels1.setPixelColor(random_led, pixels1.Color(0, 238, 255));
    pixels1.show();
    delay(450);
    pixels1.setPixelColor(random_led, pixels1.Color(0, 0, 0));
    pixels1.show();
  }
  else if (!strcmp(topic, hola))
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels1.setPixelColor(i, pixels1.Color(130, 4, 219));
      pixels1.show();
      delay(DELAYVAL);
    }
    for (int i = 4; i >= 0; i--)
    {
      pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
      pixels1.show();
      delay(DELAYVAL);
    }
  }

  else if (!strcmp(topic, adios))
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels1.setPixelColor(i, pixels1.Color(4, 219, 158));
      pixels1.show();
      delay(DELAYVAL);
    }
    for (int i = 4; i >= 0; i--)
    {
      pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
      pixels1.show();
      delay(DELAYVAL);
    }
  }

  else if (!strcmp(topic, love))
  {
    pixels1.clear();
    for (int a = 0; a < 2; a++)
    {
      for (int i = 0; i < NUMPIXELS; i++)
      {
        pixels1.setPixelColor(i, pixels1.Color(219, 4, 58));
        pixels1.show();
        delay(50);
      }
      for (int i = 4; i >= 0; i--)
      {
        pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
        pixels1.show();
        delay(50);
      }
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pixels1.begin();
  pixels1.clear();
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels1.setPixelColor(i, pixels1.Color(254, 100, 2));
    pixels1.show();
    delay(DELAYVAL);
  }
  clear_les = true;
  Serial.setTimeout(500); // Set time out for
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
}

void loop()
{
  client.loop();

  // pixels1.clear();
  // for (int i = 0; i < NUMPIXELS; i++)
  // {

  //   pixels1.setPixelColor(i, pixels1.Color(25, 100, 255));
  //   pixels1.show();
  //   delay(DELAYVAL);
  // }
}
