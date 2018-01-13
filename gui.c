
#include "gui.h"


/*File öffnen und Sourcecode in chararray speichern für Ausgabe*/
char *getSourceCode(struct ParseState *Parser)
{
    char *fname = calloc(1024, sizeof(char));

    strcpy(fname, getFileName(fname, Parser));
    FILE *file;
    file = fopen(fname, "r");
    char* sourceCode = calloc(10024, sizeof(char));

    lineCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        strcat(sourceCode, line);
        lineCount++;
    }
    strcat(sourceCode, "\0");
    free(fname);
    return sourceCode;
}

 /*chararray mit Liniennummerierung für angezeigten SourceCode*/
char *getLineNumbersString(){
    char *lineNumbersStr = calloc(1024, sizeof(char));
    char buffer[12];
    for (int i = 1; i <= lineCount; i++)
    {
        sprintf(buffer, "%d", i); //int to char
        strcat(lineNumbersStr, buffer);
        strcat(lineNumbersStr, "\n"); //newline Hinzufügen funktioniert noch nicht
    }
    strcat(lineNumbersStr, "\0");
    return lineNumbersStr;

}


sfRectangleShape *getRectangleShape(sfVector2f size, sfVector2f pos, sfColor fillColor, sfColor outlineColor, float thickness)
{
    sfRectangleShape *rec;
    rec = sfRectangleShape_create();
    sfRectangleShape_setSize(rec, size);
    sfRectangleShape_setPosition(rec, pos);
    sfRectangleShape_setFillColor(rec, fillColor);
    sfRectangleShape_setOutlineColor(rec, outlineColor);
    sfRectangleShape_setOutlineThickness(rec, thickness);
    return rec;
}

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

sfVector2f getVector(int x, int y)
{
    sfVector2f temp = {x, y};
    return temp;
}

struct StackFrameTexts *getStackFrameTexts(struct StackFrame *frame){
    struct StackFrameTexts *block = malloc(sizeof(struct StackFrameTexts));
    block->paramCount = calloc(1024, sizeof(char));
    block->currentLocalVar = calloc(1024, sizeof(char));
    block->currentReturnDetail = calloc(1024, sizeof(char));
    block->funcName = calloc(1024, sizeof(char));

    char *funcNameBuffer = calloc(1024, sizeof(char));
    char *paramBuffer = calloc(1024, sizeof(char));
    char *localVarBuffer = calloc(1024, sizeof(char));
     
    //  //Function Name
    strcpy(block->funcName, "Function name: ");
    getFuncName(funcNameBuffer, frame);
    strcat(block->funcName, funcNameBuffer);
    
    //Amount Parameter
    strcpy(block->paramCount, "Anzahl Parameter: ");
    getNumParamAsString(paramBuffer, frame);
    strcat(block->paramCount, paramBuffer);
   
    //Return details
    getRetDetails(block->currentReturnDetail, frame);
   
    //Local Data
    strcpy(block->currentLocalVar, "Lokale Variablen: ");
    getLocalVarAndVal(localVarBuffer, frame);
    strcat(block->currentLocalVar, localVarBuffer);

    return block;
}

void delStackFrameTexts(struct StackFrameTexts *sft){
    if(sft != NULL){
        free(sft->currentLocalVar);
        free(sft->currentReturnDetail);
        free(sft->funcName);
        free(sft->paramCount);
        free(sft);
    }
}

int gui_handler()
{

    if (window != NULL)
        return kill_gui();
    else
        return init_gui();
}

