#include<ncurses.h>
//file chooser for the playerradio
//will only support wav and ogg
//original code by Evan Nikitin
class filechooser{
	private: string path; string filter; string filter2;int dir=0;  string songname; string showonly;
	char listdir(int c);
	int index;
	DIR* d;
	int isBad(char* name,unsigned char type);
	public:
	int endsWith(string in,string with);
	filechooser();
	void setDef();
	void setFilter(string filter);
	void setPath(string path);
	void setDirOnly();
	void setFileOnly();
	int show();
	string getFinalPath();
	string getNameFromFileName(string in);
	string getName();
};
