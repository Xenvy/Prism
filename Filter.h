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
class Filter  : public juce::Component
{
public:
    Filter(PrismAudioProcessor&);
    //~Filter() override;
    ~Filter();

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    PrismAudioProcessor& audioProcessor;

    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;
    juce::ComboBox filterTypeMenu;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> cutoffValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> resonanceValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
