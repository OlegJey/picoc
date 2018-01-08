
#include "gui.h"



sfText *getText(sfVector2f pos, char *string, sfFont *font, int size, sfColor color) {
    sfText *text;
    text = sfText_create();
    sfText_setString(text, string);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, color);
    sfText_setPosition(text, pos);
    return text;
}

sfVector2f getVector(int x, int y) {
	sfVector2f temp = {x,y};
	return temp;
}

int gui_handler() {

	if(window != NULL)
		return kill_gui();
	else
		return init_gui();
}

int init_gui() {
	
	/* Create the main window */

	vmode.width = 1200;
	vmode.height = 600;
	vmode.bitsPerPixel = 32;
	
	window = sfRenderWindow_create(vmode, "PicoC GUI", sfResize | sfClose, NULL);
	if (!window)
	    return -1;
	sfRenderWindow_setFramerateLimit(window, 60);

	// Set Vector Positions
	codePos = getVector(50, 70);   
	lineNumbersPos = getVector(20, 70);
    nextStepPos = getVector(800, 11);
    fileNamePos = getVector(802, 46);
    runningModePos = getVector(802, 71);
    executedLinePos = getVector(802, 96);    
    infoBlockSize = getVector(500, 80);
    infoBlockPos = getVector(800, 40);
    stackframe1Size = getVector(500, 100);
    stackframe1Pos = getVector(800, 120);
    stackframe2Pos = getVector(800, 220);
    stackframe3Pos = getVector(800, 320);
    stackframe4Pos = getVector(800, 420);
    stackframe5Pos = getVector(800, 520);
    stackFrameText1Pos = getVector(802, 121);
    stackFrameText2Pos = getVector(802, 221);
    stackFrameText3Pos = getVector(802, 321);
    stackFrameText4Pos = getVector(802, 421);
    stackFrameText5Pos = getVector(802, 521);

	// Create Shapes
    infoBlock = sfRectangleShape_create();
    sfRectangleShape_setSize(infoBlock, infoBlockSize);
    sfRectangleShape_setFillColor(infoBlock, sfCyan);
    sfRectangleShape_setPosition(infoBlock, infoBlockPos);
    sfRectangleShape_setOutlineColor(infoBlock, sfBlack);
    sfRectangleShape_setOutlineThickness(infoBlock, 2.0);

    stackframe1 = sfRectangleShape_create();
    sfRectangleShape_setSize(stackframe1, stackframe1Size);
    sfRectangleShape_setFillColor(stackframe1, sfGreen);
    sfRectangleShape_setPosition(stackframe1, stackframe1Pos);
    sfRectangleShape_setOutlineColor(stackframe1, sfBlack);
    sfRectangleShape_setOutlineThickness(stackframe1, 2.0);

    stackframe2 = sfRectangleShape_create();
    sfRectangleShape_setSize(stackframe2, stackframe1Size);
    sfRectangleShape_setFillColor(stackframe2, sfRed);
    sfRectangleShape_setPosition(stackframe2, stackframe2Pos);
    sfRectangleShape_setOutlineColor(stackframe2, sfBlack);
    sfRectangleShape_setOutlineThickness(stackframe2, 2.0);

    stackframe3 = sfRectangleShape_create();
    sfRectangleShape_setSize(stackframe3, stackframe1Size);
    sfRectangleShape_setFillColor(stackframe3, sfGreen);
    sfRectangleShape_setPosition(stackframe3, stackframe3Pos);
    sfRectangleShape_setOutlineColor(stackframe3, sfBlack);
    sfRectangleShape_setOutlineThickness(stackframe3, 2.0);

    stackframe4 = sfRectangleShape_create();
    sfRectangleShape_setSize(stackframe4, stackframe1Size);
    sfRectangleShape_setFillColor(stackframe4, sfRed);
    sfRectangleShape_setPosition(stackframe4, stackframe4Pos);
    sfRectangleShape_setOutlineColor(stackframe4, sfBlack);
    sfRectangleShape_setOutlineThickness(stackframe4, 2.0);

    stackframe5 = sfRectangleShape_create();
    sfRectangleShape_setSize(stackframe5, stackframe1Size);
    sfRectangleShape_setFillColor(stackframe5, sfGreen);
    sfRectangleShape_setPosition(stackframe5, stackframe5Pos);
    sfRectangleShape_setOutlineColor(stackframe5, sfBlack);
    sfRectangleShape_setOutlineThickness(stackframe5, 2.0);

    /* Create a graphical text to display */
    font = sfFont_createFromFile("arial.ttf");
    if (!font)
        return 1;

    return 0;
}

