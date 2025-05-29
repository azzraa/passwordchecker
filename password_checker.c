#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

// Function to compute SHA-256 hash of a given input string
void sha256(const char *str, unsigned char output[SHA256_DIGEST_LENGTH]) {
   // SHA256() takes input bytes, length, and output buffer
    SHA256((unsigned char *)str, strlen(str), output);
}

int main() {
    char password[128]; // Buffer to store user-entered password
    char salted[256]; // Buffer to store password + salt concatenation
    unsigned char hash[SHA256_DIGEST_LENGTH]; // Buffer to store the computed hash output
    const char *salt = "random_salt"; // The salt string appended to the password before hashing

    // Paste the generated hash here:
    const unsigned char stored_hash[SHA256_DIGEST_LENGTH] = {
    0xfb, 0x28, 0xe1, 0x42, 0x69, 0xa7, 0x0d, 0xae, 
    0xbe, 0x10, 0x17, 0x54, 0x3c, 0xec, 0x5e, 0x22, 
    0xeb, 0x24, 0x8e, 0x2b, 0xc9, 0x62, 0x83, 0x8d, 
    0x3f, 0x99, 0xb3, 0x4f, 0x07, 0xdc, 0xfa, 0x70
};

    // Prompt the user to enter a password
    printf("Enter password: ");
    scanf("%127s", password);

    // Combine the entered password with the salt string
    snprintf(salted, sizeof(salted), "%s%s", password, salt);
    sha256(salted, hash);

    // Compare the computed hash with the stored hash byte-by-byte
    if (memcmp(hash, stored_hash, SHA256_DIGEST_LENGTH) == 0) {
        // If they match, grant access
        printf("Access Granted\n");
    } else {
        // Otherwise, deny access
        printf("Access Denied\n");
    }

    // Exit program
    return 0; 
}
