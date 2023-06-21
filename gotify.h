#include "Gotify.h"
#include <WiFiClientSecure.h>

const char* serverName = "example.com"; // Replace with your Gotify server domain name
const int serverPort = 443; // Default Gotify port is 443
const char* authToken = "your-auth-token"; // Replace with your Gotify authentication token

void sendGotifyNotification(String title, String message, int priority) {
  WiFiClientSecure client;
  if (!client.connect(serverName, serverPort)) {
    Serial.println("Connection failed.");
    return;
  }

  String body = "title=" + title + "&message=" + message + "&priority=" + String(priority);

  String request = "POST /message?token=" + String(authToken) + " HTTP/1.1\r\n";
  request += "Host: " + String(serverName) + "\r\n";
  request += "Content-Type: application/x-www-form-urlencoded\r\n";
  request += "Content-Length: " + String(body.length()) + "\r\n";
  request += "Connection: close\r\n\r\n";
  request += body;

  client.print(request);

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }

  String response = client.readString();

  Serial.println(response);
}
