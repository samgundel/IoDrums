#include "xdk/XDKSerialPortReader.hpp"

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

#include <vector>
#include <thread>

namespace {


size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos + 1 ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
}

namespace iosound {
namespace xdk {

XDKSerialPortReader::XDKSerialPortReader(const std::string& serialPort)
    : m_serialPort(serialPort)
{
}

void XDKSerialPortReader::start() {
    int device = open(m_serialPort.c_str(), O_RDONLY | O_NOCTTY | O_SYNC);
    uint8_t command = 0;
    while (true)
    {
        if (read(device, &command, 1) > 0) {
            std::cout << static_cast<uint32_t>(command) << std::endl;
            if (command == 0x01) {
                std::thread([this](){ m_hitCallback(mode); }).detach();
            } else {
                mode = command;
            }
        }
    }
    close(device);
}

void XDKSerialPortReader::setModeReceiver(const XDKModeCallback& callback)
{
    m_modeCallback = callback;
}

void XDKSerialPortReader::setHitReceiver(const XDKHitCallback& callback)
{
    m_hitCallback = callback;
}

} // namespace xdk
} // namespace iosounds