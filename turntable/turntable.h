#include "../audio/mixer.cpp"
#include "../UI/filechooser.cpp"

struct Map{
  char iden;
  char* path;
  struct Map* next;
};

class Turntable{
 private:
  Mixer m;
  struct Map* characters=NULL;
  
  void player();
  void add(char c,char* path);
  void remove(char c);
  void clear();
 public:
  void interface();
  Turntable();
  void close();
};


