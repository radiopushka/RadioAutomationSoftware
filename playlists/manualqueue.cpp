#include "manualqueue.h"

void MQueue::add(string name,string path){
 struct QList* element=(struct QList*)malloc(sizeof(struct QList));
 song* s=(song*) malloc(sizeof(song));
 new(s) song(name,path);
 element->s=s;
 element->next=NULL;
 if(head==NULL){
  head=element;
 }else{
   struct QList* tmp=head;
   while(tmp->next!=NULL){
    tmp=tmp->next;
   }
   tmp->next=element;
 }
 size++;
}

void MQueue::play(Mixer* m){
 if(head==NULL){return;}
 struct QList* tmp=head;
 head=head->next;
 song* s=tmp->s;
 s->play(m);
 s->empty();
 free(s);
 free(tmp);
 size--;
}
unsigned int MQueue::Size(){
 return size;
}
string MQueue::nameAt(int i){
   struct QList* tmp=head;
   int c=0;
   while(tmp!=NULL){
    if(c==i){
      return tmp->s->getName();
    }
    c++;
    tmp=tmp->next;
   }
  return "(one is now playing)";
}
void MQueue::close(){
   struct QList* tmp=head;
   struct QList* qh;
   while(tmp!=NULL){
    qh=tmp->next;
    tmp->s->empty();
    free(tmp->s);
    free(tmp);
    tmp=qh;
   }
  size=0;
  head=NULL;
}
