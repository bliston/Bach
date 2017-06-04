/*
  ==============================================================================

    MidiUtils.cpp
    Created: 3 Jun 2017 4:34:03pm
    Author:  blist

  ==============================================================================
*/

#include "MidiUtils.h"


Bach::MidiUtils::MidiUtils()
{
	INTERVALS.clear();
	INTERVALS.set("P1", 0); INTERVALS.set("d2", 0);
	INTERVALS.set("m2", 1); INTERVALS.set("A1", 1);
	INTERVALS.set("M2", 2); INTERVALS.set("d3", 2);
	INTERVALS.set("m3", 3); INTERVALS.set("A2", 3);
	INTERVALS.set("M3", 4); INTERVALS.set("d4", 4);
	INTERVALS.set("P4", 5); INTERVALS.set("A3", 5);
	INTERVALS.set("d5", 6); INTERVALS.set("A4", 6);
	INTERVALS.set("P5", 7); INTERVALS.set("d6", 7);
	INTERVALS.set("m6", 8); INTERVALS.set("A5", 8);
	INTERVALS.set("M6", 9); INTERVALS.set("d7", 8);
	INTERVALS.set("m7", 10); INTERVALS.set("A6", 10);
	INTERVALS.set("M7", 11); INTERVALS.set("d8", 11);
	INTERVALS.set("P8", 12); INTERVALS.set("A7", 12); INTERVALS.set("d9", 12);
	INTERVALS.set("m9", 13); INTERVALS.set("A8", 13);
	INTERVALS.set("M9", 14); INTERVALS.set("d10", 14);
	INTERVALS.set("m10", 15); INTERVALS.set("A9", 15);
	INTERVALS.set("M10", 16); INTERVALS.set("d11", 16);
	INTERVALS.set("P11", 17); INTERVALS.set("A10", 17);
	INTERVALS.set("d12", 18); INTERVALS.set("A11", 18);
	INTERVALS.set("P12", 19); INTERVALS.set("d13", 19);
	INTERVALS.set("m13", 20); INTERVALS.set("A12", 20);
	INTERVALS.set("M13", 21); INTERVALS.set("d14", 21);
	INTERVALS.set("m14", 22); INTERVALS.set("A13", 22);
	INTERVALS.set("M14", 23); INTERVALS.set("d15", 23);
	INTERVALS.set("P15", 24); INTERVALS.set("A14", 24);
	INTERVALS.set("A15", 25);

	BASIC_CHORD_SYMBOLS.clear();
	BASIC_CHORD_SYMBOLS.set("m", { "m3", "P5" });
	BASIC_CHORD_SYMBOLS.set("mi", { "m3", "P5" });
	BASIC_CHORD_SYMBOLS.set("min", { "m3", "P5" });
	BASIC_CHORD_SYMBOLS.set("-", { "m3", "P5" });

	BASIC_CHORD_SYMBOLS.set("M", { "M3", "P5" });
	BASIC_CHORD_SYMBOLS.set("ma", { "M3", "P5" });
	BASIC_CHORD_SYMBOLS.set("", { "M3", "P5" });

	BASIC_CHORD_SYMBOLS.set("+", { "M3", "A5" });
	BASIC_CHORD_SYMBOLS.set("aug", { "M3", "A5" });

	BASIC_CHORD_SYMBOLS.set("dim", { "m3", "d5" });
	BASIC_CHORD_SYMBOLS.set("o", { "m3", "d5" });

	BASIC_CHORD_SYMBOLS.set("maj", { "M3", "P5", "M7" });
	BASIC_CHORD_SYMBOLS.set("dom", { "M3", "P5", "m7" });
	//BASIC_CHORD_SYMBOLS.set("ø",{ "m3", "d5", "m7" });

	BASIC_CHORD_SYMBOLS.set("5", { "P5" });

	BASIC_CHORD_SYMBOLS.set("6/9", { "M3", "P5", "M6", "M9" });

	SUPPORTED_CHORD_TYPES = { 
		"4",
		//"64",
		"5",
		"M",
		"M#5",
		"M#5add9",
		"M13",
		"M13#11",
		"M6",
		"M6#11",
		"M69",
		"M69#11",
		"M7#11",
		"M7#5",
		"M7#5sus4",
		"M7#9#11",
		"M7add13",
		"M7b5",
		"M7b6",
		"M7b9",
		"M7sus4",
		"M9",
		"M9#11",
		"M9#5",
		"M9#5sus4",
		"M9b5",
		"M9sus4",
		"add9", // Madd9 26
		"M7",
		"Mb5",
		"Mb6",
		"Msus2",
		"Msus4",
		"addb9",
		"7",
		"9",
		"11",
		"13",
		"11b9",
		"13#11",
		"13#9",
		"13#9#11",
		"13b5",
		"13b9",
		"13b9#11",
		//"13no5",
		"13sus4",
		"69#11",
		"7#11",
		"7#11b13",
		"7#5",
		"7#5#9",
		"7#5b9",
		"7#5b9#11",
		"7#5sus4",
		"7#9",
		"7#9#11",
		"7#9#11b13",
		"7#9b13",
		"7add6",
		"7b13",
		"7b5",
		"7b6",
		"7b9",
		"7b9#11",
		"7b9#9",
		"7b9b13",
		"7b9b13#11",
		//"7no5",
		"7sus4",
		"7sus4b9",
		"7sus4b9b13",
		"9#11",
		"9#11b13",
		"9#5",
		"9#5#11",
		"9b13",
		"9b5",
		//"9no5",
		"9sus4",
		"m",
		"m#5",
		"m11",
		"m11#5", //m11 A 5 79
		"m11b5",
		"m13",
		"m6",
		"m69",
		"m7",
		"m7#5",
		"m7add11",
		"m7b5",
		"m9",
		"m9#5",
		"m9b5",
		"mM7",
		"mM7b6",
		"mM9",
		"mM9b6",
		"mb6M7",
		"mb6b9",
		"dim",
		"dim7",
		"dim7M7",
		"dimM7",
		//"sus24", // 101
		//"madd4",
		"min(add9)"
		 }; // 104
}

bool Bach::MidiUtils::isValidInterval(String interval)
{
	return INTERVALS.contains(interval);
}

bool Bach::MidiUtils::isValidBasicChordSymbol(String symbol)
{
	return BASIC_CHORD_SYMBOLS.contains(symbol);
}

int Bach::MidiUtils::intervalToMidiNoteValue(String interval)
{
	jassert(INTERVALS.contains(interval));
	return INTERVALS[interval];
}

Array<String> Bach::MidiUtils::chordSymbolToIntervalArray(String symbol)
{
	jassert(isValidBasicChordSymbol(symbol));
	return BASIC_CHORD_SYMBOLS[symbol];
}

bool Bach::MidiUtils::isPitchClass(String pitchName) 
{
	bool result;
	Array<String> noteNames = { "C", "C#", "Db", "D", "D#", "Eb", "E", "F", "F#", "Gb", "G", "G#", "Ab", "A", "A#","Bb", "B"};
	result = noteNames.contains(pitchName);
	return result;
}

int Bach::MidiUtils::pitchClassAndOctaveToMidiNumber(String keyName, const int octaveForMiddleC) {
	Array<String> noteNames = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "", "Db", "", "Eb", "", "", "Gb", "", "Ab", "", "Bb" };
	int keyNumber, octave = 0;

	octave = octaveForMiddleC;      //default to octave of middle C if none found

	String name(keyName.trim());
	keyNumber = noteNames.indexOf(name) % 12;
	if (keyNumber < 0) {
		return -1;
	}
	return keyNumber + octave * 12;
}