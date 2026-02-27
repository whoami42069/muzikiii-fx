#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace muzikiii {

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override;

    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
                          bool shouldDrawButtonAsHighlighted,
                          bool shouldDrawButtonAsDown) override;

    // DAW theme colours
    static constexpr juce::uint32 bgColour        = 0xFF1a1a2e;
    static constexpr juce::uint32 surfaceColour    = 0xFF16213e;
    static constexpr juce::uint32 accentColour     = 0xFF0f3460;
    static constexpr juce::uint32 highlightColour  = 0xFFe94560;
    static constexpr juce::uint32 textColour       = 0xFFe0e0e0;
    static constexpr juce::uint32 mutedTextColour  = 0xFF888888;
};

} // namespace muzikiii
