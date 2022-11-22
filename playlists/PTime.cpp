#include "PTime.h"
#include <ctime>
#include<cstring>

//time class
//original code by Evan Nikitin

void PTime::setTimeAsCurrent(){
	time_t vremya=time(0);
	tm* now=localtime(&vremya);
	day=now->tm_wday; //0-6
	hour=now->tm_hour; //0-23
	minute=now->tm_min; //0-59
}
void PTime::setTime(int dayi,int houri,int minutei){
	day=dayi;
	hour=houri;
	minute=minutei;
}
int PTime::getDay(){return day;}
int PTime::getHour(){return hour;}
int PTime::getMinute(){return minute;}

int PTime::isPast(){
	time_t vremya=time(0);
	tm* now=localtime(&vremya);
	int dayc=now->tm_wday;
	int hourc=now->tm_hour;
	int minutec=now->tm_min;
	if(dayc>day){return 1;}
	if(dayc==day){
	 if(hourc>hour){return 1;}	
	 if(hourc==hour){
	   if(minutec>minute){
		return 1;   
	   }else if(minutec==minute){return 1;}	 
	 }
	}
	return -1;
}
string PTime::toString(){
 return to_string(day)+"|"+to_string(hour)+"|"+to_string(minute);	
}
void PTime::fromString(string in){
const char *sfs=in.c_str();
char *s=(char*)malloc(sizeof(sfs));
char *sorig=s;
strcpy(s,sfs);
char *days=(char *)malloc(sizeof(s));
char *end=strstr(s,"|");
char *p=s;
char *dp=days;
for(p=s;p<end;p++){
 *dp=*p;
 dp++;
}
*dp='\0';
day=atoi(days);
s=strstr(s,"|")+1;
end=strstr(s,"|");
p=s;
dp=days;
for(p=s;p<end;p++){
 *dp=*p;
 dp++;
}
*dp='\0';
hour=atoi(days);
s=strstr(s,"|")+1;
minute=atoi(s);
free(sorig);
free(days);
}
PTime::PTime(int d,int h, int m){
	setTime(d,h,m);
}
PTime::PTime(){
 	setTimeAsCurrent();
}
