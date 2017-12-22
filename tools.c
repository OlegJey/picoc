#include "tools.h"


char* resolveVal(char* to,char * name,struct Value *Val){

		char* val = malloc(sizeof(char) * 1024);	
	
		strcpy(to,"");

	
	if(Val != NULL){
	
	
		switch(Val->Typ->Base){
		
		case 0: 
		to = "Type: Void";

		break;
//NOTE: string literals declared with char* are stored in readonly section. its necessary to use strcpy here so strcat is able to write
		case 1: 
		strcpy(to,"Int "); 
		strcat(to, name); 
		sprintf(val," = %d ",Val->Val->Integer);
		strcat(to,val);
		
		break;

		case 2: 
		strcpy(to,"Short ");
		strcat(to, name); 
		sprintf( val, " = %hd ",Val->Val->ShortInteger);
		strcat(to,val);
		break;
		
		case 3: 
		strcpy(to,"Char ");
		strcat(to, name); 
		sprintf( val, " = %c ",Val->Val->Character);
		strcat(to,val);
	
		break;

		case 4: 
		strcpy(to,"Long ");
		strcat(to, name); 
		sprintf( val, " = %ld ",Val->Val->LongInteger);
		strcat(to,val);
	
		break;

		case 5: 
		strcpy(to,"Unsigned Int ");
		strcat(to, name); 
		sprintf( val, " = %u ",Val->Val->UnsignedInteger);
		strcat(to,val);

		break;

		case 6: 
		strcpy(to,"Unsigned Short ");
		strcat(to, name); 
		sprintf( val, " = %hu ",Val->Val->UnsignedShortInteger);
		strcat(to,val);
	
		break;
		
		case 7: 
		strcpy(to,"Unsigned Char ");
		strcat(to, name); 
		sprintf( val, " = %u ",Val->Val->UnsignedCharacter);
		strcat(to,val);
	
		break;

		case 8:
		strcpy(to,"Unsigned Long ");
		strcat(to, name); 
		sprintf( val, " = %lu ",Val->Val-> UnsignedLongInteger);
		strcat(to,val);
	
		break;
		
		case 9: 
		strcpy(to,"Float ");
		strcat(to, name); 
		sprintf( val, " = %f ",Val->Val->FP);
		strcat(to,val);
		
		break;
	
		case 12: 
		strcpy(to,"Pointer ");
		strcat(to, name); 
		sprintf( val, " = %p ",Val->Val->Pointer);
		strcat(to,val);

		break;

		default: to = "Not supported Type";

		}
	
	}

	else to = "no ReturnType at this moment";
	

	free(val);
	
	
	return to;
}

char* getRunningMode(char* to, struct ParseState *Parser){

	strcpy(to,"");
	switch(Parser->Mode){

	case 0: to = "Run";
	break;
	
	case 1: to = "Skip";
	break;

	case 2: to = "Return";
	break;

	case 3: to = "CaseSearch";
	break;
	
	case 4: to = "Break";
	break;

	case 5: to = "Continue";
	break;

	case 6: to = "GoTo";
	break;

	default: to = "No RunningMode detected";

	}
	return to;
}


char* getFileName(char* to, struct ParseState *Parser){

	strcpy(to,"");
	if(Parser->FileName)
	strcpy(to,Parser->FileName);
	else to = "No FileName to display at this moment";
	
	return to;
}


char* getFuncName(char* to, struct StackFrame *Frame){

	strcpy(to,"");
	if(Frame)
	strcpy(to,Frame->FuncName);
	else to = "No FuncName to display at this moment";
	
	return to;

}




