/*
  ==============================================================================

    LFO_B.h
    Created: 18 Nov 2020 4:40:14pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LFO_2  : public juce::Component
{
public:
    LFO_2(PrismAudioProcessor&);
    ~LFO_2() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    PrismAudioProcessor& audioProcessor;

    juce::Slider rateSlider2;
    juce::Slider depthSlider2;
    juce::ComboBox LFOType2;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> rateValue2;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> depthValue2;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> LFOTypeValue2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO_2)
};
