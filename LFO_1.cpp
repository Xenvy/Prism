/*
  ==============================================================================

    LFO_A.cpp
    Created: 18 Nov 2020 4:40:02pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFO_1.h"

//==============================================================================
LFO_1::LFO_1(PrismAudioProcessor& p):
audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setSize(200, 200);

    LFOType1.addItem("None", 1);
    LFOType1.addItem("Volume A", 2);
    LFOType1.addItem("Volume B", 3);
    LFOType1.addItem("Cutoff A", 4);
    LFOType1.addItem("Cutoff B", 5);
    LFOType1.addItem("Pitch A", 6);
    LFOType1.addItem("Pitch B", 7);
    LFOType1.addItem("Pan A", 8);
    LFOType1.addItem("Pan B", 9);
    LFOType1.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&LFOType1);
    LFOTypeValue1 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "LFOtype1", LFOType1);

    rateSlider1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider1.setRange(20.0, 20000.0);
    rateSlider1.setValue(500.0);
    rateSlider1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&rateSlider1);
    rateValue1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "LFOrate1", rateSlider1);

    depthSlider1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider1.setRange(1, 5);
    depthSlider1.setValue(1);
    depthSlider1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&depthSlider1);
    depthValue1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "LFOdepth1", depthSlider1);

}

LFO_1::~LFO_1()
{
}

void LFO_1::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("LFO 1", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::lightblue);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void LFO_1::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    LFOType1.setBounds(area.removeFromTop(20));
    rateSlider1.setBounds(30, 100, 70, 70);
    depthSlider1.setBounds(100, 100, 70, 70);

}
