/*
  ==============================================================================

    ADSR_Envelope.cpp
    Created: 31 Oct 2020 2:14:11pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSR_A_Envelope.h"

//==============================================================================
ADSR_A_Envelope::ADSR_A_Envelope(PrismAudioProcessor& p):
audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    attackSliderA.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSliderA.setRange(0.0f, 5000.0f);
    attackSliderA.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    attackSliderA.setValue(0.1f);

    decaySliderA.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySliderA.setRange(0.0f, 5000.0f);
    decaySliderA.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    decaySliderA.setValue(500.0f);

    sustainSliderA.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSliderA.setRange(0.0f, 1.0f);
    sustainSliderA.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sustainSliderA.setValue(0.5f);

    releaseSliderA.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSliderA.setRange(0.0f, 5000.0f);
    releaseSliderA.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    releaseSliderA.setValue(800.0f);

    addAndMakeVisible(&attackSliderA);
    addAndMakeVisible(&decaySliderA);
    addAndMakeVisible(&sustainSliderA);
    addAndMakeVisible(&releaseSliderA);

    treeAttackA = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "attackA", attackSliderA);
    treeDecayA = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "decayA", decaySliderA);
    treeSustainA = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "sustainA", sustainSliderA);
    treeReleaseA = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "releaseA", releaseSliderA);

}

ADSR_A_Envelope::~ADSR_A_Envelope()
{
}

void ADSR_A_Envelope::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("ADSR A", titleArea, juce::Justification::centredTop);

    //static positioning for now due to time, make dynamic later
    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void ADSR_A_Envelope::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    int sliderWidth = 25;
    int sliderHeight = 175;

    attackSliderA.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySliderA.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSliderA.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSliderA.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));

}
