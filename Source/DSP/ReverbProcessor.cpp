#include "ReverbProcessor.h"
#include "../Parameters/ParameterLayout.h"

namespace muzikiii {

ReverbProcessor::ReverbProcessor(juce::AudioProcessorValueTreeState& apvts)
{
    enabledParam  = apvts.getRawParameterValue(ParamIDs::reverbEnabled);
    decayParam    = apvts.getRawParameterValue(ParamIDs::reverbDecay);
    preDelayParam = apvts.getRawParameterValue(ParamIDs::reverbPreDelay);
    wetParam      = apvts.getRawParameterValue(ParamIDs::reverbWet);
}

void ReverbProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    reverb.prepare(spec);
    dryWetMixer.prepare(spec);
    dryWetMixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}

void ReverbProcessor::process(juce::dsp::AudioBlock<float>& block)
{
    updateParameters();

    if (!enabled)
        return;

    juce::dsp::ProcessContextReplacing<float> context(block);
    dryWetMixer.pushDrySamples(block);
    reverb.process(context);
    dryWetMixer.mixWetSamples(block);
}

void ReverbProcessor::reset()
{
    reverb.reset();
    dryWetMixer.reset();
}

void ReverbProcessor::updateParameters()
{
    enabled = enabledParam->load() > 0.5f;
    dryWetMixer.setWetMixProportion(wetParam->load());

    juce::dsp::Reverb::Parameters reverbParams;
    reverbParams.roomSize = juce::jmap(decayParam->load(), 0.1f, 30.0f, 0.0f, 1.0f);
    reverbParams.damping = 0.5f;
    reverbParams.wetLevel = 1.0f;
    reverbParams.dryLevel = 0.0f;
    reverbParams.width = 1.0f;
    reverb.setParameters(reverbParams);
}

} // namespace muzikiii
