# HƯỚNG DẪN TẠO VÀ CHẠY THƯ VIỆN TĨNH & ĐỘNG  

## 1. Thư viện tĩnh  
### 1.2 Tạo các object file:  

```bash
    gcc -c ./src/sub.c -I./include -o ./static_lib/sub.o
    gcc -c ./src/add.c -I./include -o ./static_lib/add.o
    gcc -c ./src/main.c -I./include -o ./static_lib/main.o
```  

- **Giải thích**:  
    - *`-I./include`* là một cách để báo cho chương trình biết phải tìm header file ở đâu. Trong trường hợp này nằm trong thư mục include.  

### 1.2 Tạo thư viện tĩnh:  
```bash
    ar -rcs ./static_lib/libmymath.a ./static_lib/add.o ./static_lib/sub.o
```  
- **Giải thích**:  
    - **ar** là viết tắt của **archive** file, là tên gọi của thư viện tĩnh.
    - *`rcs`*: 
        - **(r)** replace: Thêm hoặc cập nhật file `.o` vào thư viện `.a`. Nếu file `.o` đã có trong thư viện, nó sẽ được thay thế.
        - **(c)** create: Tạo thư viện mới nếu chưa tồn tại. Nếu đã có thì không làm gì.
        - **(s)** index table: Tạo **chỉ mục** cho thư viện đó (giúp linker trong quá trình linking).

### 1.3 Tạo file thực thi và chạy
```bash
    gcc ./static_lib/main.o -L./static_lib -lmymath -o ./static_lib/prog
    ./static_lib/pro
```  
- **Giải thích**:  
    - Dòng đầu tạo chương trình thực thi tên *prog* nằm trong thư mục *static_lib*. Cú pháp `-L` chỉ đường dẫn đến thư viện & cú pháp `-l` chỉ tên thư viện đó. Khi viết tên thư viện, ta bỏ tiền tố `lib` và phần mở rộng `.a`.  

## 2. Thư viện động  
### 2.1 Tạo các object file:  

```bash
    gcc -I./include -fPIC -c ./src/sub.c -o ./dynamic_lib/sub.o
    gcc -I./inlucde -fPIC -c ./src/add.c -o ./dynamic_lib/add.o
    gcc -I./include -fPIC -c ./src/main.c -o ./dynamic_lib/main.o
```

- **Giải thích**:  
    - *`PIC`*: position independent code, cho phép code được thực thi bất kể được load vào từ vị trí nào trong bộ nhớ.  

### 2.2 Tạo thư viện động:
```bash
    gcc -shared ./dynamic_lib/sub.o ./dynamic_lib/add.o -o ./dynamic_lib/libmymath.so
```
- **Giải thích**:
    - *`-shared`* là loại ký hiệu để chương trình biết cần tạo thư viện động. Do thư viện động được phép dùng chung từ nhiều nơi và tải vào trong runtime.
    - Khi đặt tên thư viện, nên để tên có **lib** ở đằng trước. Đây là cách đặt tên thư viện trong tiêu chuẩn.  

### 2.3 Tạo file thực thi và chạy:
```bash
    gcc ./dynamic_lib/main.o -L./dynamic_lib -lmymath -o ./dynamic_lib/prog
    export LD_LIBRARY_PATH=./dynamic_lib:$LD_LIBRARY_PATH
    ./dynalib/prog
```
- **Giải thích**:  
    - Dòng đầu tạo chương trình thực thi tên *prog* nằm trong thư mục *dynamic_lib*. Cú pháp `-L` chỉ đường dẫn đến thư viện & cú pháp `-l` chỉ tên thư viện đó. Khi viết tên thư viện, ta bỏ tiền tố `lib` và phần mở rộng `.so*`.  
    - Do thư viện động được tải vào trong runtime, nên để chạy được file thực thi, cần thêm đường dẫn tới thư viện động.
    Cú pháp: `export LD_LIBRARY_PATH=`**`[đường dẫn]`**`:$LD_LIBRARY_PATH`  