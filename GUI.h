/*
  ==============================================================================

    GUI.h
    Created: 11 Nov 2020 2:03:07pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class GUI  : public juce::Component
{
public:
    GUI(PrismAudioProcessor&);
    ~GUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider masterVolumeSlider;


    PrismAudioProcessor& audioProcessor;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> masterVolume;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI)
};
