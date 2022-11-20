#include "timemanager.h"

TimeManager::TimeManager(PLmanager* input){
	pls=input;
}

void TimeManager::increment(int* day,int* hour,int* minute){
	if(*minute>59){
	  *hour=*hour+1;
	  *minute=*minute-59;	
	}
	if(*hour>23){
	  *day=*day+1;
	  *hour=*hour-23;	
    }
}

void TimeManager::autoOrganize(){
  int size=pls->size();
  float subday=7/size;
  int day=7/size;
  subday=subday-day;
  float hour=(subday/(1/0.23))*100;	
  int truehour=hour;
  int minutes=((hour-truehour)/(1/0.59))*100;
  int startday=0;
  int starthour=0;
  int startminute=0;
  int i;
  for(i=0;i<size;i++){
	playlist* p=pls->at(i);
	p->starttime->setTime(startday,starthour,startminute);
	startday=startday+day;
	starthour=starthour+truehour;
	startminute=startminute+minutes;
	if(i+1>=size){
	  startday=6;
	  starthour=23;
	  startminute=59;	
	}
	increment(&startday,&starthour,&startminute);
	p->endtime->setTime(startday,starthour,startminute);
  }
}
string TimeManager::trimstring(unsigned int width,string input){

if(input.length()>width){
 return input.substr(0,width);
}
if(input.length()==width){
 return input;	
}
int padding=width-input.length();
int begin=padding/2;
int end=begin;
if(padding%2!=0){
 end++;	
}
string out=input;
int i;
for(i=0;i<begin;i++){
 out=" "+out;
}
for(i=0;i<end;i++){
 out=out+" ";	
}
return out;
}
string TimeManager::generatetimeline(){
	string out="";
	int size=pls->size();
	int oneblock=COLS/7-1;
	int i;
	int i2;
	int i3;
	int start;
	int draw=0;
	int ding=0;
	float anhour=24/oneblock;
	PTime date;
	for(i2=0;i2<7;i2++){
	 start=0;
	 for(i=start;i<oneblock;i++){
	  draw=0;
	  ding=0;
	  if(((int)i*anhour)==date.getHour()&&i2==date.getDay()){
		ding=1;  
	  }
	  for(i3=0;i3<size;i3++){
	   playlist* p=pls->at(i3);
	   int daystart=p->starttime->getDay();
	   int dayend=p->endtime->getDay();
	   int hourstart=p->starttime->getHour();
	   int hourend=p->endtime->getHour();
	   if(daystart<=i2&&dayend>=i2){
		if(hourstart<=i*anhour&&daystart==i2&&dayend!=i2){
		 draw=1;	
		}
		if(daystart<i2&&dayend>i2){
		  draw=1;	
		}   
		if(dayend==i2&&hourend>=i*anhour&&daystart!=i2){
		  draw=1;
		}
		if(daystart==dayend&&dayend==i2&&hourend>=i*anhour&&hourstart<=i*anhour){draw=1;}
	   }
      }
       if(ding==1){
		  out=out+"+";
	   }else{
        if(draw==0){
		 out=out+" ";
	    }else{out=out+"#";}
	   }
	 }
	 out=out+"|";
    }
    out=out+"\n";
    string day="Sun";
    for(i2=0;i2<7;i2++){
		switch(i2){
		  case 1:day="Mon";break;
		  case 2:day="Tue";break;
		  case 3:day="Wed";break;
		  case 4:day="Thur";break;
		  case 5:day="Fri";break;
		  case 6:day="Sat";break;	
		}
		if(i2==date.getDay()){
		  day=">"+day;	
		}
		out=out+trimstring(oneblock,day)+" ";
	}
	return out;
}
playlist* TimeManager::selectPlaylist(){
	int size=pls->size();
	int i;
	int c=0;
	int index=0;
	while(c!='q'&&c!='\n'){
	 clear();
	 for(i=index;i<size&&i<LINES+index;i++){
		if(i==index){printw(">");attron(A_STANDOUT);}else{printw(" ");}
		printw("%s\n",pls->getName(i));
		attroff(A_STANDOUT);
	 }
	 c=getch();
	 if(c=='s'||c==KEY_DOWN){
	   index++;
	   if(index>=size){
		 index--;   
	   }	 
	 }
	 if(c=='w'||c==KEY_UP){
	   index--;
	   if(index<0){index=0;}	 
	 }
    }
    if(c=='q'){return NULL;} 
    return pls->at(index);  
}
void TimeManager::editPtime(playlist* p,string name){
	string text="now editing "+name;
	int c=0;
	int startday=p->starttime->getDay();
	int endday=p->endtime->getDay();
	int starthour=p->starttime->getHour();
	int endhour=p->endtime->getHour();
	int startmin=p->starttime->getMinute();
	int endmin=p->endtime->getMinute();
	int editing=0;
	int cc=0;
	int move=0;
	playlist* selected=NULL;
	while(c!='q'&&c!='\n'){
	 clear();
	 printw("%s\n",text.c_str());
	 printw("tab- next| h- hours| m- minutes| d- days| e- end date| s- startdate| p- other playlist's start date| y- other playlist's end date| t- today\n");
	 if(editing==0){
	  switch(cc){
		  case 0: startday=startday+move;if(startday>6){startday=6;}if(startday<0){startday=0;}break;
		  case 1: starthour=starthour+move;if(starthour>23){starthour=23;}if(starthour<0){starthour=0;}break;
		  case 2: startmin=startmin+move;if(startmin>59){startmin=59;}if(startmin<0){startmin=0;}break;
	  }
	  if(c=='s'){startday=0;starthour=0;startmin=0;}
	  if(c=='e'){startday=6;starthour=23;startmin=59;}
	  if(selected!=NULL){
		if(c=='p'){
		 startday=selected->starttime->getDay();
		 starthour=selected->starttime->getHour();
		 startmin=selected->starttime->getMinute();
		}  
		if(c=='y'){
		 startday=selected->endtime->getDay();
		 starthour=selected->endtime->getHour();
		 startmin=selected->endtime->getMinute();
		} 
		selected=NULL; 
	  }
	  attron(A_STANDOUT);
	  printw("start time: D:%d H:%d Min:%d\n\n",startday,starthour,startmin);	 
	  attroff(A_STANDOUT);
	  printw("  end time: D:%d H:%d Min:%d\n",endday,endhour,endmin);
	 }
	  if(editing==1){
	  switch(cc){
		  case 0: endday=endday+move;if(endday>6){endday=6;}if(endday<0){endday=0;}break;
		  case 1: endhour=endhour+move;if(endhour>23){endhour=23;}if(endhour<0){endhour=0;}break;
		  case 2: endmin=endmin+move;if(endmin>59){endmin=59;}if(endmin<0){endmin=0;}break;
	  }
	  if(c=='s'){endday=0;endhour=0;endmin=0;}
	  if(c=='e'){endday=6;endhour=23;endmin=59;}
	   if(selected!=NULL){
		if(c=='p'){
		 endday=selected->starttime->getDay();
		 endhour=selected->starttime->getHour();
		 endmin=selected->starttime->getMinute();
		}  
		if(c=='y'){
		 endday=selected->endtime->getDay();
		 endhour=selected->endtime->getHour();
		 endmin=selected->endtime->getMinute();
		} 
		selected=NULL; 
	  }
	  attron(A_STANDOUT);
	  printw("  end time: D:%d H:%d Min:%d\n\n",endday,endhour,endmin);	 
	  attroff(A_STANDOUT);
	  printw("start time: D:%d H:%d Min:%d\n",startday,starthour,startmin);	
	 }
	 PTime psec;
	 printw("\n\ncurrent time: D:%d H:%d Min:%d\n",psec.getDay(),psec.getHour(),psec.getMinute());
	 c=getch();
	 move=0;
	 if(c=='h'){cc=1;}
	 if(c=='m'){cc=2;}
	 if(c=='d'){cc=0;}
	 if(c=='w'||c==KEY_UP){move=1;}
	 if(c=='s'||c==KEY_DOWN){move=-1;}
	 if(c==KEY_STAB||c=='\t'){if(editing==1){editing=0;}else{editing=1;}}
	 if(c=='p'||c=='y'){
	  selected=selectPlaylist();	 
	 }
   }
   if(c=='\n'){
	   p->starttime->setTime(startday,starthour,startmin);
	   p->endtime->setTime(endday,endhour,endmin);
   }
}
void TimeManager::show(){
	
	int size=pls->size();
	string timeline=generatetimeline();
	int c=0;
	int index=0;
	while(c!='q'){
	 clear();
     printw("%s\npress p to auto organize, enter to edit, q to exit\n",timeline.c_str());
     int i;
     for(i=index;i<size&&i<(LINES/2)-4+index;i++){
	   playlist* p=pls->at(i);
	   if(index==i){printw(">");attron(A_STANDOUT);}else{printw(" ");}
	   printw("%s\n",pls->getName(i));
	   attroff(A_STANDOUT);
	   printw("  -start time: d:%d h:%d m:%d   ",p->starttime->getDay(),p->starttime->getHour(),p->starttime->getMinute());	
	   printw("end time: d:%d h:%d m:%d\n",p->endtime->getDay(),p->endtime->getHour(),p->endtime->getMinute());
	 }
     c=getch();
     if(c=='s'||c==KEY_DOWN){
	   index++;
	   if(index>=size){
		 index--;   
	   }	 
	 }
	 if(c=='w'||c==KEY_UP){
	   index--;
	   if(index<0){index=0;}	 
	 }
	 if(c=='\n'){
	   	 editPtime(pls->at(index),string(pls->getName(index)));
	   	 timeline=generatetimeline();
	 }
     if(c=='p'){autoOrganize();timeline=generatetimeline();}
    }
}
