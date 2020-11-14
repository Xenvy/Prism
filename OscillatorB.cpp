/*
  ==============================================================================

    OscillatorB.cpp
    Created: 11 Nov 2020 1:25:22pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorB.h"

//==============================================================================
OscillatorB::OscillatorB(PrismAudioProcessor& p):
    audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(200, 200);

    oscBWaveform.addItem("Sine", 1);
    oscBWaveform.addItem("Saw", 2);
    oscBWaveform.addItem("Square", 3);
    oscBWaveform.addItem("Triangle", 4);
    oscBWaveform.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&oscBWaveform);

    WaveformB = std::make_unique <juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "waveformB", oscBWaveform);

    mixBSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mixBSlider.setRange(0.0f, 1.0f);
    mixBSlider.setValue(0.5f);
    mixBSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&mixBSlider);

    mixBValue = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "mixB", mixBSlider);
}

OscillatorB::~OscillatorB()
{
}

void OscillatorB::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Oscillator B", titleArea, juce::Justification::centredTop);


    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void OscillatorB::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    oscBWaveform.setBounds(area.removeFromTop(20));

    int sliderWidth = 25;
    int sliderHeight = 175;

    mixBSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}

//void OscillatorB::comboBoxChanged(juce::ComboBox* combobox)
//{

//}