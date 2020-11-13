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
    //~OscillatorB() override;
    ~OscillatorB();

    void paint (juce::Graphics&) override;
    void resized() override;

    //void comboBoxChanged(juce::ComboBox*) override;

private:

    juce::ComboBox oscBWaveform;
    juce::Slider blendSlider;

    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> WaveformB;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> blendValue;

    PrismAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorB)
};
