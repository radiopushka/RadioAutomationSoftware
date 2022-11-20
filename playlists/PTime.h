#include <string>
using namespace std;

class PTime{
	private:
	 int day;//0-6
	 int hour;//0-23
	 int minute;//0-60
	public: 
	 PTime();
	 void setTime(int dayi,int houri,int minutei);
	 string toString();
	 void fromString(string in);
	 int getHour();
	 int getMinute();
	 int getDay();
	 void setTimeAsCurrent();
	 int isPast();
	};
