#include "playlist.cpp"
#define MAX_PRE_QUEUE_SIZE -2
#define SMALL_QUEUE_SIZE  0

class Queue{
	private:
	struct list* toplay;
	int exists(song s);
	void add(song s);
	int compareS(song s1,song s2);
	song strkr;
	public:
	song returnTracker();
	Queue(playlist p,int songbid,song prev,int Qs);
	Queue(playlist p,int songbid,song prev);
	song getNext();
	int canNext();
	void clear();
};
