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

    auto estimatorLeft = std::make_shared<ml::MSEEstimator>();
    auto estimatorRight = std::make_shared<ml::MSEEstimator>();

    auto callback = [&player](bool plates){
        if (plates) {
            player.playNote(player::DrumsNote::PLATES);
        } else {
            player.playNote(player::DrumsNote::R_DRUM);
        }
    };

    estimatorLeft->setGestureReceiver(callback);
    estimatorRight->setGestureReceiver(callback);

    xdkReaderLeft->setAccelerationReceiver([&estimatorLeft](const auto& ...args){ estimatorLeft->pushAccelerationEntry(args...); });
    xdkReaderRight->setAccelerationReceiver([&estimatorRight](const auto& ...args){ estimatorRight->pushAccelerationEntry(args...); });

    xdkReaderLeft->setModeReceiver([&estimatorLeft](bool plates){ estimatorLeft->changeMode(plates); });
    xdkReaderRight->setModeReceiver([&estimatorRight](bool plates){ estimatorRight->changeMode(plates); });

    std::thread([&xdkReaderLeft](){ xdkReaderLeft->start(); }).detach();
    xdkReaderRight->start();
    return 0;
}
