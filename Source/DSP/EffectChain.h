#pragma once

#include "BaseEffect.h"
#include "ReverbProcessor.h"
#include "DelayProcessor.h"
#include "EQProcessor.h"
#include "DistortionProcessor.h"
#include "ChorusProcessor.h"
#include "CompressorProcessor.h"

namespace muzikiii {

class EffectChain
{
public:
    EffectChain(juce::AudioProcessorValueTreeState& apvts);

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

private:
    ReverbProcessor reverb;
    DelayProcessor delay;
    EQProcessor eq;
    DistortionProcessor distortion;
    ChorusProcessor chorus;
    CompressorProcessor compressor;

    std::array<BaseEffect*, 6> chain;
};

} // namespace muzikiii
