#pragma once

#include "BaseEffect.h"

namespace muzikiii {

class DistortionProcessor : public BaseEffect
{
public:
    DistortionProcessor(juce::AudioProcessorValueTreeState& apvts);

    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::dsp::AudioBlock<float>& block) override;
    void reset() override;
    void updateParameters() override;

private:
    juce::dsp::WaveShaper<float> waveShaper;
    juce::dsp::DryWetMixer<float> dryWetMixer;
    juce::dsp::Oversampling<float> oversampling2x { 2, 1, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR };
    juce::dsp::Oversampling<float> oversampling4x { 2, 2, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR };
    float amount = 0.4f;
    int oversampleMode = 0;

    std::atomic<float>* enabledParam = nullptr;
    std::atomic<float>* amountParam = nullptr;
    std::atomic<float>* oversampleParam = nullptr;
    std::atomic<float>* wetParam = nullptr;
};

} // namespace muzikiii
