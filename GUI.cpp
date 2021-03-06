/*
  ==============================================================================

    GUI.cpp
    Created: 11 Nov 2020 2:03:07pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GUI.h"

//==============================================================================
GUI::GUI(PrismAudioProcessor& p):
audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    //slider initialization values
    masterVolumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    masterVolumeSlider.setRange(0.0f, 1.0f);
    masterVolumeSlider.setValue(0.6f);
    masterVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&masterVolumeSlider);



    //sends value of the sliders to the tree state in the processor
    masterVolume = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "masterVolume", masterVolumeSlider);

}

GUI::~GUI()
{
}

void GUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Main", titleArea, juce::Justification::centredTop);

    //static positioning for now due to time, make dynamic later
    g.drawText("Master", 53, 40, 40, 20, juce::Justification::centredLeft);



    juce::Rectangle<float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::lightblue);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void GUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..


    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    int sliderWidth = 25;
    int sliderHeight = 25;

    //draw sliders by reducing area from rectangle above

    masterVolumeSlider.setBounds(45, 20, 120, 100);

}
