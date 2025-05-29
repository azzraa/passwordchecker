#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

// Function to generate SHA-256 hash
void sha256(const char *str, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)str, strlen(str), output);
}

// Function to print the hash in hexadecimal
void print_hash(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);
    printf("\n");
}

int main() {
    char password[128]; // User input password
    char salted[256]; // Buffer to hold password + salt
    unsigned char hash[SHA256_DIGEST_LENGTH];
    const char *salt = "random_salt"; // Fixed salt for this example

    // Paste the generated hash here:
    const unsigned char stored_hash[SHA256_DIGEST_LENGTH] = {
        0xfb, 0x28, 0xe1, 0x42, 0x69, 0xa7, 0x0d, 0xae,
        0xbe, 0x10, 0x17, 0x54, 0x3c, 0xec, 0x5e, 0x22,
        0xeb, 0x24, 0x8e, 0x2b, 0xc9, 0x62, 0x83, 0x8d,
        0x3f, 0x99, 0xb3, 0x4f, 0x07, 0xdc, 0xfa, 0x70
    };

    // Prompt user to enter a password
    printf("Enter password: ");
    scanf("%127s", password);

    // Salting: combine password + salt
    snprintf(salted, sizeof(salted), "%s%s", password, salt);
    // Hashing: generate SHA-256 hash of salted password
    sha256(salted, hash);

    // Compare generated hash with stored hash
    if (memcmp(hash, stored_hash, SHA256_DIGEST_LENGTH) == 0) {
        printf("Access Granted\n");
    } else {
        printf("Access Denied\n");
    }

    return 0;
}
