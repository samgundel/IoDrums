#pragma once

#include "ml/GestureEstimator.hpp"

namespace iosound {
namespace ml {

class MSEEstimator : public GestureEstimator {
public:
    void pushGiroEntry(const xdk::XDKGiro& giro) override;
    void pushAccelerationEntry(const xdk::XDKAcceleration& giro) override;
    void setGestureReceiver(const GestureReceiver& receiver) override;
private:
    float m_acceptanceThreshold = 225; //!< 15**2
    float m_rejectionThreshold = 100;  //!< 10**2
    float m_pitchThreshould = 30;
    xdk::XDKGiro m_giro;
    bool m_hit = false;
    GestureReceiver m_gestureReceiver;
};

} // namespace ml
} // namespace iosound