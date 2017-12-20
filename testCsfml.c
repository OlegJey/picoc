#include <SFML/Audio.h>
#include <SFML/Graphics.h>


#include "tools.h"

int view_gui(struct ParseState *Parser)
{
    sfVideoMode mode = {1200, 600, 32};
    sfRenderWindow* window;
    sfFont* font; 
    sfText* code;
    sfVector2f codePos = {50, 80};
    sfText* lineNumbers;
    sfVector2f lineNumbersPos = {20, 80};  
    sfText* nextStep;
    sfVector2f nextStepPos = {800, 21};
    sfText* fileName;
    sfVector2f fileNamePos = {802, 56};
    sfText* runningMode;
    sfVector2f runningModePos = {802, 81};
    sfText* executedLine;
    sfVector2f executedLinePos = {802, 106};
    sfText* functionName;
    sfVector2f functionNamePos = {802, 131};
    sfText* parameterCount;
    sfVector2f parameterCountPos = {802, 156};
    sfText* returnType;
    sfVector2f returnTypePos = {802, 181};
    sfText* returnValue;
    sfVector2f returnValuePos = {802, 206};
    sfText* returnAddress;
    sfVector2f returnAddressPos = {802, 231};
    sfEvent event;
    
    sfRectangleShape* infoBlock;
    sfVector2f infoBlockSize = {500, 200};
    sfVector2f infoBlockPos = {800, 50};
    
    sfRectangleShape* stackframe1;
    sfVector2f stackframe1Size = {500, 100};
    sfVector2f stackframe1Pos = {800, 250};
    
    sfRectangleShape* stackframe2;
    sfVector2f stackframe2Pos = {800, 350};
    
    sfRectangleShape* stackframe3;
    sfVector2f stackframe3Pos = {800, 450};
    
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
    sfRectangleShape_setOutlineThickness(infoBlock, 5.0);
    
    stackframe1 = sfRectangleShape_create();
    sfRectangleShape_setSize(stackframe1, stackframe1Size);
    sfRectangleShape_setFillColor(stackframe1, sfGreen);
    sfRectangleShape_setPosition(stackframe1, stackframe1Pos);
    
    stackframe2 = sfRectangleShape_create();
    sfRectangleShape_setSize(stackframe2, stackframe1Size);
    sfRectangleShape_setFillColor(stackframe2, sfRed);
    sfRectangleShape_setPosition(stackframe2, stackframe2Pos);
    
    stackframe3 = sfRectangleShape_create();
    sfRectangleShape_setSize(stackframe3, stackframe1Size);
    sfRectangleShape_setFillColor(stackframe3, sfGreen);
    sfRectangleShape_setPosition(stackframe3, stackframe3Pos);
    
    /* Create a graphical text to display */
    font = sfFont_createFromFile("arial.ttf");
    if (!font)
        return 1;

    nextStep = sfText_create();
    sfText_setString(nextStep, "Mit Leertaste weiter");//Parser->FileName);
    sfText_setFont(nextStep, font);
    sfText_setCharacterSize(nextStep, 17);
    sfText_setColor(nextStep, sfBlack);
    sfText_setPosition(nextStep, nextStepPos);

    /*File öffnen und Sourcecode in chararray speichern für Ausgabe*/
    //if(getLine(Parser)>5){
        char* fname = malloc(sizeof(char) * 1024);
        strcpy(fname, getFileName(fname, Parser));
        fname = getFileName(fname, Parser);
        
        FILE* file = fopen(fname, "r");
        char line[256];
        char* sourceCode= calloc(10024, sizeof(char));
        int lineCount = 0;
        while(fgets(line, sizeof(line), file)){
            strcat(sourceCode, line);
            lineCount++;
            //printf("%s", line);
        }strcat(sourceCode, "\0");
    

        code = sfText_create();
        sfText_setString(code, sourceCode);
        sfText_setFont(code, font);
        sfText_setCharacterSize(code, 13);
        sfText_setColor(code, sfBlack);
        sfText_setPosition(code, codePos);
    

        /*chararray mit Liniennummerierung für angezeigten SourceCode*/
        char* lineNumbersStr = calloc(1024, sizeof(char));
        char buffer[12];  
        for(int i=1; i<=lineCount; i++){
            sprintf(buffer, "%d", i); //int to char
            strcat(lineNumbersStr, buffer);
            strcat(lineNumbersStr, "\n");	//newline Hinzufügen funktioniert noch nicht        
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
    char* fileNameChar = malloc(1024);
    strcpy(fileNameChar, "Dateiname: ");
    char* val1 = malloc(1024);
    strcpy(val1, getFileName(val1, Parser));
    strcat(fileNameChar, val1);
    sfText_setString(fileName, fileNameChar);
    sfText_setFont(fileName, font);
    sfText_setCharacterSize(fileName, 13);
    sfText_setColor(fileName, sfBlack);
    sfText_setPosition(fileName, fileNamePos);

	runningMode = sfText_create();
    char* runModeString = malloc(sizeof(char) * 1024);
    strcpy(runModeString, "PicoC Running Mode: ");
    char* val2 = malloc(sizeof(char) * 1024);
    strcpy(val2, getRunningMode(val2, Parser));
    strcat(runModeString, val2);
    sfText_setString(runningMode, runModeString);
    sfText_setFont(runningMode, font);
    sfText_setCharacterSize(runningMode, 13);
    sfText_setColor(runningMode, sfBlack);
    sfText_setPosition(runningMode, runningModePos);
    
    executedLine = sfText_create();
    char* currentLineString = malloc(sizeof(char) * 1024);
    strcpy(currentLineString, "Ausgefuehrte Zeile: ");
    char* val3 = malloc(sizeof(char) * 1024);
    strcpy(val3, getLineAsString(val3, Parser));
    strcat(currentLineString, val3);
    sfText_setString(executedLine, currentLineString);
    sfText_setFont(executedLine, font);
    sfText_setCharacterSize(executedLine, 13);
    sfText_setColor(executedLine, sfBlack);
    sfText_setPosition(executedLine, executedLinePos);

    functionName = sfText_create();
    sfText_setString(functionName, "Funktionsname: ");
    sfText_setFont(functionName, font);
    sfText_setCharacterSize(functionName, 13);
    sfText_setColor(functionName, sfBlack);
    sfText_setPosition(functionName, functionNamePos);

    parameterCount = sfText_create();
    char* paramCount = malloc(sizeof(char) * 1024);
    strcpy(paramCount, "Anzahl Parameter: ");
    char* val4 = malloc(sizeof(char) * 1024);
    strcpy(val4, getNumParamAsString(val4, Parser));
    strcat(paramCount, val4);
    sfText_setString(parameterCount, paramCount);
    sfText_setFont(parameterCount, font);
    sfText_setCharacterSize(parameterCount, 13);
    sfText_setColor(parameterCount, sfBlack);
    sfText_setPosition(parameterCount, parameterCountPos);

    returnType = sfText_create();
    char* currentReturnType = malloc(sizeof(char) * 1024);
    strcpy(currentReturnType, "Rueckgabetyp: ");
    char* val5 = malloc(sizeof(char) * 1024);
    strcpy(val5, getRetDetails(val5, Parser));
    strcat(currentReturnType, val5);
    sfText_setString(returnType, currentReturnType);
    sfText_setFont(returnType, font);
    sfText_setCharacterSize(returnType, 13);
    sfText_setColor(returnType, sfBlack);
    sfText_setPosition(returnType, returnTypePos);

    returnValue = sfText_create();
    sfText_setString(returnValue, "Rueckgabewert: ");
    sfText_setFont(returnValue, font);
    sfText_setCharacterSize(returnValue, 13);
    sfText_setColor(returnValue, sfBlack);
    sfText_setPosition(returnValue, returnValuePos);

    returnAddress = sfText_create();
    sfText_setString(returnAddress, "Ruecksprungadresse: ");
    sfText_setFont(returnAddress, font);
    sfText_setCharacterSize(returnAddress, 13);
    sfText_setColor(returnAddress, sfBlack);
    sfText_setPosition(returnAddress, returnAddressPos);

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
			else if(event.type == sfEvtKeyPressed) {				
				printf("Key pressed! \n");
				if(event.key.code == sfKeySpace) {							
					printf("Space pressed! \n");
					sfRenderWindow_close(window);
				}
                /*Move displayed source code up or down with arrow keys */
				else if(event.key.code == sfKeyUp){
					printf("Up Arrow pressed! \n");
                    codePos.y += (float)10.0;
                    lineNumbersPos.y += (float)10.0;
                    sfText_setPosition(code, codePos);
                    sfText_setPosition(lineNumbers, lineNumbersPos);
				}
				else if(event.key.code == sfKeyDown){
					printf("Down Arrow pressed! \n");
                    codePos.y -= (float)10.0;
                    lineNumbersPos.y -= (float)10.0;
                    sfText_setPosition(code, codePos);
                    sfText_setPosition(lineNumbers, lineNumbersPos);
				}
				
			}
        }	
	
        /* Clear the screen */
        sfRenderWindow_clear(window, sfWhite);//sfColor_fromRGBA(49, 60, 72, 1.0));

        /* Draw the sprite */
        //sfRenderWindow_drawSprite(window, sprite, NULL);
        
        sfRenderWindow_drawRectangleShape(window, infoBlock, NULL);
        sfRenderWindow_drawRectangleShape(window, stackframe1, NULL);
        sfRenderWindow_drawRectangleShape(window, stackframe2, NULL);
        sfRenderWindow_drawRectangleShape(window, stackframe3, NULL);
        
        /* Draw the text */
        sfRenderWindow_drawText(window, nextStep, NULL);
        sfRenderWindow_drawText(window, code, NULL);
        sfRenderWindow_drawText(window, lineNumbers, NULL);
        sfRenderWindow_drawText(window, fileName, NULL);
        sfRenderWindow_drawText(window, runningMode, NULL);
        sfRenderWindow_drawText(window, executedLine, NULL);
        sfRenderWindow_drawText(window, functionName, NULL);
        sfRenderWindow_drawText(window, parameterCount, NULL);
        sfRenderWindow_drawText(window, returnType, NULL);
        sfRenderWindow_drawText(window, returnValue, NULL);
        sfRenderWindow_drawText(window, returnAddress, NULL);
        


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
    sfText_destroy(functionName);
    sfText_destroy(parameterCount);
    sfText_destroy(returnType);
    sfText_destroy(returnValue);
    sfText_destroy(returnAddress);
    sfRectangleShape_destroy(infoBlock);
    sfRectangleShape_destroy(stackframe1);
    sfRectangleShape_destroy(stackframe2);
    sfRectangleShape_destroy(stackframe3);
    sfRenderWindow_destroy(window);

return 1;
    
}
