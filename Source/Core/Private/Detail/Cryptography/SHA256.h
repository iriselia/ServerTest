#include <openssl/sha.h>

class BigNumber;

class Core_API SHA256Hash
{
    public:
        typedef std::integral_constant<uint32, SHA256_DIGEST_LENGTH> DigestLength;

        SHA256Hash();
        ~SHA256Hash();

        void UpdateBigNumbers(BigNumber* bn0, ...);

        void UpdateData(const uint8 *dta, int len);
        void UpdateData(const std::string &str);

        void Initialize();
        void Finalize();

        uint8 *GetDigest(void) { return mDigest; }
        int GetLength(void) const { return SHA256_DIGEST_LENGTH; }

    private:
        SHA256_CTX mC;
        uint8 mDigest[SHA256_DIGEST_LENGTH];
};
