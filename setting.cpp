#include "setting.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::vector<std::string> Words(const int argc, char* argv[]) {
	std::vector<std::string> words;
	for (unsigned index = 1; index < argc; ++index) {
		words.push_back(argv[index]);
		std::transform(words.back().begin(), words.back().end(), words.back().begin(), ::tolower);
	}
	return words;
};
Setting::Data Setting::Init(const int argc, char* argv[]) {
	unsigned size = 20;
	unsigned scale = 20;
	unsigned delay = 1000;
	const auto& words{ Words(argc,argv) };
	for (const auto& word : words) {
		auto pos{ word.find(':') };
		std::string_view key{ word.begin(), word.begin() + pos };
		std::string value{ word.begin() + pos + 1, word.end() };
		if ("-h" == key || "help" == key) {
			std::cout <<
				"-h help\n",
				"size:integer -s:integer - set the size of the playing field\n",
				"scale:integer -c:integer - set cell margin size\n",
				"delay:integer -d:integer - set the running delay time\n\n";
		}
		else if ("-s" == key || "size" == key) {
			size = std::stoi(value);
		}
		else if ("-c" == key || "scale" == key) {
			scale = std::stoi(value);
		}
		else if ("-d" == key || "delay" == key) {
			delay = std::stoi(value);
		}
	}
	return { size, scale, delay };
}