/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PrismAudioProcessorEditor::PrismAudioProcessorEditor (PrismAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscA(p), oscB(p), adsrA(p), adsrB(p), envelope1(p), envelope2(p), lfo1(p), lfo2(p), filterA(p), filterB(p), gui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1200, 400);

    addAndMakeVisible(&oscA);
    addAndMakeVisible(&oscB);
    addAndMakeVisible(&adsrA);
    addAndMakeVisible(&adsrB);
    addAndMakeVisible(&envelope1);
    addAndMakeVisible(&envelope2);
    addAndMakeVisible(&lfo1);
    addAndMakeVisible(&lfo2);
    addAndMakeVisible(&filterA);
    addAndMakeVisible(&filterB);
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
    oscA.setBounds(0, 0, 200, 200);
    adsrA.setBounds(200, 0, 200, 200);
    envelope1.setBounds(400, 0, 200, 200);
    lfo1.setBounds(600, 0, 200, 200);
    filterA.setBounds(800, 0, 200, 200);
    oscB.setBounds(0, 200, 200, 200);
    adsrB.setBounds(200, 200, 200, 200);
    envelope2.setBounds(400, 200, 200, 200);
    lfo2.setBounds(600, 200, 200, 200);
    filterB.setBounds(800, 200, 200, 200);
    gui.setBounds(1000, 0, 200, 200);
}

