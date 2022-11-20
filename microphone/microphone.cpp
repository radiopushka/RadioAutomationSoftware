#include "microphone.h"


int Microphone::init(){
	if(snd_pcm_open(&output, PCM_DEVICE,SND_PCM_STREAM_PLAYBACK, 0)<0){
     return -1;//on failure
    }
    if(snd_pcm_set_params(output, SND_PCM_FORMAT_S16_LE,SND_PCM_ACCESS_RW_INTERLEAVED, 1, rate, 1, 500000)<0){
	 return -1;	
	}
	if(snd_pcm_open(&input, PCM_DEVICE,SND_PCM_STREAM_CAPTURE, 0)<0){
     return -1;//on failure
    }
    if(snd_pcm_set_params(input, SND_PCM_FORMAT_S16_LE,SND_PCM_ACCESS_RW_INTERLEAVED, 1, rate, 1, 500000)<0){
	 return -1;	
	}
	int framecount=rate/294;
	buffsize = framecount*4;
	buff=(char*)malloc(buffsize);
	return 1;
}

Microphone::Microphone(){
	SUCCESSFULL=init();
}
void Microphone::toggle(){
	if(RUNNING==1){
     snd_pcm_pause(input,1);
     RUNNING=0;
    }else{
		snd_pcm_pause(input,0);
		RUNNING=1;
	}
}
void Microphone::repause(){
	snd_pcm_pause(input,1);
	snd_pcm_pause(input,0);
}
void Microphone::close(){
  free(buff);
  snd_pcm_close(input);
  snd_pcm_close(output);
}
void Microphone::kill(){
 	snd_pcm_pause(input,1);
    RUNNING=0;
    close();
}
void Microphone::runner(){
   snd_pcm_pause(input,1);
   while(KILL!=1){
	while(RUNNING==0){sleep(1);}
	if(snd_pcm_readi (input, buff, buffsize/4)==-EPIPE){
		snd_pcm_close(input);
		snd_pcm_close(output);
		free(buff);
		init();
	  }
	  if(snd_pcm_writei(output, buff, buffsize/(4)) == -EPIPE){
		snd_pcm_close(input);
		snd_pcm_close(output);
		free(buff);
		init();
	  }
   }
}
