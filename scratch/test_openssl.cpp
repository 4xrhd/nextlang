#include <openssl/evp.h>
#include <iostream>

int main() {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx) {
        std::cout << "OpenSSL EVP initialized successfully.\n";
        EVP_CIPHER_CTX_free(ctx);
    }
    return 0;
}
