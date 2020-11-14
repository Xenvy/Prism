/*
  ==============================================================================

    Custom_Envelope_1.h
    Created: 14 Nov 2020 3:35:09pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Custom_Envelope_1  : public juce::Component
{
public:
    Custom_Envelope_1(PrismAudioProcessor&);
    ~Custom_Envelope_1() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    PrismAudioProcessor& audioProcessor;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeAttack1;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeDecay1;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeSustain1;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeRelease1;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> envType1;

    juce::Slider attackSlider1;
    juce::Slider decaySlider1;
    juce::Slider sustainSlider1;
    juce::Slider releaseSlider1;

    juce::ComboBox envTypeSelection1;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Custom_Envelope_1)
};
