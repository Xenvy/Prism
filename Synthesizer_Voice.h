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

        void getADSRParam(float* attack, float* decay, float* sustain, float* release)
        {
            envelope1.setAttack(double(*attack));
            envelope1.setDecay(double(*decay));
            envelope1.setSustain(double(*sustain));
            envelope1.setRelease(double(*release));
        }

        double setADSR()
        {
            return envelope1.adsr(setOscType(), envelope1.trigger);
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

            return sampleA + sampleB * oscBblend;
        }

        void getParams(float* mVol, float* blend, float* pbup, float* pbdn)
        {
            masterVolume = *mVol;
            oscBblend = *blend;
            pitchBendUpSemitones = *pbup;
            pitchBendDownSemitones = *pbdn;
        }

        void getFilterParam(float* type, float* cutoff, float* resonance)
        {
            filterType = *type;
            filterCutoff = *cutoff;
            filterResonance = *resonance;
        }


        void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
        {
            noteNumber = midiNoteNumber;
            envelope1.trigger = 1;
            setPitchBend(currentPitchWheelPosition);
            level = velocity;
            frequency = noteHz(noteNumber, pitchBendCents());
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
                    outputBuffer.addSample(channel, startSample, setADSR()*masterVolume);
                }

                ++startSample;
            }
        }

    private:
        double level;
        double frequency;
        int waveA, waveB;

        float masterVolume;
        float oscBblend;

        int noteNumber;
        float pitchBend = 0.0f;
        float pitchBendUpSemitones = 2.0f;
        float pitchBendDownSemitones = 2.0f;

        int filterType;
        float filterCutoff;
        float filterResonance;

        maxiOsc oscA, oscB;
        maxiEnv envelope1;

};