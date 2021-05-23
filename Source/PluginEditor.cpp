/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IIRFilterAudioProcessorEditor::IIRFilterAudioProcessorEditor (IIRFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 100);

    filterTypeMenu.addItem("All Pass", 1);
    filterTypeMenu.addItem("Low Pass", 2);
    filterTypeMenu.addItem("Band Pass", 3);
    filterTypeMenu.addItem("High Pass", 4);
    filterTypeMenu.addItem("Peak Filter", 5);
    filterTypeMenu.addItem("High Shelf", 6);
    filterTypeMenu.addItem("Low Shelf", 7);
    filterTypeMenu.addItem("Notch", 8);
    filterTypeMenu.addItem("First Order AllPass", 9);
    filterTypeMenu.addItem("First Order HighPass", 10);
    filterTypeMenu.addItem("First Order LowPass", 11);
    filterTypeMenu.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(&filterTypeMenu);

    filterCutoffDial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    filterCutoffDial.setRange(audioProcessor.minFilterCutoff, audioProcessor.maxFilterCutoff);
    filterCutoffDial.setValue(audioProcessor.defaultFilterCutoff);
    filterCutoffDial.setTextValueSuffix("hz");
    filterCutoffDial.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(&filterCutoffDial);

    filterResonanceDial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    filterResonanceDial.setRange(audioProcessor.minFilterResonance, audioProcessor.maxFilterResonance);
    filterResonanceDial.setValue(audioProcessor.defaultFilterResonance);
    filterResonanceDial.setTextValueSuffix("");
    filterResonanceDial.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);


    addAndMakeVisible(&filterResonanceDial);

    filterGainFactorDial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    filterGainFactorDial.setRange(audioProcessor.minFilterGainFactor, audioProcessor.maxFilterGainFactor);
    filterGainFactorDial.setValue(audioProcessor.defaultFilterGainFactor);
    filterGainFactorDial.setTextValueSuffix("");
    filterGainFactorDial.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);


    addAndMakeVisible(&filterGainFactorDial);

    filterCutoffValue = new juce::AudioProcessorValueTreeState::SliderAttachment
    (audioProcessor.treeState, audioProcessor.filterCutoffId, filterCutoffDial);

    filterResonanceValue = new juce::AudioProcessorValueTreeState::SliderAttachment
    (audioProcessor.treeState, audioProcessor.filterResonanceId, filterResonanceDial);

    filterTypeMenuValue = new juce::AudioProcessorValueTreeState::ComboBoxAttachment
    (audioProcessor.treeState, audioProcessor.filterTypeMenuId, filterTypeMenu);

}


IIRFilterAudioProcessorEditor::~IIRFilterAudioProcessorEditor()
{
}

//==============================================================================
void IIRFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
   
}

void IIRFilterAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    juce::Rectangle<int> dialArea(50, 50);
    filterCutoffDial.setBounds(50, 50, 50, 50);
    filterResonanceDial.setBounds(110, 50, 50, 50);
    filterGainFactorDial.setBounds(170, 50, 50, 50);
    filterTypeMenu.setBounds(50, 10, 200, 30);
}

void IIRFilterAudioProcessorEditor::comboBoxChanged(juce::ComboBox* selection)
{

}
