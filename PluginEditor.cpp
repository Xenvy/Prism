/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PrismAudioProcessorEditor::PrismAudioProcessorEditor (PrismAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.0f, 5000.0f);
    //attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
    attackSlider.setValue(0.1f);
    attackSlider.addListener(this);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.0f, 5000.0f);
    //decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
    decaySlider.setValue(500.0f);
    decaySlider.addListener(this);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    //sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
    sustainSlider.setValue(0.5f);
    sustainSlider.addListener(this);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.0f, 5000.0f);
    //releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
    releaseSlider.setValue(800.0f);
    releaseSlider.addListener(this);

    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);

    treeAttack = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "attack", attackSlider);
    treeDecay = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "decay", decaySlider);
    treeSustain = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "sustain", sustainSlider);
    treeRelease = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "release", releaseSlider);
}

PrismAudioProcessorEditor::~PrismAudioProcessorEditor()
{
}

//==============================================================================
void PrismAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PrismAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    attackSlider.setBounds(10, 10, 40, 100);
    decaySlider.setBounds(70, 10, 40, 100);
    sustainSlider.setBounds(130, 10, 40, 100);
    releaseSlider.setBounds(190, 10, 40, 100);
}

void PrismAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &attackSlider)
    {
        audioProcessor.attackTime = attackSlider.getValue();
    }
    if (slider == &decaySlider)
    {
        audioProcessor.decayTime = decaySlider.getValue();
    }
    if (slider == &sustainSlider)
    {
        audioProcessor.sustainValue = sustainSlider.getValue();
    }
    if (slider == &releaseSlider)
    {
        audioProcessor.releaseTime = releaseSlider.getValue();
    }
}