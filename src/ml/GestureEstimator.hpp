#pragma once

#include "xdk/XDKTypes.hpp"

namespace iosound {
namespace ml {

class GestureEstimator {
public:
    virtual void pushGiroEntry(const xdk::XDKGiro& giro) = 0;
    virtual void pushAccelerationEntry(const xdk::XDKAcceleration& giro) = 0;
}

} // namespace ml
} // namespace iosound