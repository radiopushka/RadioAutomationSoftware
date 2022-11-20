#include <ncurses.h>
#include "../../playlists/PLmanager.cpp"

class TimeManager{
	private:
	 PLmanager* pls;
	 void autoOrganize();
	 void increment(int* day,int* hour, int* minute);
	 string generatetimeline();
	 string trimstring(unsigned int boxwidth,string input);
	 void editPtime(playlist* p,string name);
	 playlist* selectPlaylist();
	public:
	 TimeManager(PLmanager* input);
	 void show();
};
