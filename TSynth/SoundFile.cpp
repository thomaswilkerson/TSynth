#include "SoundFile.h"
#include "SoundFileException.h"
#include <stdlib.h>

SoundFile::SoundFile(void)
{
}

SoundFile::SoundFile(std::string name, SF_INFO info, float* data): data_(data), curPos_(data), framesRead_(0)
{
	channels_ = info.channels;
	format_ = info.format;
	frames_ = info.frames;
	samplerate_ = info.samplerate;
	sections_ = info.sections;
	seekable_ = info.seekable;
}

SoundFile::~SoundFile(void)
{
	if(data_ != 0)
		free(data_);
}

SoundFile* SoundFile::openSoundFile(const char* path, int mode)
{
	SF_INFO info;
	int error = 0;
	SNDFILE* file = sf_open(path, mode, &info);
	if(file == (void*) 0 )
		throw SoundFileException("Cannot open file.");
	
	int fileSize = info.frames * info.channels;	
	float* data = (float*) malloc(fileSize * sizeof(float));
	
	error = sf_readf_float(file, data, info.frames);
	
	if(error < 0)
		throw SoundFileException("Cannot read file.");
	
	return new SoundFile(path, info, data);
}


int SoundFile::play(const void *input,
						void *output,
						unsigned long frameCount,
						void *userData)
{
	float* out = (float*) output;
	sf_count_t framesRemaining = frames_ - framesRead_;
	if(framesRemaining < frameCount)
	{
		frameCount = framesRemaining;
	}
	size_t totalFloats = frameCount * channels_;
	for(int i = 0; i < totalFloats; i++)
	{
		*out = *curPos_;
		out++;
		curPos_++;
	}
	framesRead_ += frameCount;
	return 0;
}