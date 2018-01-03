#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#include "tools.h"

sfText *getText(sfVector2f pos, char *string, sfFont *font, int size, sfColor color)
{
    sfText *text;
    text = sfText_create();
    sfText_setString(text, string);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, color);
    sfText_setPosition(text, pos);
    return text;
}

int view_gui(struct ParseState *Parser)
{

    sfVideoMode mode = {1200, 600, 32};
    sfRenderWindow *window;
    sfFont *font;
    sfText *code;
    sfVector2f codePos = {50, 70};
    sfText *lineNumbers;
    sfVector2f lineNumbersPos = {20, 70};
    sfText *nextStep;
    sfVector2f nextStepPos = {800, 11};
    sfText *fileName;
    sfVector2f fileNamePos = {802, 46};
    sfText *runningMode;
    sfVector2f runningModePos = {802, 71};
    sfText *executedLine;
    sfVector2f executedLinePos = {802, 96};

    sfEvent event;

    sfRectangleShape *infoBlock;
    sfVector2f infoBlockSize = {500, 80};
    sfVector2f infoBlockPos = {800, 40};

    sfRectangleShape *stackframe1;
    sfVector2f stackframe1Size = {500, 100};
    sfVector2f stackframe1Pos = {800, 120};

    sfRectangleShape *stackframe2;
    sfVector2f stackframe2Pos = {800, 220};

    sfRectangleShape *stackframe3;
    sfVector2f stackframe3Pos = {800, 320};

    sfRectangleShape *stackframe4;
    sfVector2f stackframe4Pos = {800, 420};

    sfRectangleShape *stackframe5;
    sfVector2f stackframe5Pos = {800, 520};

    /* Create the main window */
    window = sfRenderWindow_create(mode, "PicoC GUI", sfResize | sfClose, NULL);
    if (!window)
        return 1;
    sfRenderWindow_setFramerateLimit(window, 60);

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

    sfVector2f stackFrameText1Pos = {802, 121};
    sfVector2f stackFrameText2Pos = {802, 221};
    sfVector2f stackFrameText3Pos = {802, 321};
/*     sfVector2f stackFrameText4Pos = {802, 421};
    sfVector2f stackFrameText5Pos = {802, 521}; */

    //STACKRFAME 1

    sfText *stackFrameText1 = getText(stackFrameText1Pos, "Stackframe 1", font, 13, sfBlack);

    sfVector2f functionNameSF1Pos = {802, 137};
   /*  char *funcNameSF1 = calloc(1024, sizeof(char));     //Speicherzugriffsfehler
    strcpy(funcNameSF1, "Funktionsname: ");
    char *funcNameBuffer1 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer1, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF1, funcNameBuffer1); */
    sfText *functionNameSF1 = getText(functionNameSF1Pos, "Funktionsname: ", font, 13, sfBlack); 

    sfVector2f parameterCountPos1 = {802, 153};
    char *paramCount1 = calloc(1024, sizeof(char));
    strcpy(paramCount1, "Anzahl Parameter: ");
    char *paramBuffer1 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer1, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount1, paramBuffer1);
    sfText *parameterCount1 = getText(parameterCountPos1, paramCount1, font, 13, sfBlack);

    sfVector2f returnTypePos1 = {802, 169};
    char *currentReturnType1 = calloc(1024, sizeof(char));
    strcpy(currentReturnType1, "Rueckgabetyp: ");
    char *returnTypeBuffer1 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer1, Parser->pc->TopStackFrame);
    strcat(currentReturnType1, returnTypeBuffer1);
    sfText *returnType1 = getText(returnTypePos1, currentReturnType1, font, 13, sfBlack);

    sfVector2f localVarPos1 = {802, 185};
    char *currentlocalVar1 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar1, "Lokale Variablen: ");
    char *localVarBuffer1 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer1, Parser->pc->TopStackFrame);
    strcat(currentlocalVar1, localVarBuffer1);
    sfText *localVar1 = getText(localVarPos1, currentlocalVar1, font, 13, sfBlack);

    sfVector2f returnAddressPos1 = {802, 201};
    char *currentreturnAddress1 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress1, "Returndetails: ");
    char *currentAddressBuffer1 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer1, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress1, currentAddressBuffer1);
    sfText *returnAddress1 = getText(returnAddressPos1, currentreturnAddress1, font, 13, sfBlack);

    //STACKFRAME 2

    sfText *stackFrameText2 = getText(stackFrameText2Pos, "Stackframe 2", font, 13, sfBlack);

    sfVector2f functionNameSF2Pos = {802, 237};
