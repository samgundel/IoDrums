#pragma once

#include <memory>
#include <vector>

#include <RtMidi.h>

#include "player/Player.hpp"

namespace iosound {
namespace player {

class MidiPlayer : public Player {
public:

void initialize() override;

void playDrumsNote(DrumsNote note, int msecs = 500, unsigned char intensity = 60) override;

private:
    bool m_connected = false;             //!< The state of the player.
    unsigned int m_port = 2;              //!< Midi Port we are connecting to.
    std::vector<unsigned char> message;   //!< Midi Message 
    std::unique_ptr<RtMidiOut> m_midiOut; //!< Midi Connector;
};

} // namespace player
} // namespace iosound
