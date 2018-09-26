#ifndef _RAINBOW_COLOUR_H_
#define _RAINBOW_COLOUR_H_

#include <vector>

#define MAX_RGB_CHANNEL 1.0f
#define MIN_RGB_CHANNEL 0.0f

enum ColourState {
    RISING,
    FALLING,
    IDLE
};

class RainbowColour {
    public:
        RainbowColour(float _rate=0.05f);
        float r, g, b, a;
        void setRate(float _rate);
        void update();
    private:
        float rate;
        std::vector<ColourState> channelStates;
        int getWrappedIndex(int index, int size);
        float &getColourByIndex(int index);
        ColourState &getChannelStateByIndex(int index);
};

#endif