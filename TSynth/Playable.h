#ifndef TSYNTH_PLAYABLE_H
#define TSYNTH_PLAYABLE_H

#include <portaudio.h>

class Playable
{
public:
	Playable(void);
	virtual ~Playable(void);


	virtual int play(const void *input,
			       void *output,
				   unsigned long frameCount,
				   void *userData)
	{
		return 0;
	}

};



#endif //TSYNTH_PLAYABLE_H
