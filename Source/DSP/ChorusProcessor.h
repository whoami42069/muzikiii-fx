#pragma once

#include "BaseEffect.h"

namespace muzikiii {

class ChorusProcessor : public BaseEffect
{
public:
    ChorusProcessor(juce::AudioProcessorValueTreeState& apvts);

    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::dsp::AudioBlock<float>& block) override;
    void reset() override;
    void updateParameters() override;

private:
    juce::dsp::Chorus<float> chorus;
    juce::dsp::DryWetMixer<float> dryWetMixer;

    std::atomic<float>* enabledParam = nullptr;
    std::atomic<float>* rateParam = nullptr;
    std::atomic<float>* delayParam = nullptr;
    std::atomic<float>* depthParam = nullptr;
    std::atomic<float>* wetParam = nullptr;
};

} // namespace muzikiii
