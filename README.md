📌 **Giới thiệu**

Dự án xây dựng một hệ thống đăng ký, đăng nhập và quản lý ví điểm cho người dùng. Bao gồm 2 vai trò chính:

-Người dùng thường: có thể đăng ký tài khoản, đăng nhập, đổi mật khẩu, chuyển điểm, và xem lịch sử giao dịch.

-Quản trị viên (admin): có thể tạo tài khoản admin, chỉnh sửa thông tin người dùng, xóa tài khoản, chuyển điểm, và xem danh sách người dùng.

📋 **Đặc tả chức năng**

🔐 *Chức năng Đăng ký / Đăng nhập*

-Đăng ký tài khoản mới: nhập tên đăng nhập, tên đầy đủ, có thể để trống mật khẩu để hệ thống tự sinh.

-Đăng nhập bằng username + mật khẩu.

-Nếu mật khẩu là tự sinh, hệ thống sẽ yêu cầu đổi trong lần đăng nhập đầu tiên.

📁 *Quản lý tài khoản*

Người dùng có thể:

-Xem thông tin tài khoản

-Đổi mật khẩu (ẩn bằng dấu *)

-Cập nhật tên

-Xem lịch sử giao dịch

-Chuyển điểm sang ví khác (OTP xác minh)

-Admin có thể:

-Xem danh sách tài khoản

-Tạo tài khoản admin khác

-Chỉnh sửa tên người dùng (không đổi username hoặc mật khẩu)

-Xem thông tin người dùng

-Xóa tài khoản (trừ chính mình)

-Chuyển điểm cho người dùng khác

🛠️ **Hướng dẫn cài đặt & dịch chương trình**

1. *Yêu cầu*

-Visual Studio 2022 (hoặc IDE C++ hỗ trợ và ISO C++14 Standard)

Không yêu cầu thư viện ngoài

2. **Cấu trúc thư mục*

├── Auth.cpp
├── Data_io.cpp
├── login_system.h
├── Main.cpp
├── Menu.cpp
├── User_ops.cpp
├── Utils.cpp
└── users.dat (sẽ tự tạo nếu chưa có)

3. Cách dịch chương trình

-Tạo project mới trên Visual Studio 2022 (Console App, Empty Project)

-Thêm tất cả 7 file .cpp vào project

-Đảm bảo file Main.cpp là file chính (Startup File)

-Build → Run (Ctrl + F5)

▶️ **Cách chạy chương trình**

Khi chạy lần đầu:

-Hệ thống tự tạo tài khoản admin mặc định:

Username: admin
Password: admin

Menu chính:

1. Register    2. Login    0. Exit



Sau khi đăng nhập:

Người dùng:

1. View Profile   2. Change Password
3. Update Name    4. Transaction History
5. Transfer Points

Quản trị viên:

1. List Users     2. Create Admin
3. Edit User      4. View User Info
5. Transfer Points   6. Delete User

🔒 **Bảo mật**

Mật khẩu được mã hóa bằng std::hash

OTP được sinh ngẫu nhiên khi thực hiện chuyển điểm hoặc thao tác quản trị quan trọng

Mật khẩu nhập vào được ẩn bằng dấu *

📚 **Tài liệu tham khảo**

- https://stackoverflow.com/
- https://www.geeksforgeeks.org/
- https://chatgpt.com/
- https://www.youtube.com/watch?v=rkmxgfnj5yM&t=893s
- https://www.youtube.com/watch?v=fTdkqOS5_ro
- https://www.geeksforgeeks.org/generate-one-time-password-unique-identification-url/
- https://www.draytek.com/support/knowledge-base/4923 (tham khảo giao diện)

