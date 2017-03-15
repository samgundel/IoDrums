#pragma once

#include "xdk/XDKTypes.hpp"

#include <cstdint>
#include <functional>

namespace iosound {
namespace xdk {

class XDKReader {

public:
    using XDKGiroCallback = std::function<void(const XDKGiro& data)>;
    using XDKAccelerationCallback = std::function<void(const XDKAcceleration& data)>;
    virtual void setGiroReceiver(const XDKGiroCallback& callback) = 0;
    virtual void setAccelerationReceiver(const XDKAccelerationCallback& callback) = 0;
};

} // namespace xdk
} // namespace iosounds