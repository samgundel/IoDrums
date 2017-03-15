#include "xdk/XDKSerialPortReader.hpp"

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

#include <vector>

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
    char buffer[64];
    do
    {
        int n = read(device, buffer, sizeof(buffer));
        if (n > 0) {
            parse(std::string(buffer));
        }
    } while (buffer[0] != 'X'); // 'X' means end of transmission
    close(device);
}

void XDKSerialPortReader::parse(const std::string& row, const char separator) {
    std::vector<std::string> values;
    split(row, values, separator);

    if (values[0][1] == 'A') {
        XDKAcceleration acceleration;
        acceleration.x = std::atof(values[1].c_str());
        acceleration.y = std::atof(values[2].c_str());
        acceleration.z = std::atof(values[3].c_str());
        m_accelerationCallback(acceleration);
    } else if (values[0][1] == 'B'){
        m_modeCallback(values[1][1] == '1');
    }
}

void XDKSerialPortReader::setModeReceiver(const XDKModeCallback& callback)
{
    m_modeCallback = callback;
}

void XDKSerialPortReader::setAccelerationReceiver(const XDKAccelerationCallback& callback)
{
    m_accelerationCallback = callback;
}

} // namespace xdk
} // namespace iosounds