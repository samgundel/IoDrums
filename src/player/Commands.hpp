#pragma once

namespace iosound {
namespace player {

enum Command {
    NOTE_OFF       = 0x80,
    NOTE_ON        = 0x90,
    POLY_KEY_PRESS = 0xA0,
    CONTROL_CHANGE = 0xB0,
    PROGRAM_CHANGE = 0xC0,
    MONO_KEY_PRESS = 0xD0,
    PITCH_BEN      = 0xE0,
    SYSTEM         = 0xF0
};

} // namespace player
} // namespace iosound
