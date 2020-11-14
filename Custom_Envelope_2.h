/*
  ==============================================================================

    Custom_Envelope_2.h
    Created: 14 Nov 2020 3:35:32pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Custom_Envelope_2  : public juce::Component
{
public:
    Custom_Envelope_2(PrismAudioProcessor&);
    ~Custom_Envelope_2() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    PrismAudioProcessor& audioProcessor;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeAttack2;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeDecay2;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeSustain2;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeRelease2;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> envType2;

    juce::Slider attackSlider2;
    juce::Slider decaySlider2;
    juce::Slider sustainSlider2;
    juce::Slider releaseSlider2;

    juce::ComboBox envTypeSelection2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Custom_Envelope_2)
};
