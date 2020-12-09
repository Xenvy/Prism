/*
  ==============================================================================

    LFO_B.cpp
    Created: 18 Nov 2020 4:40:14pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFO_2.h"

//==============================================================================
LFO_2::LFO_2(PrismAudioProcessor& p):
audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    LFOType2.addItem("None", 1);
    LFOType2.addItem("Volume A", 2);
    LFOType2.addItem("Volume B", 3);
    LFOType2.addItem("Cutoff A", 4);
    LFOType2.addItem("Cutoff B", 5);
    LFOType2.addItem("Pitch A", 6);
    LFOType2.addItem("Pitch B", 7);
    LFOType2.addItem("Pan A", 8);
    LFOType2.addItem("Pan B", 9);
    LFOType2.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&LFOType2);
    LFOTypeValue2 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "LFOtype2", LFOType2);

    rateSlider2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider2.setRange(20.0, 20000.0);
    rateSlider2.setValue(2000.0);
    rateSlider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&rateSlider2);
    rateValue2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "LFOrate2", rateSlider2);

    depthSlider2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider2.setRange(1, 5);
    depthSlider2.setValue(1);
    depthSlider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&depthSlider2);
    depthValue2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "LFOdepth2", depthSlider2);

}

LFO_2::~LFO_2()
{
}

void LFO_2::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("LFO 2", titleArea, juce::Justification::centredTop);

    g.drawText("Rate", 34, 145, 60, 20, juce::Justification::centredTop);
    g.drawText("Depth", 105, 145, 60, 20, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::lightblue);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void LFO_2::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    LFOType2.setBounds(area.removeFromTop(20));
    rateSlider2.setBounds(30, 80, 70, 70);
    depthSlider2.setBounds(100, 80, 70, 70);

}
