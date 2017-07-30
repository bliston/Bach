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
	struct ChordInfo;
class ChordNameToMidiNotes {
public:
    ChordNameToMidiNotes();
	Bach::ChordInfo getChordInfo(String chordName);
	String getChordBass(String chordName);
	String getChordRoot(String chordName);
	String getChordType(String chordName);
	Array<int> get(String chordRoot, String chordType, String chordBass, int chordOctave);
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
