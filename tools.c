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
		printf("Moin  \n");
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












