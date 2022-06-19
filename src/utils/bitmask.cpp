#include "bitmask.hpp"

Bitmask::Bitmask() :
__mask(0)
{}
void Bitmask::setMask(const Bitmask& other)
{
    __mask = other.getMask();
}
uint64_t Bitmask::getMask() const
{
    return __mask;
}
bool Bitmask::getBit(const int pos) const
{
    return (__mask & (1 << pos)) != 0;
}
void Bitmask::setBit(const int pos, const bool on)
{
    if(on)
        setBit(pos);
    else
        clearBit(pos);
}
void Bitmask::setBit(const int pos)
{
    __mask = __mask | 1 << pos;
}
void Bitmask::clearBit(const int pos)
{
    __mask = __mask & ~(1 << pos);
}
void Bitmask::clearMask()
{
    __mask = 0;
}
uint64_t Bitmask::operator|(const Bitmask& other) const
{
    return this->__mask | other.getMask();
}
uint64_t Bitmask::operator&(const Bitmask& other) const
{
    return this->__mask & other.getMask();
}
bool Bitmask::operator==(const Bitmask& other) const
{
    return this->__mask == other.__mask;
}
bool Bitmask::operator==(const uint64_t& other) const
{
    return this->__mask == other;
}
