#include "DelayProcessor.h"
#include "../Parameters/ParameterLayout.h"

namespace muzikiii {

DelayProcessor::DelayProcessor(juce::AudioProcessorValueTreeState& apvts)
{
    enabledParam  = apvts.getRawParameterValue(ParamIDs::delayEnabled);
    timeParam     = apvts.getRawParameterValue(ParamIDs::delayTime);
    feedbackParam = apvts.getRawParameterValue(ParamIDs::delayFeedback);
    wetParam      = apvts.getRawParameterValue(ParamIDs::delayWet);
}

void DelayProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    delayLine.prepare(spec);
    dryWetMixer.prepare(spec);
    dryWetMixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    delayLine.setMaximumDelayInSamples(static_cast<int>(spec.sampleRate * 5.0));
}

void DelayProcessor::process(juce::dsp::AudioBlock<float>& block)
{
    updateParameters();

    if (!enabled)
        return;

    dryWetMixer.pushDrySamples(block);

    for (int channel = 0; channel < static_cast<int>(block.getNumChannels()); ++channel)
    {
        auto* channelData = block.getChannelPointer(static_cast<size_t>(channel));

        for (int sample = 0; sample < static_cast<int>(block.getNumSamples()); ++sample)
        {
            float delayedSample = delayLine.popSample(channel, delayTimeSamples);
            float inputSample = channelData[sample] + delayedSample * feedback;
            delayLine.pushSample(channel, inputSample);
            channelData[sample] = delayedSample;
        }
    }

    dryWetMixer.mixWetSamples(block);
}

void DelayProcessor::reset()
{
    delayLine.reset();
    dryWetMixer.reset();
}

void DelayProcessor::updateParameters()
{
    enabled = enabledParam->load() > 0.5f;
    feedback = feedbackParam->load();
    delayTimeSamples = timeParam->load() * static_cast<float>(sampleRate);
    dryWetMixer.setWetMixProportion(wetParam->load());
}

} // namespace muzikiii
