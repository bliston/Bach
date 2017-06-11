/*
  ==============================================================================

    DataUtils.cpp
    Created: 3 Jun 2017 4:34:03pm
    Author:  blist

  ==============================================================================
*/

#include "DataUtils.h"


Bach::DataUtils::DataUtils()
{
	
}

Array<String> Bach::DataUtils::split(::std::string s, ::std::regex regexDelimiter)
{
	Array<String> outArray;
	::std::vector<::std::string> out;

	::std::regex re = regexDelimiter;
	::std::string word;

	auto i = s.begin();
	while (i != s.end()) {
		::std::match_results<::std::string::iterator> m;
		if (regex_match(i, s.end(), m, re)) {
			out.push_back(word);
			word.clear();
			out.push_back(::std::string(m[1].first, m[1].second));
			i += out.back().size();
		}
		else {
			word += *i++;
		}
	}
	if (!word.empty()) {
		out.push_back(word);
	}
	for (auto& a : out)
	{
		outArray.add(a);
	}
	return outArray;
}