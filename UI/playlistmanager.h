#include "timeManager/timemanager.cpp"

class playlistmanager{
	private:
	void DisPL(playlist* p,int start);
	int selectPlaylist(int size,PLmanager* info);
	int editPlaylist(playlist* p);
	int SelectSong(playlist* p);
	int SelectId(playlist* p);
	void NewPL(PLmanager* p);
	void songoptions(playlist p,int index,int isid,int rc);
	void addid(playlist p);
	void adddir(playlist p);
	public:
	void openDialogue(PLmanager* p);
	
};
