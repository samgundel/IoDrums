#include <iostream>
#include <vector>

#include "player/Notes.hpp"
#include "player/MidiPlayer.hpp"
#include "xdk/XDKSerialPortReader.hpp"
#include "ml/MSEEstimator.hpp"

int main(int argc, char**argv) {
    using namespace iosound;
    
    player::MidiPlayer player;
    player.initialize();

    auto xdkReader = std::make_shared<xdk::XDKSerialPortReader>("/dev/ttyACM0");
    auto estimator = std::make_shared<ml::MSEEstimator>();
    estimator->setGestureReceiver([&player](){ player.playNote(player::DrumsNote::PLATES); });
    xdkReader->setGiroReceiver([&estimator](const auto& ...args){ estimator->pushGiroEntry(args...); });
    xdkReader->setAccelerationReceiver([&estimator](const auto& ...args){ estimator->pushAccelerationEntry(args...);  });
    xdkReader->start();
    return 0;
}
