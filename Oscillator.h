/*
  ==============================================================================

    Oscillator.h
    Created: 20 Oct 2020 11:43:30am
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator  : public juce::Component,
                    private juce::ComboBox::Listener
{
public:
    Oscillator(PrismAudioProcessor&);
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox*) override;

private:

    juce::ComboBox oscWaveform;

    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> WaveformA;

    PrismAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
