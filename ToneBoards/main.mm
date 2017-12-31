
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "scrollbar.hpp"

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

//#include "SoundHelperOBJ.h"
#include <cmath>
//#include <iostream>
#include <string>
#include <fstream>

#include "NSFileManager+DirectoryLocations.h"
//#import <Foundation/Foundation.h>

const int windowWidth = 800;
const int windowheight = 600;

//const unsigned SAMPLES = 49152;
//const unsigned SAMPLE_RATE = 98304;
//const unsigned AMPLITUDE = 30000;
const unsigned NOTES = 101;
const int volumeSTART = 100; //40;//50; //30; //20;
const int volumeZERO = 0;


std::string myKeys[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket", "RBracket", "SemiColon", "Comma", "Period", "Quote", "Slash", "BackSlash", "Tilde", "Equal", "Dash", "Space", "Return", "BackSpace", "Tab", "PageUp", "PageDown", "End", "Home", "Insert", "Delete", "Add", "Subtract", "Multiply", "Divide", "Left", "Right", "Up", "Down", "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7", "Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause", "KeyCount"};

void saveState(std::string cfgFile, int volume){
    NSString * tbAppSupport = [[NSFileManager defaultManager] applicationSupportDirectory];
    std::string stringtbAS([tbAppSupport UTF8String]);
    //std::cout << "called saveState: " << cfgFile << " " << "\n"; //displays correct
    //std::cout << resourcePath() << "\n";
    //NSString * myNSrpath = NSHomeDirectory();
    //std::cout << myNSrpath << " save\n";
    //std::string rpath([myNSrpath UTF8String]);
    //std::cout << rpath << " save\n";// = /Users/trygveloken/Library/Containers/com.kipplebits-.ToneBoards/Data
    std::ofstream dataout;//works no sandbox//works no sandbox//works no sandbox//works no sandbox//works no sandbox
    //dataout.open(resourcePath() + "data.txt", std::ofstream::trunc);//works no sandbox//works no sandbox//works no sandbox
    dataout.open(stringtbAS + "/data.txt", std::ofstream::trunc);
    dataout << cfgFile << "\n" << volume << std::endl; // << "\n";
    dataout.close();
}

int getSavedVolume(){
    NSString * tbAppSupport = [[NSFileManager defaultManager] applicationSupportDirectory];
    std::string stringtbAS([tbAppSupport UTF8String]);
    std::cout << stringtbAS << "\n";
    std::ifstream datain;//works no sandbox//works no sandbox//works no sandbox//works no sandbox//works no sandbox
    //datain.open(resourcePath() + "data.txt");//works no sandbox//works no sandbox//works no sandbox//works no sandbox
    datain.open(stringtbAS + "/data.txt");
    if (!datain.is_open()) {
        return 50;
    }
    //while(datain.good() && !datain.eof()){
    std::string line;
    getline(datain, line);
    std::cout << "line 1: " << line << "\n";
    getline(datain, line);
    std::cout << "line 2: " << line << "\n";
    //}
    datain.close();
    if(line == ""){
        return 50;
    }
    return std::stoi(line);
}

std::string getSavedCFGname(){
    NSString * tbAppSupport = [[NSFileManager defaultManager] applicationSupportDirectory];
    std::string stringtbAS([tbAppSupport UTF8String]);
    //std::cout << stringtbAS << " (get TEST App Support)\n\n";
    //NSString * musername =  NSFullUserName();
    //std::string mun([musername UTF8String]);
    //std::cout << mun << " get mun\n";
    //NSString * myNSrpath = NSHomeDirectory();
    //std::cout << myNSrpath << " get\n";
    //std::string * rpath = new std::string([myNSrpath UTF8String]);
    //std::string rpath([myNSrpath UTF8String]);
    //std::cout << *rpath << " get\n";
    //std::cout << rpath << " get rpath\n";
    std::ifstream datain;//works no sandbox//works no sandbox//works no sandbox//works no sandbox//works no sandbox
    //datain.open(resourcePath() + "data.txt");//works no sandbox//works no sandbox//works no sandbox//works no sandbox
    datain.open(stringtbAS + "/data.txt");
    if (!datain.is_open()) {
        return "Welcome_Intro";
    }
    //while(datain.good() && !datain.eof()){
    std::string line;
    getline(datain, line);
    //}
    datain.close();
    std::string retline = line;
    std::size_t found = line.find("_cfg");
    if (found!=std::string::npos) {
        retline = line.substr (0, found);
    }
    return retline;
}

std::string loadcfgSounds(std::string filename, int translators[NOTES], sf::SoundBuffer Buffers[NOTES], sf::Sound Sounds[NOTES]){
    //std::cout << "\nloadcfgSounds() called\n\n";
    //std::cout << "\n" << filename << " chosen\n";
    std::string retname = filename;
    std::ifstream datain;
    datain.open(resourcePath() + "sConfigFiles/" + filename + "_cfg_.txt");
    if (!datain.is_open()) {
        std::cout << "Config file not found!\n";
        ///////////////////////////////////////////////////////////////////////////
        std::string foldername = resourcePath() + "sConfigFiles";
        const char* cfoldername = foldername.c_str();
        std::string dnamestring = "";
        //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
        struct dirent *de=NULL;
        DIR *d=NULL;
        d=opendir(cfoldername);
        if(d == NULL)
        {
            perror("Couldn't open directory");
            //std::cout << "Couldn't open directory\n";
            //return(2);
        }
        // Loop while not NULL
        while((de = readdir(d))){
            //printf("open_dir: %s\n",de->d_name);
            dnamestring = de->d_name;
            if (dnamestring == "." || dnamestring == "..") {
                //do nothing
            }else if(dnamestring.substr(dnamestring.size()-9, dnamestring.size()-1) == "_cfg_.txt"){
                retname = dnamestring.substr(0, dnamestring.size()-9);
                break;
            }
        }
        //std::cout << "filecount#: " << mfilecount << "\n";
        closedir(d);
        ///////////////////////////////////////////////////////////////////////////
        datain.open(resourcePath() + "sConfigFiles/" + dnamestring);
        if (!datain.is_open()) {
            std::cerr << "Config file not found!\n";
            //return(2);
        }
    }
    for (int i=0; i<NOTES; i++) {
        //remember formatting:::::==>>outfile_RENAME << myKeys[i] << "<-::->" << (138 + i) <<"\n";
        std::string line;
        getline(datain, line);
        std::string tsub;
        for (int j=5; j<line.length(); j++) {
            if (line[j] == '>') {
                tsub = line.substr(j+1, line.length());
                break;
            }
        }
        //std::cout << line << "\t" << tsub << "\n";
        translators[i]= std::stoi(tsub);
        std::string sfilename = "TONESv10/tone_" + std::to_string(translators[i]) + "_.ogg";
        if (!Buffers[i].loadFromFile(resourcePath() + sfilename)){
            std::cerr << "could not load soundbuffer\n";
            //return -1;
        }
        Sounds[i].setBuffer(Buffers[i]);
        Sounds[i].setLoop(true);
    }
    datain.close();
    //std::cout << "\nloadcfgSounds() exit\n\n";
    return retname;
}

bool checkKey(int input) {
    bool output;
    switch(input) {
        case 0: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        }
            break;
            
        case 1: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::B);
        }
            break;
            
        case 2: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
        }
            break;
            
        case 3: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        }
            break;
            
        case 4: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
        }
            break;
            
        case 5: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
        }
            break;
            
        case 6: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::G);
        }
            break;
            
        case 7: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::H);
        }
            break;
            
        case 8: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::I);
        }
            break;
            
        case 9: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::J);
        }
            break;
            
        case 10: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::K);
        }
            break;
            
        case 11: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::L);
        }
            break;
            
        case 12: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
        }
            break;
            
        case 13: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::N);
        }
            break;
            
        case 14: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::O);
        }
            break;
            
        case 15: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
        }
            break;
            
        case 16: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
        }
            break;
            
        case 17: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
        }
            break;
            
        case 18: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        }
            break;
            
        case 19: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::T);
        }
            break;
            
        case 20: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::U);
        }
            break;
            
        case 21: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::V);
        }
            break;
            
        case 22: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        }
            break;
            
        case 23: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
        }
            break;
            
        case 24: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
        }
            break;
            
        case 25: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
        }
            break;
            
        case 26: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num0);
        }
            break;
            
        case 27: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
        }
            break;
            
        case 28: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
        }
            break;
            
        case 29: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
        }
            break;
            
        case 30: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num4);
        }
            break;
            
        case 31: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num5);
        }
            break;
            
        case 32: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num6);
        }
            break;
            
        case 33: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num7);
        }
            break;
            
        case 34: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num8);
        }
            break;
            
        case 35: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Num9);
        }
            break;
            
        case 36: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
        }
            break;
            
        case 37: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
        }
            break;
            
        case 38: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
        }
            break;
            
        case 39: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
        }
            break;
            
        case 40: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem);
        }
            break;
            
        case 41: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
        }
            break;
            
        case 42: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
        }
            break;
            
        case 43: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);
        }
            break;
            
        case 44: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem);
        }
            break;
            
        case 45: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Menu);
        }
            break;
            
        case 46: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket);
        }
            break;
            
        case 47: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket);
        }
            break;
            
        case 48: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon);
        }
            break;
            
        case 49: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Comma);
        }
            break;
            
        case 50: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Period);
        }
            break;
            
        case 51: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Quote);
        }
            break;
            
        case 52: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Slash);
        }
            break;
            
        case 53: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash);
        }
            break;
            
        case 54: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde);
        }
            break;
            
        case 55: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Equal);
        }
            break;
            
        case 56: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Dash);
        }
            break;
            
        case 57: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        }
            break;
            
        case 58: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
        }
            break;
            
        case 59: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
        }
            break;
            
        case 60: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
        }
            break;
            
        case 61: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp);
        }
            break;
            
        case 62: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown);
        }
            break;
            
        case 63: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::End);
        }
            break;
            
        case 64: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Home);
        }
            break;
            
        case 65: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Insert);
        }
            break;
            
        case 66: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Delete);
        }
            break;
            
        case 67: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Add);
        }
            break;
            
        case 68: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract);
        }
            break;
            
        case 69: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply);
        }
            break;
            
        case 70: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Divide);
        }
            break;
            
        case 71: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        }
            break;
            
        case 72: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        }
            break;
            
        case 73: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        }
            break;
            
        case 74: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        }
            break;
            
        case 75: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0);
        }
            break;
            
        case 76: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1);
        }
            break;
            
        case 77: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2);
        }
            break;
            
        case 78: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3);
        }
            break;
            
        case 79: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4);
        }
            break;
            
        case 80: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5);
        }
            break;
            
        case 81: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6);
        }
            break;
            
        case 82: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7);
        }
            break;
            
        case 83: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8);
        }
            break;
            
        case 84: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9);
        }
            break;
            
        case 85: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F1);
        }
            break;
            
        case 86: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F2);
        }
            break;
            
        case 87: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F3);
        }
            break;
            
        case 88: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F4);
        }
            break;
            
        case 89: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F5);
        }
            break;
            
        case 90: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F6);
        }
            break;
            
        case 91: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F7);
        }
            break;
            
        case 92: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F8);
        }
            break;
            
        case 93: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F9);
        }
            break;
            
        case 94: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F10);
        }
            break;
            
        case 95: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F11);
        }
            break;
            
        case 96: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F12);
        }
            break;
            
        case 97: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F13);
        }
            break;
            
        case 98: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F14);
        }
            break;
            
        case 99: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::F15);
        }
            break;
            
        case 100: {
            output = sf::Keyboard::isKeyPressed(sf::Keyboard::Pause);
        }
            break;
            
        default:
            break;
    }
    return output;
}

