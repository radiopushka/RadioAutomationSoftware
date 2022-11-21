#include "PLmanager.cpp"

struct QList{
 song* s;
 struct QList* next;
};

class MQueue{
 private:
  struct QList* head=NULL;
  unsigned int size=0;
 public:
  int isEmpty();
  void add(string name,string path);
  unsigned int Size();
  void play(Mixer* m);
  string nameAt(int i);
  void close();
};
