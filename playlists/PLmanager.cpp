#include "PLmanager.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

//original code by Evan Nikitin

PLmanager::PLmanager(int beforei){//initialization
	pls=NULL;
	sizel=0;
	loaded=0;
	beforeid=beforei;
	prevp="null";
	prevn="null";
}
void PLmanager::setSongsBeforeId(int num){
 beforeid=num;	
}

void PLmanager::add(playlist p,string name){//add from the top
	playlist* pin=p.copy();
	struct ListofPLs* l=(struct ListofPLs*)malloc(sizeof(struct ListofPLs));
	char* namep=(char*)malloc((name.length()+1)*sizeof(char));
	strcpy(namep,name.c_str());
	l->name=namep;
	l->next=pls;
	l->p=pin;
	sizel++;
	pls=l;
}
void PLmanager::addBottom(playlist p,string name){//add from bottom to keep the list in order
	playlist* pin=p.copy();
	struct ListofPLs* l=(struct ListofPLs*)malloc(sizeof(struct ListofPLs));
	char* namep=(char*)malloc((name.length()+1)*sizeof(char));
	strcpy(namep,name.c_str());
	l->name=namep;
	l->p=pin;
	l->next=NULL;
	sizel++;
	if(pls==NULL){pls=l;return;}
	struct ListofPLs* tmp=pls;
	while(tmp->next!=NULL){
	  tmp=tmp->next;	
    }
    tmp->next=l;
}
void PLmanager::rem(int i){//remove playlist at an index
	struct ListofPLs* tmp=pls;
	struct ListofPLs* next;
	struct ListofPLs* prev=NULL;
	int c=0;
	while(tmp!=NULL){
	 if(c==i){
		tmp->p->close();
		free(tmp->name);
		free(tmp->p);
		next=tmp->next;
		free(tmp); 
		sizel--;
		if(prev!=NULL){
		 prev->next=next;
		}else{
		 pls=next;
		}
		tmp=next;
	 }else{
	  prev=tmp;
	  tmp=tmp->next;
     }	
     c++;
	}
}
void PLmanager::clear(){//free memory
	struct ListofPLs* tmp=pls;
	struct ListofPLs* holder;
	while(tmp!=NULL){
	 holder=tmp->next;
	 free(tmp->name);
	 tmp->p->close();
	 free(tmp->p);
	 free(tmp);
	 tmp=holder;	
	}
}
playlist* PLmanager::at(int i){
 int c=0;	
 struct ListofPLs* tmp=pls;
 while(tmp!=NULL){
  if(i==c){
	return tmp->p;  
  }
  c++;	 
  tmp=tmp->next;
 }
 return NULL;
}
int PLmanager::size(){
 return sizel;	
}

Queue PLmanager::next(){
	struct ListofPLs* tmp=pls;
	playlist* p;
	while(tmp!=NULL){
	 p=tmp->p;
	 if(p->ShouldPlay()==1){
		song inp(prevn,prevp);
		Queue q(*p,beforeid,inp);//generate the playback queue
		song tt=q.returnTracker();//return the last song information
		inp.empty();
		prevn=tt.getName();//save in the stack
		prevp=tt.getPath();
		return q;
	 }
	 tmp=tmp->next;	
	}
	
	return next();//loop until the right time comes
}
int PLmanager::canNext(){
	int c=0;
	struct ListofPLs* tmp=pls;
	playlist* p;
	while(tmp!=NULL){
	 p=tmp->p;
	 if(p->ShouldPlay()==1){//does any play list match
		
		return c;
	 }
	 c++;
	 tmp=tmp->next;	
	}
	
	return -1;
}
int PLmanager::exists(string name){
  struct ListofPLs* tmp=pls;
  const char* comparison=name.c_str();
  while(tmp!=NULL){
	if(strcmp(comparison,tmp->name)==0){
	 return 1;	
	}
	tmp=tmp->next;  
  }	
  return -1;
}
char* PLmanager::getName(int i){
 struct ListofPLs* tmp=pls;
 int c=0;
 while(tmp!=NULL){
  if(c==i){
	return tmp->name;  
  }
  c++;
  tmp=tmp->next;	 
 }
	return NULL;
}
void PLmanager::load(){//load playlists from a directory
 const char* home=getenv("HOME");
 string path=string(home)+"/radioPlaylists";
 mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);	
 DIR* d=opendir(path.c_str());
 if(d==NULL){return;}
 struct dirent *dinfo;
 while((dinfo=readdir(d))!=NULL){
	 if(strcmp(dinfo->d_name,".")==0||strcmp(dinfo->d_name,"..")==0){}else{
	 playlist p;
	 p.loadFromFile(path+"/"+dinfo->d_name);
	 addBottom(p,string(dinfo->d_name));
    }
	 
 }
 closedir(d);
 
 
}
void PLmanager::save(){//save playlists to the directory
 const char* home=getenv("HOME");
 string path=string(home)+"/radioPlaylists";
 mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);	
 DIR* d=opendir(path.c_str());
 if(d==NULL){
	 cout<<"save failed"<<endl;
	 return;}
 struct dirent *dinfo;
 while((dinfo=readdir(d))!=NULL){
	 remove((path+"/"+dinfo->d_name).c_str());
 }
 closedir(d);
 int c=0;
 struct ListofPLs* strt=pls;
 string path2;
 while(strt!=NULL){
  path2=path+"/"+string(strt->name);
  c++;
  (*(strt->p)).saveToFile(path2);
  strt=strt->next;	 
 }
}
