/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PrismAudioProcessorEditor::PrismAudioProcessorEditor (PrismAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscA(p), adsrA(p), filterA(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 200);

    addAndMakeVisible(&oscA);
    addAndMakeVisible(&adsrA);
    addAndMakeVisible(&filterA);
}

PrismAudioProcessorEditor::~PrismAudioProcessorEditor()
{
}

//==============================================================================
void PrismAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PrismAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    juce::Rectangle<int> area = getLocalBounds();

    const int componentHeight = 200;
    const int componentWidth = 200;
    oscA.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    adsrA.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterA.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}

