#include <WiFi.h>
#include <WiFiAP.h>

char ssid[] = "WiFi_Name";        // your network SSID
char pass[] = "12345678";         // your network password

WiFiServer server(80);            // Create a web server on port 80

void setup() {
  Serial.begin(115200);
  delay(3000);

  // Start the access point
  WiFi.beginAP(ssid, pass);
  
  // Wait for the AP to initialize
  delay(5000);

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Start the web server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");

    // Wait for data from the client
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);  // Echo received data back to the serial monitor
        // Serve an HTTP response
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        client.println("<html><body><h1>Hello from the ESP32!</h1></body></html>");
        break;
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}