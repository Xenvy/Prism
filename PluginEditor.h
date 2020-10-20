/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PrismAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    PrismAudioProcessorEditor (PrismAudioProcessor&);
    ~PrismAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PrismAudioProcessor& audioProcessor;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeAttack;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeDecay;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeSustain;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> treeRelease;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrismAudioProcessorEditor)
};