int kill_gui() {

    // Cleanup resources
    sfText_destroy(nextStep);
    sfText_destroy(code);
	sfText_destroy(lineNumbers);
    sfText_destroy(fileName);
    sfText_destroy(runningMode);
    sfText_destroy(executedLine);

    sfRectangleShape_destroy(infoBlock);
    sfRectangleShape_destroy(stackframe1);
    sfRectangleShape_destroy(stackframe2);
    sfRectangleShape_destroy(stackframe3);
    sfRectangleShape_destroy(stackframe4);
    sfRectangleShape_destroy(stackframe5);


	// Stackframe 1
	sfText_destroy(stackFrameText1);
	free(funcNameSF1);
	free(funcNameBuffer1);
	sfText_destroy(functionNameSF1);
	free(paramCount1);
	free(paramBuffer1);
	sfText_destroy(parameterCount1);
	free(currentReturnType1);
	free(returnTypeBuffer1);
	sfText_destroy(returnType1);
	free(currentlocalVar1); 
	free(localVarBuffer1);
	sfText_destroy(localVar1);
	free(currentreturnAddress1);
	free(currentAddressBuffer1);
	sfText_destroy(returnAddress1);

	// Stackframe 2
	sfText_destroy(stackFrameText2);
	free(funcNameSF2);
	free(funcNameBuffer2);
	sfText_destroy(functionNameSF2);
	free(paramCount2);
	free(paramBuffer2);
	sfText_destroy(parameterCount2);
	free(currentReturnType2);
	free(returnTypeBuffer2);
	sfText_destroy(returnType2);
	free(currentlocalVar2);
	free(localVarBuffer2);
	sfText_destroy(localVar2);
	free(currentreturnAddress2);
	free(currentAddressBuffer2);
	sfText_destroy(returnAddress2);

	// Stackframe 3
	sfText_destroy(stackFrameText3);
	free(funcNameSF3);
	free(funcNameBuffer3);
	sfText_destroy(functionNameSF3);
	free(paramCount3);
	free(paramBuffer3);
	sfText_destroy(parameterCount3);
	free(currentReturnType3);
	free(returnTypeBuffer3);
	sfText_destroy(returnType3);
	free(currentlocalVar3);
	free(localVarBuffer3);
	sfText_destroy(localVar3);
	free(currentreturnAddress3);
	free(currentAddressBuffer3);
	sfText_destroy(returnAddress3);

	// Stackframe 4
	sfText_destroy(stackFrameText4);
	free(funcNameSF4);
	free(funcNameBuffer4);
	sfText_destroy(functionNameSF4);
	free(paramCount4);
	free(paramBuffer4);
	sfText_destroy(parameterCount4);
	free(currentReturnType4);
	free(returnTypeBuffer4);
	sfText_destroy(returnType4);
	free(currentlocalVar4); 
	free(localVarBuffer4); 
	sfText_destroy(localVar4);
	free(currentreturnAddress4);
	free(currentAddressBuffer4);
	sfText_destroy(returnAddress4);

	// Stackframe 5
	sfText_destroy(stackFrameText5); 
	free(funcNameSF5);
	free(funcNameBuffer5);
	sfText_destroy(functionNameSF5);
	free(paramCount5);
	free(paramBuffer5);
	sfText_destroy(parameterCount5);
	free(currentReturnType5); 
	free(returnTypeBuffer5);
	sfText_destroy(returnType5);
	free(currentlocalVar5);
	free(localVarBuffer5);
	sfText_destroy(localVar5);
	free(currentreturnAddress5);
	free(currentAddressBuffer5);
	sfText_destroy(returnAddress5);

	// Read File
	free(fname);
	free(file);
	free(sourceCode);
	free(lineNumbersStr);
	free(fileNameChar);
	free(val1);
	free(runModeString);
	free(val2);
	free(currentLineString);
	free(val3);



	sfFont_destroy(font);

    sfRenderWindow_destroy(window);

	return 0;
}



