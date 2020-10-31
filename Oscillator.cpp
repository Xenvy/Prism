/*
  ==============================================================================

    Oscillator.cpp
    Created: 20 Oct 2020 11:43:30am
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(PrismAudioProcessor& P):
    audioProcessor(P)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    oscWaveform.addItem("Sine", 1);
    oscWaveform.addItem("Saw", 2);
    oscWaveform.addItem("Square", 3);
    oscWaveform.addItem("Triangle", 4);
    oscWaveform.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&oscWaveform);
    oscWaveform.addListener(this);

    WaveformA = std::make_unique <juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "waveform", oscWaveform);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    
}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    oscWaveform.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(juce::ComboBox* combobox)
{

}
