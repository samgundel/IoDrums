#pragma once

#include <cstdint>
#include <functional>

namespace iosound {
namespace xdk {

struct XDKData {
    float   yaw;
    float   pitch;
    float   roll;
    uint32_t pressure;
};

class XDKReader {

public:
    using XDKReceiverCallback = std::function<void(const XDKData& data)>;
    virtual void setReceiver(const XDKReceiverCallback& callback) = 0;
};

} // namespace xdk
} // namespace iosounds