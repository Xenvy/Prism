/*
  ==============================================================================

    Filter.cpp
    Created: 1 Nov 2020 5:05:12pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(PrismAudioProcessor& p):
audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    filterTypeMenu.addItem("None", 1);
    filterTypeMenu.addItem("Lowpass", 2);
    filterTypeMenu.addItem("Highpass", 3);
    filterTypeMenu.addItem("Bandpass", 4);
    filterTypeMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterTypeMenu);
    filterTypeValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "filterType", filterTypeMenu);

    cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSlider.setRange(30.0, 8000.0);
    cutoffSlider.setValue(1000.0);
    cutoffSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&cutoffSlider);
    cutoffValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "cutoff", cutoffSlider);
    cutoffSlider.setSkewFactorFromMidPoint(1000.0);

    resonanceSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonanceSlider.setRange(1, 5);
    resonanceSlider.setValue(1);
    resonanceSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&resonanceSlider);
    resonanceValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "resonance", resonanceSlider);
}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::black);
}

void Filter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    filterTypeMenu.setBounds(area.removeFromTop(20));
    cutoffSlider.setBounds(30, 100, 70, 70);
    resonanceSlider.setBounds(100, 100, 70, 70);
}
