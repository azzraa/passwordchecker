#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

// Function to compute SHA-256 hash of a given input string
void sha256(const char *str, unsigned char output[SHA256_DIGEST_LENGTH]) {
   // SHA256() takes input bytes, length and output buffer
    SHA256((unsigned char *)str, strlen(str), output);
}

int main() {
    char password[128]; // Buffer to store user-entered password
    char salted[256]; // Buffer to store password + salt combination
    unsigned char hash[SHA256_DIGEST_LENGTH]; // Buffer to store the computed hash output
    const char *salt = "random_salt"; // The salt string appended to the password before hashing

    // Paste the generated hash here:
    const unsigned char stored_hash[SHA256_DIGEST_LENGTH] = {
    0x62, 0x44, 0x4a, 0x72, 0x11, 0x86, 0xd7, 0xa3, 
    0x1c, 0x3b, 0xd1, 0xa3, 0x84, 0x1d, 0xd8, 0xdd, 
    0xa9, 0x55, 0xe4, 0xf2, 0x0e, 0x17, 0x0e, 0xbd, 
    0x2d, 0x4c, 0x99, 0x09, 0x54, 0x29, 0xc8, 0x22
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
