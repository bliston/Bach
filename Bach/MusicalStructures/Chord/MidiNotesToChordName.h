/*
  ==============================================================================

    MidiNotesToChordName.h
    Created: 3 Jun 2017 4:17:59pm
    Author:  blist

  ==============================================================================
*/

#ifndef MIDINOTESTOCHORDNAME_H_INCLUDED
#define MIDINOTESTOCHORDNAME_H_INCLUDED
#include "../../BachCommon.h"
#include "../../Utils/MidiUtils.h"
namespace Bach {
	class MidiNotesToChordName {
	public:
		MidiNotesToChordName();
		String get(Array<int> midiNotes);

	};
}



#endif  // MIDINOTESTOCHORDNAME_H_INCLUDED
