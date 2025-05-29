#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void sha256(const char *str, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)str, strlen(str), output);
}

int main() {
    char password[128];
    char salted[256];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    const char *salt = "random_salt";

    // Paste the generated hash here:
    const unsigned char stored_hash[SHA256_DIGEST_LENGTH] = {
        0xe4, 0x55, 0x52, 0xea, 0x9f, 0xa0, 0xf1, 0xd8, 
        0xb2, 0x53, 0x07, 0x4e, 0x54, 0x6c, 0x7f, 0x21, 
        0x78, 0x7b, 0x01, 0x3c, 0x05, 0x7b, 0x13, 0x48, 
        0xeb, 0xe9, 0x81, 0xe5, 0xd7, 0x0e, 0x76, 0xe2
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
