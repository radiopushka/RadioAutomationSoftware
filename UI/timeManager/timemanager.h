#include <ncurses.h>
#include "../../playlists/manualqueue.cpp"

class TimeManager{
	private:
	 PLmanager* pls;
	 void autoOrganize();
	 void increment(int* day,int* hour, int* minute);
	 PTimes* selectTime(playlist* p,string name,int exit);
	 string generatetimeline(playlist* p);
	 string trimstring(unsigned int boxwidth,string input);
	 void editPtime(PTimes* p,string name);
	 playlist* selectPlaylist();
	 int selectPlaylistByIndex();
	public:
	 TimeManager(PLmanager* input);
	 void show();
};
