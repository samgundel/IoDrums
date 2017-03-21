#include <iostream>
#include <vector>
#include <thread>

#include "player/Notes.hpp"
#include "player/MidiPlayer.hpp"
#include "xdk/XDKSerialPortReader.hpp"
#include "ml/MSEEstimator.hpp"

int main(int argc, char**argv) {
    using namespace iosound;
    
    player::MidiPlayer player;
    player.initialize();

    auto xdkReaderLeft  = std::make_shared<xdk::XDKSerialPortReader>("/dev/ttyACM1");
    auto xdkReaderRight = std::make_shared<xdk::XDKSerialPortReader>("/dev/ttyACM0");

    auto leftCallback = [&player](uint8_t mode){
        switch (mode) {
            case 0x11:
                player.playNote(player::DrumsNote::BUM);
                break;
            case 0x21:
                player.playNote(player::DrumsNote::L_PLATE);
                break;
            default:
                player.playNote(player::DrumsNote::L_DRUM);
                break;
        }
    };

    auto rightCallback = [&player](uint8_t mode){
        switch (mode) {
            case 0x11:
                player.playNote(player::DrumsNote::PLATES);
                break;
            case 0x21:
                player.playNote(player::DrumsNote::L_PLATE);
                break;
            default:
                player.playNote(player::DrumsNote::R_DRUM);
                break;
        }
    };

    xdkReaderLeft->setHitReceiver(leftCallback);
    xdkReaderRight->setHitReceiver(rightCallback);

    std::thread([&xdkReaderLeft](){ xdkReaderLeft->start(); }).detach();
    xdkReaderRight->start();
    return 0;
}
