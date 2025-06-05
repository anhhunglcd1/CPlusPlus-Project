# 🎁 HỆ THỐNG ĐĂNG NHẬP, ĐĂNG KÝ & QUẢN LÝ VÍ ĐIỂM THƯỞNG

---

## 🚀 Giới thiệu dự án

**Hệ thống đăng nhập, đăng ký và quản lý ví điểm thưởng** là ứng dụng mô phỏng hệ thống quản lý tài khoản người dùng kèm ví điểm thưởng, với xác thực bảo mật, phân quyền và đầy đủ chức năng chuyển điểm, đổi thông tin, ghi log lịch sử.

---

## 👨‍💻👩‍💻 Thành viên & phân công công việc

| Thành viên                | Công việc chính phụ trách                                                                                                                                                             |
|---------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 🧑‍💻**Phạm Ngọc Nghĩa**  | Thiết kế, xây dựng giao diện menu, luồng đăng nhập/đăng ký, xử lý quản lý thông tin tài khoản, đổi mật khẩu, xác thực OTP, tham gia xây dựng giao diện quản lý tài khoản cho admin.   |
| 👨‍💻 **Nguyễn Đức Công**    | Thiết kế và cài đặt chức năng quản lý ví, giao dịch chuyển điểm, quản lý lịch sử giao dịch, lưu trữ dữ liệu ra file, tham gia xây dựng chức năng chỉnh sửa, xóa user, backup dữ liệu.|

---

## 📑 Phân tích & Đặc tả chức năng

### 1️⃣ Đăng ký tài khoản
- Nhập username (không trùng, không rỗng), họ tên, mật khẩu (ẩn hoặc auto-gen nếu để trống).
- Điểm thưởng được cộng tự động từ pool hệ thống.

### 2️⃣ Đăng nhập hệ thống
- Đăng nhập bằng username và mật khẩu (ẩn).
- Nếu có thao tác pending (đổi tên/mật khẩu do admin đổi hộ), sẽ phải xác nhận OTP ở lần đăng nhập tiếp theo.

### 3️⃣ Quản lý thông tin tài khoản
- Xem, đổi tên, đổi mật khẩu (yêu cầu OTP với thao tác nhạy cảm).
- Nếu mật khẩu là auto-generated, bắt buộc đổi mật khẩu sau lần đăng nhập đầu.

### 4️⃣ Quản lý ví điểm & giao dịch
- Mỗi user có ví với ID riêng, lưu số dư và điểm nguồn gốc pool.
- Chuyển điểm qua wallet ID (không phân biệt hoa/thường).
- Ghi lại lịch sử giao dịch đầy đủ cho minh bạch.

### 5️⃣ Phân quyền
- **Admin:** có thể tạo user, chỉnh sửa, xóa user, chuyển điểm không giới hạn, xem reward pool, xem chi tiết mọi user.
- **Người dùng thường:** chỉ thao tác trên tài khoản, ví và lịch sử của mình.

### 6️⃣ Bảo mật & xác thực
- Mật khẩu hash, không lưu plain text.
- OTP xác nhận cho đổi tên/đổi mật khẩu quan trọng.
- Giao dịch, thao tác lớn luôn được log hoặc xác thực lại.

### 7️⃣ Lưu trữ, backup
- Tự động backup dữ liệu người dùng trước mọi thao tác nguy hiểm.
- Lịch sử giao dịch, trạng thái pool, thay đổi pending đều ghi file, dễ kiểm tra/phục hồi.

---

## 🗂️ Cấu trúc thư mục & các file nguồn

| File                | Chức năng                                                         |
|---------------------|-------------------------------------------------------------------|
| `Main.cpp`          | Chương trình chính, menu ngoài, kiểm tra & khởi tạo admin         |
| `Auth.cpp`          | Đăng ký, đăng nhập, xóa user, xác thực OTP                       |
| `Data_io.cpp`       | Đọc, ghi dữ liệu user, reward pool, backup, quản lý file          |
| `Menu.cpp`          | Xây dựng giao diện menu cho user & admin                         |
| `User_ops.cpp`      | Đổi tên, đổi mật khẩu, chuyển điểm, log giao dịch, xác nhận OTP   |
| `Utils.cpp`         | Tiện ích: sinh mật khẩu ngẫu nhiên, sinh OTP, hash, clear màn hình|
| `login_system.h`    | Khai báo các struct, hàm chung dùng toàn bộ chương trình          |
| `users.dat`         | Dữ liệu user (tạo tự động khi chạy chương trình)                  |
| `reward_pool.dat`   | Số điểm thưởng còn lại trong pool                                 |
| `pending_change.txt`| Log các thay đổi chờ xác nhận OTP                                 |
| `users.bak`         | File backup dữ liệu user dự phòng                                 |