/*     char *funcNameSF2 = calloc(1024, sizeof(char));
    strcpy(funcNameSF2, "Funktionsname: ");
    char *funcNameBuffer2 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer2, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF2, funcNameBuffer2); */
    sfText *functionNameSF2 = getText(functionNameSF2Pos, "Funktionsname: ", font, 13, sfBlack); //Speicherzugriffsfehler

    sfVector2f parameterCountPos2 = {802, 253};
    char *paramCount2 = calloc(1024, sizeof(char));
    strcpy(paramCount2, "Anzahl Parameter: ");
    char *paramBuffer2 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer2, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount2, paramBuffer2);
    sfText *parameterCount2 = getText(parameterCountPos2, paramCount2, font, 13, sfBlack);

    sfVector2f returnTypePos2 = {802, 269};
    char *currentReturnType2 = calloc(1024, sizeof(char));
    strcpy(currentReturnType2, "Rueckgabetyp: ");
    char *returnTypeBuffer2 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer2, Parser->pc->TopStackFrame);
    strcat(currentReturnType2, returnTypeBuffer2);
    sfText *returnType2 = getText(returnTypePos2, currentReturnType1, font, 13, sfBlack);

    sfVector2f localVarPos2 = {802, 285};
    char *currentlocalVar2 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar2, "Lokale Variablen: ");
    char *localVarBuffer2 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer2, Parser->pc->TopStackFrame);
    strcat(currentlocalVar2, localVarBuffer2);
    sfText *localVar2 = getText(localVarPos2, currentlocalVar2, font, 13, sfBlack);

    sfVector2f returnAddressPos2 = {802, 301};
    char *currentreturnAddress2 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress2, "Returndetails: ");
    char *currentAddressBuffer2 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer2, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress2, currentAddressBuffer2);
    sfText *returnAddress2 = getText(returnAddressPos2, currentreturnAddress2, font, 13, sfBlack);

    //STACKFRAME 3
    sfText *stackFrameText3 = getText(stackFrameText3Pos, "Stackframe 3", font, 13, sfBlack);

    sfVector2f functionNameSF3Pos = {802, 337};
/*     char *funcNameSF3 = calloc(1024, sizeof(char));
    strcpy(funcNameSF3, "Funktionsname: ");
    char *funcNameBuffer3 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer3, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF3, funcNameBuffer3); */
    sfText *functionNameSF3 = getText(functionNameSF3Pos, "Funktionsname: ", font, 13, sfBlack); //Speicherzugriffsfehler

    sfVector2f parameterCountPos3 = {802, 353};
    char *paramCount3 = calloc(1024, sizeof(char));
    strcpy(paramCount3, "Anzahl Parameter: ");
    char *paramBuffer3 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer3, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount3, paramBuffer3);
    sfText *parameterCount3 = getText(parameterCountPos3, paramCount3, font, 13, sfBlack);

    sfVector2f returnTypePos3 = {802, 369};
    char *currentReturnType3 = calloc(1024, sizeof(char));
    strcpy(currentReturnType3, "Rueckgabetyp: ");
    char *returnTypeBuffer3 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer3, Parser->pc->TopStackFrame);
    strcat(currentReturnType3, returnTypeBuffer3);
    sfText *returnType3 = getText(returnTypePos3, currentReturnType3, font, 13, sfBlack);

    sfVector2f localVarPos3 = {802, 385};
    char *currentlocalVar3 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar3, "Lokale Variablen: ");
    char *localVarBuffer3 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer3, Parser->pc->TopStackFrame);
    strcat(currentlocalVar3, localVarBuffer3);
    sfText *localVar3 = getText(localVarPos3, currentlocalVar3, font, 13, sfBlack);

    sfVector2f returnAddressPos3 = {802, 401};
    char *currentreturnAddress3 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress3, "Returndetails: ");
    char *currentAddressBuffer3 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer3, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress3, currentAddressBuffer3);
    sfText *returnAddress3 = getText(returnAddressPos3, currentreturnAddress3, font, 13, sfBlack);

    //STACKFRAME 4
