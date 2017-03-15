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

    auto xdkReaderLeft  = std::make_shared<xdk::XDKSerialPortReader>("/dev/ttyACM0");
    auto xdkReaderRight = std::make_shared<xdk::XDKSerialPortReader>("/dev/ttyACM1");

    auto estimatorLeft = std::make_shared<ml::MSEEstimator>();
    auto estimatorRight = std::make_shared<ml::MSEEstimator>();

    estimatorLeft->setGestureReceiver([&player](){ player.playNote(player::DrumsNote::L_DRUM); });
    estimatorRight->setGestureReceiver([&player](){ player.playNote(player::DrumsNote::PLATES); });

    xdkReaderLeft->setGiroReceiver([&estimatorLeft](const auto& ...args){ estimatorLeft->pushGiroEntry(args...); });
    xdkReaderLeft->setAccelerationReceiver([&estimatorLeft](const auto& ...args){ estimatorLeft->pushAccelerationEntry(args...); });

    xdkReaderRight->setGiroReceiver([&estimatorRight](const auto& ...args){ estimatorRight->pushGiroEntry(args...); });
    xdkReaderRight->setAccelerationReceiver([&estimatorRight](const auto& ...args){ estimatorRight->pushAccelerationEntry(args...); });

    std::thread([&xdkReaderLeft](){ xdkReaderLeft->start(); }).detach();
    xdkReaderRight->start();
    return 0;
}