int init_gui()
{

    /* Create the main window */

    vmode.width = 1200;
    vmode.height = 600;
    vmode.bitsPerPixel = 32;

    window = sfRenderWindow_create(vmode, "PicoC GUI", sfResize | sfClose, NULL);
    if (!window)
        return -1;
    sfRenderWindow_setFramerateLimit(window, 60);

    /* Create a font for sfText */
    font = sfFont_createFromFile("arial.ttf");
    if (!font)
        return 1;

    // Create Shapes
    //infoBlock shows: filename, runmode, executed line
    infoBlock = getRectangleShape(getVector(590, 72), getVector(600, 40), sfCyan, sfBlack, 2.0);

    stackframeBox1 = getRectangleShape(getVector(590, 100), getVector(600, 120), sfColor_fromRGBA(154, 192, 205, 255), sfBlack, 2.0);

    stackframeBox2 = getRectangleShape(getVector(590, 100), getVector(600, 220), sfColor_fromRGBA(131, 111, 255, 240), sfBlack, 2.0);

    stackframeBox3 = getRectangleShape(getVector(590, 100), getVector(600, 320), sfColor_fromRGBA(255, 127, 36, 240), sfBlack, 2.0);

    stackframeBox4 = getRectangleShape(getVector(590, 100), getVector(600, 420), sfColor_fromRGBA(127, 255, 0, 240), sfBlack, 2.0);

    stackframeBox5 = getRectangleShape(getVector(590, 100), getVector(600, 520), sfColor_fromRGBA(205, 198, 115, 240), sfBlack, 2.0);

    // Set position, font, size, color and create Text
    //setString happens in refresh_gui()
    codePos = getVector(50, 70);
    code = sfText_create();
    sfText_setFont(code, font);
    sfText_setCharacterSize(code, 13);
    sfText_setColor(code, sfBlack);
    sfText_setPosition(code, codePos);

    lineNumbersPos = getVector(20, 70);
    lineNumbers = sfText_create();
    sfText_setFont(lineNumbers, font);
    sfText_setCharacterSize(lineNumbers, 13);
    sfText_setColor(lineNumbers, sfBlack);
    sfText_setPosition(lineNumbers, lineNumbersPos);

    nextStepPos = getVector(600, 11);
    nextStep = sfText_create();
    sfText_setString(nextStep, "Mit Leertaste weiter"); //Parser->FileName);
    sfText_setFont(nextStep, font);
    sfText_setCharacterSize(nextStep, 17);
    sfText_setColor(nextStep, sfBlack);
    sfText_setPosition(nextStep, nextStepPos);

    fileNamePos = getVector(602, 46);
    fileName = sfText_create();
    sfText_setFont(fileName, font);
    sfText_setCharacterSize(fileName, 13);
    sfText_setColor(fileName, sfBlack);
    sfText_setPosition(fileName, fileNamePos);

    runningModePos = getVector(602, 71);
    runningMode = sfText_create();
    sfText_setFont(runningMode, font);
    sfText_setCharacterSize(runningMode, 13);
    sfText_setColor(runningMode, sfBlack);
    sfText_setPosition(runningMode, runningModePos);

    executedLinePos = getVector(602, 96);
    executedLine = sfText_create();
    sfText_setFont(executedLine, font);
    sfText_setCharacterSize(executedLine, 13);
    sfText_setColor(executedLine, sfBlack);
    sfText_setPosition(executedLine, executedLinePos);

    return 0;
}

