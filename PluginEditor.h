/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "ADSR_Envelope.h"

//==============================================================================
/**
*/
class PrismAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PrismAudioProcessorEditor (PrismAudioProcessor&);
    ~PrismAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PrismAudioProcessor& audioProcessor;

    Oscillator oscA;
    ADSR_Envelope adsrA;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrismAudioProcessorEditor)
};
