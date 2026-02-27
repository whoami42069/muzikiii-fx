cmake_minimum_required(VERSION 3.22)
project(MuzikiiiFX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch JUCE
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 7.0.12
)
FetchContent_MakeAvailable(JUCE)

# Plugin target
juce_add_plugin(MuzikiiiFX
    COMPANY_NAME "Muzikiii"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE Mzki
    PLUGIN_CODE MzFx
    FORMATS AU VST3 Standalone
    AU_MAIN_TYPE kAudioUnitType_Effect
    PRODUCT_NAME "Muzikiii FX"
    BUNDLE_ID "com.muzikiii.fx"
)

# Source files
target_sources(MuzikiiiFX
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
        Source/DSP/EffectChain.cpp
        Source/DSP/ReverbProcessor.cpp
        Source/DSP/DelayProcessor.cpp
        Source/DSP/EQProcessor.cpp
        Source/DSP/DistortionProcessor.cpp
        Source/DSP/ChorusProcessor.cpp
        Source/DSP/CompressorProcessor.cpp
        Source/UI/EffectChainEditor.cpp
        Source/UI/EffectSlot.cpp
        Source/UI/CustomLookAndFeel.cpp
        Source/Parameters/ParameterLayout.cpp
)

# JUCE modules
target_link_libraries(MuzikiiiFX
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# JUCE compile definitions
target_compile_definitions(MuzikiiiFX
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
)
