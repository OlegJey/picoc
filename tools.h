// collection of some functions we might need for the visualisation of PicoC
// not fully tested


#include "picoc.h" // this already includes many powerful standard libs like string.h or math.h



extern char* getRetDetails(char* to, struct ParseState *Parser); //done

extern char* getRunningMode(char* to, struct ParseState *Parser); //done

extern char* getFileName(char* to, struct ParseState *Parser); //done

extern char* getLocalVarAndVal(char* to, struct ParseState *Parser); // TBD!!

extern void* get_HeapBottom(struct ParseState *Parser); //For Pro Mode

extern void* get_HeapStackTop(struct ParseState *Parser);

extern void* get_StackFrame(struct ParseState *Parser);

extern struct StackFrame* get_TopStackFrame(struct ParseState *Parser);

extern void* get_PreviousStackFrame(struct ParseState *Parser);

extern int getLine(struct ParseState *Parser);

extern int getNumP(struct ParseState *Parser);

extern int getScopeID(struct ParseState *Parser);

extern int countStackFrames(struct ParseState *Parser);  




struct Model {


struct StackFrame *TopStackFr;


char* fileName;

char* funcName;

char* runMode;

char* localVarAndVal;

int line;

int scopeID;

int NumP;

void* HeapBottom;

void* HeapStackTop;

void* StackFrame;


};





