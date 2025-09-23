# k58.ktp-baitap1

nội dung bài tập  một

1 — Caesar

Tên gọi: Caesar cipher (mã Caesar / shift cipher)

Thuật toán mã hoá:

Khóa: k ∈ {0..25}.

Với mỗi ký tự P (A=0..Z=25): C = (P + k) mod 26.

Thuật toán giải mã:

P = (C − k + 26) mod 26.

Không gian khóa: 26 khả năng.

Cách phá (không cần khóa):

Brute-force thử 26 khóa.

Phân tích tần suất (văn bản dài) để đoán k.

* kết quả thực hiện

- c++
  
 <img width="1097" height="912" alt="image" src="https://github.com/user-attachments/assets/e03c4eda-1651-47a7-99f7-df4d3939081d" />

- bằng html+css+javascript
  
  + mã hóa
   <img width="1576" height="733" alt="image" src="https://github.com/user-attachments/assets/ade03766-d4b0-4400-893b-83c732807061" />

  +giải mã
  
  <img width="1705" height="766" alt="image" src="https://github.com/user-attachments/assets/6f3ce305-98f6-4b33-ad8a-38b697743387" />
  
2 — Affine

Tên gọi: Affine cipher

Thuật toán mã hoá:

Khóa: (a,b) với gcd(a,26)=1 (a ∈ {1,3,5,7,9,11,15,17,19,21,23,25}), b ∈ {0..25}.

C = (a·P + b) mod 26.

Thuật toán giải mã:

Tính a^{-1} modulo 26 (nghịch đảo).

P = a^{-1} · (C − b) mod 26.

Không gian khóa: 12 * 26 = 312.

Cách phá:

Brute-force thử mọi cặp (a,b) (312 khả năng).

Frequency analysis (do đây là substitution tuyến tính).

* kết quả

-bằng c++

 <img width="923" height="531" alt="image" src="https://github.com/user-attachments/assets/1a60e17a-a9d1-4039-ba26-688adc131541" />

- bằng html+css+javascript

+ mã hóa
  
  <img width="1871" height="831" alt="image" src="https://github.com/user-attachments/assets/7f6809c2-80f1-424e-926c-46f118279dbc" />

+ giải mã

  <img width="1731" height="815" alt="image" src="https://github.com/user-attachments/assets/2038af3a-7b49-4efa-b473-edca51dca1f5" />

3 — Hoán vị (Columnar transposition)

Tên gọi: Columnar transposition (mã tráo cột / hoán vị)

Thuật toán mã hoá (columnar đơn giản):

Khóa: một từ (ví dụ "SECRET") — thứ tự cột tính bằng thứ tự chữ cái.

Viết plaintext theo hàng vào ma trận có số cột = độ dài khóa (m).

Đệm ký tự (ví dụ 'X') nếu chữ cuối thiếu.

Đọc các cột theo thứ tự khóa (cột nhỏ hơn theo chữ cái đọc trước) → ciphertext.

Giải mã:

Biết m, chia ciphertext theo chiều dài cột rồi đặt cột theo thứ tự khóa, đọc theo hàng.

Không gian khóa: Nếu khóa là hoán vị của m phần tử → m! khả năng (rất lớn khi m tăng).

Cách phá:

Thử mọi hoán vị cho m nhỏ.

Dùng phân tích ngôn ngữ hoặc đo lường độ "tiếng" kết quả.

* kết quả bài tập

- c++

  <img width="961" height="492" alt="image" src="https://github.com/user-attachments/assets/a49a3a3e-b26f-4b54-b838-5f457941ad4f" />

- bằng html+css+javascript

+ mã hóa
+ 
  <img width="1894" height="919" alt="image" src="https://github.com/user-attachments/assets/41e25cda-facc-4a8f-b747-3cf0223b279f" />

+ giải mã

 <img width="1894" height="919" alt="image" src="https://github.com/user-attachments/assets/e5a05f47-a4ea-46d6-87de-f9ce294955df" />

4 — Vigenère

Tên gọi: Vigenère cipher

Thuật toán mã hoá:

Khóa: từ khóa K có độ dài m.

