/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PrismAudioProcessorEditor::PrismAudioProcessorEditor (PrismAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscA(p), oscB(p), adsrA(p), adsrB(p), envelope1(p), envelope2(p), lfo1(p), lfo2(p), filterA(p), gui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 400);

    addAndMakeVisible(&oscA);
    addAndMakeVisible(&oscB);
    addAndMakeVisible(&adsrA);
    addAndMakeVisible(&adsrB);
    addAndMakeVisible(&envelope1);
    addAndMakeVisible(&envelope2);
    addAndMakeVisible(&lfo1);
    addAndMakeVisible(&lfo2);
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
    adsrA.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envelope1.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    lfo1.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterA.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    area.expand(componentWidth*4, componentHeight);
    oscB.setBounds(area.removeFromBottom(componentHeight).removeFromLeft(componentWidth));
    adsrB.setBounds(area.removeFromLeft(componentWidth).removeFromBottom(componentHeight));
    envelope2.setBounds(area.removeFromLeft(componentWidth).removeFromBottom(componentHeight));
    lfo2.setBounds(area.removeFromLeft(componentWidth).removeFromBottom(componentHeight));
    gui.setBounds(area.removeFromLeft(componentWidth).removeFromBottom(componentHeight));
}

