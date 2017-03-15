#include "player/MidiPlayer.hpp"
#include "player/Commands.hpp"
#include <thread>
#include <vector>

namespace iosound {
namespace player {

void sleep_for(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void MidiPlayer::initialize() {
    try {
        m_midiOut = std::make_unique<RtMidiOut>();
        if (m_midiOut->getPortCount() == 0) {
            std::cout << "No output ports available!" << std::endl;
            return;
        }
        std::cout << "Connecting to port #" << m_port << ": " << m_midiOut->getPortName(m_port) << std::endl;
        m_midiOut->openPort(m_port);
        m_connected = true;
    } catch (const RtMidiError &error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    } 
}

void MidiPlayer::playDrumsNote(DrumsNote note, int msecs, unsigned char intensity) {
    std::vector<unsigned char> message = {NOTE_ON, note, intensity};
    m_midiOut->sendMessage(&message);
    sleep_for(msecs);
    message = {NOTE_OFF, note, intensity};
    m_midiOut->sendMessage(&message);
}

} // namespace player
} // namespace iosound
