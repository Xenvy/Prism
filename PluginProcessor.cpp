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
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
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
          std::make_unique<juce::AudioParameterFloat>("cutoffA", "CutoffA", juce::NormalisableRange<float>(30.0f, 8000.0f), 500.0f),
          std::make_unique<juce::AudioParameterFloat>("resonanceA", "ResonanceA", juce::NormalisableRange<float>(1, 5), 1),
          std::make_unique<juce::AudioParameterFloat>("filterTypeA", "FilterTypeA", juce::NormalisableRange<float>(0, 3), 0),
          std::make_unique<juce::AudioParameterFloat>("cutoffB", "CutoffB", juce::NormalisableRange<float>(30.0f, 8000.0f), 500.0f),
          std::make_unique<juce::AudioParameterFloat>("resonanceB", "ResonanceB", juce::NormalisableRange<float>(1, 5), 1),
          std::make_unique<juce::AudioParameterFloat>("filterTypeB", "FilterTypeB", juce::NormalisableRange<float>(0, 3), 0),
          std::make_unique<juce::AudioParameterFloat>("envType1", "EnvType1", juce::NormalisableRange<float>(0, 5), 0),
          std::make_unique<juce::AudioParameterFloat>("envType2", "EnvType2", juce::NormalisableRange<float>(0, 5), 0),
          std::make_unique<juce::AudioParameterFloat>("LFOrate1", "LFO_1_Rate", juce::NormalisableRange<float>(0.1f, 20.0f), 2.0f),
          std::make_unique<juce::AudioParameterFloat>("LFOdepth1", "LFO_1_Depth", juce::NormalisableRange<float>(0.1f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("LFOtype1", "LFO_1_Type", juce::NormalisableRange<float>(0, 8), 0),
          std::make_unique<juce::AudioParameterFloat>("LFOrate2", "LFO_2_Rate", juce::NormalisableRange<float>(0.1f, 20.0f), 2.0f),
          std::make_unique<juce::AudioParameterFloat>("LFOdepth2", "LFO_2_Depth", juce::NormalisableRange<float>(0.1f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("LFOtype2", "LFO_2_Type", juce::NormalisableRange<float>(0, 8), 0),
          std::make_unique<juce::AudioParameterFloat>("mixA", "MixA", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("mixB", "MixB", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
          std::make_unique<juce::AudioParameterFloat>("masterVolume", "MasterVolume", juce::NormalisableRange<float>(0.0f, 1.0f), 0.6f) })
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

void PrismAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String PrismAudioProcessor::getProgramName(int index)
{
    return {};
}

void PrismAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void PrismAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    Prism.setCurrentPlaybackSampleRate(lastSampleRate);

}

void PrismAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PrismAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
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


void PrismAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

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
            float* filterAPtr = (float*)tree.getRawParameterValue("filterTypeA");
            float* cutoffAPtr = (float*)tree.getRawParameterValue("cutoffA");
            float* resonanceAPtr = (float*)tree.getRawParameterValue("resonanceA");
            float* filterBPtr = (float*)tree.getRawParameterValue("filterTypeB");
            float* cutoffBPtr = (float*)tree.getRawParameterValue("cutoffB");
            float* resonanceBPtr = (float*)tree.getRawParameterValue("resonanceB");
            float* envType1Ptr = (float*)tree.getRawParameterValue("envType1");
            float* envType2Ptr = (float*)tree.getRawParameterValue("envType2");
            float* LFOtype1Ptr = (float*)tree.getRawParameterValue("LFOtype1");
            float* LFOrate1Ptr = (float*)tree.getRawParameterValue("LFOrate1");
            float* LFOdepth1Ptr = (float*)tree.getRawParameterValue("LFOdepth1");
            float* LFOtype2Ptr = (float*)tree.getRawParameterValue("LFOtype2");
            float* LFOrate2Ptr = (float*)tree.getRawParameterValue("LFOrate2");
            float* LFOdepth2Ptr = (float*)tree.getRawParameterValue("LFOdepth2");
            float* mixAPtr = (float*)tree.getRawParameterValue("mixA");
            float* mixBPtr = (float*)tree.getRawParameterValue("mixB");
            float* masterVolumePtr = (float*)tree.getRawParameterValue("masterVolume");
            PrismVoice->getADSR_AParam(attackAPtr, decayAPtr, sustainAPtr, releaseAPtr);
            PrismVoice->getADSR_BParam(attackBPtr, decayBPtr, sustainBPtr, releaseBPtr);
            PrismVoice->getEnv1Param(attack1Ptr, decay1Ptr, sustain1Ptr, release1Ptr);
            PrismVoice->getEnv2Param(attack2Ptr, decay2Ptr, sustain2Ptr, release2Ptr);
            PrismVoice->getWaveformAType(waveformAPtr);
            PrismVoice->getWaveformBType(waveformBPtr);
            PrismVoice->getFilterParam(filterAPtr, cutoffAPtr, resonanceAPtr, filterBPtr, cutoffBPtr, resonanceBPtr);
            PrismVoice->getParams(masterVolumePtr, mixAPtr, mixBPtr);
            PrismVoice->getEnv1Type(envType1Ptr);
            PrismVoice->getEnv2Type(envType2Ptr);
            PrismVoice->getLFO1Param(LFOtype1Ptr, LFOrate1Ptr, LFOdepth1Ptr);
            PrismVoice->getLFO2Param(LFOtype2Ptr, LFOrate2Ptr, LFOdepth2Ptr);
        }
    }

    buffer.clear();
    Prism.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool PrismAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PrismAudioProcessor::createEditor()
{
    return new PrismAudioProcessorEditor(*this);
}

//==============================================================================
void PrismAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PrismAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
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