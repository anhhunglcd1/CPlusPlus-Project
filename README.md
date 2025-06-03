✨**1. Giới thiệu dự án**
📌 **Tên dự án:**
Hệ thống đăng nhập, đăng ký tài khoản và quản lý ví điểm thưởng

📝 **Mô tả:**
Dự án xây dựng một hệ thống phần mềm trên nền tảng C++ hỗ trợ các chức năng:

📝 Đăng ký tài khoản mới (User Registration)

🔑 Đăng nhập tài khoản (Login)

👤 Quản lý thông tin cá nhân (Profile)

💰 Quản lý ví điểm thưởng (Wallet)

🔄 Thực hiện các giao dịch chuyển điểm giữa các ví (Transfer Points)

🔐 Xác thực giao dịch, đổi thông tin bằng mã OTP (OTP Verification)

🛠️ Chức năng quản trị viên (Admin): quản lý, chỉnh sửa, xóa tài khoản, xem lịch sử giao dịch...

👥 **2. Giới thiệu thành viên và phân công công việc**
Nhóm thực hiện: 2 thành viên

STT	👨‍💻 Họ và tên	📝 Công việc được giao
1	[Tên thành viên 1]	- Thiết kế, xây dựng giao diện menu, luồng đăng nhập/đăng ký
- Xử lý quản lý thông tin tài khoản, đổi mật khẩu, xác thực OTP
- Tham gia xây dựng giao diện quản lý tài khoản cho admin
2	[Tên thành viên 2]	- Thiết kế và cài đặt chức năng quản lý ví, giao dịch chuyển điểm
- Quản lý lịch sử giao dịch, lưu trữ dữ liệu ra file
- Tham gia xây dựng chức năng chỉnh sửa, xóa user, backup dữ liệu

*️⃣ Mỗi thành viên đều tham gia test, viết tài liệu và hoàn thiện báo cáo.

📋 **3. Bản phân tích, đặc tả chức năng**
🎯 **Chức năng chính**
📝 **Đăng ký tài khoản:**
- Nhập username, mật khẩu, họ tên. Kiểm tra trùng lặp, lưu nếu hợp lệ.

🔑 **Đăng nhập:**
- Nhập username, mật khẩu để truy cập hệ thống.

👤 **Quản lý tài khoản cá nhân:**
- Xem thông tin cá nhân, đổi mật khẩu (OTP), đổi họ tên (OTP).

💰 **Quản lý ví điểm thưởng:**
- Xem số dư, lịch sử giao dịch.

🔄 **Giao dịch chuyển điểm:**
- Chuyển điểm sang ví khác (kiểm tra số dư, OTP), ghi lại lịch sử giao dịch hai chiều.

🛠️ **Quản trị viên (admin):**

- Tạo tài khoản mới cho user khác

- Chỉnh sửa thông tin tài khoản (đổi tên, đổi mật khẩu – cần xác nhận OTP)

- Xóa tài khoản

- Xem danh sách người dùng

- Xem và kiểm tra lịch sử giao dịch của bất kỳ user nào

💾 **Sao lưu dữ liệu:**
- Tự động sao lưu dữ liệu mỗi lần chạy chương trình.

📦 **4. Hướng dẫn tải, biên dịch, các tập tin và thư viện**
📂 **Cấu trúc tập tin:**

- Main.cpp: Chương trình chính, luồng điều khiển menu

- Auth.cpp: Xử lý đăng nhập, đăng ký, xác thực OTP

- Data_io.cpp: Đọc/ghi dữ liệu người dùng và ví từ file

- Menu.cpp: Giao diện menu cho user và admin

- User_ops.cpp: Xử lý chức năng user/admin

- Utils.cpp: Hàm tiện ích chung (OTP, password, clear screen...)

- login_system.h: Định nghĩa cấu trúc, khai báo hàm

- users.dat, users.bak: File dữ liệu và backup

- pending_change.txt: Lưu thông tin các thay đổi cần xác nhận OTP

📚 **Thư viện sử dụng:**

- Chuẩn C++: <iostream>, <fstream>, <vector>, <string>, <iomanip>, <ctime>, <random>, <sstream>, <conio.h> (Windows)

- Không dùng thư viện ngoài

⚙️ **Cách tải/chạy/dịch chương trình:**

**Tải mã nguồn:**

- Copy tất cả file .cpp, .h vào cùng thư mục.

**Dịch chương trình:**

- Sử dụng Visual Studio 2022 hoặc g++ (chuẩn C++11 trở lên).

**Nếu dùng dòng lệnh:**
- css
- Copy
- Edit
- g++ Main.cpp Auth.cpp Data_io.cpp Menu.cpp User_ops.cpp Utils.cpp -o AccountManager
- Nếu dùng Visual Studio: tạo project mới, thêm các file vào project, build là xong.

- Không cần thư viện ngoài.

▶️ **5. Hướng dẫn chạy chương trình & thao tác**
🚀 **Khởi động chương trình:**

- Lần đầu chạy, hệ thống tự tạo tài khoản nếu chưa có.

📌 **Các thao tác cơ bản:**

📝 **Đăng ký tài khoản mới:**

- Chọn "Register", nhập username, họ tên, mật khẩu (có thể để trống để tự sinh).

🔑 **Đăng nhập:**

- Chọn "Login", nhập username, mật khẩu.

👤 **Sau khi đăng nhập:**

- User vào menu user: xem/đổi thông tin, chuyển điểm, xem lịch sử ví...

- Admin vào menu admin: quản lý tài khoản, tạo/sửa/xóa user, xem lịch sử giao dịch hệ thống.

🔄 **Chuyển điểm:**

- Menu "Transfer Points" → nhập ID ví nhận → nhập số điểm → xác thực OTP.

✏️ **Đổi thông tin cá nhân (họ tên/mật khẩu):**

- Đổi xong sẽ sinh OTP, lần đăng nhập sau xác nhận OTP để áp dụng thay đổi.

🗑️ **Xóa user:**

- Chỉ admin được phép xóa tài khoản, không được xóa chính mình.

💡 **Lưu ý:**

- Dữ liệu lưu file, tự động sao lưu mỗi lần chạy.

- Đổi tên/mật khẩu do admin thao tác hộ cần xác nhận OTP khi user login lần sau.

- Chạy hoàn toàn trên console (dòng lệnh).



📚 **Tài liệu tham khảo**

- https://stackoverflow.com/
- https://www.geeksforgeeks.org/
- https://chatgpt.com/
- https://www.youtube.com/watch?v=rkmxgfnj5yM&t=893s
- https://www.youtube.com/watch?v=fTdkqOS5_ro
- https://www.geeksforgeeks.org/generate-one-time-password-unique-identification-url/
- https://www.draytek.com/support/knowledge-base/4923 (tham khảo giao diện)
- https://www.youtube.com/watch?v=TDR_jECRHpg

