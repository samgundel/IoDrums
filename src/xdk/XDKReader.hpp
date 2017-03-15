#pragma once

#include "xdk/XDKTypes.hpp"

#include <cstdint>
#include <functional>

namespace iosound {
namespace xdk {

class XDKReader {

public:
    using XDKReceiverCallback = std::function<void(const XDKGiro& data)>;
    virtual void setReceiver(const XDKReceiverCallback& callback) = 0;
};

} // namespace xdk
} // namespace iosounds