//
//  scrollbar.hpp
//  scrollbar_v0
//
//  Created on 11/1/15.
//  Copyright © 2015 kipplebits llc. All rights reserved.
//

#ifndef scrollbar_hpp
#define scrollbar_hpp
#include <sys/types.h>
#include <dirent.h>

#include <stdlib.h>

#include <fstream>

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

namespace mygui_test{
    
    namespace style
    {
        enum
        {
            clean = 0,
            alternate = 1
        };
    };
    
    namespace state
    {
        enum
        {
            normal = 0,
            hovered = 1,
            clicked = 2,
            selected = 3
        };
    };
    
    class scrollbar : public sf::Drawable{
        public:
            scrollbar();
            //scrollbar(sf::RenderWindow& window, sf::Uint32 style, sf::Uint32 style2, int listlength, float buttonheight, std::string pathprefix);
            scrollbar(sf::RenderWindow& window, sf::Uint32 style, std::string pathprefix, sf::Font& font);
            ~scrollbar();
        
            /////////////////////////////////////////////////////////////////import Config files
            void setCFileListSIZE(std::string pathprefix);
            void importConfigFiles(std::string pathprefix);
            // fix build, update, draw
            int getSelected();
            void resetSelected();
            std::string getConfigFileName(int index);
            /////////////////////////////////////////////////////////////////import Config files
        
            void setColorNormal(sf::Color bgNormal){m_bgNormal = bgNormal;};
            void setColorHover(sf::Color bgHover){m_bgHover = bgHover;};
            void setColorClicked(sf::Color bgClicked){m_bgClicked = bgClicked;};
            void setColorselected(sf::Color bgSelected){m_bgSelected = bgSelected;};
        
            void setPosition(sf::Vector2f position){scrollbar_position = position;};
        
            sf::Vector2f getPosition(){return scrollbar_position;};
            //sf::Vector2f getDimensions(){return sf::Vector2f(scroll_bar.getGlobalBounds().width, scroll_bar.getGlobalBounds().height + up_button.getGlobalBounds().height + down_button.getGlobalBounds().height);};
            sf::Uint32 getState(){return bar_state;};
        
            void update(sf::Event& event, sf::RenderWindow& window);
            void mouseScroll(sf::Event& event, sf::RenderWindow& window);
            void arrowScroll(sf::Event& event, sf::RenderWindow& window);
            void mouseDrag(sf::Event& event, sf::RenderWindow& window);
            void selectEntry(sf::Event& event, sf::RenderWindow& window);
    
        private:
        
            virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

        private:
        
            sf::Color m_bgNormal;
            sf::Color m_bgHover;
            sf::Color m_bgClicked;
            sf::Color m_bgSelected;
        
            sf::Color am_bgNormal;
            sf::Color am_bgHover;
            sf::Color am_bgClicked;
            sf::Color am_bgSelected;
        
            //######//######//######//######cfg colors//check
            sf::Color cfg1_bgNormal;//check
            sf::Color cfg1_bgHover;
            sf::Color cfg1_bgClicked;
            sf::Color cfg1_bgSelected;
            sf::Color cfg2_bgNormal;//check
            sf::Color cfg2_bgHover;
            sf::Color cfg2_bgClicked;
            sf::Color cfg2_bgSelected;
        
            sf::Color cfg1_textNormal;//check
            sf::Color cfg1_textHover;
            sf::Color cfg1_textClicked;
            sf::Color cfg1_textSelected;
            sf::Color cfg2_textNormal;//check
            sf::Color cfg2_textHover;
            sf::Color cfg2_textClicked;
            sf::Color cfg2_textSelected;
            //######//######//######//######cfg colors
        
            sf::Vector2f m_size;
            sf::Vector2f ud_size;
            sf::Vector2f slider_size;
            //######//######//######//######
            sf::Vector2f cfg_entry_size; // check
            //######//######//######//######
        
            sf::Vector2f scrollbar_position;
            sf::Vector2f upbutton_position;
            sf::Vector2f downbutton_position;
            sf::Vector2f slider_position;
            //######//######//######//######
            sf::Vector2f * cfg_entry_positions; //check
            sf::Vector2f * cfg_text_positions;
            //######//######//######//######
        
            sf::Vector2i mouseDrag_position;
        
            float stop_bound;
            float sbot_bound;
            float stepsize;
            //float entryheight;
        
            /////////////////////////////////////////////////////////////////config files
            int cfg_list_size;
            std::string * c_files_list;
            /////////////////////////////////////////////////////////////////config files
        
            sf::Uint32 m_style;
        
            sf::Uint32 bar_state;
            sf::Uint32 upbutton_state;
            sf::Uint32 downbutton_state;
            sf::Uint32 slider_state;
            sf::Uint32 utriangle_state;
            sf::Uint32 dtriangle_state;
            //######//######//######//######
            sf::Uint32 * cfg_entry_states; //check
            //######//######//######//######
        
            sf::RectangleShape scroll_slider;
            sf::RectangleShape scroll_bar;
            sf::RectangleShape up_button;
            sf::RectangleShape down_button;
            sf::ConvexShape up_triangle;
            sf::ConvexShape down_triangle;
            //######//######//######//######
            sf::RectangleShape * cfg_rect_list; //check
            sf::Text * m_texts;
            //sf::Text * m_shadows;
            int cfg_entry_selected;
            bool * in_list_entries;
            //######//######//######//######
    };
};
#endif /* scrollbar_hpp */
