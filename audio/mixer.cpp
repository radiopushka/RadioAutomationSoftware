#include "mixer.h"
#include <iostream>
//original code by Evan Nikitin

int Mixer::init(){
	readfd=-1;
	nchannels=2;
	rate=44100;
	if(snd_pcm_open(&pcm_handle, PCM_DEVICE,SND_PCM_STREAM_PLAYBACK, 0)<0){
     return -1;//on failure
    }
    if(snd_pcm_set_params(pcm_handle, SND_PCM_FORMAT_S16_LE,SND_PCM_ACCESS_RW_INTERLEAVED, 2, rate, 1, 500000)<0){
	 return -1;	
	}
	int framecount=rate/294;
	buff_size = framecount*nchannels*2;//buffer size a little less than 256 for a rate of 44100
	return 1;
}
int Mixer::openLine(unsigned int irate){
	readfd=-1;
	nchannels=2;
	rate=irate;
	if(snd_pcm_open(&pcm_handle, PCM_DEVICE,SND_PCM_STREAM_PLAYBACK, 0)<0){
     return -1;
    }
    if(snd_pcm_set_params(pcm_handle, SND_PCM_FORMAT_S16_LE,SND_PCM_ACCESS_RW_INTERLEAVED, 2, rate, 1, 500000)<0){
	 return -1;
	}
	int framecount=rate/294;
	buff_size = framecount*nchannels*2;//buffer size a little less than 256 for a rate of 44100 
	return 1;
}
Mixer::Mixer(){
	buff=NULL;
	PAUSE=0;
	ABORT=0;
	init();
}
void Mixer::setRate(unsigned int irate){
	 snd_pcm_set_params(pcm_handle, SND_PCM_FORMAT_S16_LE,SND_PCM_ACCESS_RW_INTERLEAVED, 2, irate, 1, 500000);//new paremeters half second latency
	 rate=irate;//new rate
	 int framecount=rate/294;
     buff_size = framecount*nchannels*2;//new buffer size calculation a little less than the maximum size by alsa
}
void Mixer::pause(){
   snd_pcm_pause(pcm_handle,1);
}
void Mixer::unpause(){
	snd_pcm_pause(pcm_handle,0);
}
void Mixer::play(string file){
	if(buff!=NULL){free(buff);}
	readfd=open(file.c_str(),O_RDONLY);
	if(readfd==-1){return;}
	setRate(44100);//no multiple rate support
	buff=(char*)malloc(buff_size);
	 int pcm=0;
     int rdv;
	 while((rdv=read(readfd,buff,buff_size))>-1){
		 while(PAUSE==1){}
		if(ABORT==1){ABORT=0;free(buff);buff=NULL;close(readfd);return;}
		
		if ((pcm = snd_pcm_writei(pcm_handle, buff, buff_size/(nchannels*2))) == -EPIPE) {
			
                 snd_pcm_prepare(pcm_handle);
         
        
		} else if (pcm < 0) {
		     
             snd_pcm_close(pcm_handle);
		    while(init()==-1){sleep(5);}//when the sound card cannot be opened
			
		}
		
		if(rdv<=0){
		  
		  break;
		}
 }
 free(buff);
 buff=NULL;
 close(readfd);
 snd_pcm_sframes_t delayp;
	if(snd_pcm_delay(pcm_handle,&delayp)==0){
	  float sleeptime=delayp/(rate/4);
	  sleep(sleeptime);
    }
}

void Mixer::playOgg(string file){
	if(buff!=NULL){free(buff);}//free any existing buffer if its still not freed for some reason
	OggVorbis_File vf;
	FILE* f=fopen(file.c_str(),"r");//open the file
	int i;
	
	if((i=ov_open(f, &vf,NULL,0))<0){usleep(1000);ov_clear(&vf);
		//cout<<"could not play:"<<file<<endl;
		return;}
	vorbis_info *vi = ov_info(&vf, -1);//extract information
    setRate(vi->rate);//supports different bit rates
	int rdv=1;
	int current_section;
	buff = (char *) malloc(buff_size);//new buffer
	while(rdv>0){
	long ret = ov_read(&vf, buff, buff_size, 0, 2, 1,&current_section);
	if(ret<=0){
	 break;
	}
	int pcm=0;
	while(PAUSE==1){}
	if(ABORT==1){ABORT=0;free(buff);buff=NULL;ov_clear(&vf);return;}
	
		if ((pcm = snd_pcm_writei(pcm_handle, buff, ret/4)) == -EPIPE) {
			
                 snd_pcm_prepare(pcm_handle);
         
        
		} else if (pcm < 0) {
		     
             snd_pcm_close(pcm_handle);
		    while(init()==-1){sleep(5);}
			
		}
		
	}
	free(buff);//free variables
	buff=NULL;
	ov_clear(&vf);
	snd_pcm_sframes_t delayp;
	if(snd_pcm_delay(pcm_handle,&delayp)==0){
	  float sleeptime=delayp/(rate/4);
	  sleep(sleeptime);
    }
}
void Mixer::flush(){
	snd_pcm_drop(pcm_handle);
}
void Mixer::closeMixer(){
       if(buff!=NULL){free(buff);}
	   if(readfd!=-1){
	     close(readfd);
       }
       snd_pcm_drop(pcm_handle);
       snd_pcm_close(pcm_handle);

}
