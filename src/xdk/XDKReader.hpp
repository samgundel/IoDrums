#pragma once

#include "xdk/XDKTypes.hpp"

#include <cstdint>
#include <functional>

namespace iosound {
namespace xdk {

class XDKReader {

public:
    using XDKModeCallback = std::function<void(bool plates)>;
    using XDKAccelerationCallback = std::function<void(const XDKAcceleration& data)>;
    virtual void setModeReceiver(const XDKModeCallback& callback) = 0;
    virtual void setAccelerationReceiver(const XDKAccelerationCallback& callback) = 0;
};

} // namespace xdk
} // namespace iosounds