char* getRetDetails(char* to, struct StackFrame *Frame){   

	char* val = malloc(sizeof(char) * 1024);
	strcpy(to,""); 	
		
	if(NULL != Frame){
	
	
		switch(Frame->ReturnValue->Typ->Base){
		
		case 0: 
		strcpy(to,"ReturnType: Void"); 

		break;
//NOTE: string literals declared with char* are stored in readonly section. its necessary to use strcpy here so strcat is able to write
		case 1: 
		strcpy(to,"ReturnType: Int, Value: ");  
		sprintf(val,"%d",Frame->ReturnValue->Val->Integer);
		strcat(to,val);
		
		break;

		case 2: 
		strcpy(to,"ReturnType: Short, Value: ");
		sprintf( val, "%hd",Frame->ReturnValue->Val->ShortInteger);
		strcat(to,val);
		break;
		
		case 3: 
		strcpy(to,"ReturnType: Char, Value: ");
		sprintf( val, "%c",Frame->ReturnValue->Val->Character);
		strcat(to,val);
	
		break;

		case 4: 
		strcpy(to,"ReturnType: Long, Value: ");
		sprintf( val, "%ld",Frame->ReturnValue->Val->LongInteger);
		strcat(to,val);
	
		break;

		case 5: 
		strcpy(to,"ReturnType: Unsigned Int, Value: ");
		sprintf( val, "%u",Frame->ReturnValue->Val->UnsignedInteger);
		strcat(to,val);

		break;

		case 6: 
		strcpy(to,"ReturnType: Unsigned Short, Value: ");
		sprintf( val, "%hu",Frame->ReturnValue->Val->UnsignedShortInteger);
		strcat(to,val);
	
		break;
		
		case 7: 
		strcpy(to,"ReturnType: Unsigned Char, Value: ");
		sprintf( val, "%u",Frame->ReturnValue->Val->Integer);
		strcat(to,val);
	
		break;

		case 8:
		strcpy(to,"ReturnType: Unsigned Long, Value: ");
		sprintf( val, "%lu",Frame->ReturnValue->Val-> UnsignedLongInteger);
		strcat(to,val);
	
		break;
		
		case 9: 
		strcpy(to,"ReturnType: Float, Value: ");
		sprintf( val, "%f",Frame->ReturnValue->Val->FP);
		strcat(to,val);
		

		case 12: 
		strcpy(to,"ReturnType: Pointer, Value: ");
		sprintf( val, "%p",Frame->ReturnValue->Val->Pointer);
		strcat(to,val);

		break;

		default: to = "Not supported ReturnType";

		}
	
	}

	else to = "no ReturnType at this moment";

	free(val);
	
	return to;




}

int getLine(struct ParseState *Parser){

	int ret = 0;

	if(Parser)ret = Parser->Line; 
			
	return ret; 
}

char* getLineAsString(char* to, struct ParseState *Parser){
	strcpy(to,"");
	if(Parser)sprintf(to, "%d", Parser->Line);
		else to = "no Line at this Moment";

	return to;

}

int getNumParam(struct StackFrame *Frame){
	
	int ret = 0;	

	if(Frame) ret =  Frame->NumParams;

	return ret;

}


char* getNumParamAsString(char* to, struct StackFrame *Frame){
	
	strcpy(to,"");
	
	if(Frame)sprintf(to,"%d",Frame->NumParams);
	else to = "cant get NumParam";
	return to; 
}





int getScopeID(struct ParseState *Parser){

	int ret = 0;	

	if(Parser) ret = Parser->ScopeID;

	return ret;
}

char* getScopeIDAsString(char* to, struct ParseState *Parser){

	strcpy(to,"");

	if(Parser)sprintf(to,"%d",Parser->ScopeID);
	
	else to = "cant get scopeID";
	
	return to;
}


int countStackFrames(struct ParseState *Parser){

	int count = 1;
	
	struct StackFrame *current;
	
	if(Parser->pc->TopStackFrame){
			 
		current = Parser->pc->TopStackFrame;
	
		while(current->PreviousStackFrame){
		
		current = current->PreviousStackFrame;
		count++;		

		}

	}	
	
	return count;
}

void* get_HeapBottom(struct ParseState *Parser){

	if(Parser->pc)
		return Parser->pc->HeapBottom;
  	  else return NULL;

} 

