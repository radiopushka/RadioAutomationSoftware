#include <string>
#include "../audio/mixer.cpp"
//song class for the radio player
//original code by Evan Nikitin
using namespace std;

class song{
	private:
	char* name;
	char* path;
	public:
	song();
	void empty();
	song(string name,string path);
	void play(Mixer* m);
	string toString();
	void fromString(string in);
	string getPath();
	string getName();
	void set(string name,string path);
	};
