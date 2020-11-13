/*
  ==============================================================================

    Synthesizer_Sound.h
    Created: 18 Sep 2020 6:51:48pm
    Author:  Burza

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"


class SynthSound : public juce::SynthesiserSound
{
  public:
  bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    
  bool appliesToChannel (int midiChannelNumber) override
    {
        return true;
    }
};