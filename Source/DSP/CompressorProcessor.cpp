#include "CompressorProcessor.h"
#include "../Parameters/ParameterLayout.h"

namespace muzikiii {

CompressorProcessor::CompressorProcessor(juce::AudioProcessorValueTreeState& apvts)
{
    enabledParam   = apvts.getRawParameterValue(ParamIDs::compEnabled);
    thresholdParam = apvts.getRawParameterValue(ParamIDs::compThreshold);
    ratioParam     = apvts.getRawParameterValue(ParamIDs::compRatio);
    attackParam    = apvts.getRawParameterValue(ParamIDs::compAttack);
    releaseParam   = apvts.getRawParameterValue(ParamIDs::compRelease);
    kneeParam      = apvts.getRawParameterValue(ParamIDs::compKnee);
}

void CompressorProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    compressor.prepare(spec);
}

void CompressorProcessor::process(juce::dsp::AudioBlock<float>& block)
{
    updateParameters();

    if (!enabled)
        return;

    juce::dsp::ProcessContextReplacing<float> context(block);
    compressor.process(context);
}

void CompressorProcessor::reset()
{
    compressor.reset();
}

void CompressorProcessor::updateParameters()
{
    enabled = enabledParam->load() > 0.5f;
    compressor.setThreshold(thresholdParam->load());
    compressor.setRatio(ratioParam->load());
    compressor.setAttack(attackParam->load() * 1000.0f); // Convert seconds to milliseconds
    compressor.setRelease(releaseParam->load() * 1000.0f);
}

} // namespace muzikiii
