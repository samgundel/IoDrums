#pragma once

#include <string>
#include "xdk/XDKReader.hpp"

namespace iosound {
namespace xdk {

class XDKSerialPortReader : public XDKReader {
public:
    explicit XDKSerialPortReader(const std::string& serialPort);
    
    void setReceiver(const XDKReceiverCallback& callback) override;
    
    /**
     * Start reading from the Serial Port and send message to the receiver (if available)
     */
    void start();

private:
    XDKData parse(const std::string& row, const char separator = ' ');
    
    std::string m_serialPort;
    XDKReceiverCallback m_callback;
};

} // namespace xdk
} // namespace iosounds