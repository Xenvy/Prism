/*
  ==============================================================================

    Synthesizer_Voice.h
    Created: 18 Sep 2020 6:52:14pm
    Author:  Burza

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Synthesizer_Sound.h"
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
    public:
        bool canPlaySound(juce::SynthesiserSound* sound)
        {
            return dynamic_cast<SynthSound*>(sound) != nullptr;
        }

        void getParam(float* attack, float* decay, float* sustain, float* release)
        {
            envelope1.setAttack(double(*attack));
            envelope1.setDecay(double(*decay));
            envelope1.setSustain(double(*sustain));
            envelope1.setRelease(double(*release));
        }

        void getWaveformType(float* selection)
        {
            wave = *selection;
        }

        double setOscType()
        {
            switch (wave)
            {
                case 0:
                    return oscA.sinewave(frequency);
                    break;
                case 1:
                    return oscA.saw(frequency);
                    break;
                case 2:
                    return oscA.square(frequency);
                    break;
                case 3:
                    return oscA.triangle(frequency);
                    break;
                default:
                    return oscA.sinewave(frequency);
                    break;
            }
        }

        void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
        {
            envelope1.trigger = 1;
            level = velocity;
            frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
            std::cout << midiNoteNumber << std::endl;
        }

        void stopNote(float velocity, bool allowTailOff)
        {
            envelope1.trigger = 0;
            allowTailOff = true;

            if (velocity == 0)
            {
                clearCurrentNote();
            }
        }

        void pitchWheelMoved(int newPitchWheelValue)
        {

        }

        void controllerMoved(int controllerNumber, int newControllerValue)
        {

        }

        void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numOfSamples)
        {

            for (int sample = 0; sample < numOfSamples; ++sample)
            {
                //double wave = oscA.saw(frequency);
                double sound = envelope1.adsr(setOscType(), envelope1.trigger) * level;
                double soundFiltered = filter1.lores(sound, 500, 0.1);
                for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                {
                    outputBuffer.addSample(channel, startSample, soundFiltered);
                }

                ++startSample;
            }
        }

    private:
        double level;
        double frequency;
        int wave;
        maxiOsc oscA;
        maxiEnv envelope1;
        maxiFilter filter1;
};