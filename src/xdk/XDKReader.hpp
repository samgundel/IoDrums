#pragma once

#include "xdk/XDKTypes.hpp"

#include <cstdint>
#include <functional>

namespace iosound {
namespace xdk {

class XDKReader {

public:
    using XDKModeCallback = std::function<void(bool plates)>;
    using XDKHitCallback = std::function<void(uint8_t mode)>;
    virtual void setModeReceiver(const XDKModeCallback& callback) = 0;
    virtual void setHitReceiver(const XDKHitCallback& callback) = 0;
};

} // namespace xdk
} // namespace iosounds