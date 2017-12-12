#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 600), "PicoC GUI");
    sf::RectangleShape stack(sf::Vector2f(400.f, 100.f));
    stack.setFillColor(sf::Color::Cyan);
    stack.setPosition(800,50);
   // stack.setOrigin(stack.getSize().x/2, stack.getSize().y/2);
    
    sf::RectangleShape stack1(sf::Vector2f(400.f, 100.f));
    stack1.setFillColor(sf::Color::Cyan);
    stack1.setPosition(800,150);
    
    sf::RectangleShape stack2(sf::Vector2f(400.f, 100.f));
    stack2.setFillColor(sf::Color::Red);
    stack2.setPosition(800,250);
    
    sf::RectangleShape stack3(sf::Vector2f(400.f, 100.f));
    stack3.setFillColor(sf::Color::Green);
    stack3.setPosition(800,350);
    
    std::ifstream file("test.c");
    std::string str;
    std::string sourceCode;
    while(std::getline(file, str)){
        sourceCode += str;
        sourceCode.push_back('\n');
    }
    
    std::string lineNumbers;
    for(int i=1; i<16; i++){        //Anzahl lines einsetzen
        lineNumbers += std::to_string(i);
        lineNumbers.push_back('\n');
    }
    
    sf::Font font;
    font.loadFromFile("arial.ttf");
    
    sf::Text numbers(lineNumbers, font);
    numbers.setCharacterSize(13);
    numbers.setStyle(sf::Text::Regular);
    numbers.setColor(sf::Color::Black);
    numbers.setPosition(20, 80);
    
    sf::Text line(sourceCode, font);
    line.setCharacterSize(13);
    line.setStyle(sf::Text::Regular);
    line.setColor(sf::Color::Black);
    line.setPosition(50, 80);

    sf::Text nextStep("Mit Leertaste zum naechsten Schritt", font);
    nextStep.setCharacterSize(17);
    nextStep.setStyle(sf::Text::Regular);
    nextStep.setColor(sf::Color::Black);
    nextStep.setPosition(window.getView().getCenter().x/2, 21);
    
    sf::Text fileName("Dateiname: Beispiel", font);
    fileName.setCharacterSize(13);
    fileName.setStyle(sf::Text::Regular);
    fileName.setColor(sf::Color::Black);
    fileName.setPosition(802, 51);
    
    sf::Text runningMode("PicoC Running Mode: ", font);
    runningMode.setCharacterSize(13);
    runningMode.setStyle(sf::Text::Regular);
    runningMode.setColor(sf::Color::Black);
    runningMode.setPosition(802, 71);
    
    sf::Text executedLine("Executed Line: ", font);
    executedLine.setCharacterSize(13);
    executedLine.setStyle(sf::Text::Regular);
    executedLine.setColor(sf::Color::Black);
    executedLine.setPosition(802, 91);
    
    sf::Text functionName("Funktionsname: ", font);
    functionName.setCharacterSize(13);
    functionName.setStyle(sf::Text::Regular);
    functionName.setColor(sf::Color::Black);
    functionName.setPosition(802, 111);
    
    sf::Text parameterCount("Anzahl Parameter: ", font);
    parameterCount.setCharacterSize(13);
    parameterCount.setStyle(sf::Text::Regular);
    parameterCount.setColor(sf::Color::Black);
    parameterCount.setPosition(802, 131);
    
    sf::Text returnType("Rueckgabetyp: ", font);
    returnType.setCharacterSize(13);
    returnType.setStyle(sf::Text::Regular);
    returnType.setColor(sf::Color::Black);
    returnType.setPosition(802, 151);
    
    sf::Text returnValue("Rueckgabewert: ", font);
    returnValue.setCharacterSize(13);
    returnValue.setStyle(sf::Text::Regular);
    returnValue.setColor(sf::Color::Black);
    returnValue.setPosition(802, 171);

    sf::Text returnAddress("Ruecksprungadresse: ", font);
    returnAddress.setCharacterSize(13);
    returnAddress.setStyle(sf::Text::Regular);
    returnAddress.setColor(sf::Color::Black);
    returnAddress.setPosition(802, 191);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
            {
            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
            else if(event.type == sf::Event::KeyPressed)
            {
             if(event.key.code == sf::Keyboard::Space)
             {
                 //execute next line with PicoC
             }
            }
        }
        

        window.clear(sf::Color::White);
        window.draw(stack);
        window.draw(stack1);
        window.draw(stack2);
        window.draw(stack3);
        window.draw(nextStep);
        window.draw(numbers);
        window.draw(line);
        window.draw(fileName);
        window.draw(parameterCount);
        window.draw(runningMode);
        window.draw(executedLine);
        window.draw(functionName);
        window.draw(returnType);
        window.draw(returnValue);
        window.draw(returnAddress);
        
        window.display();
    }

    return 0;
}
