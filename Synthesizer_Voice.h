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
        return ADSR_A.adsr(setOscTypeA() * oscAMix, ADSR_A.trigger);
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
        return ADSR_B.adsr(setOscTypeB() * oscBMix, ADSR_B.trigger);
    }

    void getWaveformAType(float* selection)
    {
        waveA = *selection;
    }

    void getWaveformBType(float* selection)
    {
        waveB = *selection;
    }

    double setOscTypeA()
    {

        switch (waveA)
        {
        case 0:
            return oscA.sinewave(frequencyA);
            break;
        case 1:
            return oscA.saw(frequencyA);
            break;
        case 2:
            return oscA.square(frequencyA);
            break;
        case 3:
            return oscA.triangle(frequencyA);
            break;
        default:
            return oscA.sinewave(frequencyA);
            break;
        }

    }

    double setOscTypeB()
    {
        switch (waveB)
        {
        case 0:
            return oscB.sinewave(frequencyB);
            break;
        case 1:
            return oscB.saw(frequencyB);
            break;
        case 2:
            return oscB.square(frequencyB);
            break;
        case 3:
            return oscB.triangle(frequencyB);
            break;
        default:
            return oscB.sinewave(frequencyB);
            break;
        }
    }

    void getParams(float* mVol, float* mixA, float* mixB)
    {
        masterVolume = *mVol;
        oscAMix = *mixA;
        oscBMix = *mixB;
    }

    void getFilterParam(float* typeA, float* cutoffA, float* resonanceA, float* typeB, float* cutoffB, float* resonanceB)
    {
        filterTypeA = *typeA;
        filterCutoffA = *cutoffA;
        filterResonanceA = *resonanceA;

        filterTypeB = *typeB;
        filterCutoffB = *cutoffB;
        filterResonanceB = *resonanceB;

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

    void getEnv1Type(float* selection)
    {
        env1Type = *selection;
    }

    void getEnv2Type(float* selection)
    {
        env2Type = *selection;
    }


    void setEnv1()
    {
        switch (env1Type)
        {
        case 0:
            resetEnv();
            break;
        case 1:
            cutoffLFOA = env1.adsr(filterCutoffA, env1.trigger);
            break;
        case 2:
            cutoffLFOB = env1.adsr(filterCutoffB, env1.trigger);
            break;
        case 3:
            frequencyA = noteHz(noteNumber, env1.adsr(pitchoffsetA, env1.trigger));
            break;
        case 4:
            frequencyB = noteHz(noteNumber, env1.adsr(pitchoffsetB, env1.trigger));
            break;
        case 5:
            levelRA = env1.adsr(panningA, env1.trigger);
            break;
        case 6:
            levelRB = env1.adsr(panningB, env1.trigger);
            break;
        default:
            break;
        }
    }

    void setEnv2()
    {
        switch (env2Type)
        {
        case 0:
            resetEnv();
            break;
        case 1:
            cutoffLFOA = env2.adsr(filterCutoffA, env2.trigger);
            break;
        case 2:
            cutoffLFOB = env2.adsr(filterCutoffB, env2.trigger);
            break;
        case 3:
            frequencyA = noteHz(noteNumber, env2.adsr(pitchoffsetA, env2.trigger));
            break;
        case 4:
            frequencyB = noteHz(noteNumber, env2.adsr(pitchoffsetB, env2.trigger));
            break;
        case 5:
            levelRA = env2.adsr(panningA, env2.trigger);
            break;
        case 6:
            levelRB = env2.adsr(panningB, env2.trigger);
            break;
        default:
            break;
        }
    }

    void getLFO1Param(float* type, float* rate, float* depth)
    {
        LFO1Type = *type;
        LFO1Rate = *rate;
        LFO1Depth = *depth;
    }

    void getLFO2Param(float* type, float* rate, float* depth)
    {
        LFO2Type = *type;
        LFO2Rate = *rate;
        LFO2Depth = *depth;
    }

    void set_LFO_1()
    {
        switch (LFO1Type)
        {
        case 0:
            resetLFO();
            break;
        case 1:
            cutoffLFOA = cutoffLFOA * (LFO1.sinewave(LFO1Rate) * LFO1Depth * 0.75f + 1);
            break;
        case 2:
            cutoffLFOB = cutoffLFOB * (LFO1.sinewave(LFO1Rate) * LFO1Depth * 0.75f + 1);
            break;
        case 3:
            LFO_VolumeA = LFO1.sinewave(LFO1Rate) * LFO1Depth + 1;
            break;
        case 4:
            LFO_VolumeB = LFO1.sinewave(LFO1Rate) * LFO1Depth + 1;
            break;
        case 5:
            frequencyA = frequencyA * (LFO1.sinewave(LFO1Rate) * LFO1Depth * 0.25f + 1);
            break;
        case 6:
            frequencyB = frequencyB * (LFO1.sinewave(LFO1Rate) * LFO1Depth * 0.25f + 1);
            break;
        case 7:
            levelRA = levelRA * (LFO1.sinewave(LFO1Rate) * LFO1Depth + 1);
            break;
        case 8:
            levelRB = levelRB * (LFO1.sinewave(LFO1Rate) * LFO1Depth + 1);
            break;
        default:
            break;
        }
    }

    void set_LFO_2()
    {
        switch (LFO2Type)
        {
        case 0:
            resetLFO();
            break;
        case 1:
            cutoffLFOA = cutoffLFOA * (LFO2.sinewave(LFO2Rate) * LFO2Depth * 0.75f + 1);
            break;
        case 2:
            cutoffLFOB = cutoffLFOB * (LFO2.sinewave(LFO2Rate) * LFO2Depth * 0.75f + 1);
            break;
        case 3:
            LFO_VolumeA = LFO2.sinewave(LFO2Rate) * LFO2Depth + 1;
            break;
        case 4:
            LFO_VolumeB = LFO2.sinewave(LFO2Rate) * LFO2Depth + 1;
            break;
        case 5:
            frequencyA = frequencyA * (LFO2.sinewave(LFO2Rate) * LFO2Depth * 0.25f + 1);
            break;
        case 6:
            frequencyB = frequencyB * (LFO2.sinewave(LFO2Rate) * LFO2Depth * 0.25f + 1);
            break;
        case 7:
            levelRA = levelRA * (LFO2.sinewave(LFO2Rate) * LFO2Depth + 1);
            break;
        case 8:
            levelRB = levelRB * (LFO2.sinewave(LFO2Rate) * LFO2Depth + 1);
            break;
        default:
            break;
        }
    }

    void resetEnv()
    {
        frequencyA = noteHz(noteNumber, 0);
        frequencyB = noteHz(noteNumber, 0);

        panningA = 1;
        panningB = 1;
        levelRA = 0.5f;
        levelRB = 0.5f;

        cutoffLFOA = filterCutoffA;
        cutoffLFOB = filterCutoffB;
    }

    void resetLFO()
    {
        LFO_VolumeA = 1.0f;
        LFO_VolumeB = 1.0f;
    }

    double filterSoundLA()
    {

        switch (filterTypeA)
        {
        case 0:
            return 0;
            break;
        case 1:
            return filter1.lores(soundLA, cutoffLFOA, filterResonanceA);
            break;
        case 2:
            return filter1.hires(soundLA, cutoffLFOA, filterResonanceA);
            break;
        case 3:
            return filter1.bandpass(soundLA, cutoffLFOA, filterResonanceA);
            break;
        default:
            return 0;
            break;
        }

    }

    double filterSoundLB()
    {
        switch (filterTypeB)
        {
        case 0:
            return 0;
            break;
        case 1:
            return filter2.lores(soundLB, cutoffLFOB, filterResonanceB);
            break;
        case 2:
            return filter2.hires(soundLB, cutoffLFOB, filterResonanceB);
            break;
        case 3:
            return filter2.bandpass(soundLB, cutoffLFOB, filterResonanceB);
            break;
        default:
            return 0;
            break;
        }
    }

    double filterSoundRA()
    {

        switch (filterTypeA)
        {
        case 0:
            return 0;
            break;
        case 1:
            return filter3.lores(soundRA, cutoffLFOA, filterResonanceA);
            break;
        case 2:
            return filter3.hires(soundRA, cutoffLFOA, filterResonanceA);
            break;
        case 3:
            return filter3.bandpass(soundRA, cutoffLFOA, filterResonanceA);
            break;
        default:
            return 0;
            break;
        }

    }

    double filterSoundRB()
    {
        switch (filterTypeB)
        {
        case 0:
            return 0;
            break;
        case 1:
            return filter4.lores(soundRB, cutoffLFOB, filterResonanceB);
            break;
        case 2:
            return filter4.hires(soundRB, cutoffLFOB, filterResonanceB);
            break;
        case 3:
            return filter4.bandpass(soundRB, cutoffLFOB, filterResonanceB);
            break;
        default:
            return 0;
            break;
        }
    }

    void pitchWheelMoved(int newPitchWheelValue)
    {

    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        noteNumber = midiNoteNumber;
        ADSR_A.trigger = 1;
        ADSR_B.trigger = 1;
        env1.trigger = 1;
        env2.trigger = 1;
        level = velocity;

        frequencyA = noteHz(noteNumber, pitchBendCents());
        frequencyB = noteHz(noteNumber, pitchBendCents());

        panningA = 1;
        panningB = 1;
        levelRA = 0.5f;
        levelRB = 0.5f;

        LFO_VolumeA = 1.0f;
        LFO_VolumeB = 1.0f;
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


    void controllerMoved(int controllerNumber, int newControllerValue)
    {

    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numOfSamples)
    {

        float soundFilteredA, soundFilteredB;


        for (int sample = 0; sample < numOfSamples; ++sample)
        {

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                setEnv1();
                setEnv2();
                set_LFO_1();
                set_LFO_2();
                if (channel == 0)
                {
                    soundLA = setADSR_A() * (1.0 - levelRA) * LFO_VolumeA;
                    soundLB = setADSR_B() * (1.0 - levelRB) * LFO_VolumeB;
                    if (filterTypeA != 0)
                    {
                        soundFilteredA = filterSoundLA();
                    }
                    else
                    {
                        soundFilteredA = soundLA;
                    }
                    if (filterTypeB != 0)
                    {
                        soundFilteredB = filterSoundLB();
                    }
                    else
                    {
                        soundFilteredB = soundLB;
                    }
                    outputBuffer.addSample(channel, startSample, (soundFilteredA + soundFilteredB) * masterVolume);
                }
                else
                {
                    soundRA = setADSR_A() * levelRA * LFO_VolumeA;
                    soundRB = setADSR_B() * levelRB * LFO_VolumeB;
                    if (filterTypeA != 0)
                    {
                        soundFilteredA = filterSoundRA();
                    }
                    else
                    {
                        soundFilteredA = soundRA;
                    }
                    if (filterTypeB != 0)
                    {
                        soundFilteredB = filterSoundRB();
                    }
                    else
                    {
                        soundFilteredB = soundRB;
                    }

                    outputBuffer.addSample(channel, startSample, (soundFilteredA + soundFilteredB) * masterVolume);
                }
            }

            ++startSample;
        }

    }

private:
    double level;
    double frequencyA, frequencyB;
    int waveA, waveB;
    int env1Type, env2Type;
    int LFO1Type, LFO2Type;

    float LFO1Rate, LFO2Rate, LFO1Depth, LFO2Depth;

    float pitchoffsetA = 1200.0f;
    float pitchoffsetB = 1200.0f;
    float panningA = 1;
    float panningB = 1;
    float levelRA = 0.5f;
    float levelRB = 0.5f;

    float LFO_VolumeA = 1.0f;
    float LFO_VolumeB = 1.0f;

    float masterVolume;
    float oscAMix, oscBMix;

    int noteNumber;
    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;

    int filterTypeA;
    float filterCutoffA;
    float filterResonanceA;

    int filterTypeB;
    float filterCutoffB;
    float filterResonanceB;


    float cutoffLFOA;
    float cutoffLFOB;

    float soundRA, soundRB, soundLA, soundLB;

    maxiOsc oscA, oscB, LFO1, LFO2;
    maxiEnv ADSR_A, ADSR_B, env1, env2;

    maxiFilter filter1, filter2, filter3, filter4;

};