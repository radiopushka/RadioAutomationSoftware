#include "Queue.cpp"
//header file for the PLmanager class
//original code by Evan Nikitin

struct ListofPLs{
	playlist* p;
	char* name;
	struct ListofPLs* next;
};

class PLmanager{
	private:
	 struct ListofPLs* pls;
	 int sizel;
	 int loaded;
	 int beforeid;
	 string prevp;
	 string prevn;
	public:
	 int canNext();
	 int exists(string name);
	 void addBottom(playlist p,string name);
	 void clear();
	 void add(playlist p,string name);
	 PLmanager(int beforei);
	 playlist* at(int i);
	 char* getName(int i);
	 void setSongsBeforeId(int num);
	 int size();
	 Queue next();
	 void save();
	 void load();
	 void rem(int i);
};
