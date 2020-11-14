/*
  ==============================================================================

    OscillatorB.h
    Created: 11 Nov 2020 1:25:22pm
    Author:  Jasiek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OscillatorB  : public juce::Component
{
public:
    OscillatorB(PrismAudioProcessor&);
    ~OscillatorB() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    //void comboBoxChanged(juce::ComboBox*) override;

private:

    juce::ComboBox oscBWaveform;
    juce::Slider mixBSlider;

    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> WaveformB;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> mixBValue;

    PrismAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorB)
};
