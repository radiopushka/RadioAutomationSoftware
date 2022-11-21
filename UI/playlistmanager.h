#include "timeManager/timemanager.cpp"

class playlistmanager{
	private:
	MQueue* mp;
	void DisPL(playlist* p,int start);
	int selectPlaylist(int size,PLmanager* info);
	int editPlaylist(playlist* p);
	int SelectSong(playlist* p);
	int SelectId(playlist* p);
	void NewPL(PLmanager* p);
	void songoptions(playlist p,int index,int isid,int rc);
	void addid(playlist p);
	void adddir(playlist p);
	void viewQ();
	public:
	void openDialogue(PLmanager* p,MQueue* mq);
	
};
