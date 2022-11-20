#include "playlist.cpp"
#define PRE_QUEUE_SIZE 10


class Queue{
	private:
	struct list* toplay;
	int exists(song s);
	void add(song s);
	int compareS(song s1,song s2);
	song strkr;
	public:
	song returnTracker();
	Queue(playlist p,int songbid,song prev);
	song getNext();
	int canNext();
	void clear();
};
