#include "playlist.h"
#include <fstream>
//playlist data holder
//original code by Evan Nikitin

playlist::playlist(){
 head=NULL;	
 ids=NULL;
 nsongs=(int*)malloc(sizeof(int));
 nids=(int*)malloc(sizeof(int));
 *nsongs=0;
 *nids=0;
 starttime=(PTime*)malloc(sizeof(PTime));
 endtime=(PTime*)malloc(sizeof(PTime));
 new(starttime) PTime();
 new(endtime) PTime();
}
song playlist::convert(song* s){//heap to stack
 song n(s->getName(),s->getPath());
 return n;
	
}
int playlist::getI(song s){//get index, never used, may be used later but needs to be debuged
	struct list* cp=head;
	int c=0;
	while(cp!=NULL){
	 song ss=convert(cp->s);
	 if(ss.getName().compare(s.getName())&&ss.getPath().compare(s.getPath())){
	   return c;	 
	 }
	 c++;
	 cp=cp->next;	
	}
	return -1;
}

void playlist::putId(song s){//put the ID into the playlist
	struct IDs* newitm=(struct IDs*)malloc(sizeof(struct IDs));
	song* ns=(song*)malloc(sizeof(song));
	new(ns) song;
	ns->set(s.getName(),s.getPath());
	s.empty();
	newitm->s=ns;
	newitm->next=ids;
	ids=newitm;
	int nss=*nids;
	nss++;
	*nids=nss;
}
int playlist::countIDs(){//count number of IDs
    int id=*nids;
	return id;
}
void playlist::removeId(int i){
	if(i==0){
		if(ids==NULL){return;}
		if(ids->next==NULL){
		  ids->s->empty();
		  free(ids->s);
		  free(ids);
		  ids=NULL;	
		  *nids=0;
		  return;
		}
		ids->s->empty();
		free(ids->s);
		song* s=(song*)malloc(sizeof(song));
		new(s) song;
		s->set(ids->next->s->getName(),ids->next->s->getPath());
		ids->s=s;
		i=1;
	}
    struct IDs* cp=ids;
	struct IDs* tmp;
	struct IDs* prev=NULL;
	int c=0;
	while(cp!=NULL){
	 if(c==i){
	   if(prev!=NULL){prev->next=cp->next;}else{ids=cp->next;}
	   tmp=cp->next;
	   (*nids)--;
	   cp->s->empty();
	   free(cp->s);
	   free(cp);
	   cp=tmp;
	   c++;	 
	 }else{
	  c++;
	  prev=cp;
	  cp=cp->next;	
     }
     
	}
}
int playlist::countSongs(){//count number of songs in the playlist
 int songs=*nsongs;
 return songs;
}
void playlist::setStartTime(PTime in){//start time set, never used
 	starttime->fromString(in.toString());
}
void playlist::setEndTime(PTime en){//end time set, never used
  endtime->fromString(en.toString());	
}
playlist* playlist::copy(){
  playlist* dest=(playlist*)malloc(sizeof(playlist));
  new(dest) playlist;
  dest->playtimes=playtimes;
  dest->timecount=timecount;
  struct list* l=head;
  dest->setStartTime(*starttime);
  dest->setEndTime(*endtime);
  struct list *tmp;
  while(l!=NULL){
	dest->add(*(l->s));
	free(l->s);
	tmp=l->next;
	free(l);
	l=tmp;  
  }
  struct IDs* id=ids;
  struct IDs* tmpi;
  while(id!=NULL){
	
	dest->putId(*(id->s));
	free(id->s);
	tmpi=id->next;
	free(id);
	id=tmpi;  
  }
  free(nsongs);
  free(nids);
  free(starttime);
  free(endtime);
  return dest;
}
void playlist::add(song sin){//add song to the playlist
	struct list* ll=(struct list*)malloc(sizeof(struct list));
	song* s=(song*)malloc(sizeof(song));
	new(s) song;
	s->set(sin.getName(),sin.getPath());
	ll->prev=NULL;
	sin.empty();
	ll->s=s;
	ll->next=head;
	head=ll;
	int sc=*nsongs;
	sc++;
	*nsongs=sc;
}

