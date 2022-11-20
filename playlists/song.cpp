#include "song.h"
#include<iostream>
//original code by Evan Nikitin
song::song(){
 name=NULL;
 path=NULL;	
}

song::song(string nameofs,string pathofs){//same as set but no free command
 const char* namecp=nameofs.c_str();
 name=(char*)malloc((strlen(namecp)+1)*sizeof(char));
 char *np=name;
 strcpy(np,namecp);
 const char* pathptr=pathofs.c_str();
 path=(char*)malloc((strlen(pathptr)+1)*sizeof(char));
 char *pp=path;
 strcpy(pp,pathptr);
}
void song::empty(){
 
if(name!=NULL){
 free(name);
 name=NULL;
}
if(path!=NULL){
 free(path);	
 path=NULL;
}

}
void song::fromString(string in){
 const char *cp=in.c_str();
 char *cst=(char*)malloc(sizeof(char)*(strlen(cp)+1));
 strcpy(cst,cp);
 char *strtp;
 char *endp=strstr(cst,"\\");
 char *output=(char*)malloc(sizeof(char)*(strlen(cst)+1));
 char *ptoutput=output;
 for(strtp=cst;strtp<endp;strtp++){//all chracaters left of separator char are the name
   	 *ptoutput=*strtp;
   	 ptoutput++;
 }	
 *ptoutput='\0';
 ptoutput=output;
  
 string namep(output);//set only accepts string so it needs to be converted to a string
 endp=cst+strlen(cst)*sizeof(char);
 for(strtp=strstr(cst,"\\")+1;strtp<endp;strtp++){// all characters right of separator char are the path
   	 *ptoutput=*strtp;
   	 ptoutput++;
 }	
 *ptoutput='\0';
 ptoutput=output;
 string s(output);
 string paths=s;
 free(output);
 free(cst);
 set(namep,paths);
}
string song::toString(){
 char *ptn=name;
 char *ptp=path;
 return ""+string(ptn)+"\\"+string(ptp)+"";	
}
void song::play(Mixer* input){
	//cout<<getPath()<<endl; debug point
	if(path[strlen(path)-1]=='g'){
		input->playOgg(getPath());
	}else{
	  input->play(getPath());
    }
}
string song::getName(){//all getters convert the value in the heap under the memory pointer to a string in the stack memory.
 if(name==NULL){return "";}
 char* ptn=name;
 return string(ptn);	
}
string song::getPath(){
 if(path==NULL){return "";}
 char *ptn=path;
 return string(ptn);	
}
void song::set(string nameofs,string pathofs){//universal set method
 empty();
 const char* namecp=nameofs.c_str();
 name=(char*)malloc((strlen(namecp)+1)*sizeof(char));
 char *np=name;
 strcpy(np,namecp);
 const char* pathptr=pathofs.c_str();
 path=(char*)malloc((strlen(pathptr)+1)*sizeof(char));
 char *pp=path;
 strcpy(pp,pathptr);
}
