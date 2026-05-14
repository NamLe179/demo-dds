Khác biệt công nghệ:
- Thay thế FastDDS bằng thư viện RTI Connext
- Yêu cầu: đăng ký bản free (free 60 ngày/bản non-commercial), yêu cầu điền form và đợi phản hồi, hết hạn cần gửi mail xin license mới (cho bản non-commercial)
- Add path rti sau khi đã cài đặt
- Cần ghi đè license vào path của thư viện (có 1 file rti_license.dat mẫu ghi đè file này)
- Thêm path license vào Qt Creator để chạy 

Khác biệt về cấu hình:
- Sử dụng UDP
- Tách thành từng gói tin nhỏ, batching tự động bằng rti, (đủ 2000 tin/đạt giới hạn 128KB - hiện tổng gói tin ~ 110KB/đạt giới hạn thời gian) tự động gửi đi
- Logs sẽ khác 1 chút do hiển thị theo từng giây chính xác, nên sẽ bị lẻ về log thay vì chính xác chẵn hàng nghìn, thời gian xử lý sẽ lâu hơn nên tốc độ gửi/nhận chênh lệch nhiều hơn và do cần lấy các gói tin đơn ra xử lý thay vì lấy 2000 gói tin trong 1 frame như trước 