void playMyKeys(sf::Sound inSounds[NOTES], bool booKPs[NOTES], int vols[NOTES], int volHs[NOTES], int mastervol){
    for (int i=0; i<101; i++) {
        if(booKPs[i] && checkKey(i)){//rise_stable
            if(volHs[i] < 10000){
                volHs[i] += 25;
                vols[i] = volHs[i]/100*mastervol/100;
                inSounds[i].setVolume(vols[i]);
            }
        }
        if(!booKPs[i] && !checkKey(i)){//fall_stable
            if(volHs[i] >= 100){
                volHs[i] -= 100;
                vols[i] = volHs[i]/100*mastervol/100;
                inSounds[i].setVolume(vols[i]);
            }
            else{
                inSounds[i].stop();
            }
        }
        if(!booKPs[i] && checkKey(i)){//rise_initial
            booKPs[i] = true;
            vols[i] = volumeSTART*mastervol/100;
            volHs[i] = 100*volumeSTART*mastervol/100;
            inSounds[i].stop();
            inSounds[i].setVolume(vols[i]);
            inSounds[i].play();
        }
        if(booKPs[i] && !checkKey(i)){//fall_initial
            booKPs[i] = false;
        }
    }
    sf::sleep(sf::milliseconds(2));
}


int main(int, char const**)
{
    //windowfocus variable
    bool windowinfocus = false;
    // volume variable;
    int appvolume = getSavedVolume();
    std::cout << "appvolume = " << appvolume << "\n";
    //get startup CFG file
    std::string startcfgfilename = getSavedCFGname();
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowheight), "ToneBoards: ");
    sf::String::String titleSTRING = sf::String::String("ToneBoards: " + startcfgfilename);
    
    sf::VertexArray background_grad(sf::Quads, 4);
    
    background_grad[0].position = sf::Vector2f(0, 0);
    background_grad[1].position = sf::Vector2f(windowWidth, 0);
    background_grad[2].position = sf::Vector2f(windowWidth, windowheight);
    background_grad[3].position = sf::Vector2f(0, windowheight);
    
    background_grad[0].color = sf::Color::Cyan;//Red;
    background_grad[1].color = sf::Color::Blue;//Cyan;//Green;
    background_grad[2].color = sf::Color::Magenta;//Blue;
    background_grad[3].color = sf::Color::Red;//Magenta;
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "TBiconv1_1024.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "graphic.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    //sprite.setColor(sf::Color(255,255,255,32));
    sprite.setColor(sf::Color(0,0,0,32));
    //sprite.setPosition(sf::Vector2f(0.f, 0.f));
    sprite.setScale(sf::Vector2f(.9f, .9f));
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    std::string mpathprefix = resourcePath();
    mygui_test::scrollbar my_scrollbar(window, mygui_test::style::clean, mpathprefix, font);
    
    //sf::Text text(" MUSIC_KEYS:", font, 50);
    //text.setColor(sf::Color::Black);
    //________________________WINDOW_INIT_DONE_________________________
    
    //load Sounds
    int *mtranslators = new int[NOTES];
    sf::SoundBuffer *myBuffers = new sf::SoundBuffer[NOTES];///__________load sounds from files___________
    sf::Sound *mySounds = new sf::Sound[NOTES];
    //loadSOUNDS;
    std::string checkcfgfilename = loadcfgSounds(startcfgfilename, mtranslators, myBuffers, mySounds);
    titleSTRING = "ToneBoards: " + checkcfgfilename;
    bool *bKPs = new bool[NOTES];
    int *vHelpers = new int[NOTES];
    int *volumes = new int[NOTES];
    
    for (int i=0; i<NOTES; i++){//_______________________________________________init
        bKPs[i] = false;
        vHelpers[i]= volumeZERO;
        volumes[i] = volumeZERO;
    }
    sf::Clock clock;
    bool dccandidateP = false;
    bool dccandidateR = false;
    
    while (window.isOpen())
    {
        playMyKeys(mySounds, bKPs, volumes, vHelpers, appvolume);//-------------CALL_LISTENER-------------
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            // catch lose focus
            if (event.type == sf::Event::LostFocus){
                //std::cout << "window lost focus\n";//myGame.pause();
                windowinfocus = false;
            }
            //catch gain focus
            if (event.type == sf::Event::GainedFocus){
                //std::cout << "\t window gained focus\n";//myGame.resume();
                windowinfocus = true;
            }
            // catch the resize events
            if (event.type == sf::Event::Resized){
                // update the view to the new size of the window
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                
                background_grad[0].position = sf::Vector2f(0, 0);
                background_grad[1].position = sf::Vector2f(event.size.width, 0);
                background_grad[2].position = sf::Vector2f(event.size.width, event.size.height);
                background_grad[3].position = sf::Vector2f(0, event.size.height);
                
                sprite.setScale(sf::Vector2f(.9f*(event.size.width/800.f),.9f*(event.size.height/600.f)));
            }
            
            // Close window: exit // Escape pressed: exit
            //if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code ==
            //sf::Keyboard::Escape)) {
            if (event.type == sf::Event::Closed) {
                //delete[] mNOTESarray;// not valid no dynamic allocation
                saveState(startcfgfilename, appvolume);
                window.close();
            }
            
            if (windowinfocus) {
                // Mouse scroll
                my_scrollbar.mouseScroll(event, window);
                
                // Arrows scroll
                my_scrollbar.arrowScroll(event, window);
                
                // Mouse Drag scroll
                //my_scrollbar.mouseDrag(event, window);//called in update
                
                //select entry
                //my_scrollbar.selectEntry(event, window);//called in update
                int tmpselected = my_scrollbar.getSelected();
                if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) && tmpselected != -1) {
                    /////#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
                    std::string temp_loadfilename = my_scrollbar.getConfigFileName(tmpselected);
                    //std::cout << " load config file " << temp_loadfilename << "_cfg_.txt\n";
                    // rename savedata
                    startcfgfilename = temp_loadfilename;
                    saveState(startcfgfilename, appvolume);
                    //Insert loadfile call here vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                    temp_loadfilename = loadcfgSounds(startcfgfilename, mtranslators, myBuffers, mySounds);
                    //Insert loadfile call here ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                    /////#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
                    titleSTRING = "ToneBoards: " + temp_loadfilename;
                    my_scrollbar.resetSelected();
                }
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.mouseButton.button == sf::Mouse::Left){
                        //std::cout << "       pressed\n";
                        sf::Time time = clock.getElapsedTime();
                        if (!dccandidateP) {
                            clock.restart();
                        }
                        dccandidateP = true;
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased){
                    if (event.mouseButton.button == sf::Mouse::Left){
                        //std::cout << "  released\n";
                        if (dccandidateP && dccandidateR) {
                            //double click events here
                            if (tmpselected != -1) {
                                std::string temp_loadfilename = my_scrollbar.getConfigFileName(tmpselected);
                                //std::cout << " load config file " << temp_loadfilename << "_cfg_.txt\n";
                                // rename savedata
                                startcfgfilename = temp_loadfilename;
                                saveState(startcfgfilename, appvolume);
                                //Insert loadfile call here vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                                temp_loadfilename = loadcfgSounds(startcfgfilename, mtranslators, myBuffers, mySounds);
                                //Insert loadfile call here ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                                /////#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
                                titleSTRING = "ToneBoards: " + temp_loadfilename;
                                my_scrollbar.resetSelected();
                            }
                        }else{
                            //do nothing: single click events interfere with double click here
                        }
                        dccandidateR = true;
                    }
                }
                if (clock.getElapsedTime().asMilliseconds() > 200) {
                    dccandidateP = false;
                    dccandidateR = false;
                    clock.restart();
                }
            }
        }
        
        // Clear screen
        window.clear();
        
        //background
        window.draw(background_grad);
        
        // Draw the sprite
        window.draw(sprite);
        
        // Draw the string
        //window.draw(text);
        
        // update scrollbar
        if(windowinfocus){
            my_scrollbar.update(event, window);
        }
        
        //draw scrollbar
        window.draw(my_scrollbar);
        
        //set window Title
        window.setTitle(titleSTRING);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}

/*
 sf::Clock clock;
 ...
 Time time1 = clock.getElapsedTime();
 ...
 Time time2 = clock.restart();
 */

