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
class ADSR_Envelope  : public juce::Component
{
public:
    ADSR_Envelope(PrismAudioProcessor&);
    ~ADSR_Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:

    PrismAudioProcessor& audioProcessor;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeAttack;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeDecay;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeSustain;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeRelease;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSR_Envelope)
};
