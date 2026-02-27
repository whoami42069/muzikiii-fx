#pragma once

#include "BaseEffect.h"

namespace muzikiii {

class ReverbProcessor : public BaseEffect
{
public:
    ReverbProcessor(juce::AudioProcessorValueTreeState& apvts);

    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::dsp::AudioBlock<float>& block) override;
    void reset() override;
    void updateParameters() override;

private:
    juce::dsp::Reverb reverb;
    juce::dsp::DryWetMixer<float> dryWetMixer;

    std::atomic<float>* enabledParam = nullptr;
    std::atomic<float>* decayParam = nullptr;
    std::atomic<float>* preDelayParam = nullptr;
    std::atomic<float>* wetParam = nullptr;
};

} // namespace muzikiii
