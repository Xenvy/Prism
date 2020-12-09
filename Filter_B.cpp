/*
  ==============================================================================

    Filter_2.cpp
    Created: 25 Nov 2020 3:34:05pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter_B.h"

//==============================================================================
Filter_B::Filter_B(PrismAudioProcessor& p):
    audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(200, 200);

    filterTypeMenuB.addItem("None", 1);
    filterTypeMenuB.addItem("Lowpass", 2);
    filterTypeMenuB.addItem("Highpass", 3);
    filterTypeMenuB.addItem("Bandpass", 4);
    filterTypeMenuB.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterTypeMenuB);
    filterTypeValueB = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "filterTypeB", filterTypeMenuB);

    cutoffSliderB.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSliderB.setRange(30.0, 8000.0);
    cutoffSliderB.setValue(500.0);
    cutoffSliderB.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&cutoffSliderB);
    cutoffValueB = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "cutoffB", cutoffSliderB);
    cutoffSliderB.setSkewFactorFromMidPoint(640.0);

    resonanceSliderB.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonanceSliderB.setRange(1, 5);
    resonanceSliderB.setValue(1);
    resonanceSliderB.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&resonanceSliderB);
    resonanceValueB = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "resonanceB", resonanceSliderB);
}

Filter_B::~Filter_B()
{
}

void Filter_B::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter B", titleArea, juce::Justification::centredTop);

    g.drawText("Cutoff", 34, 145, 60, 20, juce::Justification::centredTop);
    g.drawText("Resonance", 96, 145, 80, 20, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::lightblue);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter_B::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    filterTypeMenuB.setBounds(area.removeFromTop(20));
    cutoffSliderB.setBounds(30, 80, 70, 70);
    resonanceSliderB.setBounds(100, 80, 70, 70);
}
