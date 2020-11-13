/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PrismAudioProcessorEditor::PrismAudioProcessorEditor (PrismAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscA(p), oscB(p), adsrA(p), filterA(p), gui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 200);

    addAndMakeVisible(&oscA);
    addAndMakeVisible(&oscB);
    addAndMakeVisible(&adsrA);
    addAndMakeVisible(&filterA);
    addAndMakeVisible(&gui);
}

PrismAudioProcessorEditor::~PrismAudioProcessorEditor()
{
}

//==============================================================================
void PrismAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.fillAll(juce::Colours::black);
}

void PrismAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    juce::Rectangle<int> area = getLocalBounds();

    const int componentHeight = 200;
    const int componentWidth = 200;
    oscA.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    oscB.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    adsrA.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterA.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}

