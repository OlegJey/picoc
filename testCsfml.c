#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "picoc.h"

int main()//struct ParseState *Parser)
{
    sfVideoMode mode = {1200, 600, 32};
    sfRenderWindow* window;
    sfFont* font;
    sfText* nextStep;
    sfVector2f nextStepPos = {500, 21};
    sfText* code;
    sfVector2f codePos = {50, 80};
    sfText* lineNumbers;
    sfVector2f lineNumbersPos = {20, 80};
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
    
    
    infoBlock = sfRectangleShape_create();
    sfRectangleShape_setSize(infoBlock, infoBlockSize);
    sfRectangleShape_setFillColor(infoBlock, sfCyan);
    sfRectangleShape_setPosition(infoBlock, infoBlockPos);
    
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

    
    
    FILE* file = fopen("test.c", "r");
    char line[256];
    char sourceCode[10000];
    int lineCount = 0;
    while(fgets(line, sizeof(line), file)){
        strcat(sourceCode, line);
        lineCount++;
        //printf("%s", line);
    }
    
    code = sfText_create();
    sfText_setString(code, sourceCode);
    sfText_setFont(code, font);
    sfText_setCharacterSize(code, 13);
    sfText_setColor(code, sfBlack);
    sfText_setPosition(code, codePos);
    
    char lineNumbersStr[lineCount*2+1];
    char buffer[20];
  
    for(int i=1; i<=lineCount; i++){
        sprintf(buffer, "%d", i); //int to char
        lineNumbersStr[i-1] = buffer[0];
        strcat(lineNumbersStr, "\n");
        
    }
   
    
    lineNumbers = sfText_create();
    sfText_setString(lineNumbers, lineNumbersStr);
    sfText_setFont(lineNumbers, font);
    sfText_setCharacterSize(lineNumbers, 13);
    sfText_setColor(lineNumbers, sfBlack);
    sfText_setPosition(lineNumbers, lineNumbersPos);
    
    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfWhite);

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

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfText_destroy(nextStep);
    sfText_destroy(code);
    sfFont_destroy(font);
    sfText_destroy(lineNumbers);
    sfRectangleShape_destroy(infoBlock);
    sfRectangleShape_destroy(stackframe1);
    sfRectangleShape_destroy(stackframe2);
    sfRectangleShape_destroy(stackframe3);
    sfRenderWindow_destroy(window);

return 1;
    
}
