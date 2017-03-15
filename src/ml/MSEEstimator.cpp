#include "ml/MSEEstimator.hpp"
#include <cmath>
#include <iostream>
#include <thread>

namespace iosound {
namespace ml {

void MSEEstimator::pushGiroEntry(const xdk::XDKGiro& giro) {
    m_giro = giro;
}

void MSEEstimator::setGestureReceiver(const GestureReceiver& gestureReceiver) {
    m_gestureReceiver = gestureReceiver;
}

void MSEEstimator::pushAccelerationEntry(const xdk::XDKAcceleration& acceleration) {
    float result = pow(acceleration.x,2) + pow(acceleration.y,2) + pow(acceleration.z,2);
    //std::cout <<  "<Result>:" << result << std::endl; 
    if (!m_hit) {
        if (result > m_acceptanceThreshold && m_gestureReceiver) {
            //std::cout << "Hit!: " << m_giro.yaw << " " << m_giro.pitch << " " << m_giro.roll << std::endl;
            m_hit = true;
            std::thread([this](){ m_gestureReceiver(); }).detach();
            
        }
    } else {
        if (result < m_rejectionThreshold) {
            m_hit = false;
        }
    }
}

} // namespace ml
} // namespace iosound
