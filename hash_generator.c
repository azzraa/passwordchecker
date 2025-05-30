#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

// Function to print SHA-256 hash bytes in a formatted way
void print_hash_bytes(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    printf("{\n    ");
    // Loop through each byte of the hash
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        // Print each byte as a two-digit hexadecimal number prefixed with 0x
        printf("0x%02x", hash[i]);
        // Print a comma after every byte except the last one
        if (i != SHA256_DIGEST_LENGTH - 1)
            printf(", ");
        // After every 8 bytes, print a newline and indent for readability, except after the last byte
        if ((i + 1) % 8 == 0 && i != SHA256_DIGEST_LENGTH - 1)
            printf("\n    ");
    }
    printf("\n};\n");
}

int main() {
    const char *password = "mypassword";
    const char *salt = "random_salt";
    char combined[256]; // Buffer to hold password + salt concatenated
    unsigned char hash[SHA256_DIGEST_LENGTH]; // Buffer to hold the SHA-256 hash result

    // Combine password and salt into the combined buffer
    snprintf(combined, sizeof(combined), "%s%s", password, salt);
    // Combine the SHA-256 hash of the combined string
    SHA256((unsigned char *)combined, strlen(combined), hash);

    // Print info about what is being hashed
    printf("SHA-256 hash of \"%s\" + \"%s\":\n", password, salt);
    // Call function to print the hash bytes in formatted hexadecimal
    print_hash_bytes(hash);

    // Exit program
    return 0;
}
