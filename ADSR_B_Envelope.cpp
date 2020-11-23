/*
  ==============================================================================

    ADSR_B_Envelope.cpp
    Created: 14 Nov 2020 3:58:13pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSR_B_Envelope.h"

//==============================================================================
ADSR_B_Envelope::ADSR_B_Envelope(PrismAudioProcessor& p):
    audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    attackSliderB.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSliderB.setRange(0.0f, 5000.0f);
    attackSliderB.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    attackSliderB.setValue(0.1f);

    decaySliderB.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySliderB.setRange(0.0f, 5000.0f);
    decaySliderB.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    decaySliderB.setValue(500.0f);

    sustainSliderB.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSliderB.setRange(0.0f, 1.0f);
    sustainSliderB.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sustainSliderB.setValue(0.5f);

    releaseSliderB.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSliderB.setRange(0.0f, 5000.0f);
    releaseSliderB.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    releaseSliderB.setValue(800.0f);

    addAndMakeVisible(&attackSliderB);
    addAndMakeVisible(&decaySliderB);
    addAndMakeVisible(&sustainSliderB);
    addAndMakeVisible(&releaseSliderB);

    treeAttackB = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "attackB", attackSliderB);
    treeDecayB = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "decayB", decaySliderB);
    treeSustainB = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "sustainB", sustainSliderB);
    treeReleaseB = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "releaseB", releaseSliderB);

}

ADSR_B_Envelope::~ADSR_B_Envelope()
{
}

void ADSR_B_Envelope::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("ADSR B", titleArea, juce::Justification::centredTop);

    //static positioning for now due to time, make dynamic later
    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::lightblue);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void ADSR_B_Envelope::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    int sliderWidth = 25;
    int sliderHeight = 175;

    attackSliderB.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySliderB.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSliderB.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSliderB.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));

}
