/*
  ==============================================================================

    Custom_Envelope_2.cpp
    Created: 14 Nov 2020 3:35:32pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Custom_Envelope_2.h"

//==============================================================================
Custom_Envelope_2::Custom_Envelope_2(PrismAudioProcessor& p):
    audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    attackSlider2.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider2.setRange(0.0f, 5000.0f);
    attackSlider2.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    attackSlider2.setValue(0.1f);

    decaySlider2.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider2.setRange(0.0f, 5000.0f);
    decaySlider2.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    decaySlider2.setValue(500.0f);

    sustainSlider2.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider2.setRange(0.0f, 1.0f);
    sustainSlider2.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider2.setValue(0.5f);

    releaseSlider2.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider2.setRange(0.0f, 5000.0f);
    releaseSlider2.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider2.setValue(800.0f);

    envTypeSelection2.addItem("None", 1);
    envTypeSelection2.addItem("Cutoff A", 2);
    envTypeSelection2.addItem("Cutoff B", 3);
    envTypeSelection2.addItem("Pitch A", 4);
    envTypeSelection2.addItem("Pitch B", 5);
    envTypeSelection2.addItem("Pan A", 6);
    envTypeSelection2.addItem("Pan A", 7);
    envTypeSelection2.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&envTypeSelection2);
    envType2 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "filterType", envTypeSelection2);

    addAndMakeVisible(&attackSlider2);
    addAndMakeVisible(&decaySlider2);
    addAndMakeVisible(&sustainSlider2);
    addAndMakeVisible(&releaseSlider2);

    treeAttack2 = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "attackA", attackSlider2);
    treeDecay2 = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "decayA", decaySlider2);
    treeSustain2 = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "sustainA", sustainSlider2);
    treeRelease2 = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "releaseA", releaseSlider2);

}

Custom_Envelope_2::~Custom_Envelope_2()
{
}

void Custom_Envelope_2::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Envelope 2", titleArea, juce::Justification::centredTop);

    //static positioning for now due to time, make dynamic later
    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Custom_Envelope_2::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    int sliderWidth = 25;
    int sliderHeight = 175;

    envTypeSelection2.setBounds(area.removeFromTop(20));
    attackSlider2.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider2.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider2.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider2.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));

}
