#include <alsa/asoundlib.h>

class Microphone{
 private:
  int channels=1;
  int rate=44100;
  int buffsize;
  char* buff;
  
  volatile int skiprun=0;//нужно чтобы производит синхронизацаю при разных бит рейтах
  
  volatile int gadzos=0;
  
  
  
  volatile int pitch=0;
  
  snd_pcm_t *input;//саунд интерфейсы
  snd_pcm_t *output;
  
  volatile int bd=0;
  
  int init();
 public:
  volatile int gadzosFrequency=10;//чистота обреза
  int SUCCESSFULL=0;
  Microphone();
  volatile int RUNNING=0;
  volatile int KILL=0;
  void repause();
  void toggle();
  char calculateByte(char input,char number);
  void DemoMachine();
  void Pitch();
  void normalaudio();
  void runner();
  void close();	
  void kill();
};
