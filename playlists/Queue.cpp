#include "Queue.h"
//queue generator algorithm to avoid repetition
//original code by Evan Nikitin


int Queue::exists(song sin){//song exists in the playlist
	struct list* nn=toplay;
	int c=0;
	while(nn!=NULL){
	 song s=*(nn->s);
	 if(s.getPath().compare(sin.getPath())==0){
	   return 1;	 
	 }
	 c++;
	 nn=nn->next;	
	}
	return -1;
}
int Queue::compareS(song s1,song s2){//compare two songs
	if(s1.toString().compare(s2.toString())==0){
	   return 1;	 
	 }
	 return -1;
}
void Queue::add(song s){
 song* ss=(song*)malloc(sizeof(song));
 new(ss) song(s.getName(),s.getPath());
 struct list* nitm=(struct list*)malloc(sizeof(struct list));
 nitm->s=ss;
 nitm->prev=NULL;
 if(toplay!=NULL){
  toplay->prev=nitm;	 
 }
 nitm->next=toplay;
 toplay=nitm;
}


Queue::Queue(playlist in,int songbid,song prev){
	//algoritm to generate the queue
	//checks if a song is in the queue and does not put it in unless the playslist size is less than the queue size
	//IDs can repeat
	//songs can not repeat
	int Qsize=PRE_QUEUE_SIZE;
	toplay=NULL;
	if(songbid==-1){return;}
	int nsongs=in.countSongs();
	if(nsongs<40){Qsize=nsongs;}
	if(Qsize<10){Qsize=10;}
	int nids=in.countIDs();
	int count=0;
	int scount=0;
	int c=0;
	string prevpath=prev.getPath();
	while(count<Qsize){
	 if(nids!=0){
	 int idinde=rand()%nids;
	 song id=in.getID(idinde);
	 if(scount>=songbid){
	  scount=0;
	  c=0;
	  while(exists(id)!=-1){
		 c++;
		 
		 idinde=rand()%nids;
		 //id.empty();
		 id=in.getID(idinde);
		 if(nids<Qsize){
		  if(c>10){break;}
		 }
	  }
	  add(id );
	  //id.empty();
     }
     }
     if(nsongs!=0){
	 scount++;
	 c=0;
	 int sinde=rand()%nsongs;
	 song s=in.getAt(sinde);
	 while(exists(s)==1||prevpath.compare(s.getPath())==0){
		 sinde=rand()%nsongs;
		 //s.empty();
		 
		 s=in.getAt(sinde);
		
		 c++;
		 if(nsongs<Qsize){
		  if(prevpath.compare(s.getPath())!=0){break;}else{c=0;}
		  if(c>10){break;};
	     }
	  }
	 
	  prevpath=s.getPath();
	  add(s);
      }
	//  s.empty();
	 count++;	
	}
	
}
int Queue::canNext(){
    if(toplay==NULL){
		return -1;
	}
	return 1;
}
song Queue::returnTracker(){//return the last song in the list to avoid repetition
 struct list* l=toplay;
 song spull=*(l->s);
 return spull;	
}
song Queue::getNext(){//get next song
	struct list *traver=toplay;
	struct list* tmp;
	while(traver!=NULL){
	 tmp=traver;
	 traver=traver->next;	
	}
	if(tmp->prev!=NULL){
	 (tmp->prev)->next=NULL;
    }else{
	  toplay=NULL;	
	}
    song* s=tmp->s;
    free(tmp);
	song sret(s->getName(),s->getPath());
	s->empty();
    free(s);
	return sret;
}
void Queue::clear(){//free memmory
 struct list* l=toplay;
 struct list* tmp;
 while(l!=NULL){
  tmp=l->next;
  l->s->empty();
  free(l->s);
  free(l);
  l=tmp;	 
 }
}
