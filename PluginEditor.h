/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OscillatorA.h"
#include "OscillatorB.h"
#include "ADSR_A_Envelope.h"
#include "ADSR_B_Envelope.h"
#include "Custom_Envelope_1.h"
#include "Custom_Envelope_2.h"
#include "Filter.h"
#include "GUI.h"

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

    OscillatorA oscA;
    OscillatorB oscB;
    ADSR_A_Envelope adsrA;
    ADSR_B_Envelope adsrB;
    Custom_Envelope_1 envelope1;
    Custom_Envelope_2 envelope2;
    Filter filterA;
    GUI gui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrismAudioProcessorEditor)
};
