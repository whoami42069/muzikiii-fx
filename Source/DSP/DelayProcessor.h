#pragma once

#include "BaseEffect.h"

namespace muzikiii {

class DelayProcessor : public BaseEffect
{
public:
    DelayProcessor(juce::AudioProcessorValueTreeState& apvts);

    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::dsp::AudioBlock<float>& block) override;
    void reset() override;
    void updateParameters() override;

private:
    juce::dsp::DelayLine<float> delayLine { 480000 }; // Max 10s at 48kHz
    juce::dsp::DryWetMixer<float> dryWetMixer;
    float feedback = 0.4f;
    float delayTimeSamples = 0.0f;
    double sampleRate = 44100.0;

    std::atomic<float>* enabledParam = nullptr;
    std::atomic<float>* timeParam = nullptr;
    std::atomic<float>* feedbackParam = nullptr;
    std::atomic<float>* wetParam = nullptr;
};

} // namespace muzikiii
