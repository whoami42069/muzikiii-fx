#include "EQProcessor.h"
#include "../Parameters/ParameterLayout.h"

namespace muzikiii {

EQProcessor::EQProcessor(juce::AudioProcessorValueTreeState& apvts)
{
    enabledParam  = apvts.getRawParameterValue(ParamIDs::eqEnabled);
    lowParam      = apvts.getRawParameterValue(ParamIDs::eqLow);
    midParam      = apvts.getRawParameterValue(ParamIDs::eqMid);
    highParam     = apvts.getRawParameterValue(ParamIDs::eqHigh);
    lowFreqParam  = apvts.getRawParameterValue(ParamIDs::eqLowFrequency);
    highFreqParam = apvts.getRawParameterValue(ParamIDs::eqHighFrequency);
}

void EQProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    lowShelf.prepare(spec);
    peak.prepare(spec);
    highShelf.prepare(spec);
}

void EQProcessor::process(juce::dsp::AudioBlock<float>& block)
{
    updateParameters();

    if (!enabled)
        return;

    juce::dsp::ProcessContextReplacing<float> context(block);
    lowShelf.process(context);
    peak.process(context);
    highShelf.process(context);
}

void EQProcessor::reset()
{
    lowShelf.reset();
    peak.reset();
    highShelf.reset();
}

void EQProcessor::updateParameters()
{
    enabled = enabledParam->load() > 0.5f;

    float lowGain  = lowParam->load();
    float midGain  = midParam->load();
    float highGain = highParam->load();
    float lowFreq  = lowFreqParam->load();
    float highFreq = highFreqParam->load();
    float midFreq  = std::sqrt(lowFreq * highFreq); // Geometric mean

    *lowShelf.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(
        sampleRate, lowFreq, 0.707f, juce::Decibels::decibelsToGain(lowGain));
    *peak.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(
        sampleRate, midFreq, 0.707f, juce::Decibels::decibelsToGain(midGain));
    *highShelf.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(
        sampleRate, highFreq, 0.707f, juce::Decibels::decibelsToGain(highGain));
}

} // namespace muzikiii
