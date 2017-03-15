#pragma once

#include "player/Notes.hpp"

namespace iosound {
namespace player {

class Player {
public:

/**
 *  Initialize the Player by connecting to the synthetizer. 
 *  @throw an exception if no midi connection can be built.
 */
virtual void initialize() = 0;

/**
 * Play a midi note in a fire and forget fashion.
 */
virtual void playDrumsNote(DrumsNote note, int msecs = 500, unsigned char intensity = 60) = 0;

};

} // namespace player
} // namespace iosound