void playlist::delAt(int i){//remove the song at this index
	if(i==0){
		if(head==NULL){return;}
		if(head->next==NULL){
		  head->s->empty();
		  free(head->s);
		  free(head);
		  head=NULL;
		  *nsongs=0;
		  return;	
		}
		head->s->empty();
		free(head->s);
		song* s=(song*)malloc(sizeof(song));
		new(s) song;
		s->set(head->next->s->getName(),head->next->s->getPath());
		head->s=s;
		i=1;
	}
	struct list* cp=head;
	struct list* tmp;
	struct list* prev=NULL;
	int c=0;
	while(cp!=NULL){
	 if(c==i){
	   if(prev!=NULL){prev->next=cp->next;}else{break;}
	   tmp=cp->next;
	   (cp->s)->empty();
	   free(cp->s);
	   free(cp);
	   cp=tmp;
	   (*nsongs)--;
	   return;
	   c++;	 
	 }else{
	  c++;
	  prev=cp;
	  cp=cp->next;	
     }
     
	}
	
	
}
song playlist::getAt(int i){//get a song at this index
	struct list* cp=head;
	int c=0;
	while(cp!=NULL){
	 if(cp->s==NULL){break;}
	 song* ss=(cp->s);
	 if(c==i){
	   return *ss;	 
	 }
	 c++;
	 cp=cp->next;	
	}
	song s("","");
	return s;
}
song* playlist::getPointerAt(int i){//get the song as the original pointer(prevents memory leaks in some cases)
	struct list* cp=head;
	int c=0;
	while(cp!=NULL){
	 if(cp->s==NULL){break;}
	 song* ss=(cp->s);
	 if(c==i){
	   return ss;	 
	 }
	 c++;
	 cp=cp->next;	
	}
	return NULL;
}
song playlist::getID(int i){//get the ID at this index
	struct IDs* cp=ids;
	int c=0;
	while(cp!=NULL){
	 song ss=*(cp->s);
	 if(c==i){
	   return ss;	 
	 }
	 c++;
	 cp=cp->next;	
	}
	song s("","");
	return s;
}
void playlist::clearSongs(){
	struct list* cp=head;
	struct list* tmp;
	while(cp!=NULL){
	 tmp=cp->next;
	 cp->s->empty();
	 free(cp->s);
	 free(cp);
	 cp=tmp;	
	}
	head=NULL;
	*nsongs=0;
	
}
void playlist::close(){//free memmory
	free(nids);
	free(nsongs);
	free(endtime);
	free(starttime);
	struct list* cp=head;
	struct list* tmp;
	while(cp!=NULL){
	 tmp=cp->next;
	 cp->s->empty();
	 free(cp->s);
	 free(cp);
	 cp=tmp;	
	}
    struct IDs* cp2=ids;
	struct IDs* tmp2;
	while(cp2!=NULL){
	 tmp2=cp2->next;
	 
	 cp2->s->empty();
	 free(cp2->s);
	 free(cp2);
	 cp2=tmp2;	
	}
	struct PTimes* times=playtimes;
	struct PTimes* tmp3;
	while(times!=NULL){
	  tmp3=times->next;
	  free(times->start);
	  free(times->end);
	  free(times);
	  times=tmp3;	
	}
	
}