/*     sfText *stackFrameText4 = getText(stackFrameText4Pos, "Stackframe 4", font, 13, sfBlack);

    sfVector2f functionNameSF4Pos = {802, 437};
    char *funcNameSF4 = calloc(1024, sizeof(char));
    strcpy(funcNameSF4, "Funktionsname: ");
    char *funcNameBuffer4 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer4, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF4, funcNameBuffer4);
    sfText *functionNameSF4 = getText(functionNameSF4Pos, "Funktionsname: ", font, 13, sfBlack); //Speicherzugriffsfehler

    sfVector2f parameterCountPos4 = {802, 453};
    char *paramCount4 = calloc(1024, sizeof(char));
    strcpy(paramCount4, "Anzahl Parameter: ");
    char *paramBuffer4 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer4, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount4, paramBuffer4);
    sfText *parameterCount4 = getText(parameterCountPos4, paramCount4, font, 13, sfBlack);

    sfVector2f returnTypePos4 = {802, 469};
    char *currentReturnType4 = calloc(1024, sizeof(char));
    strcpy(currentReturnType4, "Rueckgabetyp: ");
    char *returnTypeBuffer4 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer4, Parser->pc->TopStackFrame);
    strcat(currentReturnType4, returnTypeBuffer4);
    sfText *returnType4 = getText(returnTypePos4, currentReturnType4, font, 13, sfBlack);

    sfVector2f localVarPos4 = {802, 485};
    char *currentlocalVar4 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar4, "Lokale Variablen: ");
    char *localVarBuffer4 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer4, Parser->pc->TopStackFrame);
    strcat(currentlocalVar4, localVarBuffer4);
    sfText *localVar4 = getText(localVarPos4, currentlocalVar4, font, 13, sfBlack);

    sfVector2f returnAddressPos4 = {802, 501};
    char *currentreturnAddress4 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress4, "Returndetails: ");
    char *currentAddressBuffer4 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer4, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress4, currentAddressBuffer4);
    sfText *returnAddress4 = getText(returnAddressPos4, currentreturnAddress4, font, 13, sfBlack);

    //STACKFRAME 5
    sfText *stackFrameText5 = getText(stackFrameText5Pos, "Stackframe 5", font, 13, sfBlack);

    sfVector2f functionNameSF5Pos = {802, 537};
    char *funcNameSF5 = calloc(1024, sizeof(char));
    strcpy(funcNameSF5, "Funktionsname: ");
    char *funcNameBuffer5 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getFuncName(funcNameBuffer5, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(funcNameSF5, funcNameBuffer5);
    sfText *functionNameSF5 = getText(functionNameSF5Pos, "Funktionsname: ", font, 13, sfBlack); //Speicherzugriffsfehler

    sfVector2f parameterCountPos5 = {802, 553};
    char *paramCount5 = calloc(1024, sizeof(char));
    strcpy(paramCount5, "Anzahl Parameter: ");
    char *paramBuffer5 = calloc(1024, sizeof(char));
    if (Parser->pc->TopStackFrame)
        getNumParamAsString(paramBuffer5, get_StackFrame(Parser)); //Parser->pc->TopStackFrame);
    strcat(paramCount5, paramBuffer5);
    sfText *parameterCount5 = getText(parameterCountPos5, paramCount5, font, 13, sfBlack);

    sfVector2f returnTypePos5 = {802, 569};
    char *currentReturnType5 = calloc(1024, sizeof(char));
    strcpy(currentReturnType5, "Rueckgabetyp: ");
    char *returnTypeBuffer5 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(returnTypeBuffer5, Parser->pc->TopStackFrame);
    strcat(currentReturnType5, returnTypeBuffer5);
    sfText *returnType5 = getText(returnTypePos5, currentReturnType5, font, 13, sfBlack);

    sfVector2f localVarPos5 = {802, 585};
    char *currentlocalVar5 = calloc(1024, sizeof(char));
    strcpy(currentlocalVar5, "Lokale Variablen: ");
    char *localVarBuffer5 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getLocalVarAndVal(localVarBuffer5, Parser->pc->TopStackFrame);
    strcat(currentlocalVar5, localVarBuffer5);
    sfText *localVar5 = getText(localVarPos5, currentlocalVar5, font, 13, sfBlack);

    sfVector2f returnAddressPos5 = {802, 601};
    char *currentreturnAddress5 = calloc(1024, sizeof(char));
    strcpy(currentreturnAddress5, "Returndetails: ");
    char *currentAddressBuffer5 = calloc(1024, sizeof(char));

    if (Parser->pc->TopStackFrame)
        getRetDetails(currentAddressBuffer5, Parser->pc->TopStackFrame);
    strcat(currentreturnAddress5, currentAddressBuffer5);
    sfText *returnAddress5 = getText(returnAddressPos5, currentreturnAddress5, font, 13, sfBlack); */

    nextStep = sfText_create();
    sfText_setString(nextStep, "Mit Leertaste weiter"); //Parser->FileName);
    sfText_setFont(nextStep, font);
    sfText_setCharacterSize(nextStep, 17);
    sfText_setColor(nextStep, sfBlack);
    sfText_setPosition(nextStep, nextStepPos);

    /*File öffnen und Sourcecode in chararray speichern für Ausgabe*/
    //if(getLine(Parser)>5){
    char *fname = calloc(1024, sizeof(char));
    strcpy(fname, getFileName(fname, Parser));
    fname = getFileName(fname, Parser);

    FILE *file = fopen(fname, "r");
    char line[256];
    char *sourceCode = calloc(10024, sizeof(char));
    int lineCount = 0;
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
    char *lineNumbersStr = calloc(1024, sizeof(char));
    char buffer[12];
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
    char *fileNameChar = malloc(1024);
    strcpy(fileNameChar, "Dateiname: ");
    char *val1 = malloc(1024);
    strcpy(val1, getFileName(val1, Parser));
    strcat(fileNameChar, val1);
    sfText_setString(fileName, fileNameChar);
    sfText_setFont(fileName, font);
    sfText_setCharacterSize(fileName, 13);
    sfText_setColor(fileName, sfBlack);
    sfText_setPosition(fileName, fileNamePos);

    runningMode = sfText_create();
    char *runModeString = calloc(1024, sizeof(char));
    strcpy(runModeString, "PicoC Running Mode: ");
    char *val2 = calloc(1024, sizeof(char));
    strcpy(val2, getRunningMode(val2, Parser));
    strcat(runModeString, val2);
    sfText_setString(runningMode, runModeString);
    sfText_setFont(runningMode, font);
    sfText_setCharacterSize(runningMode, 13);
    sfText_setColor(runningMode, sfBlack);
    sfText_setPosition(runningMode, runningModePos);

    executedLine = sfText_create();
    char *currentLineString = calloc(1024, sizeof(char));
    strcpy(currentLineString, "Ausgefuehrte Zeile: ");
    char *val3 = calloc(1024, sizeof(char));
    strcpy(val3, getLineAsString(val3, Parser));
    strcat(currentLineString, val3);
    sfText_setString(executedLine, currentLineString);
    sfText_setFont(executedLine, font);
    sfText_setCharacterSize(executedLine, 13);
    sfText_setColor(executedLine, sfBlack);
    sfText_setPosition(executedLine, executedLinePos);

    

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtKeyPressed)
            {
                printf("Key pressed! \n");
                if (event.key.code == sfKeySpace)
                {
                    printf("Space pressed! \n");
                    sfRenderWindow_close(window);
                }
                /*Move displayed source code up or down with arrow keys */
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

        /* Clear the screen */
        sfRenderWindow_clear(window, sfWhite); //sfColor_fromRGBA(49, 60, 72, 1.0));

        /* Draw the sprite */
        //sfRenderWindow_drawSprite(window, sprite, NULL);

        sfRenderWindow_drawRectangleShape(window, infoBlock, NULL);

        switch (countStackFrames(Parser))
        {
            case 1:
            sfRenderWindow_drawRectangleShape(window, stackframe1, NULL);
            sfRenderWindow_drawText(window, stackFrameText1, NULL);
            sfRenderWindow_drawText(window, functionNameSF1, NULL);
            sfRenderWindow_drawText(window, parameterCount1, NULL);
            sfRenderWindow_drawText(window, returnType1, NULL);
            sfRenderWindow_drawText(window, localVar1, NULL);
            sfRenderWindow_drawText(window, returnAddress1, NULL); break;

            case 2:
            sfRenderWindow_drawRectangleShape(window, stackframe2, NULL);
            sfRenderWindow_drawText(window, stackFrameText2, NULL);
            sfRenderWindow_drawText(window, functionNameSF2, NULL);
            sfRenderWindow_drawText(window, parameterCount2, NULL);
            sfRenderWindow_drawText(window, returnType2, NULL);
            sfRenderWindow_drawText(window, localVar2, NULL);
            sfRenderWindow_drawText(window, returnAddress2, NULL); break;

            case 3:
            sfRenderWindow_drawRectangleShape(window, stackframe3, NULL);
            sfRenderWindow_drawText(window, stackFrameText3, NULL);
            sfRenderWindow_drawText(window, functionNameSF3, NULL);
            sfRenderWindow_drawText(window, parameterCount3, NULL);
            sfRenderWindow_drawText(window, returnType3, NULL);
            sfRenderWindow_drawText(window, localVar3, NULL);
            sfRenderWindow_drawText(window, returnAddress3, NULL); break;

 /*            case 4:
            sfRenderWindow_drawRectangleShape(window, stackframe4, NULL);
            sfRenderWindow_drawText(window, stackFrameText4, NULL);
            sfRenderWindow_drawText(window, functionNameSF4, NULL);
            sfRenderWindow_drawText(window, parameterCount4, NULL);
            sfRenderWindow_drawText(window, returnType4, NULL);
            sfRenderWindow_drawText(window, localVar4, NULL);
            sfRenderWindow_drawText(window, returnAddress4, NULL); break;

            case 5:
            sfRenderWindow_drawRectangleShape(window, stackframe5, NULL);
            sfRenderWindow_drawText(window, stackFrameText5, NULL);
            sfRenderWindow_drawText(window, functionNameSF5, NULL);
            sfRenderWindow_drawText(window, parameterCount5, NULL);
            sfRenderWindow_drawText(window, returnType5, NULL);
            sfRenderWindow_drawText(window, localVar5, NULL);
            sfRenderWindow_drawText(window, returnAddress5, NULL); break; */

            default: break;
        }

        /* Draw the text */

        sfRenderWindow_drawText(window, nextStep, NULL);
        sfRenderWindow_drawText(window, code, NULL);
        sfRenderWindow_drawText(window, lineNumbers, NULL);
        sfRenderWindow_drawText(window, fileName, NULL);
        sfRenderWindow_drawText(window, runningMode, NULL);
        sfRenderWindow_drawText(window, executedLine, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfFont_destroy(font);
    sfText_destroy(nextStep);
    sfText_destroy(code);
    sfText_destroy(lineNumbers);
    free(sourceCode);
    free(lineNumbersStr);
    sfText_destroy(fileName);
    sfText_destroy(runningMode);
    sfText_destroy(executedLine);
    sfText_destroy(functionNameSF1);
    sfText_destroy(parameterCount1);
    sfText_destroy(returnType1);
    sfText_destroy(localVar1);
    sfText_destroy(returnAddress1);
    sfText_destroy(functionNameSF2);
    sfText_destroy(parameterCount2);
    sfText_destroy(returnType2);
    sfText_destroy(localVar2);
    sfText_destroy(returnAddress2);
    sfText_destroy(functionNameSF3);
    sfText_destroy(parameterCount3);
    sfText_destroy(returnType3);
    sfText_destroy(localVar3);
    sfText_destroy(returnAddress3);
/*     sfText_destroy(functionNameSF4);
    sfText_destroy(parameterCount4);
    sfText_destroy(returnType4);
    sfText_destroy(localVar4);
    sfText_destroy(returnAddress4);
    sfText_destroy(functionNameSF5);
    sfText_destroy(parameterCount5);
    sfText_destroy(returnType5);
    sfText_destroy(localVar5);
    sfText_destroy(returnAddress5);
    sfText_destroy(stackFrameText1);
    sfText_destroy(stackFrameText2);
    sfText_destroy(stackFrameText3);
    sfText_destroy(stackFrameText4);
    sfText_destroy(stackFrameText5); */
    sfRectangleShape_destroy(infoBlock);
    sfRectangleShape_destroy(stackframe1);
    sfRectangleShape_destroy(stackframe2);
    sfRectangleShape_destroy(stackframe3);
    sfRectangleShape_destroy(stackframe4);
    sfRectangleShape_destroy(stackframe5);
    sfRenderWindow_destroy(window);

    return 1;
}
