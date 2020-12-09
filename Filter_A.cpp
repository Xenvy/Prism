/*
  ==============================================================================

    Filter.cpp
    Created: 1 Nov 2020 5:05:12pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter_A.h"

//==============================================================================
Filter_A::Filter_A(PrismAudioProcessor& p):
audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    filterTypeMenuA.addItem("None", 1);
    filterTypeMenuA.addItem("Lowpass", 2);
    filterTypeMenuA.addItem("Highpass", 3);
    filterTypeMenuA.addItem("Bandpass", 4);
    filterTypeMenuA.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterTypeMenuA);
    filterTypeValueA = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "filterTypeA", filterTypeMenuA);

    cutoffSliderA.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSliderA.setRange(30.0, 8000.0);
    cutoffSliderA.setValue(500.0);
    cutoffSliderA.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&cutoffSliderA);
    cutoffValueA = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "cutoffA", cutoffSliderA);
    cutoffSliderA.setSkewFactorFromMidPoint(640.0);

    resonanceSliderA.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonanceSliderA.setRange(1, 5);
    resonanceSliderA.setValue(1);
    resonanceSliderA.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&resonanceSliderA);
    resonanceValueA = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "resonanceA", resonanceSliderA);
}

Filter_A::~Filter_A()
{
}

void Filter_A::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter A", titleArea, juce::Justification::centredTop);

    g.drawText("Cutoff", 34, 145, 60, 20, juce::Justification::centredTop);
    g.drawText("Resonance", 96, 145, 80, 20, juce::Justification::centredTop);


    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::lightblue);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter_A::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    filterTypeMenuA.setBounds(area.removeFromTop(20));
    cutoffSliderA.setBounds(30, 80, 70, 70);
    resonanceSliderA.setBounds(100, 80, 70, 70);
}
