#pragma once

class AnimationClip
{
public:
    float* properties[10];
    float durations[10];
    float startProperties[10];
    float endProperties[10];
    bool loop = false;
    bool shouldPlay = true;
    float currentTime = 0;
    
};
