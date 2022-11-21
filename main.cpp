
#include "UI/playlistmanager.cpp"
#include<iostream>
#include <exception>
#include <unistd.h>
#include<thread>
#include "microphone/microphone.cpp"

//requires: vorbis pthread ncurses alsasound
PLmanager pm(2);
playlistmanager p;
volatile int exitv=0;
volatile int hang=0;
volatile int putname=0;
volatile int PauseAS=0;

string nowplaying="";
string path="";
Mixer m;
MQueue manQ;
Microphone mic;
//orignal code by Evan Nikitin
void waitForEn(){
	if(PauseAS==1){
	  cout<<"\n\n--info song is over"<<endl;	
	}
	while(PauseAS==1){
	 sleep(1);	
	}
}

void songs( Mixer* m,MQueue* mq){
	if(pm.canNext()==-1){sleep(1);//one second delay
		
		return;}
	//debug point
	while(iswriting!=0){}
	isreading=1;
	//debug point
	Queue a=pm.next();
	song s3;
	//debug point
	 
	 while(a.canNext()==1){
		s3=a.getNext();
		isreading=0;
		putname=1;
		nowplaying=s3.getName();
		string tmpath=s3.getPath();//check for repetition in case decoder has failed in the play function
		putname=0;
		while(hang==1){}
		try{
		 if(tmpath.compare(path)!=0){//condition for the check
		  s3.play(m);
		  waitForEn();
	     }
	    }catch(...){}
	    path=tmpath;
		while(iswriting!=0){}
		isreading=1;
        s3.empty();
        isreading=0;
        while(mq->Size()>0){
		  nowplaying=mq->nameAt(0);
		  mq->play(m);
		  waitForEn();	
		}
    }
    a.clear();
}
void playSongs(){//song playing thread
 while(exitv==0){
  songs(&m,&manQ);	 
 }	
 m.closeMixer();
}
void microphone(){
 mic.runner();
}
void mainInterface(){//ncurses main screen

 int c=0;
 int mi=0;
 while(c!='q'){
  clear();
  while(putname==1){}
  printw("Now Playing: %s\n",nowplaying.c_str());
  line();
  printw("press p to manage playlists, press any key to update \"Now Playing\"\n press s to pause\n press j to jump, press a to skip\n press m to toggle ");
  if(mi==1){attron(A_STANDOUT);}
  printw("microphone");
  if(mi==1){attroff(A_STANDOUT);}
  printw("\n press g to pause after the end of this song");
  if(PauseAS==1){printw(" (yes)");}
  printw("\n");
  printw("\nmicrophone options: u- enable demo machine, y- enable pitch shifter, o- normal audio\n");
  c=getch();	
  if(c=='u'&&mi!=1){
	mic.normalaudio();
	mic.DemoMachine();  
  }
   if(c=='y'&&mi!=1){
	mic.normalaudio();
	mic.Pitch();  
  }
  if(c=='o'&&mi!=1){
	mic.normalaudio();  
  }
  if(c=='g'){
	switch(PauseAS){
	 case 1:PauseAS=0;break;
	 case 0:PauseAS=1;break;
	}  
	
  }
  if(c=='a'){
	
	m.ABORT=1;
	m.pause();
	m.unpause();
	
  } 
  if(c=='j'){
	
	
	m.PAUSE=0;
	m.ABORT=1;
	m.pause();
	m.unpause();
	
  } 
  if(c=='m'){
	mic.toggle();  
	if(mi==0){mi=1;}else{mi=0;}
  }
  if(c=='s'){
	if(m.PAUSE==1){
	 m.PAUSE=0;
	 m.unpause();
    }else{
	  m.PAUSE=1;
	  m.pause();	
	}
  }
  if(c=='p'){
	  p.openDialogue(&pm,&manQ);
  }
 }	
}
int main(){
	srand(time(NULL));//random initialization
	thread fplayer(playSongs);//queu and playback thread
	thread micro(microphone);//microphone thread
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	keypad(stdscr, TRUE);//arrow keys and tab
	int s=curs_set(0);
    pm.load();//load from file
    mainInterface();
    endwin();

    exitv=1;
    iswriting=1;
    pm.save();
    pm.clear();//cleanup
    curs_set(s);
    manQ.close();
    exit_curses(0);
    mic.kill();
    m.PAUSE=1;
    m.pause();
    m.closeMixer();
    return 0;
	}

