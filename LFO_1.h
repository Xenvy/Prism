/*
  ==============================================================================

    LFO_A.h
    Created: 18 Nov 2020 4:40:02pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LFO_1  : public juce::Component
{
public:
    LFO_1(PrismAudioProcessor&);
    ~LFO_1() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    PrismAudioProcessor& audioProcessor;

    juce::Slider rateSlider1;
    juce::Slider depthSlider1;
    juce::ComboBox LFOType1;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> rateValue1;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> depthValue1;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> LFOTypeValue1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO_1)
};
