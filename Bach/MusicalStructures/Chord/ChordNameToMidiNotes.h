/*
  ==============================================================================

    ChordNameToMidiNotes.h
    Created: 7 Apr 2017 5:49:51pm
    Author:  blist

  ==============================================================================
*/

#ifndef CHORDNAMETOMIDINOTES_H_INCLUDED
#define CHORDNAMETOMIDINOTES_H_INCLUDED
#include "../../BachCommon.h"
#include "../../Utils/MidiUtils.h"
#include "../../Utils/DataUtils.h"
#include<string>
#include<regex>
#include<vector>
namespace Bach {
	struct ChordRootAndType;
class ChordNameToMidiNotes {
public:
    ChordNameToMidiNotes();
	Bach::ChordRootAndType getChordRootAndType(String chordName, int octave);
	int getChordRoot(String chordName, int octave);
	String getChordType(String chordName, int octave);
	Array<int> get(int chordRoot, String chordType);
private:
	MidiUtils midiUtils;
	Array<String> readChord(String symbol);
	var c;
	String parsing;
	Array<String> additionals;
	String name;
	var chordLength;
	Array<String> notes;
	bool explicitMajor;
	void resetState();
	void setChord(String name);
};
}



#endif  // CHORDNAMETOMIDINOTES_H_INCLUDED