void playlist::addTimesTop(PTime start,PTime end){
  struct PTimes* loft=(struct PTimes*)malloc(sizeof(struct PTimes));
  PTime* pst=(PTime*)malloc(sizeof(PTime));	
  PTime* pen=(PTime*)malloc(sizeof(PTime));
  new(pst) PTime(start.getDay(),start.getHour(),start.getMinute());
  new(pen) PTime(end.getDay(),end.getHour(),end.getMinute());
  loft->start=pst;
  loft->end=pen;
  loft->next=playtimes;
  playtimes=loft;
  timecount++;
}
int playlist::ShouldPlay(){
 struct PTimes* tx=playtimes;
 while(tx!=NULL){
   if(tx->start->isPast()==1&&tx->end->isPast()==-1){
	 return 1;  
   }
   tx=tx->next;	 
 }
	return -1;
}
void playlist::addTimesBottom(PTime start,PTime end){
  struct PTimes* loft=(struct PTimes*)malloc(sizeof(struct PTimes));
  PTime* pst=(PTime*)malloc(sizeof(PTime));	
  PTime* pen=(PTime*)malloc(sizeof(PTime));
  new(pst) PTime(start.getDay(),start.getHour(),start.getMinute());
  new(pen) PTime(end.getDay(),end.getHour(),end.getMinute());
  loft->start=pst;
  loft->end=pen;
  loft->next=NULL;
  if(playtimes==NULL){
   playtimes=loft;
  }else{
	struct PTimes* st=playtimes;
	while(st->next!=NULL){
		st=st->next;
	}
	st->next=loft;
  }
  
  timecount++;
}
int playlist::countTimes(){
return timecount;	
}
PTimes* playlist::getTAt(int i){
	int c=0;
	struct PTimes* tmp=playtimes;
	while(tmp!=NULL){
	  if(c==i){
		  return tmp;
	  }
	  c++;
	  tmp=tmp->next;	
	}
	return NULL;
}
string playlist::TtoString(){
	string out="";
	struct PTimes* tmp=playtimes;
	while(tmp!=NULL){
	  out=out+tmp->start->toString()+","+tmp->end->toString()+",";
	  tmp=tmp->next;	
	}
	return out;
}
void playlist::TfromString(string input){
	string tmp=input;
	string one;
	string two;
	PTime start;
	PTime stop;
	while(strstr(tmp.c_str(),",")!=NULL){
	  one=tmp.substr(0,tmp.find(","));
	  tmp=tmp.substr(tmp.find(",")+1);
	  two=tmp.substr(0,tmp.find(","));
	  tmp=tmp.substr(tmp.find(",")+1);
	  start.fromString(one);
	  stop.fromString(two);
	  addTimesBottom(start,stop);
	}
}
void playlist::removeTime(int i){
 int c=0;
 if(i==0){return;}
 struct PTimes* prev;
 struct PTimes* tmp=playtimes;
 struct PTimes* v;
 while(tmp!=NULL){
   if(c==i){
	 v=tmp->next;   
	 free(tmp->start);
	 free(tmp->end);
	 free(tmp);
	 prev->next=v;
	 tmp=v;
	 timecount--;
   }else{
	 prev=tmp;
	 tmp=tmp->next;   
   }
   c++;	 
 }	
}


void playlist::loadFromFile(string in){//load a playlist from file
 fstream f;
 f.open(in);
 if(!f.is_open()){return;}
 string line;
 getline(f,line);
 TfromString(line);
 while(getline(f,line)){
   if(line.compare("#IDS")==0){break;}
  
    song sin("","");
    string nst=line;
    sin.fromString(nst);
    add(sin);
 }
 while(getline(f,line)){
  if(line.size()<4){break;}
  song s("","");
  s.fromString(line);
  putId(s);	 
 }
 f.close();
 
}
void playlist::saveToFile(string in){//save the playlist to file
	if(nsongs<=0){return;}
	ofstream of;
	of.open(in);
	if(!of.is_open()){return;}
	of<<TtoString()<<endl;
	struct list* songs=head;
	while(songs!=NULL){
	 of<<songs->s->toString()<<endl;
	 songs=songs->next;	
	}
	of<<"#IDS"<<endl;
	struct IDs* id=ids;
	if(nids<=0){return;}
	while(id!=NULL){
	  of<<(*(id->s)).toString()<<endl;
	  id=id->next;	
	}
	of.close();
}