---

## ⚙️ Yêu cầu & Cách cài đặt

- **Hệ điều hành:** Windows hoặc Linux (test chuẩn trên cả hai)
- **Trình biên dịch:** Visual Studio 2022, hoặc g++/clang++ mới
- **Thư viện:** Chuẩn C++ (không cần thêm thư viện ngoài)
- **Không cần cài thêm thư viện!**

---

## 📥 Cách tải, biên dịch và chạy chương trình

1️⃣ **Tải source code**

**Clone hoặc tải về từ GitHub:**
```bash
https://github.com/anhhunglcd1/CPlusPlus-Project.git
```
2️⃣ **Biên dịch**

🖥️ **Visual Studio 2022**

- Mở project, thêm toàn bộ file .cpp và .h vào project mới.
- Nhấn Ctrl+Shift+B để Build Solution.

🐧 **Linux (g++ khuyến nghị)**

- g++ -o wallet Main.cpp Auth.cpp Data_io.cpp Menu.cpp User_ops.cpp Utils.cpp -std=c++17

3️⃣ **Chạy chương trình**

- Windows: nhấn F5 trong Visual Studio 2022.
- Linux: Chạy lệnh: ./wallet

🕹️ **Hướng dẫn sử dụng & thao tác chức năng**

🚪 **Menu chính**

| **Chức năng**           |**Ý nghĩa**                                      |
|-------------------------|-------------------------------------------------|
| **Register**            | Đăng ký tài khoản mới                           |
| **Login**               | Đăng nhập (dành cho cả admin & user)            |
| **Exit**                | Thoát chương trình                              |
  
👤 **User Menu**
| **Chức năng**           |**Ý nghĩa**                                      |
|-------------------------|-------------------------------------------------|
| **View Profile**        | Xem thông tin tài khoản                         | 
| **Change Password**     | Đổi mật khẩu (yêu cầu OTP)                      |
| **Change Name**         | Đổi tên (yêu cầu OTP)                           |
| **Transaction History** | Xem lịch sử giao dịch điểm                      |
| **Transfer Points**     | Chuyển điểm cho user khác                       |
| **Logout**              | Đăng xuất                                       |



👑 **Admin Menu**
| **Chức năng**           |**Ý nghĩa**                                      |
|-------------------------|-------------------------------------------------|
| **List Users**          | Danh sách tài khoản                             |
| **Create User**         | Tạo user mới                                    |
| **Edit User**           | Đổi tên/mật khẩu hộ user (user xác nhận qua OTP)|
| **View User**           | Xem chi tiết thông tin user bất kỳ              |
| **Transfer Points**     | Chuyển điểm (admin không bị trừ)                |
| **Delete User**         | Xóa tài khoản user                              |
| **View Reward Pool**    | Xem số điểm thưởng còn lại (tối đa 30 điểm)     |
| **Logout**              | Đăng xuất admin                                 |

🎯 **Ghi chú sử dụng**

- Mỗi thao tác quan trọng đều có xác nhận OTP hoặc backup dự phòng.
- Lịch sử giao dịch lưu rõ nguồn nhận/chuyển, minh bạch.
- Giao diện menu căn chỉnh rõ ràng, dùng được cả trên Windows và Linux.
- Dữ liệu user, log, pool tự động lưu file, thuận tiện phục hồi.
---
📚 **Tài liệu tham khảo**
```bash
- https://stackoverflow.com/
- https://www.geeksforgeeks.org/
- https://chatgpt.com/
- https://www.youtube.com/watch?v=rkmxgfnj5yM&t=893s
- https://www.youtube.com/watch?v=fTdkqOS5_ro
- https://www.geeksforgeeks.org/generate-one-time-password-unique-identification-url/
```
- https://www.draytek.com/support/knowledge-base/4923 (tham khảo giao diện)
- https://www.youtube.com/watch?v=TDR_jECRHpg


