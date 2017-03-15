#pragma once

#include <deque>

#include "ml/GestureEstimator.hpp"

namespace iosound {
namespace ml {

class MSEEstimator : public GestureEstimator {
public:
    void changeMode(bool plates) override;
    void pushGiroEntry(const xdk::XDKGiro& giro) override;
    void pushAccelerationEntry(const xdk::XDKAcceleration& giro) override;
    void setGestureReceiver(const GestureReceiver& receiver) override;
private:
    float m_acceptanceThreshold = 50; //!< 15**2
    float m_rejectionThreshold = 30;  //!< 10**2

    GestureReceiver m_gestureReceiver;
    bool m_hit = false;
    bool m_plates = false;
};

} // namespace ml
} // namespace iosound