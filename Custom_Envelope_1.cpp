/*
  ==============================================================================

    Custom_Envelope_1.cpp
    Created: 14 Nov 2020 3:35:09pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Custom_Envelope_1.h"

//==============================================================================
Custom_Envelope_1::Custom_Envelope_1(PrismAudioProcessor& p):
    audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    attackSlider1.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider1.setRange(0.0f, 5000.0f);
    attackSlider1.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    attackSlider1.setValue(0.1f);

    decaySlider1.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider1.setRange(0.0f, 5000.0f);
    decaySlider1.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    decaySlider1.setValue(500.0f);

    sustainSlider1.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider1.setRange(0.0f, 1.0f);
    sustainSlider1.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider1.setValue(0.5f);

    releaseSlider1.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider1.setRange(0.0f, 5000.0f);
    releaseSlider1.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider1.setValue(800.0f);

    envTypeSelection1.addItem("None", 1);
    envTypeSelection1.addItem("Cutoff A", 2);
    envTypeSelection1.addItem("Cutoff B", 3);
    envTypeSelection1.addItem("Pitch A", 4);
    envTypeSelection1.addItem("Pitch B", 5);
    envTypeSelection1.addItem("Pan A", 6);
    envTypeSelection1.addItem("Pan A", 7);
    envTypeSelection1.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&envTypeSelection1);
    envType1 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "filterType", envTypeSelection1);

    addAndMakeVisible(&attackSlider1);
    addAndMakeVisible(&decaySlider1);
    addAndMakeVisible(&sustainSlider1);
    addAndMakeVisible(&releaseSlider1);

    treeAttack1 = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "attackA", attackSlider1);
    treeDecay1 = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "decayA", decaySlider1);
    treeSustain1 = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "sustainA", sustainSlider1);
    treeRelease1 = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "releaseA", releaseSlider1);

}

Custom_Envelope_1::~Custom_Envelope_1()
{
}

void Custom_Envelope_1::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Envelope 1", titleArea, juce::Justification::centredTop);

    //static positioning for now due to time, make dynamic later
    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Custom_Envelope_1::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    int sliderWidth = 25;
    int sliderHeight = 175;

    envTypeSelection1.setBounds(area.removeFromTop(20));
    attackSlider1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));

}
