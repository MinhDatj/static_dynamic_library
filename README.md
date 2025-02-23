# HƯỚNG DẪN TẠO VÀ CHẠY THƯ VIỆN TĨNH & ĐỘNG  

## Thư viện động  
### Tạo các object file:  

```bash
    gcc -I./include -fPIC -c ./src/sub.c -o ./dynalib/sub.o
    gcc -I./inlucde -fPIC -c ./src/add.c -o ./dynalib/add.o
    gcc -I./include -fPIC -c ./src/main.c -o ./dynalib/main.o
```

- **Giải thích**:
    - *`-I./include`* là một cách để báo cho chương trình biết phải tìm header file ở đâu. Trong trường hợp này nằm trong thư mục include.  
    - *`PIC`*: position independent code, cho phép code được thực thi bất kể được load vào từ vị trí nào trong bộ nhớ.  

### Tạo thư viện động
```bash
    gcc -shared ./dynalib/sub.o ./dynalib/add.o -o libmymath.so
```
- **Giải thích**:
    - *`-shared`* là loại ký hiệu để chương trình biết cần tạo thư viện động. Do thư viện động được phép dùng chung từ nhiều nơi và tải vào trong runtime.
    - Khi đặt tên thư viện, nên để tên có **lib** ở đằng trước. Đây là cách đặt tên thư viện trong tiêu chuẩn.  

### Tạo file thực thi và chạy
```bash
    gcc ./dynalib/main.o -L./dynalib -lmymath -o ./dynalib/prog
    export LD_LIBRARY_PATH=./dynalib:$LD_LIBRARY_PATH
    ./dynalib/prog
```
- **Giải thích**:  
    - Dòng đầu tạo chương trình thực thi tên *prog* nằm trong thư mục *dynalib*. Cú pháp `-L` chỉ đường dẫn đến thư viện & cú pháp `-l` chỉ tên thư viện đó. Khi viết tên thư viện, ta bỏ tiền tố *lib* và phần mở rộng *.so*.  
    - Do thư viện động được tải vào trong runtime, nên để chạy được file thực thi, cần thêm đường dẫn tới thư viện động.
    Cú pháp: `export LD_LIBRARY_PATH=`**`[đường dẫn]`**`:$LD_LIBRARY_PATH`  