/*
  ==============================================================================

    MidiUtils.h
    Created: 3 Jun 2017 4:34:03pm
    Author:  blist

  ==============================================================================
*/

#ifndef MIDIUTILS_H_INCLUDED
#define MIDIUTILS_H_INCLUDED

#include "../BachCommon.h"
namespace Bach {
	class MidiUtils {
	public:
		MidiUtils();
		HashMap<String, int> INTERVALS;
		HashMap<String, Array<String>> BASIC_CHORD_SYMBOLS;
		Array<String> SUPPORTED_CHORD_TYPES;
		bool isValidInterval(String interval);
		bool isValidBasicChordSymbol(String symbol);
		int intervalToMidiNoteValue(String interval);
		Array<String> chordSymbolToIntervalArray(String symbol);
		bool isPitchClass(String pitchName);
		int pitchClassAndOctaveToMidiNumber(String keyName, int octaveForMiddleC);
	private:
		
	};
}



#endif  // MIDIUTILS_H_INCLUDED
