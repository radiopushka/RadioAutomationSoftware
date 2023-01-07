#include <alsa/asoundlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vorbis/vorbisfile.h>

#define PCM_DEVICE "default"

//mixer class for playerradio
//original code by evan nikitin

class Mixer{
	private:
	
	 unsigned int rate=44100;
	 //for the audio interface:
     snd_pcm_t *pcm_handle=NULL;
     
     int buff_size;
     int readfd;
     int nchannels;
     char* buff;
	public:
	 
	 Mixer();
	 volatile int PAUSE;
	 volatile int ABORT;
	 unsigned int currentrate;
	 void setRate(unsigned int rate);
	 void flush();
	 int init();
	 int openLine(unsigned int rate);
	 void unpause();
	 void pause();
	 void play(string path);
	 void playOgg(string path);
	 void closeMixer();
	
};
