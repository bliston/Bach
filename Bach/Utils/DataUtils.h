/*
  ==============================================================================

    DataUtils.h
    Created: 3 Jun 2017 4:34:03pm
    Author:  blist

  ==============================================================================
*/

#ifndef DATAUTILS_H_INCLUDED
#define DATAUTILS_H_INCLUDED

#include "../BachCommon.h"
#include<string>
#include<regex>
#include<vector>
namespace Bach {
	class DataUtils {
	public:
		DataUtils();
		static Array<String> split(::std::string s, ::std::regex regexDelimiter);
	private:
		
	};
}



#endif  // DATAUTILS_H_INCLUDED