int refresh_gui(struct ParseState *Parser) {
	
	// Clear the screen
	sfRenderWindow_clear(window, sfWhite); //sfColor_fromRGBA(49, 60, 72, 1.0));

    //STACKRFAME 1
    stackFrameText1 = getText(stackFrameText1Pos, "Stackframe 1", font, 13, sfBlack);

    functionNameSF1Pos = getVector(802, 137);
   /*  funcNameSF1 = calloc(1024, sizeof(char));     //Speicherzugriffsfehler
    strcpy(funcNameSF1, "Funktionsname: ");
    funcNameBuffer1 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer1, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF1, funcNameBuffer1); */
    functionNameSF1 = getText(functionNameSF1Pos, "Funktionsname: ", font, 13, sfBlack); 

    parameterCountPos1 = getVector(802, 153);
    paramCount1 = calloc(1024, sizeof(char));
    strcpy(paramCount1, "Anzahl Parameter: ");
    paramBuffer1 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer1, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount1, paramBuffer1);
    parameterCount1 = getText(parameterCountPos1, paramCount1, font, 13, sfBlack);

    returnTypePos1 = getVector(802, 169);
    currentReturnType1 = calloc(1024, sizeof(char));
    strcpy(currentReturnType1, "Rueckgabetyp: ");
    returnTypeBuffer1 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer1, Parser->pc->TopStackFrame);
    strcat(currentReturnType1, returnTypeBuffer1);
    returnType1 = getText(returnTypePos1, currentReturnType1, font, 13, sfBlack);

    localVarPos1 = getVector(802, 185);
    currentlocalVar1 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar1, "Lokale Variablen: ");
    localVarBuffer1 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer1, Parser->pc->TopStackFrame);
    strcat(currentlocalVar1, localVarBuffer1);
    localVar1 = getText(localVarPos1, currentlocalVar1, font, 13, sfBlack);

    returnAddressPos1 = getVector(802, 201);
    currentreturnAddress1 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress1, "Returndetails: ");
    currentAddressBuffer1 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer1, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress1, currentAddressBuffer1);
    returnAddress1 = getText(returnAddressPos1, currentreturnAddress1, font, 13, sfBlack);

    //STACKFRAME 2

    stackFrameText2 = getText(stackFrameText2Pos, "Stackframe 2", font, 13, sfBlack);

    functionNameSF2Pos = getVector(802, 237);
/*     funcNameSF2 = calloc(1024, sizeof(char));
    strcpy(funcNameSF2, "Funktionsname: ");
    funcNameBuffer2 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer2, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF2, funcNameBuffer2); */
    functionNameSF2 = getText(functionNameSF2Pos, "Funktionsname: ", font, 13, sfBlack); //Speicherzugriffsfehler

    parameterCountPos2 = getVector(802, 253);
    paramCount2 = calloc(1024, sizeof(char));
    strcpy(paramCount2, "Anzahl Parameter: ");
    paramBuffer2 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer2, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount2, paramBuffer2);
    sfText *parameterCount2 = getText(parameterCountPos2, paramCount2, font, 13, sfBlack);

    returnTypePos2 = getVector(802, 269);
    currentReturnType2 = calloc(1024, sizeof(char));
    strcpy(currentReturnType2, "Rueckgabetyp: ");
    returnTypeBuffer2 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer2, Parser->pc->TopStackFrame);
    strcat(currentReturnType2, returnTypeBuffer2);
    returnType2 = getText(returnTypePos2, currentReturnType1, font, 13, sfBlack);

    localVarPos2 = getVector(802, 285);
    currentlocalVar2 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar2, "Lokale Variablen: ");
    localVarBuffer2 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer2, Parser->pc->TopStackFrame);
    strcat(currentlocalVar2, localVarBuffer2);
    localVar2 = getText(localVarPos2, currentlocalVar2, font, 13, sfBlack);

    returnAddressPos2 = getVector(802, 301);
    currentreturnAddress2 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress2, "Returndetails: ");
    currentAddressBuffer2 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer2, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress2, currentAddressBuffer2);
    sfText *returnAddress2 = getText(returnAddressPos2, currentreturnAddress2, font, 13, sfBlack);

    //STACKFRAME 3
    stackFrameText3 = getText(stackFrameText3Pos, "Stackframe 3", font, 13, sfBlack);

    functionNameSF3Pos = getVector(802, 337);
