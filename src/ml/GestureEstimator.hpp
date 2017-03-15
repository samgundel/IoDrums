#pragma once

#include "xdk/XDKTypes.hpp"

#include <functional>

namespace iosound {
namespace ml {

using GestureReceiver = std::function<void(bool)>;

class GestureEstimator {
public:
    virtual void pushGiroEntry(const xdk::XDKGiro& giro) = 0;
    virtual void pushAccelerationEntry(const xdk::XDKAcceleration& giro) = 0;
    virtual void changeMode(bool plates) = 0;
    virtual void setGestureReceiver(const GestureReceiver& gestureReceiver) = 0;
    virtual ~GestureEstimator() = default;
};

} // namespace ml
} // namespace iosound