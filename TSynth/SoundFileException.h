#ifndef TSYNTH_SOUNDFILEEXCEPTION_H
#define TSYNTH_SOUNDFILEEXCEPTION_H
#include <exception>
#include <string>

class SoundFileException
{
public:
	SoundFileException(std::string str);
	virtual	~SoundFileException(void);

	std::string message() { return message_; }
private:
	std::string message_;
};

#endif // TSYNTH_SOUNDFILEEXCEPTION_H