/*     funcNameSF3 = calloc(1024, sizeof(char));
    strcpy(funcNameSF3, "Funktionsname: ");
    funcNameBuffer3 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer3, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF3, funcNameBuffer3); */
    functionNameSF3 = getText(functionNameSF3Pos, "Funktionsname: ", font, 13, sfBlack); //Speicherzugriffsfehler

    parameterCountPos3 = getVector(802, 353);
    paramCount3 = calloc(1024, sizeof(char));
    strcpy(paramCount3, "Anzahl Parameter: ");
    paramBuffer3 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer3, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount3, paramBuffer3);
    parameterCount3 = getText(parameterCountPos3, paramCount3, font, 13, sfBlack);

    returnTypePos3 = getVector(802, 369);
    currentReturnType3 = calloc(1024, sizeof(char));
    strcpy(currentReturnType3, "Rueckgabetyp: ");
    returnTypeBuffer3 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer3, Parser->pc->TopStackFrame);
    strcat(currentReturnType3, returnTypeBuffer3);
    returnType3 = getText(returnTypePos3, currentReturnType3, font, 13, sfBlack);

    localVarPos3 = getVector(802, 385);
    currentlocalVar3 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar3, "Lokale Variablen: ");
    localVarBuffer3 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer3, Parser->pc->TopStackFrame);
    strcat(currentlocalVar3, localVarBuffer3);
    localVar3 = getText(localVarPos3, currentlocalVar3, font, 13, sfBlack);

    returnAddressPos3 = getVector(802, 401);
    currentreturnAddress3 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress3, "Returndetails: ");
    currentAddressBuffer3 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer3, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress3, currentAddressBuffer3);
    returnAddress3 = getText(returnAddressPos3, currentreturnAddress3, font, 13, sfBlack);

    //STACKFRAME 4
