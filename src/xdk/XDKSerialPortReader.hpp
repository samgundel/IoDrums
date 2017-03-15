#pragma once

#include "xdk/XDKReader.hpp"
#include <string>

namespace iosound {
namespace xdk {

class XDKSerialPortReader : public XDKReader {
public:
    explicit XDKSerialPortReader(const std::string& serialPort);
    
    void setGiroReceiver(const XDKGiroCallback& callback) override;
    void setAccelerationReceiver(const XDKAccelerationCallback& callback) override;
    
    /**
     * Start reading from the Serial Port and send message to the receiver (if available)
     */
    void start();

private:
    void parse(const std::string& row, const char separator = ' ');
    
    std::string m_serialPort;
    XDKGiroCallback m_giroCallback;
    XDKAccelerationCallback m_accelerationCallback;
};

} // namespace xdk
} // namespace iosounds