Mỗi ký tự: C_i = (P_i + k_{i mod m}) mod 26.

Giải mã:

P_i = (C_i − k_{i mod m} + 26) mod 26.

Không gian khóa: 26^m (rất lớn khi m tăng).

Cách phá (không cần khóa):

Kasiski examination để tìm độ dài khóa m.

Friedman test (index of coincidence) để ước lượng m.

Sau khi tìm m, tách chuỗi thành m chuỗi con và áp dụng phân tích tần suất (mỗi chuỗi con tương đương Caesar).

* kết quả bài tập

- c++
  
  <img width="970" height="511" alt="image" src="https://github.com/user-attachments/assets/6950a8f3-3941-4dfa-a7d0-0355a345aae0" />

- bằng html+css+javascript
   + Mã hóa
   
   <img width="1872" height="788" alt="image" src="https://github.com/user-attachments/assets/9bcaa91e-6718-4702-a6fc-28d20820fc0a" />

   + Giair mã
     
   <img width="1823" height="922" alt="image" src="https://github.com/user-attachments/assets/f73e2825-ffa3-48ee-ac74-7d7290d81b58" />
   
5 — Playfair

Tên gọi: Playfair cipher (mã Playfair)

Mô tả nhanh: mã hai-chữ (digraph) dùng ma trận 5×5 key-square. Thường gộp I/J để vừa 25 ô.

Tạo bảng khóa (5×5):

Khóa là một từ/ cụm từ. Viết các chữ cái trong khóa (loại trùng lặp), sau đó điền các chữ cái còn lại theo thứ tự A→Z (bỏ J hoặc gộp J→I).

Chuẩn hoá plaintext (digraph):

Loại bỏ dấu, giữ A–Z, biến J→I (theo quy ước).

Tách thành các digraph (cặp ký tự). Nếu một cặp có hai chữ cái giống nhau (ví dụ "AA"), chèn ký tự padding (thường là 'X') giữa chúng rồi tiếp tục phân cặp.

Nếu cuối cùng còn 1 ký tự lẻ, thêm chữ 'X' để hoàn thiện.

Thuật toán mã hoá (cho mỗi digraph XY):

Nếu X và Y cùng hàng: thay bởi ký tự ngay bên phải từng chữ (wrap-around).

Nếu X và Y cùng cột: thay bởi ký tự ngay dưới từng chữ (wrap-around).

Nếu khác hàng và khác cột: thay bằng hai chữ tạo thành 2 góc còn lại của hình chữ nhật: X' = (hàng X, cột Y), Y' = (hàng Y, cột X).

Giải mã: làm ngược lại:

cùng hàng → lấy ký tự bên trái.

cùng cột → lấy ký tự bên trên.

khác hàng/cột → hoán đổi cột tương tự.

Không gian khóa: tất cả các hoán vị có thể của 25 chữ cái → 25! (rất rất lớn). Nhưng thực tế khóa chỉ là một chuỗi ký tự khả dĩ — không gian thực tế phụ thuộc cách bạn tạo key-square (26! scaled down).

Cách phá:

Brute-force toàn bộ key-space không thực tế.

Phân tích kiếm tra các digraph, thử dùng heuristic / hill-climbing / simulated annealing để tìm key-square tốt (các công trình về giải Playfair dùng search heuristic).

Nếu plaintext có cấu trúc (từ phổ biến), có thể tận dụng pattern digraph.

* kết quả bài tập

- c++
  
- mã hóa

<img width="1485" height="744" alt="image" src="https://github.com/user-attachments/assets/ee1c7ada-6508-48fe-8114-5b1fd129e090" />

- giải mã

  <img width="1261" height="664" alt="image" src="https://github.com/user-attachments/assets/ac4b1990-da2c-4602-98a3-4c9eb9f01f6a" />


- bằng html+css+javascript

  + mã hóa

    <img width="1692" height="698" alt="image" src="https://github.com/user-attachments/assets/cfb8fb45-8ee4-47d5-879c-e8a91ca86f6c" />

  + giải mã

    <img width="1808" height="728" alt="image" src="https://github.com/user-attachments/assets/113feb9e-6b6f-4e80-9a86-6fa2e77cb33b" />
