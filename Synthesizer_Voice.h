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
        bool canPlaySound(juce::SynthesiserSound* sound) override
        {
            return dynamic_cast<SynthSound*>(sound) != nullptr;
        }

        void setPitchBend(int pitchWheelPos)
        {
            if (pitchWheelPos > 8192)
            {
                // shifting up
                pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
            }
            else
            {
                // shifting down
                pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
            }
        }

        float pitchBendCents()
        {
            if (pitchBend >= 0.0f)
            {
                // shifting up
                return pitchBend * pitchBendUpSemitones * 100;
            }
            else
            {
                // shifting down
                return pitchBend * pitchBendDownSemitones * 100;
            }
        }

        static double noteHz(int midiNoteNumber, double centsOffset)
        {
            double hertz = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
            hertz *= std::pow(2.0, centsOffset / 1200);
            return hertz;
        }

        void getADSR_AParam(float* attack, float* decay, float* sustain, float* release)
        {
            ADSR_A.setAttack(double(*attack));
            ADSR_A.setDecay(double(*decay));
            ADSR_A.setSustain(double(*sustain));
            ADSR_A.setRelease(double(*release));
        }

        double setADSR_A()
        {
            return ADSR_A.adsr(setOscType(), ADSR_A.trigger);
        }

        void getADSR_BParam(float* attack, float* decay, float* sustain, float* release)
        {
            ADSR_B.setAttack(double(*attack));
            ADSR_B.setDecay(double(*decay));
            ADSR_B.setSustain(double(*sustain));
            ADSR_B.setRelease(double(*release));
        }

        double setADSR_B()
        {
            return ADSR_B.adsr(setOscType(), ADSR_B.trigger);
        }

        void getWaveformAType(float* selection)
        {
            waveA = *selection;
        }

        void getWaveformBType(float* selection)
        {
            waveB = *selection;
        }

        double setOscType()
        {
            double sampleA, sampleB;

            switch (waveA)
            {
                case 0:
                    sampleA = oscA.sinewave(frequency);
                    break;
                case 1:
                    sampleA = oscA.saw(frequency);
                    break;
                case 2:
                    sampleA = oscA.square(frequency);
                    break;
                case 3:
                    sampleA = oscA.triangle(frequency);
                    break;
                default:
                    sampleA = oscA.sinewave(frequency);
                    break;
            }

            switch (waveB)
            {
                case 0:
                    sampleB = oscB.sinewave(frequency);
                    break;
                case 1:
                    sampleB = oscB.saw(frequency);
                    break;
                case 2:
                    sampleB = oscB.square(frequency);
                    break;
                case 3:
                    sampleB = oscB.triangle(frequency);
                    break;
                default:
                    sampleB = oscB.sinewave(frequency);
                    break;
            }

            return sampleA * oscAMix + sampleB * oscBMix;
        }

        void getParams(float* mVol, float* mixA, float* mixB, float* pbup, float* pbdn)
        {
            masterVolume = *mVol;
            oscAMix = *mixA;
            oscBMix = *mixB;
            pitchBendUpSemitones = *pbup;
            pitchBendDownSemitones = *pbdn;
        }

        void getFilterParam(float* type, float* cutoff, float* resonance)
        {
            filterType = *type;
            filterCutoff = *cutoff;
            filterResonance = *resonance;
        }

        void getEnv1Param(float* attack, float* decay, float* sustain, float* release)
        {
            env1.setAttack(double(*attack));
            env1.setDecay(double(*decay));
            env1.setSustain(double(*sustain));
            env1.setRelease(double(*release));
        }

        void getEnv2Param(float* attack, float* decay, float* sustain, float* release)
        {
            env2.setAttack(double(*attack));
            env2.setDecay(double(*decay));
            env2.setSustain(double(*sustain));
            env2.setRelease(double(*release));
        }

        double setEnv1()
        {

        }

        double setEnv2()
        {

        }

        void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
        {
            noteNumber = midiNoteNumber;
            ADSR_A.trigger = 1;
            ADSR_B.trigger = 1;
            env1.trigger = 1;
            env2.trigger = 1;
            setPitchBend(currentPitchWheelPosition);
            level = velocity;
            frequency = noteHz(noteNumber, pitchBendCents());
        }

        void stopNote(float velocity, bool allowTailOff)
        {
            ADSR_A.trigger = 0;
            ADSR_B.trigger = 0;
            env1.trigger = 0;
            env2.trigger = 0;
            allowTailOff = true;

            if (velocity == 0)
            {
                clearCurrentNote();
            }
        }

        void pitchWheelMoved(int newPitchWheelValue)
        {
            setPitchBend(newPitchWheelValue);
            frequency = noteHz(noteNumber, pitchBendCents());
        }

        void controllerMoved(int controllerNumber, int newControllerValue)
        {

        }

        void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numOfSamples)
        {

            for (int sample = 0; sample < numOfSamples; ++sample)
            {

                for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                {
                    outputBuffer.addSample(channel, startSample, setADSR_A()*masterVolume);
                }

                ++startSample;
            }
        }

    private:
        double level;
        double frequency;
        int waveA, waveB;

        float masterVolume;
        float oscAMix, oscBMix;

        int noteNumber;
        float pitchBend = 0.0f;
        float pitchBendUpSemitones = 2.0f;
        float pitchBendDownSemitones = 2.0f;

        int filterType;
        float filterCutoff;
        float filterResonance;

        maxiOsc oscA, oscB;
        maxiEnv ADSR_A, ADSR_B, env1, env2;

};