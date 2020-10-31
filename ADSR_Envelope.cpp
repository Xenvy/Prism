/*
  ==============================================================================

    ADSR_Envelope.cpp
    Created: 31 Oct 2020 2:14:11pm
    Author:  Jasiek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSR_Envelope.h"

//==============================================================================
ADSR_Envelope::ADSR_Envelope(PrismAudioProcessor& p):
audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.0f, 5000.0f);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
    attackSlider.setValue(0.1f);
    attackSlider.addListener(this);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.0f, 5000.0f);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
    decaySlider.setValue(500.0f);
    decaySlider.addListener(this);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
    sustainSlider.setValue(0.5f);
    sustainSlider.addListener(this);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.0f, 5000.0f);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
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

ADSR_Envelope::~ADSR_Envelope()
{
}

void ADSR_Envelope::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(juce::Colours::black);
}

void ADSR_Envelope::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    attackSlider.setBounds(10, 10, 40, 100);
    decaySlider.setBounds(50, 10, 40, 100);
    sustainSlider.setBounds(90, 10, 40, 100);
    releaseSlider.setBounds(130, 10, 40, 100);

}

void ADSR_Envelope::sliderValueChanged(juce::Slider* slider)
{
    //if (slider == &attackSlider)
    //{
    //    audioProcessor.attackTime = attackSlider.getValue();
    //}
    //if (slider == &decaySlider)
    //{
    //    audioProcessor.decayTime = decaySlider.getValue();
    //}
    //if (slider == &sustainSlider)
    //{
    //    audioProcessor.sustainValue = sustainSlider.getValue();
    //}
    //if (slider == &releaseSlider)
    //{
    //    audioProcessor.releaseTime = releaseSlider.getValue();
    //}
}