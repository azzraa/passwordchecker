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
├── hash_generator.c
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

### 🔨 How to Generate the Stored Hash (hash_generator.c)

You can create a small helper program to generate the SHA-256 hash for any password + salt combination and print the raw bytes for use in your main program:

```bash
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void sha256(const char *str, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)str, strlen(str), output);
}

void print_hash_bytes(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    printf("{\n    ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("0x%02x", hash[i]);
        if (i != SHA256_DIGEST_LENGTH - 1) printf(", ");
        if ((i + 1) % 8 == 0) printf("\n    ");
    }
    printf("\n};\n");
}

int main() {
    const char *password = "secret";
    const char *salt = "random_salt";
    char salted[256];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    snprintf(salted, sizeof(salted), "%s%s", password, salt);
    sha256(salted, hash);

    printf("Hash bytes for \"%s%s\":\n", password, salt);
    print_hash_bytes(hash);

    return 0;
}
```

Compile and run:
```bash
gcc hash_generator.c -o hash_generator \
  -I/opt/homebrew/opt/openssl@3/include \
  -L/opt/homebrew/opt/openssl@3/lib \
  -lssl -lcrypto
```

```bash
./hash_generator
```

It will print out the hash byte array, which you can copy and paste as stored_hash in your password_checker.c.

### 📄 password_checker.c

Paste the following into your password_checker.c file:

```bash
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void sha256(const char *str, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)str, strlen(str), output);
}

void print_hash(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);
    printf("\n");
}

int main() {
    char password[128];
    char salted[256];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    const char *salt = "random_salt";

    const unsigned char stored_hash[SHA256_DIGEST_LENGTH] = {
        0xfb, 0x28, 0xe1, 0x42, 0x69, 0xa7, 0x0d, 0xae,
        0xbe, 0x10, 0x17, 0x54, 0x3c, 0xec, 0x5e, 0x22,
        0xeb, 0x24, 0x8e, 0x2b, 0xc9, 0x62, 0x83, 0x8d,
        0x3f, 0x99, 0xb3, 0x4f, 0x07, 0xdc, 0xfa, 0x70
    };

    printf("Enter password: ");
    scanf("%127s", password);

    snprintf(salted, sizeof(salted), "%s%s", password, salt);
    sha256(salted, hash);

    if (memcmp(hash, stored_hash, SHA256_DIGEST_LENGTH) == 0) {
        printf("Access Granted\n");
    } else {
        printf("Access Denied\n");
    }

    return 0;
}
```

### 🛠️ Build & Run

**Compile the program:**
```bash
cc password_checker.c -o password_checker \
  -I/opt/homebrew/opt/openssl@3/include \
  -L/opt/homebrew/opt/openssl@3/lib \
  -lssl -lcrypto
```

**Run the program:**
```bash
./password_checker
```

### 🛠️ VS Code Configuration (Optional but Recommended)

If you're using **Visual Studio Code** and see this error:

*include error: "openssl/sha.h" file not found*

Update your includePath by creating *.vscode/c_cpp_properties.json*:

```bash
{
    "configurations": [
        {
            "includePath": [
                "${workspaceFolder}/**",
                "/opt/homebrew/opt/openssl@3/include"
            ],
        }
    ],
}
```

💡 After adding this file, restart VS Code and reopen your .c file to apply the changes.

### ✅ Done!

Now your program securely checks a password using SHA-256 and OpenSSL. 
