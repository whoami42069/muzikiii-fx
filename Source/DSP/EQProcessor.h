#pragma once

#include "BaseEffect.h"

namespace muzikiii {

class EQProcessor : public BaseEffect
{
public:
    EQProcessor(juce::AudioProcessorValueTreeState& apvts);

    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::dsp::AudioBlock<float>& block) override;
    void reset() override;
    void updateParameters() override;

private:
    using Filter = juce::dsp::IIR::Filter<float>;
    using CoefficientsPtr = juce::dsp::IIR::Coefficients<float>::Ptr;

    juce::dsp::ProcessorDuplicator<Filter, juce::dsp::IIR::Coefficients<float>> lowShelf;
    juce::dsp::ProcessorDuplicator<Filter, juce::dsp::IIR::Coefficients<float>> peak;
    juce::dsp::ProcessorDuplicator<Filter, juce::dsp::IIR::Coefficients<float>> highShelf;

    double sampleRate = 44100.0;

    std::atomic<float>* enabledParam = nullptr;
    std::atomic<float>* lowParam = nullptr;
    std::atomic<float>* midParam = nullptr;
    std::atomic<float>* highParam = nullptr;
    std::atomic<float>* lowFreqParam = nullptr;
    std::atomic<float>* highFreqParam = nullptr;
};

} // namespace muzikiii
