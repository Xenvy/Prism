/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PrismAudioProcessor::PrismAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    tree(*this, nullptr, "PARAMETERS",
        { std::make_unique<juce::AudioParameterFloat>("attackA", "AttackA", juce::NormalisableRange<float>(0.0f, 5000.0f), 20.0f),
          std::make_unique<juce::AudioParameterFloat>("decayA", "DecayA", juce::NormalisableRange<float>(0.0f, 5000.0f), 500.0f),
          std::make_unique<juce::AudioParameterFloat>("sustainA", "SustainA", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("releaseA", "ReleaseA", juce::NormalisableRange<float>(0.0f, 5000.0f), 800.0f),
          std::make_unique<juce::AudioParameterFloat>("attackB", "AttackB", juce::NormalisableRange<float>(0.0f, 5000.0f), 20.0f),
          std::make_unique<juce::AudioParameterFloat>("decayB", "DecayB", juce::NormalisableRange<float>(0.0f, 5000.0f), 500.0f),
          std::make_unique<juce::AudioParameterFloat>("sustainB", "SustainB", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("releaseB", "ReleaseB", juce::NormalisableRange<float>(0.0f, 5000.0f), 800.0f),
          std::make_unique<juce::AudioParameterFloat>("attack1", "Attack1", juce::NormalisableRange<float>(0.0f, 5000.0f), 20.0f),
          std::make_unique<juce::AudioParameterFloat>("decay1", "Decay1", juce::NormalisableRange<float>(0.0f, 5000.0f), 500.0f),
          std::make_unique<juce::AudioParameterFloat>("sustain1", "Sustain1", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("release1", "Release1", juce::NormalisableRange<float>(0.0f, 5000.0f), 800.0f),
          std::make_unique<juce::AudioParameterFloat>("attack2", "Attack2", juce::NormalisableRange<float>(0.0f, 5000.0f), 20.0f),
          std::make_unique<juce::AudioParameterFloat>("decay2", "Decay2", juce::NormalisableRange<float>(0.0f, 5000.0f), 500.0f),
          std::make_unique<juce::AudioParameterFloat>("sustain2", "Sustain2", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("release2", "Release2", juce::NormalisableRange<float>(0.0f, 5000.0f), 800.0f),
          std::make_unique<juce::AudioParameterFloat>("waveformA", "WaveformA", juce::NormalisableRange<float>(0, 3), 0),
          std::make_unique<juce::AudioParameterFloat>("waveformB", "WaveformB", juce::NormalisableRange<float>(0, 3), 0),
          std::make_unique<juce::AudioParameterFloat>("cutoff", "Cutoff", juce::NormalisableRange<float>(20.0f, 20000.0f), 500.0f),
          std::make_unique<juce::AudioParameterFloat>("resonance", "Resonance", juce::NormalisableRange<float>(1, 5), 1),
          std::make_unique<juce::AudioParameterFloat>("filterType", "FilterType", juce::NormalisableRange<float>(0, 3), 0),
          std::make_unique<juce::AudioParameterFloat>("mixA", "MixA", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("mixB", "MixB", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("masterVolume", "MasterVolume", juce::NormalisableRange<float>(0.0f, 1.0f), 0.6f),
          std::make_unique<juce::AudioParameterFloat>("pbup", "PBup", juce::NormalisableRange<float>(1.0f, 12.0f), 1.0f),
          std::make_unique<juce::AudioParameterFloat>("pbdown", "PBdown", juce::NormalisableRange<float>(1.0f, 12.0f), 1.0f) })
#endif
{
    Prism.clearVoices();

    for (int i = 0; i < 5; i++)
    {
        Prism.addVoice(new SynthVoice());
    }

    Prism.clearSounds();
    Prism.addSound(new SynthSound());
}

PrismAudioProcessor::~PrismAudioProcessor()
{
}

//==============================================================================
const juce::String PrismAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PrismAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PrismAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PrismAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PrismAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PrismAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PrismAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PrismAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PrismAudioProcessor::getProgramName (int index)
{
    return {};
}

void PrismAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PrismAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    Prism.setCurrentPlaybackSampleRate(lastSampleRate);

    juce::dsp::ProcessSpec procSpec;
    procSpec.sampleRate = lastSampleRate;
    procSpec.maximumBlockSize = samplesPerBlock;
    procSpec.numChannels = getTotalNumOutputChannels();

    stateVarFilter.reset();
    stateVarFilter.prepare(procSpec);
    updateFilter();

}

void PrismAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PrismAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PrismAudioProcessor::updateFilter()
{
    int filterSelection = *tree.getRawParameterValue("filterType");
    int cutoffValue = *tree.getRawParameterValue("cutoff");
    int resonanceValue = *tree.getRawParameterValue("resonance");

    switch (filterSelection)
    {
    case 0:
        bypassFilter = 1;
        break;
    case 1:
        bypassFilter = 0;
        stateVarFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVarFilter.state->setCutOffFrequency(lastSampleRate, cutoffValue, resonanceValue);
        break;
    case 2:
        bypassFilter = 0;
        stateVarFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVarFilter.state->setCutOffFrequency(lastSampleRate, cutoffValue, resonanceValue);
        break;
    case 3:
        bypassFilter = 0;
        stateVarFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        stateVarFilter.state->setCutOffFrequency(lastSampleRate, cutoffValue, resonanceValue);
        break;
    default:
        bypassFilter = 1;
        break;
    }
}


void PrismAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    //}

    for (int i = 0; i < Prism.getNumVoices(); i++)
    {
        if ((PrismVoice = dynamic_cast<SynthVoice*>(Prism.getVoice(i))))
        {
            float* attackAPtr = (float*)tree.getRawParameterValue("attackA");
            float* decayAPtr = (float*)tree.getRawParameterValue("decayA");
            float* sustainAPtr = (float*)tree.getRawParameterValue("sustainA");
            float* releaseAPtr = (float*)tree.getRawParameterValue("releaseA");
            float* attackBPtr = (float*)tree.getRawParameterValue("attackB");
            float* decayBPtr = (float*)tree.getRawParameterValue("decayB");
            float* sustainBPtr = (float*)tree.getRawParameterValue("sustainB");
            float* releaseBPtr = (float*)tree.getRawParameterValue("releaseB");
            float* attack1Ptr = (float*)tree.getRawParameterValue("attack1");
            float* decay1Ptr = (float*)tree.getRawParameterValue("decay1");
            float* sustain1Ptr = (float*)tree.getRawParameterValue("sustain1");
            float* release1Ptr = (float*)tree.getRawParameterValue("release1");
            float* attack2Ptr = (float*)tree.getRawParameterValue("attack2");
            float* decay2Ptr = (float*)tree.getRawParameterValue("decay2");
            float* sustain2Ptr = (float*)tree.getRawParameterValue("sustain2");
            float* release2Ptr = (float*)tree.getRawParameterValue("release2");
            float* waveformAPtr = (float*)tree.getRawParameterValue("waveformA");
            float* waveformBPtr = (float*)tree.getRawParameterValue("waveformB");
            float* filterPtr = (float*)tree.getRawParameterValue("filterType");
            float* cutoffPtr = (float*)tree.getRawParameterValue("cutoff");
            float* resonancePtr = (float*)tree.getRawParameterValue("resonance");
            float* mixAPtr = (float*)tree.getRawParameterValue("mixA");
            float* mixBPtr = (float*)tree.getRawParameterValue("mixB");
            float* masterVolumePtr = (float*)tree.getRawParameterValue("masterVolume");
            float* pbupPtr = (float*)tree.getRawParameterValue("pbup");
            float* pbdownPtr = (float*)tree.getRawParameterValue("pbdown");
            PrismVoice->getADSR_AParam(attackAPtr, decayAPtr, sustainAPtr, releaseAPtr);
            PrismVoice->getADSR_BParam(attackBPtr, decayBPtr, sustainBPtr, releaseBPtr);
            PrismVoice->getEnv1Param(attack1Ptr, decay1Ptr, sustain1Ptr, release1Ptr);
            PrismVoice->getEnv2Param(attack2Ptr, decay2Ptr, sustain2Ptr, release2Ptr);
            PrismVoice->getWaveformAType(waveformAPtr);
            PrismVoice->getWaveformBType(waveformBPtr);
            PrismVoice->getFilterParam(filterPtr, cutoffPtr, resonancePtr);
            PrismVoice->getParams(masterVolumePtr, mixAPtr, mixBPtr, pbupPtr, pbdownPtr);
        }
    }

    buffer.clear();
    Prism.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    updateFilter();
    if (bypassFilter == 0)
    {
        juce::dsp::AudioBlock<float> aBlock(buffer);
        stateVarFilter.process(juce::dsp::ProcessContextReplacing<float>(aBlock));
    }
}

//==============================================================================
bool PrismAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PrismAudioProcessor::createEditor()
{
    return new PrismAudioProcessorEditor (*this);
}

//==============================================================================
void PrismAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PrismAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PrismAudioProcessor();
}
