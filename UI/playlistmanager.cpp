#include "playlistmanager.h"
#include "filechooser.cpp"
#include <ncurses.h>
#include <dirent.h>
#include "inputDialogue.cpp"
//playlist manager for radio player
//original code by Evan Nikitin
volatile int isreading=0;
volatile int iswriting=0;
void line(){
 int linedr;
 for(linedr=0;linedr<COLS;linedr++){
  //printw('-');	 
  addch(ACS_HLINE);
 }	
}
int playlistmanager::selectPlaylist(int s,PLmanager* info){
	int c=0;
	int index=0;
	int start=0;
	while(c!='\n'&&c!='q'&&c!='n'){
	 clear();
	 printw("Select the playlist to edit| w- up s- down| enter- select| q- quit|n - new| m-play time manager\n");
	 line();
	 int i;
	 for(i=start;i<s;i++){
	   if(index==i){
		   printw(">");
		   attron(A_STANDOUT);
		   printw("%s\n",info->getName(i));
		   attroff(A_STANDOUT);
	   }else{
	       printw(" %s\n",info->getName(i)); 	 
	   }
	 }
	 c=getch();
	 if(c=='s'||c==KEY_DOWN){index++;start++;if(index>=s-1){index=s-1;start--;}}
	 if(c=='w'||c==KEY_UP){index--;start--;if(start<0){start=0;}if(index<0){index=0;}}
	 if(c=='m'){
	  TimeManager tm(info);	
	  tm.show(); 
	 }
	}
	if(c=='n'){
	  return -2;	
    }
	if(c=='\n'){
	 return index;	
	}
	if(c=='q'){
	 return -1;	
	}
	return index;
}
int playlistmanager::SelectSong(playlist *p){
 int size=p->countSongs();	
 int c=0;
 int index=0;
 int start=0;
 
 while(c!='\n'&&c!='q'){
  clear();
  printw("q-quit|enter-select| total %d\n\n",size);
  int i;
  for(i=start;i<size;i++){
	song s=*(p->getPointerAt(i));
	if(index==i){printw(">");attron(A_STANDOUT);}else{printw(" ");}
	printw("%s\n",s.getName().c_str());  
	attroff(A_STANDOUT);
	if(i-start>LINES-4){break;}
  }
  c=getch();
  if(c=='s'||c==KEY_DOWN){index++;start++;if(index>=size-1){index=size-1;start--;}}
  if(c=='w'||c==KEY_UP){index--;start--;if(start<0){start=0;}if(index<0){index=0;}}
  
 }
 clear();
 if(c=='q'){return -1;}
 return index;
}
int playlistmanager::SelectId(playlist *p){
 int size=p->countIDs();	
 int c=0;
 int index=0;
 int start=0;
 
 while(c!='\n'&&c!='q'){
  clear();
  printw("q-quit|enter-select\n\n");
  int i;
  for(i=start;i<size;i++){
	song s=p->getID(i);
	if(index==i){printw(">");attron(A_STANDOUT);}else{printw(" ");}
	printw("%s\n",s.getName().c_str()); 
	attroff(A_STANDOUT);
	if(i-start>LINES-4){break;} 
  }
  c=getch();
  
  if(c=='s'||c==KEY_DOWN){index++;start++;if(index>=size-1){index=size-1;start--;}}
  if(c=='w'||c==KEY_UP){index--;start--;if(start<0){start=0;}if(index<0){index=0;}}
 
 }
 clear();
 if(c=='q'){return -1;}
 return index;
}
int playlistmanager::editPlaylist(playlist* p){
	int songs=p->countSongs();
	int ids=p->countIDs();
	string message="q-exit | d-delete | s-songs | i-IDs | g-add directory of songs | a-add song | f-add ID\n";
	clear();
	printw(message.c_str());
	char c=0;
	while(c!='q'&&c!='d'){
    songs=p->countSongs();
	ids=p->countIDs();
	 if(c=='s'){
	   if(songs>0){
		   int s=SelectSong(p);
		   if(s!=-1){
			  songoptions(*p,s,0,1);   
		   }
	   }	 
	 }
	 if(c=='i'){
	   if(ids>0){
		  int i=SelectId(p);  
		  if(i!=-1){
			  songoptions(*p,i,1,1);   
		   } 
	   }
	   
      }
      if(c=='f'){
	   filechooser f;
	   f.setDef();
	   int cinfo=f.show();
	   if(cinfo==1){
		string newname=Prompt("edit the display name of the ID(empty means no change)?",f.getName());
		if(newname.compare("")==0){newname=f.getName();}
		song s(newname,f.getFinalPath());  
		while(iswriting==1){}
	    isreading=1; 
		p->putId(s);
		isreading=0;
	   }
	  }
	  if(c=='g'){
	   filechooser f;
	   f.setDef();
	   f.setDirOnly();
	   int cinfo=f.show();
	   if(cinfo==1){
		DIR *d=opendir(f.getFinalPath().c_str());
		dirent *dif;
		while((dif=readdir(d))!=NULL){
		 char* name=dif->d_name;
		 if(f.endsWith(string(name),".wav")==1||f.endsWith(string(name),".ogg")==1){
			song s(f.getNameFromFileName(string(name)),f.getFinalPath()+"/"+string(name));
			while(iswriting==1){}
	        isreading=1; 
			p->add(s); 
			isreading=0;
		  }	
		}
		closedir(d);
	  }	 
     }
	 if(c=='a'){
	   filechooser f;
	   f.setDef();
	   int cinfo=f.show();
	   if(cinfo==1){
		string newname=Prompt("edit the display name of the song(empty means no change)?",f.getName());
		if(newname.compare("")==0){newname=f.getName();}
		song s(newname,f.getFinalPath());  
		while(iswriting==1){}
	    isreading=1; 
		p->add(s);
		isreading=0;
	 }
	}
	clear();
	printw(message.c_str());
	DisPL(p,2);
	 c=getch();	
	}
	if(c=='d'){
	 return 1;
	}
	return -1;
}
void playlistmanager::songoptions(playlist p,int index,int isid,int memlock){
   string name="";
   string path="";
   if(isid==0){
	 song sin=p.getAt(index);   
	 name=sin.getName();
	 path=sin.getPath();
   }
   if(isid==1){
	 song sin=p.getID(index);
	 name=sin.getName();   
	 path=sin.getPath();
   }
   clear();
   printw(name.c_str());
   printw("\n");
   attron(A_BOLD);
   printw("Path: ");
   attroff(A_BOLD);
   printw("%s\n",path.c_str());
   printw("\n\nd-delete the song");
   char opt=getch();
   if(opt=='d'){
	  if(memlock==1){
		while(iswriting==1){}
	    isreading=1;  
	  }
	  if(isid==1){
		 p.removeId(index);
	  }else{
		 p.delAt(index);  
	  }
	  if(memlock==1){
	    isreading=0;  
	  }
   }
   
   
   
}
void playlistmanager::DisPL(playlist* p,int start){
	 int linedr;
     for(linedr=0;linedr<COLS;linedr++){
      //printw('-');	 
      addch(ACS_HLINE);
    }
	int i;
	int size=p->countSongs();
	for(i=start;i<LINES-1;i++){
		if(i>size+2){return;}
	  	song* sin=p->getPointerAt(i-start); 
	  	if(sin==NULL){break;}
	  	printw("%s\n",sin->getName().c_str());
    }
}
void playlistmanager::NewPL(PLmanager* p){
	playlist n;
	clear();
	string disp="q -exit | a-add song | d-add directory of songs | i-add id | s-view songs | v-view ids | h-save\n";
	printw(disp.c_str());
	
	char c=0;
	string message="";
	while(c!='q'&&c!='h'){
      if(c=='s'){
		int sel=SelectSong(&n);
		if(sel!=-1){
		  songoptions(n,sel,0,0);	
		}  
	  }
	  if(c=='v'){
		int sel=SelectId(&n);
		if(sel!=-1){
		  songoptions(n,sel,1,0);	
		}  
	  }
	  if(c=='a'){
	   filechooser f;
	   f.setDef();
	   int cinfo=f.show();
	   if(cinfo==1){
		string newname=Prompt("edit the display name of the song(empty means no change)?",f.getName());
		if(newname.compare("")==0){newname=f.getName();}
		song s(newname,f.getFinalPath());  
		n.add(s);
		message="--song added--";
	   }
     } 
     if(c=='d'){
	   filechooser f;
	   f.setDef();
	   f.setDirOnly();
	   int cinfo=f.show();
	   if(cinfo==1){
		DIR *d=opendir(f.getFinalPath().c_str());
		dirent *dif;
		while((dif=readdir(d))!=NULL){
		 char* name=dif->d_name;
		 if(f.endsWith(string(name),".wav")==1||f.endsWith(string(name),".ogg")==1){
			song s(f.getNameFromFileName(string(name)),f.getFinalPath()+"/"+string(name));
			n.add(s); 
		  }	
		}
		closedir(d);
		message="--directory added--";
	   }
     } 
      if(c=='i'){
	   filechooser f;
	   f.setDef();
	   int cinfo=f.show();
	   if(cinfo==1){
		string newname=Prompt("edit the display name of the ID(empty means no change)?",f.getName());
		if(newname.compare("")==0){newname=f.getName();}
		song s(newname,f.getFinalPath());  
		n.putId(s);
		message="--id added--";
	   }
     } 
    
	 clear();
	 printw("%s\n",message.c_str());
	 
	 message="";
	 printw(disp.c_str());
	 DisPL(&n,3);
	 c=getch();	
	}
	if(c=='q'){
	 n.close();	
	}
	if(c=='h'){
	   string plname=PromptFilename("Please Name the playlist","");
	   while(plname.compare("")!=0&&p->exists(plname)==1){
		   plname=PromptFilename("Please Name the playlist, name already taken",plname);
	   }
	   if(plname.compare("")!=0){
	     p->add(n,plname);
       }else{n.close();}
	   	 
    }
}
void playlistmanager::openDialogue(PLmanager* input){
 while(1==1){
 int s=selectPlaylist(input->size(),input);
 clear();
 if(s==-1){
   return;	 
 }
 if(s==-2){
	 NewPL(input);
	 }else{
   if(editPlaylist(input->at(s))==1){
	 while(iswriting==1){}
	 isreading=1;
	 input->rem(s);
	 isreading=0;   
   }
   }
 }
}
