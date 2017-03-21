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
    float m_acceptanceThreshold = 40; //!< 40
    float m_rejectionThreshold = 10;  //!< 20

    GestureReceiver m_gestureReceiver;
    bool m_hit = false;
    bool m_plates = false;
};

} // namespace ml
} // namespace iosound