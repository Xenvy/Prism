/*
  ==============================================================================

    Filter.h
    Created: 1 Nov 2020 5:05:12pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter_A  : public juce::Component
{
public:
    Filter_A(PrismAudioProcessor&);
    ~Filter_A() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    PrismAudioProcessor& audioProcessor;

    juce::Slider cutoffSliderA;
    juce::Slider resonanceSliderA;
    juce::ComboBox filterTypeMenuA;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> cutoffValueA;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> resonanceValueA;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeValueA;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter_A)
};
