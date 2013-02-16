#include <stdio.h>
#include <stdlib.h>
#include "sndfile.h"
#include "SoundFile.h"
#include <portaudio.h>

static Playable* playList[20];
static int playListSize;

static void initPlayList()
{
	playListSize = 0;
}



static void addPlayable(Playable* object)
{
	playList[playListSize++] = object;
}

int PaCallback(const void *input,
						void *output,
						unsigned long frameCount,
						const PaStreamCallbackTimeInfo* timeInfo,
						PaStreamCallbackFlags statusFlags,
						void *userData )
{
	SoundFile* file = (SoundFile*) userData;
	file->play(input, output, frameCount, 0);
	return 0;
}

int main()
{
	SoundFile* file = SoundFile::openSoundFile("C:/Users/Thomas/Programming/Audio/samples/rhythm-lab.com_hiphop_electronic/Brutal 100 Cm/Brutal_Break_100.wav", SFM_READ);

	PaError err;
	err = Pa_Initialize();

	PaStream *stream;

	err = Pa_OpenDefaultStream( &stream,
		file->channels(),
		2,
		paFloat32,
		file->samplerate(),
		256,
		PaCallback,
		file);

	addPlayable(file);

	err = Pa_StartStream( stream );



	while(!file->done())
	{
		printf("%d\n", file->framesRead());
	}

	err = Pa_StopStream(stream);

	err = Pa_Terminate();
}