#include "EffectChain.h"

namespace muzikiii {

EffectChain::EffectChain(juce::AudioProcessorValueTreeState& apvts)
    : reverb(apvts)
    , delay(apvts)
    , eq(apvts)
    , distortion(apvts)
    , chorus(apvts)
    , compressor(apvts)
    , chain({ &reverb, &delay, &eq, &distortion, &chorus, &compressor })
{
}

void EffectChain::prepare(const juce::dsp::ProcessSpec& spec)
{
    for (auto* effect : chain)
        effect->prepare(spec);
}

void EffectChain::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    for (auto* effect : chain)
        effect->process(block);
}

void EffectChain::reset()
{
    for (auto* effect : chain)
        effect->reset();
}

} // namespace muzikiii
