# Secure Password Checker in C using OpenSSL

The project is written in C and uses the OpenSSL library to securely hash and verify passwords using SHA-256. The program prompts the user to enter a password, salts it, hashes it using SHA-256 and compares it to a stored hash. If the hashes match, access is granted and otherwise, access is denied.

## 🧰 Requirements

- C Compiler
- OpenSSL development libraries

### 📦 Install OpenSSL on macOS:

```bash
brew install openssl@3
```

### 📂 Project Structure

```text
passwordchecker/
├── password_checker.c
└── README.md
```

### ⚙️ How It Works

1. User inputs a password.
2. A salt (e.g., "random_salt") is appended to the input.
3. The salted password is hashed using SHA-256 via OpenSSL.
4. The resulting hash is compared to a stored reference hash.
5. The program prints Access Granted or Access Denied based on the result.

### 🧪 Example Output

```bash
Enter password: secret  
Access Granted  
Enter password: wrongpass  
Access Denied
```
