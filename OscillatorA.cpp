/*
  ==============================================================================

    Oscillator.cpp
    Created: 20 Oct 2020 11:43:30am
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorA.h"

//==============================================================================
OscillatorA::OscillatorA(PrismAudioProcessor& p):
    audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    oscAWaveform.addItem("Sine", 1);
    oscAWaveform.addItem("Saw", 2);
    oscAWaveform.addItem("Square", 3);
    oscAWaveform.addItem("Triangle", 4);
    oscAWaveform.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&oscAWaveform);

    WaveformA = std::make_unique <juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "waveformA", oscAWaveform);

    mixASlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mixASlider.setRange(0.0f, 1.0f);
    mixASlider.setValue(0.5f);
    mixASlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&mixASlider);

    mixAValue = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "mixA", mixASlider);
}

OscillatorA::~OscillatorA()
{
}

void OscillatorA::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Oscillator A", titleArea, juce::Justification::centredTop);


    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::lightblue);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void OscillatorA::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    oscAWaveform.setBounds(area.removeFromTop(20));

    int sliderWidth = 25;
    int sliderHeight = 175;

    mixASlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}

//void OscillatorA::comboBoxChanged(juce::ComboBox* combobox)
//{

//}
