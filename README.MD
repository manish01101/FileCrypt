# Encrypt-Decrypt File Processing Tool

## Overview

This tool encrypts and decrypts text files using a simple shift cipher mechanism. The encryption key is read from a `.env` file, and files are processed in place.

---

## 1. Build Instructions
  ## Makefile Details
  The Makefile has been structured to support macOS (ARM64 & Intel), Linux, and Windows. Update the given makefile variables and compiler flags based on the type of OS.

  **For macOS (Apple Silicon ARM64):**
  ```makefile
  CXX = g++
  CXXFLAGS = -std=c++17 -g -Wall -arch arm64 -I. -Isrc/app/encryptDecrypt -Isrc/app/fileHandling -Isrc/app/processes
  ```

  **For Linux & Windows (WSL/Git Bash):**
  ```makefile
  CXX = g++
  CXXFLAGS = -std=c++17 -g -Wall -I. -Isrc/app/encryptDecrypt -Isrc/app/fileHandling -Isrc/app/processes
  ```

  All compiled object files are stored in the `build/` directory for better organization.

### **Building the Project**

#### **Using a Single Core**

```sh
make
```

<span style="display:inline-block;background:#f4f4f4;padding:5px;border-radius:5px;cursor:pointer;" onclick="navigator.clipboard.writeText('make')">📋 Copy</span>

#### **Using All CPU Cores (Faster Build on All OS)**

For **macOS (ARM64 & Intel):**

```sh
make -j$(sysctl -n hw.ncpu)
```

<span style="display:inline-block;background:#f4f4f4;padding:5px;border-radius:5px;cursor:pointer;" onclick="navigator.clipboard.writeText('make -j$(sysctl -n hw.ncpu)')">📋 Copy</span>

For **Linux:**

```sh
make -j$(nproc)
```

<span style="display:inline-block;background:#f4f4f4;padding:5px;border-radius:5px;cursor:pointer;" onclick="navigator.clipboard.writeText('make -j$(nproc)')">📋 Copy</span>

For **Windows (Using Git Bash or WSL):**

```sh
make -j$(nproc)
```

<span style="display:inline-block;background:#f4f4f4;padding:5px;border-radius:5px;cursor:pointer;" onclick="navigator.clipboard.writeText('make -j$(nproc)')">📋 Copy</span>

This will compile the project using all available CPU cores for faster execution.

___

## 2. Usage

### a. **Before Running the Program**

Ensure you have a **valid encryption key** in a `.env` file:

```sh
echo "5" > .env  # Replace 5 with your desired encryption key
```

### b. **Encrypt a File**

```sh
./cryption test/test1.txt,ENCRYPT
```

### c. **Decrypt a File**

```sh
./cryption test/test1.txt,DECRYPT
```

### d. **Process a Directory**

If you want to **encrypt/decrypt all files** in a folder:

```sh
./encrypt_decrypt
```

Then, follow the prompts:

```sh
Enter the directory path: test/
Enter the action (encrypt/decrypt): encrypt
```

---

## 🛠️ Troubleshooting

### **Common Issues & Fixes**

#### 🔹 **Invalid task data format**

✔️ **Solution:** Ensure the correct command format:

```sh
./cryption test/test1.txt,ENCRYPT  # ✅ Correct
./cryption test/test1.txt  # ❌ Incorrect (Missing action)
```

#### 🔹 **File Not Found Error**

✔️ **Solution:** Ensure the file exists before running the command:

```sh
ls test/test1.txt  # Check if file exists
```

#### 🔹 **Encryption Key Error**

✔️ **Solution:** Ensure `.env` has a **valid number**:

```sh
cat .env  # Should display a numeric key (e.g., 5)
```

---

## 🏗️ Project Structure

```
project-root/
├── src/
│   ├── app/
│   │   ├── encryptDecrypt/
│   │   │   ├── Cryption.cpp
│   │   ├── fileHandling/
│   │   │   ├── IO.cpp
│   │   │   ├── ReadEnv.cpp
│   │   ├── processes/
│   │   │   ├── ProcessManagement.cpp
│   │   │   ├── Task.cpp
│   ├── main.cpp
├── Makefile
├── .env
├── README.md
```

---

## 📌 Notes

- **File processing is done in place** (no backup is created automatically).
- **Make sure to decrypt files before modifying them**, as encrypted files may become unreadable.

🚀 **Happy Coding!**