int kill_gui()
{

    // Cleanup resources
    sfText_destroy(nextStep);
    sfText_destroy(code);
    sfText_destroy(lineNumbers);
    sfText_destroy(fileName);
    sfText_destroy(runningMode);
    sfText_destroy(executedLine);

    sfRectangleShape_destroy(infoBlock);
    sfRectangleShape_destroy(stackframeBox1);
    sfRectangleShape_destroy(stackframeBox2);
    sfRectangleShape_destroy(stackframeBox3);
    sfRectangleShape_destroy(stackframeBox4);
    sfRectangleShape_destroy(stackframeBox5);

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

int refresh_gui(struct ParseState *Parser)
{

    struct StackFrame *current = get_TopStackFrame(Parser);

    struct StackFrame *frames[5];

    for (int i = 0; i < 5; i++)
    {

        frames[i] = current;
        current = get_PreviousStackFrame(current);
    }

    
    // //Frame 1
    stackFrameText1 = getText(getVector(602, 121), "Stackframe 1", font, 13, sfBlack);
    struct StackFrameTexts *block1 = getStackFrameTexts(frames[0]);
    functionNameSF1 = getText(getVector(602, 137), block1->funcName, font, 13, sfBlack);
    parameterCount1 = getText(getVector(602, 153), block1->paramCount, font, 13, sfBlack);
    returnType1 = getText(getVector(602, 169), block1->currentReturnDetail, font, 13, sfBlack);
    localVar1 = getText(getVector(602, 185), block1->currentLocalVar, font, 13, sfBlack);

    //Frame 2
     stackFrameText2 = getText(getVector(602, 221), "Stackframe 2", font, 13, sfBlack);
    struct StackFrameTexts *block2 = getStackFrameTexts(frames[1]);
    functionNameSF2 = getText(getVector(602, 237), block2->funcName, font, 13, sfBlack);
    parameterCount2 = getText(getVector(602, 253), block2->paramCount, font, 13, sfBlack);
    returnType2 = getText(getVector(602, 269), block2->currentReturnDetail, font, 13, sfBlack);
    localVar2 = getText(getVector(602, 285), block2->currentLocalVar, font, 13, sfBlack);
   

    //Frame 3
    stackFrameText3 = getText(getVector(602, 321), "Stackframe 3", font, 13, sfBlack);
    struct StackFrameTexts *block3 = getStackFrameTexts(frames[2]);
    functionNameSF3 = getText(getVector(602, 337), block3->funcName, font, 13, sfBlack);
    parameterCount3 = getText(getVector(602, 353), block3->paramCount, font, 13, sfBlack);
    returnType3 = getText(getVector(602, 369), block3->currentReturnDetail, font, 13, sfBlack);
    localVar3 = getText(getVector(602, 385), block3->currentLocalVar, font, 13, sfBlack);
   
    //STACKFRAME 4
    stackFrameText4 = getText(getVector(602, 421), "Stackframe 4", font, 13, sfBlack);
    struct StackFrameTexts *block4 = getStackFrameTexts(frames[3]);
    functionNameSF4 = getText(getVector(602, 437), block4->funcName, font, 13, sfBlack);
    parameterCount4 = getText(getVector(602, 453), block4->paramCount, font, 13, sfBlack);
    returnType4 = getText(getVector(602, 469), block4->currentReturnDetail, font, 13, sfBlack);
    localVar4 = getText(getVector(602, 485), block4->currentLocalVar, font, 13, sfBlack);
   
    //STACKFRAME 5
    stackFrameText5 = getText(getVector(602, 521), "Stackframe 5", font, 13, sfBlack);
    struct StackFrameTexts *block5 = getStackFrameTexts(frames[4]);
    functionNameSF5 = getText(getVector(602, 537), block5->funcName, font, 13, sfBlack);
    parameterCount5 = getText(getVector(602, 553), block5->paramCount, font, 13, sfBlack);
    returnType5 = getText(getVector(602, 569), block5->currentReturnDetail, font, 13, sfBlack);
    localVar5 = getText(getVector(602, 501), block5->currentLocalVar, font, 13, sfBlack);
   
    

    char *sourceCodeString = getSourceCode(Parser);
    sfText_setString(code, sourceCodeString);

    char *lineNumbersStr = getLineNumbersString();
    sfText_setString(lineNumbers, lineNumbersStr);
    

    fileNameChar = malloc(1024);
    strcpy(fileNameChar, "Dateiname: ");
    val1 = malloc(1024);
    strcpy(val1, getFileName(val1, Parser));
    strcat(fileNameChar, val1);
    sfText_setString(fileName, fileNameChar);

    runModeString = calloc(1024, sizeof(char));
    strcpy(runModeString, "PicoC Running Mode: ");
    val2 = calloc(1024, sizeof(char));
    strcpy(val2, getRunningMode(val2, Parser));
    strcat(runModeString, val2);
    sfText_setString(runningMode, runModeString);

    currentLineString = calloc(1024, sizeof(char));
    strcpy(currentLineString, "Ausgefuehrte Zeile: ");
    val3 = calloc(1024, sizeof(char));
    strcpy(val3, getLineAsString(val3, Parser));
    strcat(currentLineString, val3);
    sfText_setString(executedLine, currentLineString);

refresh:
    // Clear the screen
    sfRenderWindow_clear(window, sfWhite); //sfColor_fromRGBA(49, 60, 72, 1.0));

    if (countStackFrames(Parser) >= 1)
    {
        sfRenderWindow_drawRectangleShape(window, stackframeBox1, NULL);
        sfRenderWindow_drawText(window, stackFrameText1, NULL);
        sfRenderWindow_drawText(window, functionNameSF1, NULL);
        sfRenderWindow_drawText(window, parameterCount1, NULL);
        sfRenderWindow_drawText(window, localVar1, NULL);
        sfRenderWindow_drawText(window, returnType1, NULL);
    }
    if (countStackFrames(Parser) >= 2)
    {
        sfRenderWindow_drawRectangleShape(window, stackframeBox2, NULL);
        sfRenderWindow_drawText(window, stackFrameText2, NULL);
        sfRenderWindow_drawText(window, functionNameSF2, NULL);
        sfRenderWindow_drawText(window, parameterCount2, NULL);
        sfRenderWindow_drawText(window, returnType2, NULL);
        sfRenderWindow_drawText(window, localVar2, NULL);
        sfRenderWindow_drawText(window, returnAddress2, NULL);
    }
    if (countStackFrames(Parser) >= 3)
    {
        sfRenderWindow_drawRectangleShape(window, stackframeBox3, NULL);
        sfRenderWindow_drawText(window, stackFrameText3, NULL);
        sfRenderWindow_drawText(window, functionNameSF3, NULL);
        sfRenderWindow_drawText(window, parameterCount3, NULL);
        sfRenderWindow_drawText(window, returnType3, NULL);
        sfRenderWindow_drawText(window, localVar3, NULL);
        sfRenderWindow_drawText(window, returnAddress3, NULL);
    }
    if(countStackFrames(Parser) >= 4){    
        sfRenderWindow_drawRectangleShape(window, stackframeBox4, NULL);
        sfRenderWindow_drawText(window, stackFrameText4, NULL);
        sfRenderWindow_drawText(window, functionNameSF4, NULL);
        sfRenderWindow_drawText(window, parameterCount4, NULL);
        sfRenderWindow_drawText(window, returnType4, NULL);
        sfRenderWindow_drawText(window, localVar4, NULL);
        sfRenderWindow_drawText(window, returnAddress4, NULL); 
    }
    if(countStackFrames(Parser) >= 5){    
        sfRenderWindow_drawRectangleShape(window, stackframeBox5, NULL);
        sfRenderWindow_drawText(window, stackFrameText5, NULL);
        sfRenderWindow_drawText(window, functionNameSF5, NULL);
        sfRenderWindow_drawText(window, parameterCount5, NULL);
        sfRenderWindow_drawText(window, returnType5, NULL);
        sfRenderWindow_drawText(window, localVar5, NULL);
        sfRenderWindow_drawText(window, returnAddress5, NULL);  
    }

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
                    goto refresh;
                }
                else if (event.key.code == sfKeyDown)
                {
                    printf("Down Arrow pressed! \n");
                    codePos.y -= (float)10.0;
                    lineNumbersPos.y -= (float)10.0;
                    sfText_setPosition(code, codePos);
                    sfText_setPosition(lineNumbers, lineNumbersPos);
                    goto refresh;
                }
            }
            else if(event.type == sfEvtResized){
                goto refresh;
            }
        }
    }
breakloop:
    printf("test\n");
    delStackFrameTexts(block1);
    delStackFrameTexts(block2);
    delStackFrameTexts(block3);
    delStackFrameTexts(block4);
    delStackFrameTexts(block5);
    return 0;
}
