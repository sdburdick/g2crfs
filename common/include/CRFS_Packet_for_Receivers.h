#include <cstdint>

#pragma pack(push, 1) //don't pad bytes between structure members
struct CPR_Packet {
    uint32_t seq; //_t forces fixed width to expected size regarless of hardware
    uint64_t timestamp_ns;
    float    value;
};
#pragma pack(pop)
