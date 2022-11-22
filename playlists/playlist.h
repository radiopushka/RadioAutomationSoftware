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
struct PTimes{
 PTime* start;
 PTime* end;
 struct PTimes* next;
};

class playlist{
	private:
	struct list* head;
	struct IDs* ids;
	song convert(song *s);
	int* nsongs;
	int* nids;
	
	void addTimesBottom(PTime start,PTime end);
	
	
	
	public:
	
	int timecount=0;
	
	struct PTimes* playtimes=NULL;
	int ShouldPlay();
	void addTimesTop(PTime start,PTime end);
	void removeTime(int index);
	PTimes* getTAt(int i);
	string TtoString();
	void  TfromString(string in);
	int countTimes();
	
	playlist();
	playlist* copy();
	
	PTime* starttime;//depricated
	PTime* endtime;//depricated
	void setEndTime(PTime in);//depricated
	void setStartTime(PTime st);//depricated
	
	int countSongs();
	int countIDs();
	song* getPointerAt(int i);
	void add(song s);
	song getAt(int i);
	int getI(song s);
	void delAt(int i);
	void clearSongs();
	void putId(song s);
	song getID(int i);
	void removeId(int index);
	IDs getIDs();
	
	void saveToFile(string name);
	void loadFromFile(string name);
	
	void close();
};
