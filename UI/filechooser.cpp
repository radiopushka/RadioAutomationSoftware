#include "filechooser.h"
#include <sys/types.h>
#include <sys/stat.h>

//ncurses file chooser plugin
//original code by Evan Nikitin

filechooser::filechooser(){
 path="/";
 filter=".wav";
 filter2=".ogg";
 const char* home=getenv("HOME");
 if(home!=NULL){
  path=string(home);	 
 }
 dir=0;
}
void filechooser::setDef(){
 path="/";
 filter=".wav";
 filter2=".ogg";
 const char* home=getenv("HOME");
 if(home!=NULL){
  path=string(home);	 
 }
 dir=0;	
}
string filechooser::getFinalPath(){
 return path;	
}
void filechooser::setDirOnly(){
 dir=1;
	
}
void filechooser::setFileOnly(){
 dir=0;	
}
void filechooser::setFilter(string f){
 filter=f;	
}
void filechooser::setPath(string p){
 path=p;	
}
int filechooser::endsWith(string input,string with){
	if(input.length()<=with.length()){return -1;}
	const char *in=input.c_str();
	const char *comp=with.c_str();
	const char *startin=in+input.length();
	const char *startc=comp+with.length();
	int sizem=with.length();
	int i;
	for(i=0;i<sizem;i++){
	 if(*startin!=*startc){
	   return -1;	
	 }
	 startin--;
	 startc--;	
	}
	return 1;
}
int filechooser::isBad(char* in,unsigned char type){
	if(in[0]=='.'&&in[1]=='\0'){return -1;}
	if(in[0]=='.'&&in[1]=='.'&&in[2]=='\0'){return -1;}
	if(type==DT_DIR){return 1;}
	if(dir==1){return -1;}
	string input=string(in);
	int i=endsWith(input,filter);
	if(i==1){return 1;}
	return endsWith(input,filter2);
}
char filechooser::listdir(int opt){
 int in=0;
 clear();
 printw("enter-select | q-quit | s-down w-up | b-back | c-select current directory\n");
 printw(":%s\n",path.c_str());

 int linedr;
 for(linedr=0;linedr<COLS;linedr++){
  //printw('-');	 
  addch(ACS_HLINE);
 }
 
 
 struct dirent* di;
 int c=index;
 int before=0;
 char* name;
 char* selected=NULL;
 int lines=0;
 int strt=0;
 if(index==0){strt=1;};
 while((di=readdir(d))!=NULL){
	 name=di->d_name;
	 if(isBad(name,di->d_type)!=-1){
		 if(before>=index){
			 strt=1;
			 if(selected==NULL){selected=(char*)malloc((strlen(name)+1)*sizeof(char));
				 strcpy(selected,name);
				 songname=string(name);
				  printw("->");
				  attron(A_STANDOUT);
				 }else{attroff(A_STANDOUT);printw("  ");}
		     attron(A_BOLD);
			 printw("%c",*name);
			 attroff(A_BOLD);
			 name++;
			 int sis=strlen(name);
			 if(sis<0){sis=0;}
			 if(sis>COLS-4){
			   name[COLS-4]='\0';
			 }
			 printw("%s\n",name);
			 attroff(A_STANDOUT);
			 lines++;
			 c++;
		 }else{before++;}
	 }else{
		 if(di->d_type!=DT_DIR&&strt==1){
		  if(endsWith(string(name),filter)==1||endsWith(string(name),filter2)==1){
		   attron(A_DIM);
		   int sis=strlen(name);
			 if(sis<0){sis=0;}
			 if(sis>COLS-4){
			   name[COLS-7]='\0';
			 }
		   printw("     -%s\n",name);
		   attroff(A_DIM);
		   lines++;
	      }
	     }
	 }
	 if(lines>LINES-4){break;}
 }
 rewinddir(d);
 in=getch();
 if(in=='s'||in==KEY_DOWN){
	index++;
	if(index>=c){index--;} 
  }
 if(in=='w'||in==KEY_UP){
	 index--;
	 if(index<0){index=0;}
  } 
 if(in=='\n'){
	  if(selected!=NULL){
	  if(path.compare("/")!=0){
		 path=path+"/";  
		 
	  }
	  path=path+string(selected);
	  closedir(d);
	  d=opendir(path.c_str());
	  index=0;
  }
	 // listdir(0);
  }
  if(selected!=NULL){
  free(selected);
  }
  if(in=='b'){
	  if(path.compare("/")!=0){
		size_t found=path.find_last_of("/");
		if(found==0){
		 path="/";	
		}else{
		path=path.substr(0,path.find_last_of("/")); 
	    }
	    closedir(d);
	    d=opendir(path.c_str());
		index=0; 
	  }
	  //listdir(0);
  }
  return in;
}
int filechooser::show(){
	char c=0;
	index=0;
	d=opendir(path.c_str());
	while(c!='q'&&c!='c'){
		c=listdir(1);
		if(endsWith(path,filter)==1||endsWith(path,filter2)==1){
		 closedir(d);
		 return 1;	
		}
		if(c=='c'&&dir==0){c=0;}
   }
   closedir(d);
   if(c=='c'){
	return 1;   
   }
   if(c=='q'){
	 return -1;   
   }
   return 0;
}
string filechooser::getNameFromFileName(string name){
	size_t loc=name.find_last_of(".");
  if(loc>0){
	return name.substr(0,loc);  
  }
  return name;	
}
string filechooser::getName(){
  size_t loc=songname.find_last_of(".");
  if(loc>0){
	return songname.substr(0,loc);  
  }
  return songname;	
	
}
