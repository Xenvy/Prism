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
    //~GUI() override;
    ~GUI();

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider masterVolumeSlider;
    juce::Slider pbupSlider;
    juce::Slider pbdownSlider;

    PrismAudioProcessor& audioProcessor;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> masterVolume;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> pbupVal;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> pbdownVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI)
};
