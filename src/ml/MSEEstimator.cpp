#include "ml/MSEEstimator.hpp"
#include <cmath>
#include <iostream>
#include <thread>
#include <deque>

namespace iosound {
namespace ml {

void MSEEstimator::changeMode(bool plates) {
    m_plates = plates;
}

void MSEEstimator::pushGiroEntry(const xdk::XDKGiro& giro) {
}

void MSEEstimator::setGestureReceiver(const GestureReceiver& gestureReceiver) {
    m_gestureReceiver = gestureReceiver;
}

void MSEEstimator::pushAccelerationEntry(const xdk::XDKAcceleration& acceleration) {
    float result = pow(acceleration.x,2) + pow(acceleration.y,2) + pow(acceleration.z,2);
    //std::cout <<  "<Result>:" << result << std::endl; 
    if (!m_hit) {
        if (result > m_acceptanceThreshold && m_gestureReceiver) {
            //std::cout << "Hit!: " << pressure << std::endl;
            m_hit = true;
            std::thread([this](){ m_gestureReceiver(m_plates); }).detach();
            
        }
    } else {
        if (result < m_rejectionThreshold) {
            m_hit = false;
        }
    }
}

} // namespace ml
} // namespace iosound
