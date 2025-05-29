#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void print_hash_bytes(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    printf("{\n    ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("0x%02x", hash[i]);
        if (i != SHA256_DIGEST_LENGTH - 1)
            printf(", ");
        if ((i + 1) % 8 == 0 && i != SHA256_DIGEST_LENGTH - 1)
            printf("\n    ");
    }
    printf("\n};\n");
}

int main() {
    const char *password = "secret";
    const char *salt = "random_salt";
    char combined[256];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    snprintf(combined, sizeof(combined), "%s%s", password, salt);
    SHA256((unsigned char *)combined, strlen(combined), hash);

    printf("SHA-256 hash of \"%s\" + \"%s\":\n", password, salt);
    print_hash_bytes(hash);

    return 0;
}
