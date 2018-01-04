#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#include "picoc.h"
#include "tools.h"

#ifndef GUI_H
#define GUI_H


extern int gui_handler();
extern int init_gui();
extern int refresh_gui(struct ParseState *Parser);
extern int kill_gui();
extern sfText *getText(sfVector2f pos, char *string, sfFont *font, int size, sfColor color);

sfRenderWindow* window;
sfVideoMode vmode;

sfEvent event;

sfFont *font;

sfText *code;
sfText *lineNumbers;

sfVector2f codePos;
sfVector2f lineNumbersPos;

sfText *nextStep;
sfVector2f nextStepPos;

sfText *fileName;
sfVector2f fileNamePos;

sfText *runningMode;
sfVector2f runningModePos;

sfText *executedLine;
sfVector2f executedLinePos;

sfRectangleShape *infoBlock;
sfVector2f infoBlockSize;
sfVector2f infoBlockPos;

sfRectangleShape *stackframe1;
sfVector2f stackframe1Size;
sfVector2f stackframe1Pos;

sfRectangleShape *stackframe2;
sfVector2f stackframe2Pos;

sfRectangleShape *stackframe3;
sfVector2f stackframe3Pos;

sfRectangleShape *stackframe4;
sfVector2f stackframe4Pos;

sfRectangleShape *stackframe5;
sfVector2f stackframe5Pos;

sfVector2f stackFrameText1Pos;
sfVector2f stackFrameText2Pos;
sfVector2f stackFrameText3Pos;
sfVector2f stackFrameText4Pos;
sfVector2f stackFrameText5Pos;


// Stackframe 1
sfText *stackFrameText1;

sfVector2f functionNameSF1Pos;
char *funcNameSF1;
char *funcNameBuffer1;
sfText *functionNameSF1;

sfVector2f parameterCountPos1;
char *paramCount1;
char *paramBuffer1;
sfText *parameterCount1;

sfVector2f returnTypePos1;
char *currentReturnType1;
char *returnTypeBuffer1;

sfText *returnType1;
sfVector2f localVarPos1;
char *currentlocalVar1; 
char *localVarBuffer1;

sfText *localVar1;

sfVector2f returnAddressPos1;
char *currentreturnAddress1;
char *currentAddressBuffer1;

sfText *returnAddress1;

// Stackframe 2
sfText *stackFrameText2;

sfVector2f functionNameSF2Pos;
char *funcNameSF2;
char *funcNameBuffer2;
sfText *functionNameSF2;

sfVector2f parameterCountPos2;
char *paramCount2;
char *paramBuffer2;
sfText *parameterCount2;

sfVector2f returnTypePos2;
char *currentReturnType2;
char *returnTypeBuffer2;

sfText *returnType2;

sfVector2f localVarPos2;
char *currentlocalVar2;
char *localVarBuffer2;

sfText *localVar2;

sfVector2f returnAddressPos2;
char *currentreturnAddress2;
char *currentAddressBuffer2;

sfText *returnAddress2;


// Stackframe 3
sfText *stackFrameText3;

sfVector2f functionNameSF3Pos;
char *funcNameSF3;
char *funcNameBuffer3;
sfText *functionNameSF3;

sfVector2f parameterCountPos3;
char *paramCount3;
char *paramBuffer3;
sfText *parameterCount3;

sfVector2f returnTypePos3;
char *currentReturnType3;
char *returnTypeBuffer3;

sfText *returnType3;

sfVector2f localVarPos3;
char *currentlocalVar3;
char *localVarBuffer3;

sfText *localVar3;

sfVector2f returnAddressPos3;
char *currentreturnAddress3;
char *currentAddressBuffer3;

sfText *returnAddress3;

// Stackframe 4
sfText *stackFrameText4;

sfVector2f functionNameSF4Pos; 
char *funcNameSF4;
char *funcNameBuffer4;
sfText *functionNameSF4;

sfVector2f parameterCountPos4;
char *paramCount4;
char *paramBuffer4;
sfText *parameterCount4;

sfVector2f returnTypePos4;
char *currentReturnType4;
char *returnTypeBuffer4;

sfText *returnType4;

sfVector2f localVarPos4;
char *currentlocalVar4; 
char *localVarBuffer4; 

sfText *localVar4;

sfVector2f returnAddressPos4;
char *currentreturnAddress4;
char *currentAddressBuffer4;

sfText *returnAddress4;

// Stackframe 5
sfText *stackFrameText5; 

sfVector2f functionNameSF5Pos;
char *funcNameSF5;
char *funcNameBuffer5;
sfText *functionNameSF5;

sfVector2f parameterCountPos5; 
char *paramCount5;
char *paramBuffer5;
sfText *parameterCount5;

sfVector2f returnTypePos5; 
char *currentReturnType5; 
char *returnTypeBuffer5;

sfText *returnType5;

sfVector2f localVarPos5; 
char *currentlocalVar5;
char *localVarBuffer5;

sfText *localVar5;

sfVector2f returnAddressPos5; 
char *currentreturnAddress5;
char *currentAddressBuffer5;

sfText *returnAddress5;


// Read File
char *fname;
FILE *file;
char line[256];
char *sourceCode;
int lineCount;

char *lineNumbersStr;
char buffer[12];

char *fileNameChar;
char *val1;

char *runModeString;
char *val2;

char *currentLineString;
char *val3;








#endif






