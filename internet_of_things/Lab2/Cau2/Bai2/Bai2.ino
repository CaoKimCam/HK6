

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

const char* serverAddress = "192.168.1.100"; // Địa chỉ IP của máy tính chứa server
const int serverPort = 80; // Cổng mặc định của HTTP

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(100);

  dht.begin();

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Chờ một thời gian ngắn để chắc chắn kết nối ổn định
  delay(1000);
}

void loop() {
  // Đọc nhiệt độ và độ ẩm từ cảm biến
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Kiểm tra xem đọc dữ liệu từ cảm biến có thành công không
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% - Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Gửi dữ liệu lên server
  if (client.connect(serverAddress, serverPort)) {
    Serial.println("Connected to server");
    
    client.println("POST /data HTTP/1.1");
    client.println("Host: localhost");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    int contentLength = snprintf(NULL, 0, "temperature=%.2f&humidity=%.2f", temperature, humidity);
    client.println(contentLength);
    client.println("Connection: close");
    client.println();
    client.print("temperature=");
    client.print(temperature);
    client.print("&humidity=");
    client.print(humidity);

    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        // Kiểm tra phản hồi từ server để bật hoặc tắt đèn
        if (line.indexOf("Light turned on") != -1) {
          // Bật đèn
          Serial.println("Turning on the light");
          // Code để bật đèn ở đây
        } else if (line.indexOf("Light turned off") != -1) {
          // Tắt đèn
          Serial.println("Turning off the light");
          // Code để tắt đèn ở đây
        }
      }
    }
    
    client.stop();
    Serial.println("Disconnected from server");
  } else {
    Serial.println("Connection to server failed");
  }

  delay(5000); // Chờ 5 giây trước khi gửi dữ liệu tiếp theo
}
