/*
  ==============================================================================

    ADSR_B_Envelope.h
    Created: 14 Nov 2020 3:58:13pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ADSR_B_Envelope  : public juce::Component
{
public:
    ADSR_B_Envelope(PrismAudioProcessor&);
    ~ADSR_B_Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    PrismAudioProcessor& audioProcessor;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeAttackB;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeDecayB;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeSustainB;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeReleaseB;
    juce::Slider attackSliderB;
    juce::Slider decaySliderB;
    juce::Slider sustainSliderB;
    juce::Slider releaseSliderB;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSR_B_Envelope)
};
