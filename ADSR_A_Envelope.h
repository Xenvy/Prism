/*
  ==============================================================================

    ADSR_Envelope.h
    Created: 31 Oct 2020 2:14:11pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ADSR_A_Envelope  : public juce::Component
{
public:
    ADSR_A_Envelope(PrismAudioProcessor&);
    ~ADSR_A_Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:

    PrismAudioProcessor& audioProcessor;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeAttackA;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeDecayA;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeSustainA;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeReleaseA;
    juce::Slider attackSliderA;
    juce::Slider decaySliderA;
    juce::Slider sustainSliderA;
    juce::Slider releaseSliderA;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSR_A_Envelope)
};
