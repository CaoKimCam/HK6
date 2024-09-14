#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "firebase"; // SSID của Wi-Fi
const char* password = "12345678"; // Mật khẩu Wi-Fi

ESP8266WebServer server(80); // HTTP Server trên cổng 80

// Định nghĩa chân đèn LED
const int ledPins[] = {D3, D4, D5, D6, D7}; // 5 đèn LED
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

int score = 5; // Điểm khởi đầu
int correctAnswer = 0; // Số lượng đèn đúng
unsigned long gameStartTime; // Thời điểm bắt đầu trò chơi
unsigned long maxResponseTime = 2000; // Thời gian cho phép đoán (2 giây)
bool gameInProgress = false; // Trạng thái trò chơi
bool guessMade = false; // Đã đoán
bool isFirst=true;

// Nội dung HTML cho trang web
const char* htmlContent = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Guess the Number Game</title>
</head>
<body>
  <h1>Guess the Number Game</h1>
  <p>Choose the correct number of lights:</p>
  <div>
    <button onclick="makeGuess(0)">0</button>
    <button onclick="makeGuess(1)">1</button>
    <button onclick="makeGuess(2)">2</button>
  </div>
  <p id="result">Your score: </p>

  <script>
    function makeGuess(choice) {
      fetch('/guess?choice=' + choice)
        .then(response => response.text())
        .then(data => {
          document.getElementById('result').innerText = data;
        })
        .catch(error => {
          console.error('Error:', error);
        });
    }
  </script>
</body>
</html>
)=====";

// Bật đèn LED ngẫu nhiên
void turnOnRandomLeds() {
  if (isFirst){
    for (int i=0; i<5; i++){
      digitalWrite(ledPins[i], HIGH);
      delay(100);
    }
    delay(100);
    for (int i=4; i>=0; i--){
      digitalWrite(ledPins[i], LOW);
      delay(500);
    }
    isFirst=false;
  }
  int count = random()%5+1; // Số lượng ngẫu nhiên từ 1 đến 5
  correctAnswer = count%3; // Số lượng đúng
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW); // Tắt tất cả đèn trước
  }
  // Bật đèn ngẫu nhiên, không trùng lặp
  bool chosen[numLeds] = {false}; // Mảng để theo dõi đèn đã chọn
  for (int i = 0; i < count; i++) {
    int led;
    do {
      led = rand()%5; // Chọn đèn ngẫu nhiên
    } while (chosen[led]); // Nếu đã chọn thì chọn lại
    
    chosen[led] = true; // Đánh dấu đèn đã chọn
    digitalWrite(ledPins[led], HIGH); // Bật đèn
  }

  delay(2000); // Thời gian để người chơi quan sát
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW); // Tắt tất cả đèn
  }
  gameStartTime = millis(); // Lưu thời gian bắt đầu sau khi tắt đèn
  Serial.println(count);
}

// Hàm bắt đầu trò chơi
void handleGameStart() {
  gameInProgress = true; // Đánh dấu trò chơi đang diễn ra
  guessMade = false; // Cho phép đoán
  turnOnRandomLeds(); // Bật đèn ngẫu nhiên
  server.send(200, "text/html", htmlContent); // Gửi trang web cho người chơi
}

// Xử lý yêu cầu đoán
void handleGameGuess() {
  if (!gameInProgress) { // Trò chơi chưa bắt đầu
    server.send(400, "text/html", "Start the game first.");
    return;
  }
  unsigned long currentTime = millis(); // Thời gian hiện tại
  if (currentTime - gameStartTime > maxResponseTime) { // Quá 2 giây
    score -= 1; // Trừ 2 điểm
    server.send(200, "text/html", "Time's up! Score: " + String(score));
  } else { // Nếu đoán trong thời gian
    int guess = server.arg("choice").toInt(); // Lấy dự đoán
    if (guess == correctAnswer) { // Đúng
      score++; // Cộng điểm
      server.send(200, "text/html", "Correct! Score: " + String(score));
    } else { // Sai
      score--; // Trừ điểm
      server.send(200, "text/html", "Wrong! Score: " + String(score));
    }
  }
  if (guessMade) { // Nếu đã đoán, không cho phép đoán lại
    server.send(400, "text/html", "You've already guessed.");
    return;
  }

  guessMade = true; // Đánh dấu đã đoán

  if (score < 0) { // Kết thúc trò chơi khi điểm dưới 0
    gameInProgress = false; // Trò chơi kết thúc
    server.send(200, "text/html", "Game over. Your score is below zero.");
  } else {
    gameInProgress = true; // Tiếp tục trò chơi nếu còn điểm
  }
}

// Cài đặt Wi-Fi và máy chủ
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(WiFi.localIP());
  // Khởi tạo các chân đèn LED
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT); // Cài đặt chân LED là OUTPUT
  }

  // Thiết lập máy chủ
  server.on("/start", HTTP_GET, handleGameStart);
  server.on("/guess", HTTP_GET, handleGameGuess);
  server.begin(); // Bắt đầu máy chủ
}

void loop() {
  server.handleClient(); // Xử lý các yêu cầu HTTP
}
