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
class OscillatorA  : public juce::Component
{
public:
    OscillatorA(PrismAudioProcessor&);
    ~OscillatorA() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    //void comboBoxChanged(juce::ComboBox*) override;

private:

    juce::ComboBox oscAWaveform;
    juce::Slider mixASlider;

    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> WaveformA;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> mixAValue;

    PrismAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorA)
};
