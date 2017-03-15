#include <iostream>
#include <vector>

#include "player/Notes.hpp"
#include "player/MidiPlayer.hpp"
#include "xdk/XDKSerialPortReader.hpp"

int main(int argc, char**argv) {
    using namespace iosound;

    player::MidiPlayer player;
    player.initialize();

    player.playNote(player::DrumsNote::STICKS,100);
    player.playNote(player::DrumsNote::STICKS,100);
    player.playNote(player::DrumsNote::STICKS,100);

    player.playNote(player::DrumsNote::L_DRUM);
    player.playNote(player::DrumsNote::L_DRUM);
    player.playNote(player::DrumsNote::R_DRUM);
    player.playNote(player::DrumsNote::PLATES);
    player.playNote(player::DrumsNote::L_PLATE);

    std::shared_ptr<xdk::XDKSerialPortReader> xdkReader = std::make_shared<xdk::XDKSerialPortReader>("/dev/ttyACM0");
    xdkReader->setReceiver([](const xdk::XDKData& data){ 
        std::cout << data.pressure << "," << data.yaw << "," << data.pitch << "," << data.roll << std::endl; 
    });
    xdkReader->start();
    return 0;
}
