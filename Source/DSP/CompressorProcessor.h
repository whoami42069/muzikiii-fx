#pragma once

#include "BaseEffect.h"

namespace muzikiii {

class CompressorProcessor : public BaseEffect
{
public:
    CompressorProcessor(juce::AudioProcessorValueTreeState& apvts);

    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::dsp::AudioBlock<float>& block) override;
    void reset() override;
    void updateParameters() override;

private:
    juce::dsp::Compressor<float> compressor;

    std::atomic<float>* enabledParam = nullptr;
    std::atomic<float>* thresholdParam = nullptr;
    std::atomic<float>* ratioParam = nullptr;
    std::atomic<float>* attackParam = nullptr;
    std::atomic<float>* releaseParam = nullptr;
    std::atomic<float>* kneeParam = nullptr;
};

} // namespace muzikiii
