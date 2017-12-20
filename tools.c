#include "tools.h"




char* getRunningMode(char* to, struct ParseState *Parser){


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


	if(Parser->FileName)
	strcpy(to,Parser->FileName);
	else to = "No FileName to display at this moment";
	
	return to;
}

char* getRetDetails(char* to, struct ParseState *Parser){   

	char* val = malloc(sizeof(char) * 1024);	
		
	if(Parser->pc->TopStackFrame){
	
	
		switch(Parser->pc->TopStackFrame->ReturnValue->Typ->Base){
		
		case 0: 
		to = "ReturnType: Void";

		break;
//NOTE: string literals declared with char* are stored in readonly section. its necessary to use strcpy here so strcat is able to write
		case 1: 
		strcpy(to,"ReturnType: Int, Value: ");  
		sprintf(val,"%d",Parser->pc->TopStackFrame->ReturnValue->Val->Integer);
		strcat(to,val);
		
		break;

		case 2: 
		strcpy(to,"ReturnType: Short, Value: ");
		sprintf( val, "%hd",Parser->pc->TopStackFrame->ReturnValue->Val->ShortInteger);
		strcat(to,val);
		break;
		
		case 3: 
		strcpy(to,"ReturnType: Char, Value: ");
		sprintf( val, "%c",Parser->pc->TopStackFrame->ReturnValue->Val->Character);
		strcat(to,val);
	
		break;

		case 4: 
		strcpy(to,"ReturnType: Long, Value: ");
		sprintf( val, "%ld",Parser->pc->TopStackFrame->ReturnValue->Val->LongInteger);
		strcat(to,val);
	
		break;

		case 5: 
		strcpy(to,"ReturnType: Unsigned Int, Value: ");
		sprintf( val, "%u",Parser->pc->TopStackFrame->ReturnValue->Val->UnsignedInteger);
		strcat(to,val);

		break;

		case 6: 
		strcpy(to,"ReturnType: Unsigned Short, Value: ");
		sprintf( val, "%hu",
		Parser->pc->TopStackFrame->ReturnValue->Val->UnsignedShortInteger);
		strcat(to,val);
	
		break;
		
		case 7: 
		strcpy(to,"ReturnType: Unsigned Char, Value: ");
		sprintf( val, "%u",Parser->pc->TopStackFrame->ReturnValue->Val->Integer);
		strcat(to,val);
	
		break;

		case 8:
		strcpy(to,"ReturnType: Unsigned Long, Value: ");
		sprintf( val, "%lu",
		Parser->pc->TopStackFrame->ReturnValue->Val-> UnsignedLongInteger);
		strcat(to,val);
	
		break;
		
		case 9: 
		strcpy(to,"ReturnType: Float, Value: ");
		sprintf( val, "%f",Parser->pc->TopStackFrame->ReturnValue->Val->FP);
		strcat(to,val);
	
		break;

		default: to = "Not supported ReturnType";

		}
	
	}

	else to = "no ReturnType at this moment";

	return to;




}

int getLine(struct ParseState *Parser){

	int ret = 0;

	if(Parser)ret = Parser->Line; 
			
	return ret; 
}

char* getLineAsString(char* to, struct ParseState *Parser){

	if(Parser)sprintf(to, "%d", Parser->Line);
		else to = "no Line at this Moment";

	return to;

}

int getNumParam(struct ParseState *Parser){
	
	int ret = 0;	

	if(Parser) ret =  Parser->pc->TopStackFrame->NumParams;

	return ret;

}


char* getNumParamAsString(char* to, struct ParseState *Parser){

	if(Parser->pc->TopStackFrame)sprintf(to,"%d", Parser->pc->TopStackFrame->NumParams);
	else to = "cant get NumParam";
	return to; 
}





int getScopeID(struct ParseState *Parser){

	int ret = 0;	

	if(Parser) ret = Parser->ScopeID;

	return ret;
}

char* getScopeIDAsString(char* to, struct ParseState *Parser){

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
	
	struct StackFrame *ret;

	if(Parser->pc->TopStackFrame->PreviousStackFrame) 
	ret = Parser->pc->TopStackFrame->PreviousStackFrame; 
	
	return ret;

}


char* getGlobalVarAndVal(char* to, struct ParseState *Parser){



return to;
}


char* getLocalVarAndVal(char* to, struct ParseState *Parser){
/*
	short int declLine = 0;

	if(Parser->pc->TopStackFrame){
	
	struct Table Tbl = Parser->pc->TopStackFrame->LocalTable;
	
	int HashValue = ((unsigned long)Key) % Tbl->Size;
    
	struct TableEntry *Entry;	
	
	// for (Entry = Tbl->HashTable[HashValue]; Entry != NULL; Entry = Entry->Next) {
        
            
    //}	


	}

	
	sprintf(to,"%d", declLine);
*/

return to;
}


void printStrTbl(Picoc *pc)
{
    int Count;
    struct TableEntry *Entry;
    struct TableEntry *NextEntry;

    for (Count = 0; Count < pc->StringTable.Size; Count++) {
        for (Entry = pc->StringTable.HashTable[Count];
                Entry != NULL; Entry = NextEntry) {
            NextEntry = Entry->Next;
           //	printf("%s, %d\n", Entry->p.v.Key, Count);
        }
    }
}















