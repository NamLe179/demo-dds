Hiện đang sử dụng 1 số config sau:
1. Sử dụng SHM
2. Flow Control đang để 10MB + chu kỳ 33ms
3. Log theo mỗi giây
4. QoS Reliability = Best Effort
5. QoS History = Keep last depth = 1
6. Cấp phát sẵn không gian nhớ + ghi đè
7. Deadline Writer = 38ms (33+5) và Reader = 50ms
8. XỬ lý đơn giản tại Sub: Duyệt qua 1 lượt tát cả các object nhận được