/*    stackFrameText4 = getText(stackFrameText4Pos, "Stackframe 4", font, 13, sfBlack);

    functionNameSF4Pos = getVector(802, 437);
    funcNameSF4 = calloc(1024, sizeof(char));
    strcpy(funcNameSF4, "Funktionsname: ");
    funcNameBuffer4 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer4, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF4, funcNameBuffer4);
    functionNameSF4 = getText(functionNameSF4Pos, "Funktionsname: ", font, 13, sfBlack); //Speicherzugriffsfehler

    parameterCountPos4 = getVector(802, 453);
    paramCount4 = calloc(1024, sizeof(char));
    strcpy(paramCount4, "Anzahl Parameter: ");
    paramBuffer4 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer4, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount4, paramBuffer4);
    parameterCount4 = getText(parameterCountPos4, paramCount4, font, 13, sfBlack);

    returnTypePos4 = getVector(802, 469);
    currentReturnType4 = calloc(1024, sizeof(char));
    strcpy(currentReturnType4, "Rueckgabetyp: ");
    returnTypeBuffer4 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer4, Parser->pc->TopStackFrame);
    strcat(currentReturnType4, returnTypeBuffer4);
    returnType4 = getText(returnTypePos4, currentReturnType4, font, 13, sfBlack);

    localVarPos4 = getVector(802, 485);
    currentlocalVar4 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar4, "Lokale Variablen: ");
    localVarBuffer4 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer4, Parser->pc->TopStackFrame);
    strcat(currentlocalVar4, localVarBuffer4);
    localVar4 = getText(localVarPos4, currentlocalVar4, font, 13, sfBlack);

    returnAddressPos4 = getVector(802, 501);
    currentreturnAddress4 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress4, "Returndetails: ");
    currentAddressBuffer4 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer4, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress4, currentAddressBuffer4);
    returnAddress4 = getText(returnAddressPos4, currentreturnAddress4, font, 13, sfBlack);

    //STACKFRAME 5
    stackFrameText5 = getText(stackFrameText5Pos, "Stackframe 5", font, 13, sfBlack);

    functionNameSF5Pos = getVector(802, 537);
    funcNameSF5 = calloc(1024, sizeof(char));
    strcpy(funcNameSF5, "Funktionsname: ");
    funcNameBuffer5 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer5, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF5, funcNameBuffer5);
    functionNameSF5 = getText(functionNameSF5Pos, "Funktionsname: ", font, 13, sfBlack); //Speicherzugriffsfehler

    parameterCountPos5 = getVector(802, 553);
    paramCount5 = calloc(1024, sizeof(char));
    strcpy(paramCount5, "Anzahl Parameter: ");
    paramBuffer5 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer5, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount5, paramBuffer5);
    parameterCount5 = getText(parameterCountPos5, paramCount5, font, 13, sfBlack);

    returnTypePos5 = getVector(802, 569);
    currentReturnType5 = calloc(1024, sizeof(char));
    strcpy(currentReturnType5, "Rueckgabetyp: ");
    returnTypeBuffer5 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer5, Parser->pc->TopStackFrame);
    strcat(currentReturnType5, returnTypeBuffer5);
    returnType5 = getText(returnTypePos5, currentReturnType5, font, 13, sfBlack);

    localVarPos5 = getVector(802, 585);
    currentlocalVar5 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar5, "Lokale Variablen: ");
    localVarBuffer5 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer5, Parser->pc->TopStackFrame);
    strcat(currentlocalVar5, localVarBuffer5);
    localVar5 = getText(localVarPos5, currentlocalVar5, font, 13, sfBlack);

    returnAddressPos5 = getVector(802, 601);
    currentreturnAddress5 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress5, "Returndetails: ");
    currentAddressBuffer5 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer5, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress5, currentAddressBuffer5);
    returnAddress5 = getText(returnAddressPos5, currentreturnAddress5, font, 13, sfBlack); */

    nextStep = sfText_create();
    sfText_setString(nextStep, "Mit Leertaste weiter"); //Parser->FileName);
    sfText_setFont(nextStep, font);
    sfText_setCharacterSize(nextStep, 17);
    sfText_setColor(nextStep, sfBlack);
    sfText_setPosition(nextStep, nextStepPos);

    /*File öffnen und Sourcecode in chararray speichern für Ausgabe*/
    //if(getLine(Parser)>5){
    fname = calloc(1024, sizeof(char));

    strcpy(fname, getFileName(fname, Parser));

    fname = getFileName(fname, Parser);

    file = fopen(fname, "r");

    sourceCode = calloc(10024, sizeof(char));

    lineCount = 0;
    while (fgets(line, sizeof(line), file))
    {
        strcat(sourceCode, line);
        lineCount++;
        //printf("%s", line);
    }

    strcat(sourceCode, "\0");

    code = sfText_create();
    sfText_setString(code, sourceCode);
    sfText_setFont(code, font);
    sfText_setCharacterSize(code, 13);
    sfText_setColor(code, sfBlack);
    sfText_setPosition(code, codePos);

    /*chararray mit Liniennummerierung für angezeigten SourceCode*/
    lineNumbersStr = calloc(1024, sizeof(char));
    for (int i = 1; i <= lineCount; i++)
    {
        sprintf(buffer, "%d", i); //int to char
        strcat(lineNumbersStr, buffer);
        strcat(lineNumbersStr, "\n"); //newline Hinzufügen funktioniert noch nicht
    }
    strcat(lineNumbersStr, "\0");

    lineNumbers = sfText_create();
    sfText_setString(lineNumbers, lineNumbersStr);
    sfText_setFont(lineNumbers, font);
    sfText_setCharacterSize(lineNumbers, 13);
    sfText_setColor(lineNumbers, sfBlack);
    sfText_setPosition(lineNumbers, lineNumbersPos);
    //}

    fileName = sfText_create();
    fileNameChar = malloc(1024);
    strcpy(fileNameChar, "Dateiname: ");
    val1 = malloc(1024);
    strcpy(val1, getFileName(val1, Parser));
    strcat(fileNameChar, val1);
    sfText_setString(fileName, fileNameChar);
    sfText_setFont(fileName, font);
    sfText_setCharacterSize(fileName, 13);
    sfText_setColor(fileName, sfBlack);
    sfText_setPosition(fileName, fileNamePos);

    runningMode = sfText_create();
    runModeString = calloc(1024, sizeof(char));
    strcpy(runModeString, "PicoC Running Mode: ");
    val2 = calloc(1024, sizeof(char));
    strcpy(val2, getRunningMode(val2, Parser));
    strcat(runModeString, val2);
    sfText_setString(runningMode, runModeString);
    sfText_setFont(runningMode, font);
    sfText_setCharacterSize(runningMode, 13);
    sfText_setColor(runningMode, sfBlack);
    sfText_setPosition(runningMode, runningModePos);

    executedLine = sfText_create();
    currentLineString = calloc(1024, sizeof(char));
    strcpy(currentLineString, "Ausgefuehrte Zeile: ");
    val3 = calloc(1024, sizeof(char));
    strcpy(val3, getLineAsString(val3, Parser));
    strcat(currentLineString, val3);
    sfText_setString(executedLine, currentLineString);
    sfText_setFont(executedLine, font);
    sfText_setCharacterSize(executedLine, 13);
    sfText_setColor(executedLine, sfBlack);
    sfText_setPosition(executedLine, executedLinePos);

       
    if(countStackFrames(Parser) >= 1){
        sfRenderWindow_drawRectangleShape(window, stackframe1, NULL);
        sfRenderWindow_drawText(window, stackFrameText1, NULL);
        sfRenderWindow_drawText(window, functionNameSF1, NULL);
        sfRenderWindow_drawText(window, parameterCount1, NULL);
        sfRenderWindow_drawText(window, returnType1, NULL);
        sfRenderWindow_drawText(window, localVar1, NULL);
        sfRenderWindow_drawText(window, returnAddress1, NULL); 
    }
    if(countStackFrames(Parser) >= 2){    
        sfRenderWindow_drawRectangleShape(window, stackframe2, NULL);
        sfRenderWindow_drawText(window, stackFrameText2, NULL);
        sfRenderWindow_drawText(window, functionNameSF2, NULL);
        sfRenderWindow_drawText(window, parameterCount2, NULL);
        sfRenderWindow_drawText(window, returnType2, NULL);
        sfRenderWindow_drawText(window, localVar2, NULL);
        sfRenderWindow_drawText(window, returnAddress2, NULL); 
    }
    if(countStackFrames(Parser) >= 3){    
        sfRenderWindow_drawRectangleShape(window, stackframe3, NULL);
        sfRenderWindow_drawText(window, stackFrameText3, NULL);
        sfRenderWindow_drawText(window, functionNameSF3, NULL);
        sfRenderWindow_drawText(window, parameterCount3, NULL);
        sfRenderWindow_drawText(window, returnType3, NULL);
        sfRenderWindow_drawText(window, localVar3, NULL);
        sfRenderWindow_drawText(window, returnAddress3, NULL); 
    }
