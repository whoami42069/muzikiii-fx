#include "ChorusProcessor.h"
#include "../Parameters/ParameterLayout.h"

namespace muzikiii {

ChorusProcessor::ChorusProcessor(juce::AudioProcessorValueTreeState& apvts)
{
    enabledParam = apvts.getRawParameterValue(ParamIDs::chorusEnabled);
    rateParam    = apvts.getRawParameterValue(ParamIDs::chorusRate);
    delayParam   = apvts.getRawParameterValue(ParamIDs::chorusDelay);
    depthParam   = apvts.getRawParameterValue(ParamIDs::chorusDepth);
    wetParam     = apvts.getRawParameterValue(ParamIDs::chorusWet);
}

void ChorusProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    chorus.prepare(spec);
    dryWetMixer.prepare(spec);
    dryWetMixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}

void ChorusProcessor::process(juce::dsp::AudioBlock<float>& block)
{
    updateParameters();

    if (!enabled)
        return;

    dryWetMixer.pushDrySamples(block);

    juce::dsp::ProcessContextReplacing<float> context(block);
    chorus.process(context);

    dryWetMixer.mixWetSamples(block);
}

void ChorusProcessor::reset()
{
    chorus.reset();
    dryWetMixer.reset();
}

void ChorusProcessor::updateParameters()
{
    enabled = enabledParam->load() > 0.5f;
    chorus.setRate(rateParam->load());
    chorus.setCentreDelay(delayParam->load());
    chorus.setDepth(depthParam->load());
    chorus.setMix(1.0f); // We use our own dry/wet mixer
    dryWetMixer.setWetMixProportion(wetParam->load());
}

} // namespace muzikiii
