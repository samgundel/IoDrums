#include <iostream>
#include "player/Notes.hpp"
#include "player/MidiPlayer.hpp"

int main(int argc, char**argv) {
    using namespace iosound;

    player::MidiPlayer player;
    player.initialize();

    player.playDrumsNote(player::DrumsNote::STICKS,300);
    player.playDrumsNote(player::DrumsNote::STICKS,300);
    player.playDrumsNote(player::DrumsNote::STICKS,300);

    player.playDrumsNote(player::DrumsNote::L_DRUM);
    player.playDrumsNote(player::DrumsNote::L_DRUM);
    player.playDrumsNote(player::DrumsNote::R_DRUM);
    player.playDrumsNote(player::DrumsNote::PLATES);
    player.playDrumsNote(player::DrumsNote::L_PLATE);
    return 0;
}
