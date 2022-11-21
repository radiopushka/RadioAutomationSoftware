#include <string>
#include "PTime.cpp"
#include "song.cpp"
using namespace std;
//playlist class definition
//original code by Evan Nikitin

struct list{
 song* s;
 struct list* next;	
 struct list* prev;
};

struct IDs{
 song* s;
 struct IDs* next;	
};

class playlist{
	private:
	struct list* head;
	struct IDs* ids;
	song convert(song *s);
	int* nsongs;
	int* nids;
	public:
	playlist();
	PTime* starttime;
	PTime* endtime;
	playlist* copy();
	void setEndTime(PTime in);
	void setStartTime(PTime st);
	int countSongs();
	int countIDs();
	song* getPointerAt(int i);
	void add(song s);
	song getAt(int i);
	int getI(song s);
	void delAt(int i);
	void close();
	void clearSongs();
	list* getSongs();
	void putId(song s);
	song getID(int i);
	void removeId(int index);
	IDs getIDs();
	void saveToFile(string name);
	void loadFromFile(string name);
};
