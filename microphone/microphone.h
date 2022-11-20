#include <alsa/asoundlib.h>

class Microphone{
 private:
  int channels=1;
  int rate=44100;
  int buffsize;
  char* buff;
  
  snd_pcm_t *input;
  snd_pcm_t *output;
  
  int init();
 public:
  int SUCCESSFULL=0;
  Microphone();
  volatile int RUNNING=0;
  volatile int KILL=0;
  void repause();
  void toggle();
  void runner();
  void close();	
  void kill();
};
