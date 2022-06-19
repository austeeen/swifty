#ifndef BITMASK
#define BITMASK

#include <cstdint>

class Bitmask
{
public:
    Bitmask();

    void setMask(const Bitmask& other);
    uint64_t getMask() const;
    void clearMask();

    void setBit(const int pos, const bool on);
    void setBit(const int pos);
    bool getBit(const int pos) const;
    void clearBit(const int pos);

    uint64_t operator|(const Bitmask& other) const;
    uint64_t operator&(const Bitmask& other) const;
    bool operator==(const Bitmask& other) const;
    bool operator==(const uint64_t& other) const;

private:
    uint64_t __mask;
};

#endif /* BITMASK */
