#include "DistortionProcessor.h"
#include "../Parameters/ParameterLayout.h"

namespace muzikiii {

DistortionProcessor::DistortionProcessor(juce::AudioProcessorValueTreeState& apvts)
{
    enabledParam    = apvts.getRawParameterValue(ParamIDs::distEnabled);
    amountParam     = apvts.getRawParameterValue(ParamIDs::distAmount);
    oversampleParam = apvts.getRawParameterValue(ParamIDs::distOversample);
    wetParam        = apvts.getRawParameterValue(ParamIDs::distWet);

    // tanh waveshaper (same as Tone.Distortion default)
    waveShaper.functionToUse = [](float x) { return std::tanh(x); };
}

void DistortionProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    dryWetMixer.prepare(spec);
    dryWetMixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    oversampling2x.initProcessing(spec.maximumBlockSize);
    oversampling4x.initProcessing(spec.maximumBlockSize);
}

void DistortionProcessor::process(juce::dsp::AudioBlock<float>& block)
{
    updateParameters();

    if (!enabled)
        return;

    dryWetMixer.pushDrySamples(block);

    // Apply drive gain based on amount
    float driveGain = 1.0f + amount * 19.0f; // 1x to 20x gain
    block.multiplyBy(driveGain);

    // Process with optional oversampling
    if (oversampleMode == 1)
    {
        auto oversampledBlock = oversampling2x.processSamplesUp(block);
        juce::dsp::ProcessContextReplacing<float> context(oversampledBlock);
        waveShaper.process(context);
        oversampling2x.processSamplesDown(block);
    }
    else if (oversampleMode == 2)
    {
        auto oversampledBlock = oversampling4x.processSamplesUp(block);
        juce::dsp::ProcessContextReplacing<float> context(oversampledBlock);
        waveShaper.process(context);
        oversampling4x.processSamplesDown(block);
    }
    else
    {
        juce::dsp::ProcessContextReplacing<float> context(block);
        waveShaper.process(context);
    }

    // Compensate output level
    block.multiplyBy(1.0f / driveGain);

    dryWetMixer.mixWetSamples(block);
}

void DistortionProcessor::reset()
{
    dryWetMixer.reset();
    oversampling2x.reset();
    oversampling4x.reset();
}

void DistortionProcessor::updateParameters()
{
    enabled = enabledParam->load() > 0.5f;
    amount = amountParam->load();
    oversampleMode = static_cast<int>(oversampleParam->load());
    dryWetMixer.setWetMixProportion(wetParam->load());
}

} // namespace muzikiii