void* get_HeapStackTop(struct ParseState *Parser){

	if(Parser->pc)
		return Parser->pc->HeapStackTop;	
	  else return NULL;

}

void* get_StackFrame(struct ParseState *Parser){

	if(Parser->pc)
		return Parser->pc->StackFrame;
	  else return NULL;

}

struct StackFrame* get_TopStackFrame(struct ParseState *Parser){
	
	struct StackFrame *ret;

	if(Parser->pc->TopStackFrame) ret = Parser->pc->TopStackFrame; 
	
	return ret;

}

struct StackFrame* get_PreviousStackFrame(struct ParseState *Parser){
	
	struct StackFrame *Previous = NULL; 	
		if(Parser->pc->TopStackFrame)
		{
			
			if(Parser->pc->TopStackFrame->PreviousStackFrame)
			{
				Previous = Parser->pc->TopStackFrame->PreviousStackFrame;
			}
	
		}
	
	return Previous;

}


char* getGlobalVarAndVal(char* to, struct ParseState *Parser){
	
	int Count = 0;

	char* val = malloc(sizeof(char) * 1024);
	//in fact its necessary to erase our String
	strcpy(to,""); 
	
	struct Value *wert;
	if(Parser->pc){
	
	struct Table *Tbl = &Parser->pc->GlobalTable;
	
	struct TableEntry *Entry;
	
	
		for (Count = 0; Count < Tbl->Size; Count++) {
		printf("Count Schleife\n");	
		if(Tbl->HashTable[Count] != NULL){
			
			printf("Eintrag am Start\n");
			for(Entry = Tbl->HashTable[Count]; Entry != NULL; Entry = Entry->Next){
				
				Entry = Tbl->HashTable[Count];
				printf("Eintrag zugewiesen\n");
				strcpy(val,"");
			//DAS WIRD NICHTS
					if(strcmp(Entry->p.v.Key,"remove") !=0 						&& strcmp(Entry->p.v.Key,"clearerr")!=0
					&& strcmp(Entry->p.v.Key,"")!=0
					&& Entry->p.v.Key != NULL
					&& strcmp(Entry->p.v.Key,"feof")!=0
					&& strcmp(Entry->p.v.Key,"ftell")!=0
					){
					printf("%s", Entry->p.v.Key);
					//val = resolveVal(val,Entry->p.v.Key,Entry->p.v.Val);
								
					strcat(to,val);	
					}
		
						
			
				}	
		
			}
    		}
	}
	else  to = "ERROR";
	free(val);
return to;
}


char* getLocalVarAndVal(char* to, struct StackFrame *Frame){
	
	int Count = 0;
	char* val = malloc(sizeof(char) * 1024);
	//in fact its necessary to erase our String
	strcpy(to,"");
		
	if(Frame != NULL){
	
	struct Table *Tbl = &Frame->LocalTable;
	
	struct TableEntry *Entry;	
	
		for (Count = 0; Count < Tbl->Size; Count++) {
	
		if(Tbl->HashTable[Count] != NULL){
		

			for(Entry = Tbl->HashTable[Count]; Entry != NULL; Entry = Entry->Next){
			
				Entry = Tbl->HashTable[Count];
			
				strcpy(val,"");
			
					if(strcmp(Entry->p.v.Key,"") != 0){
					val = resolveVal(val,Entry->p.v.Key,Entry->p.v.Val);
					strcat(to,val);
					}
		
							
				
				}	
			
			}
    		}

	}

	else  to = "ERROR";
	
	free(val);

return to;
}

//not working yet
struct ParseState* getOldParser(struct ParseState *Parser){
		
	struct ParseState *old;


	if(Parser->pc->TopStackFrame){

		if(&Parser->pc->TopStackFrame->ReturnParser != NULL){
			old = &Parser->pc->TopStackFrame->ReturnParser;
		}
		
	}
	else old = NULL;
	
	return old;
}















