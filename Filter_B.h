/*
  ==============================================================================

    Filter_2.h
    Created: 25 Nov 2020 3:34:05pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter_B  : public juce::Component
{
public:
    Filter_B(PrismAudioProcessor&);
    ~Filter_B() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    PrismAudioProcessor& audioProcessor;

    juce::Slider cutoffSliderB;
    juce::Slider resonanceSliderB;
    juce::ComboBox filterTypeMenuB;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> cutoffValueB;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> resonanceValueB;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeValueB;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter_B)
};
