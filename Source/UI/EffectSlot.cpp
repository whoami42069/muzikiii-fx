#include "EffectSlot.h"
#include "CustomLookAndFeel.h"

namespace muzikiii {

EffectSlot::EffectSlot(const juce::String& effectName,
                       juce::AudioProcessorValueTreeState& apvts,
                       const juce::String& enabledParamId,
                       const juce::StringArray& paramIds,
                       const juce::StringArray& paramLabels)
    : name(effectName)
{
    // Enable toggle
    enableToggle.setButtonText(effectName);
    addAndMakeVisible(enableToggle);
    enableAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        apvts, enabledParamId, enableToggle);

    // Parameter sliders
    for (int i = 0; i < paramIds.size(); ++i)
    {
        ParamControl control;

        control.slider = std::make_unique<juce::Slider>(juce::Slider::RotaryHorizontalVerticalDrag,
                                                         juce::Slider::TextBoxBelow);
        control.slider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 16);
        control.slider->setColour(juce::Slider::textBoxTextColourId, juce::Colour(CustomLookAndFeel::textColour));
        control.slider->setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        addAndMakeVisible(*control.slider);

        control.label = std::make_unique<juce::Label>("", paramLabels[i]);
        control.label->setJustificationType(juce::Justification::centred);
        control.label->setFont(juce::Font(11.0f));
        control.label->setColour(juce::Label::textColourId, juce::Colour(CustomLookAndFeel::mutedTextColour));
        addAndMakeVisible(*control.label);

        control.attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            apvts, paramIds[i], *control.slider);

        paramControls.push_back(std::move(control));
    }
}

EffectSlot::~EffectSlot() = default;

void EffectSlot::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced(2.0f);

    // Background
    g.setColour(juce::Colour(CustomLookAndFeel::surfaceColour));
    g.fillRoundedRectangle(bounds, 6.0f);

    // Border
    bool isEnabled = enableToggle.getToggleState();
    g.setColour(isEnabled ? juce::Colour(CustomLookAndFeel::highlightColour).withAlpha(0.5f)
                          : juce::Colour(CustomLookAndFeel::accentColour).withAlpha(0.3f));
    g.drawRoundedRectangle(bounds, 6.0f, 1.0f);
}

void EffectSlot::resized()
{
    auto bounds = getLocalBounds().reduced(8);

    // Toggle at top
    enableToggle.setBounds(bounds.removeFromTop(24));
    bounds.removeFromTop(4);

    // Distribute knobs evenly
    if (!paramControls.empty())
    {
        int knobWidth = bounds.getWidth() / static_cast<int>(paramControls.size());

        for (auto& control : paramControls)
        {
            auto slotBounds = bounds.removeFromLeft(knobWidth);
            auto labelBounds = slotBounds.removeFromBottom(16);
            control.label->setBounds(labelBounds);
            control.slider->setBounds(slotBounds);
        }
    }
}

} // namespace muzikiii
