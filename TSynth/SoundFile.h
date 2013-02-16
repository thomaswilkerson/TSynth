#ifndef TSYNTH_SOUNDFILE_H
#define TSYNTH_SOUNDFILE_H

#include "Playable.h"
#include <sndfile.h>
#include <string>

class SoundFile: public Playable
{
public:
	SoundFile();

	SoundFile(std::string name, SF_INFO info, float* data);

	~SoundFile();

	/**
	 * Staic SoundFile creator, this way we can have exceptions
	 * Upon construction of a SoundFile. With the nature of File I/O
	 * This was the best way I could think of at the moment to 
	 * allow for exceptions and File opening at the same time.
	 */
	static SoundFile* openSoundFile(const char* path, int mode);

	/**
	 * Fast Callback function to be used by PortAudio.
	 */
	int play(const void *input,
			       void *output,
				   unsigned long frameCount,
				   void *userData);

	int channels() { return channels_; }
	int samplerate() { return samplerate_; }
	sf_count_t framesRead() { return framesRead_; }
	bool done() { return frames_ - framesRead_ <= 0 ? true : false; }
	
private:
	// Holder for the sound files data.
	float* data_;

	// Marker for the current position of the sound file.
	float* curPos_;

	// Number of Frames Read
	sf_count_t framesRead_;

	// Number of frames in the sound file
	sf_count_t frames_;

	// Sample rate of sound file.
	int samplerate_;

	// Number of Channels in the sound file.
	int channels_;
	// Format of the sound file.
	int format_;

	// Unsure what this is for.
	int sections_;

	// Tells whether we can seek the file or not.
	int seekable_;

	// Name of the file.
	std::string name_;

};

#endif // TSYNTH_SOUNDFILE_H

