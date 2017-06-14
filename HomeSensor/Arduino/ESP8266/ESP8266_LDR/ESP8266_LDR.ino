#include <PubSubClient.h>
#include <ESP8266WiFi.h>

/************************* WiFi Access Point *********************************/
#define WLAN_SSID "BTHub6-Q892"
#define WLAN_PWD "73YVNvwmAaqV"


/*************************** MQTT Details ***********************************/
#define MQTT_SERVER "192.168.0.5"
#define MQTT_PORT 1883
#define topic_ldr "Home/Node2/LDR"

WiFiClient espClient;
PubSubClient client(espClient);

const int ldrPin = 0;


void setup() {

  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  int ldr = 0;
  if (!client.connected()) {
    reconnect();
    }
  client.loop(); 

  ldr=analogRead(0);
  Serial.println(ldr);
  client.publish(topic_ldr, String(ldr).c_str(), true);
  delay(5000);
}
