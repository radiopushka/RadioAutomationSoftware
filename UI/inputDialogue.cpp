#include <ncurses.h>

//input functions
//original code by Evan Nikitin

string Prompt(string text,string prev){
	curs_set(1);
	string ret="";
	int c=0;
	char* inputsequence=(char*)malloc(COLS*sizeof(char));
	int len=prev.length();
	if(len>COLS-2){
		prev=prev.substr(0,COLS-2);
	}
	strcpy(inputsequence,prev.c_str());
	int length=len;
	while(c!='\n'){
	 clear();
	 printw("\n ");
	 printw(text.c_str());
	 printw("\n ");
	 printw(inputsequence); 
	 box(stdscr,'*','*');
	 c=getch();
	 if(c=='\n'){break;}
	 if(c==KEY_BACKSPACE){
	   if(length>0){
		inputsequence[length-1]=0;
		length--;   
	   }	 
	 }else{
	  inputsequence[length]=c;
	  inputsequence[length+1]=0;
	  length++;
	  if(length>COLS-2){length--;}
     }
	}
	curs_set(0);
	char output[length+1];
	strcpy(output,inputsequence);
	ret=string(output);
	free(inputsequence);
	return ret;
}

string PromptFilename(string text,string prev){
	curs_set(1);
	string ret="";
	const char* notallowed=" /\\+=()*&^%$#@!~`\"'.,?|{};:<>";
	int nal=strlen(notallowed);
	int i;
	int c=0;
	char* inputsequence=(char*)malloc(COLS*sizeof(char));
	int len=prev.length();
	if(len>COLS-2){
		prev=prev.substr(0,COLS-2);
	}
	strcpy(inputsequence,prev.c_str());
	int length=len;
	while(c!='\n'){
	 clear();
	 printw("\n ");
	 printw(text.c_str());
	 printw("\n ");
	 printw(inputsequence); 
	 box(stdscr,'*','*');
	 c=getch();
	 for(i=0;i<nal;i++){
	   if(c==notallowed[i]){
		 c='_';   
	   }	 
	 }
	 if(c=='\n'){break;}
	 if(c==KEY_BACKSPACE){
	   if(length>0){
		inputsequence[length-1]=0;
		length--;   
	   }	 
	 }else{
	  inputsequence[length]=c;
	  inputsequence[length+1]=0;
	  length++;
	  if(length>COLS-2){length--;}
     }
	}
	curs_set(0);
	char output[length+1];
	strcpy(output,inputsequence);
	ret=string(output);
	free(inputsequence);
	return ret;
}
string Prompt(string text,string prev,char* charset){
	curs_set(1);
	string ret="";
	int nal=strlen(charset);
	int i;
	int write=1;
	int c=0;
	char* inputsequence=(char*)malloc(COLS*sizeof(char));
	int len=prev.length();
	if(len>COLS-2){
		prev=prev.substr(0,COLS-2);
	}
	strcpy(inputsequence,prev.c_str());
	int length=len;
	while(c!='\n'){
	 write=1;
	 clear();
	 printw("\n ");
	 printw(text.c_str());
	 printw("\n ");
	 printw(inputsequence); 
	 box(stdscr,'*','*');
	 c=getch();
	 for(i=0;i<nal;i++){
	   if(c==charset[i]){
		   write=0;
		   break;
	   }	 
	 }
	 if(c=='\n'){break;}
	 if(c==KEY_BACKSPACE){
	   if(length>0){
		inputsequence[length-1]=0;
		length--;   
	    
	   }	 
	 }else{
	  if(write==0){
	   inputsequence[length]=c;
	   inputsequence[length+1]=0;
	   length++;
	  }
	  if(length>COLS-2){length--;}
     }
	}
	curs_set(0);
	char output[length+1];
	strcpy(output,inputsequence);
	ret=string(output);
	free(inputsequence);
	return ret;
}
int PromptInt(string display,int value,int max,int min){
	int output=value;
    int c=0;
    while(c!='\n'&&c!='q'){
	  clear();
	  printw("%s\n\n",display.c_str());
	  printw(">     ");
	  attron(A_STANDOUT);
	  printw("%d\n",output);
	  attroff(A_STANDOUT);
	  c=getch();
	  if(c=='w'||c==KEY_UP){
		output++;
		if(output>max){output=max;}
	  }	
	  if(c=='s'||c==KEY_DOWN){
		  output--;
		  if(output<min){output=min;}
	  }
	}
	if(c=='q'){return -1;}
	return output;
}
void PromptIntP(string display,volatile int* value,int max,int min){
	int output=*value;
	int initial=*value;
    int c=0;
    while(c!='\n'&&c!='q'){
	  clear();
	  printw("%s\n\n",display.c_str());
	  printw(">     ");
	  attron(A_STANDOUT);
	  printw("%d\n",output);
	  attroff(A_STANDOUT);
	  c=getch();
	  if(c=='w'||c==KEY_UP){
		output++;
		if(output>max){output=max;}
	  }	
	  if(c=='s'||c==KEY_DOWN){
		  output--;
		  if(output<min){output=min;}
	  }
	  *value=output;
	}
	if(c=='q'){*value=initial;}
	
}

