#pragma once

class Setting {
public:
	const unsigned size = 20;
	const unsigned scale = 20;
	const unsigned delay = 100;
protected:
	struct Data {
		const unsigned size = 20;
		const unsigned scale = 20;
		const unsigned delay = 100;
	};
public:
	static Data Init(const int argc, char* arg[]);
protected:
	Setting() = default;
	Setting(Setting::Data& data) :
		size{ data.size },
		scale{ data.scale },
		delay{ data.delay }
	{}
};