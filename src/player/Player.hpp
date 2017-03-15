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
virtual void startDrumsNote(DrumsNote note, int msecs = 500, unsigned char intensity = 60) = 0;
virtual void stopDrumsNote(DrumsNote note, int msecs = 500, unsigned char intensity = 60) = 0;
virtual void playNote(DrumsNote note, int msecs = 500, unsigned char intensity = 60) = 0;

};

} // namespace player
} // namespace iosound
