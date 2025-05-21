#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "HARIHARAN";
const char* password = "thanya02";

// Telegram Bot Token and chat ID
const char* botToken = "7838506267:AAGkfmdtccidygS9D3yJtCyFgg5H5Tgwz3o";
const int64_t chatID = 1437420185;

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

// OpenWeatherMap settings
const char* weatherApiKey = "11ca39d66d2c9d325051ba7a0804619e";
const float lat = 11.1271;
const float lon = 78.6569;

// Track last checked message
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

// Weather fetch function
String getWeatherReport() {
  HTTPClient http;
  String weatherURL = "http://api.openweathermap.org/data/2.5/weather?lat=" + String(lat, 4) +
                      "&lon=" + String(lon, 4) + "&appid=" + weatherApiKey + "&units=metric";

  http.begin(weatherURL);
  int httpCode = http.GET();

  if (httpCode == 200) {
    String payload = http.getString();
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, payload);

    String condition = doc["weather"][0]["main"].as<String>();
    String description = doc["weather"][0]["description"].as<String>();
    float temp = doc["main"]["temp"];
    int humidity = doc["main"]["humidity"];
    float wind = doc["wind"]["speed"];
    
    String report = "Weather Report:\n";
    report += "Condition: " + condition + " (" + description + ")\n";
    report += "Temp: " + String(temp) + "°C\n";
    report += "Humidity: " + String(humidity) + "%\n";
    report += "Wind Speed: " + String(wind) + " m/s\n";
    
    if (condition.indexOf("Rain") >= 0) {
      report += "Rain Alert: YES\n";
    } else {
      report += "Rain Alert: No rain expected.\n";
    }

    http.end();
    return report;
  } else {
    http.end();
    return "Error fetching weather data.";
  }
}

// Handle Telegram messages
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String msgText = bot.messages[i].text;
    String fromUser = bot.messages[i].from_id;

    if (msgText.equalsIgnoreCase("weather")) {
      String weatherInfo = getWeatherReport();
      bot.sendMessage(fromUser, weatherInfo, "");
    } else {
      bot.sendMessage(fromUser, "Send 'weather' to get current weather info.", "");
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("WiFi connected");
  client.setInsecure();  // Accept all SSL certs
}

void loop() {
  if (millis() - lastTimeBotRan > botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
