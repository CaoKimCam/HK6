const express = require('express');
const bodyParser = require('body-parser');

// Khởi tạo ứng dụng Express
const app = express();
const PORT = 3000;

// Middleware để xử lý dữ liệu JSON
app.use(bodyParser.json());

// Biến lưu trữ trạng thái đèn
let numberOfLights = 0;

// Endpoint POST để nhận dữ liệu từ Wemos D1 Mini và cập nhật số lượng đèn cần bật
app.post('/data', (req, res) => {
  const { light, distance } = req.body;

  // Tính toán số lượng đèn cần bật dựa trên cường độ ánh sáng và khoảng cách
  if (light < 50) {
    numberOfLights = 3; // Nếu ánh sáng yếu, bật tất cả đèn
  } else if (distance < 50) {
    numberOfLights = 2; // Nếu có người gần, bật 2 đèn
  } else {
    numberOfLights = 0; // Nếu không có người gần, tắt tất cả đèn
  }

  // Trả về phản hồi JSON để xác nhận việc xử lý thành công
  res.json({ message: 'Data received', numberOfLights });
});

// Endpoint GET để trả về số lượng đèn cần bật
app.get('/lights', (req, res) => {
  res.json({ numberOfLights }); // Trả về số lượng đèn hiện tại
});

// Khởi động máy chủ
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