/*     if(countStackFrames(Parser) >= 4){    
        sfRenderWindow_drawRectangleShape(window, stackframe4, NULL);
        sfRenderWindow_drawText(window, stackFrameText4, NULL);
        sfRenderWindow_drawText(window, functionNameSF4, NULL);
        sfRenderWindow_drawText(window, parameterCount4, NULL);
        sfRenderWindow_drawText(window, returnType4, NULL);
        sfRenderWindow_drawText(window, localVar4, NULL);
        sfRenderWindow_drawText(window, returnAddress4, NULL); 
    }
    if(countStackFrames(Parser) >= 5){    
        sfRenderWindow_drawRectangleShape(window, stackframe5, NULL);
        sfRenderWindow_drawText(window, stackFrameText5, NULL);
        sfRenderWindow_drawText(window, functionNameSF5, NULL);
        sfRenderWindow_drawText(window, parameterCount5, NULL);
        sfRenderWindow_drawText(window, returnType5, NULL);
        sfRenderWindow_drawText(window, localVar5, NULL);
        sfRenderWindow_drawText(window, returnAddress5, NULL);  
    }*/
            



    // Start the game loop
    while (sfRenderWindow_isOpen(window))
    {
        // Process events 
        while (sfRenderWindow_pollEvent(window, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtKeyPressed)
            {
                printf("Key pressed! \n");
                if (event.key.code == sfKeySpace)
                {
                    printf("Space pressed! \n");
                    goto breakloop;
                }
                // Move displayed source code up or down with arrow keys
                else if (event.key.code == sfKeyUp)
                {
                    printf("Up Arrow pressed! \n");
                    codePos.y += (float)10.0;
                    lineNumbersPos.y += (float)10.0;
                    sfText_setPosition(code, codePos);
                    sfText_setPosition(lineNumbers, lineNumbersPos);
                }
                else if (event.key.code == sfKeyDown)
                {
                    printf("Down Arrow pressed! \n");
                    codePos.y -= (float)10.0;
                    lineNumbersPos.y -= (float)10.0;
                    sfText_setPosition(code, codePos);
                    sfText_setPosition(lineNumbers, lineNumbersPos);
                }
            }
        }
	}
	breakloop:
	printf("test\n");
     

	// Clear the screen
	sfRenderWindow_clear(window, sfWhite); //sfColor_fromRGBA(49, 60, 72, 1.0));

	// Draw the sprite
	//sfRenderWindow_drawSprite(window, sprite, NULL);

	sfRenderWindow_drawRectangleShape(window, infoBlock, NULL);

	// Draw the text
	sfRenderWindow_drawText(window, nextStep, NULL);
	sfRenderWindow_drawText(window, code, NULL);
	sfRenderWindow_drawText(window, fileName, NULL);
	sfRenderWindow_drawText(window, runningMode, NULL);
	sfRenderWindow_drawText(window, executedLine, NULL);
	sfRenderWindow_drawText(window, lineNumbers, NULL);
	   
	// Update the window
	sfRenderWindow_display(window);

	return 0;
}



