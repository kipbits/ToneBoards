//
//  scrollbar.cpp
//  scrollbar_v0
//
//  Created on 11/1/15.
//  Copyright © 2015 kipplebits llc. All rights reserved.
//

#include "scrollbar.hpp"

const float bSizingHalf = 50.f;
const float bSizingWhole = 100.f;


mygui_test::scrollbar::scrollbar()
{
    
}

mygui_test::scrollbar::scrollbar(sf::RenderWindow& window, sf::Uint32 style, std::string pathprefix, sf::Font& font){
    
    /////////////////////////////////////////////////SETdisplayconfigfiles
    //std::cout << "\t***call setSIZE" << "\n";
    setCFileListSIZE(pathprefix);
    c_files_list = new std::string[cfg_list_size];// prepare c_files_list[]
    //std::cout << "\t***call import" << "\n";
    importConfigFiles(pathprefix);
    //std::cout << "\t***done with config list" << "\n";
    /////////////////////////////////////////////////
    
    m_size = sf::Vector2f(50.f, window.getSize().y - 100.f);//(w,h)
    ud_size = sf::Vector2f(50.f, 50.f);
    slider_size = sf::Vector2f(40.f, (window.getSize().y * (m_size.y - 10.f))/((float)cfg_list_size * 50.f));
    cfg_entry_size = sf::Vector2f(window.getSize().x - 50.f, 50.f);//#_#_#_#_#_#_#_# list entry size
    
    stepsize = 50.f;//(float) m_size.y/cfg_list_size;//100.f;// set_step_size_set_step_size_set_step_size_set_step_size
    //entryheight = buttonheight;
    
    stop_bound = (float) slider_size.y/2 + 55;//+50
    sbot_bound = (float) (window.getSize().y) - slider_size.y/2 - 55;//-50
    
    scrollbar_position.x = (float) (window.getSize().x) - 25;
    scrollbar_position.y = (float) (window.getSize().y)/2;
    upbutton_position.x = (float) (window.getSize().x) - 25;
    upbutton_position.y = (float) 25;
    downbutton_position.x = (float) (window.getSize().x) - 25;
    downbutton_position.y = (float) (window.getSize().y) - 25;
    slider_position.x = (float) (window.getSize().x) - 25;
    slider_position.y = (float) stop_bound;
    
    //std::cout << "x " << scrollbar_position.x << " y " << scrollbar_position.y << std::endl;
    
    bar_state = mygui_test::state::normal;
    upbutton_state = mygui_test::state::normal;
    downbutton_state = mygui_test::state::normal;
    utriangle_state = mygui_test::state::normal;
    dtriangle_state = mygui_test::state::normal;
    slider_state = mygui_test::state::normal;
    
    m_style = style;//mygui_test::style::listitem;//none;//save;
    
    switch(m_style)
    {
        case mygui_test::style::clean:
        {
            m_bgNormal = sf::Color(150,150,150,150);
            m_bgHover = sf::Color(175,175,175,150);
            m_bgClicked = sf::Color(255,255,255,150);
            m_bgSelected = sf::Color(100,150,200,150);
            //#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            am_bgNormal = sf::Color(255,255,255,150);
            am_bgHover = sf::Color(225,225,225,150);
            am_bgClicked = sf::Color(0,0,0,150);
            am_bgSelected = sf::Color(225,225,225,150);
            //#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            cfg1_bgNormal = sf::Color(255,255,255,75);
            cfg1_bgHover = sf::Color(255,255,255,125);
            cfg1_bgClicked = sf::Color(255,255,255,175);
            cfg1_bgSelected = sf::Color(255,255,255,225);
            
            cfg2_bgNormal = sf::Color(255,255,255,100);
            cfg2_bgHover = sf::Color(255,255,255,150);
            cfg2_bgClicked = sf::Color(255,255,255,200);
            cfg2_bgSelected = sf::Color(255,255,255,255);
            
            //cfg1_textNormal = sf::Color(0,0,0,100);
            cfg1_textNormal = sf::Color(0,0,0,150);
            //cfg1_textHover = sf::Color(0,0,0,150);
            cfg1_textHover = sf::Color(0,0,0,200);
            //cfg1_textClicked = sf::Color(0,0,0,200);
            cfg1_textClicked = sf::Color(0,0,0,255);
            //cfg1_textSelected = sf::Color(0,0,0,255);
            cfg1_textSelected = sf::Color(0,0,0,255);
            
            cfg2_textNormal = sf::Color(0,0,0,50);
            cfg2_textHover = sf::Color(0,0,0,100);
            cfg2_textClicked = sf::Color(0,0,0,150);
            cfg2_textSelected = sf::Color(0,0,0,200);
            //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
        }
            break;
            
        case mygui_test::style::alternate:
        {
            m_bgNormal = sf::Color(200,200,200,100);
            m_bgHover = sf::Color(225,225,225,100);
            m_bgClicked = sf::Color(0,0,0,100);
            m_bgSelected = sf::Color(225,225,225,100);
            //#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            am_bgNormal = sf::Color(255,255,255,150);
            am_bgHover = sf::Color(225,225,225,150);
            am_bgClicked = sf::Color(0,0,0,150);
            am_bgSelected = sf::Color(225,225,225,150);
            //#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            cfg1_bgNormal = sf::Color(255,255,255,50);
            cfg1_bgHover = sf::Color(255,255,255,100);
            cfg1_bgClicked = sf::Color(255,255,255,150);
            cfg1_bgSelected = sf::Color(255,255,255,200);
            cfg2_bgNormal = sf::Color(255,255,255,100);
            cfg2_bgHover = sf::Color(255,255,255,150);
            cfg2_bgClicked = sf::Color(255,255,255,200);
            cfg2_bgSelected = sf::Color(255,255,255,255);
            
            cfg1_textNormal = sf::Color(0,0,0,100);
            cfg1_textHover = sf::Color(0,0,0,150);
            cfg1_textClicked = sf::Color(0,0,0,200);
            cfg1_textSelected = sf::Color(0,0,0,255);
            cfg2_textNormal = sf::Color(0,0,0,50);
            cfg2_textHover = sf::Color(0,0,0,100);
            cfg2_textClicked = sf::Color(0,0,0,150);
            cfg2_textSelected = sf::Color(0,0,0,200);
            //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
        }
            break;
            
        default:
            break;
    }

    scroll_bar = sf::RectangleShape(m_size);
    scroll_bar.setOrigin(scroll_bar.getGlobalBounds().width/2, scroll_bar.getGlobalBounds().height/2);
    scroll_bar.setPosition(scrollbar_position);
    
    up_button = sf::RectangleShape(ud_size);
    up_button.setOrigin(up_button.getGlobalBounds().width/2, up_button.getGlobalBounds().height/2);
    up_button.setPosition(upbutton_position);
    
    down_button = sf::RectangleShape(ud_size);
    down_button.setOrigin(down_button.getGlobalBounds().width/2, down_button.getGlobalBounds().height/2);
    down_button.setPosition(downbutton_position);
    
    up_triangle = sf::ConvexShape();
    up_triangle.setPointCount(3);
    up_triangle.setPoint(0, sf::Vector2f(12.5, 0));
    up_triangle.setPoint(1, sf::Vector2f(0, 21.65));
    up_triangle.setPoint(2, sf::Vector2f(25, 21.65));
    up_triangle.setOrigin(up_triangle.getGlobalBounds().width/2, up_triangle.getGlobalBounds().height/2);
    up_triangle.setPosition(upbutton_position);
    
    down_triangle = sf::ConvexShape();
    down_triangle.setPointCount(3);
    down_triangle.setPoint(0, sf::Vector2f(12.5, 21.65));
    down_triangle.setPoint(1, sf::Vector2f(0, 0));
    down_triangle.setPoint(2, sf::Vector2f(25, 0));
    down_triangle.setOrigin(down_triangle.getGlobalBounds().width/2, down_triangle.getGlobalBounds().height/2);
    down_triangle.setPosition(downbutton_position);
    
    scroll_slider = sf::RectangleShape(slider_size);
    scroll_slider.setOrigin(scroll_slider.getGlobalBounds().width/2, scroll_slider.getGlobalBounds().height/2);
    scroll_slider.setPosition(slider_position);
    
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#list_positions
    cfg_entry_selected = -1;
    in_list_entries = new bool[cfg_list_size];
    cfg_entry_positions = new sf::Vector2f[cfg_list_size];
    cfg_text_positions = new sf::Vector2f[cfg_list_size];
    for (int j=0; j<cfg_list_size; j++) {
        cfg_entry_positions[j].x = (float) (window.getSize().x - 50.f)/2;
        cfg_entry_positions[j].y = 25.f + (50.f * j);
        cfg_text_positions[j].x = 25.f;
        cfg_text_positions[j].y = 5.f + (50.f * j);
    }
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#build scroll frame
    m_texts = new sf::Text[cfg_list_size];
    cfg_rect_list = new sf::RectangleShape[cfg_list_size];
    cfg_entry_states = new sf::Uint32[cfg_list_size];
    for (int i=0; i<cfg_list_size; i++) {
        m_texts[i].setFont(font);
        m_texts[i].setOrigin(m_texts[i].getGlobalBounds().width/2, m_texts[i].getGlobalBounds().height/2);
        m_texts[i].setString(c_files_list[i]);
        //m_texts[i].setColor(cfg_textNormal);
        
        cfg_entry_states[i] = mygui_test::state::normal;
        cfg_rect_list[i] = sf::RectangleShape(cfg_entry_size);
        cfg_rect_list[i].setOrigin(cfg_rect_list[i].getGlobalBounds().width/2, cfg_rect_list[i].getGlobalBounds().height/2);
        cfg_rect_list[i].setPosition(cfg_entry_positions[i]);
        m_texts[i].setPosition(cfg_text_positions[i]);
    }
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
}

mygui_test::scrollbar::~scrollbar()
{
    delete[] c_files_list;
}

void mygui_test::scrollbar::update(sf::Event& event, sf::RenderWindow& window)
{
    m_size = sf::Vector2f(50.f, window.sf::Window::getSize().y - 100.f);//(w,h)
    ud_size = sf::Vector2f(50.f, 50.f);
    slider_size = sf::Vector2f(40.f, (window.getSize().y * (m_size.y - 10.f))/((float)cfg_list_size * 50.f));
    cfg_entry_size = sf::Vector2f(window.getSize().x - 50.f, 50.f);
    
    stop_bound = (float) slider_size.y/2 + 55;//+50
    sbot_bound = (float) (window.getSize().y) - slider_size.y/2 - 55;//-50
    
    //perform updates for settings from user
    scrollbar_position.x = (float) (window.getSize().x) - 25;
    scrollbar_position.y = (float) (window.getSize().y)/2;
    upbutton_position.x = (float) (window.getSize().x) - 25;
    upbutton_position.y = (float) 25;
    downbutton_position.x = (float) (window.getSize().x) - 25;
    downbutton_position.y = (float) (window.getSize().y) - 25;
    slider_position.x = (float) (window.getSize().x) - 25;
    
    if (slider_position.y < stop_bound) {
        slider_position.y = (float) stop_bound;
    }else if (slider_position.y > sbot_bound){
        slider_position.y = (float) sbot_bound;
    }
    
    
    scroll_bar = sf::RectangleShape(m_size);
    scroll_bar.setOrigin(scroll_bar.getGlobalBounds().width/2, scroll_bar.getGlobalBounds().height/2);
    scroll_bar.setPosition(scrollbar_position);
    up_button = sf::RectangleShape(ud_size);
    up_button.setOrigin(up_button.getGlobalBounds().width/2, up_button.getGlobalBounds().height/2);
    up_button.setPosition(upbutton_position);
    down_button = sf::RectangleShape(ud_size);
    down_button.setOrigin(down_button.getGlobalBounds().width/2, down_button.getGlobalBounds().height/2);
    down_button.setPosition(downbutton_position);
    
    up_triangle = sf::ConvexShape();
    up_triangle.setPointCount(3);
    up_triangle.setPoint(0, sf::Vector2f(12.5, 0));
    up_triangle.setPoint(1, sf::Vector2f(0, 21.65));
    up_triangle.setPoint(2, sf::Vector2f(25, 21.65));
    up_triangle.setOrigin(up_triangle.getGlobalBounds().width/2, up_triangle.getGlobalBounds().height/2);
    up_triangle.setPosition(upbutton_position);
    down_triangle = sf::ConvexShape();
    down_triangle.setPointCount(3);
    down_triangle.setPoint(0, sf::Vector2f(12.5, 21.65));
    down_triangle.setPoint(1, sf::Vector2f(0, 0));
    down_triangle.setPoint(2, sf::Vector2f(25, 0));
    down_triangle.setOrigin(down_triangle.getGlobalBounds().width/2, down_triangle.getGlobalBounds().height/2);
    down_triangle.setPosition(downbutton_position);
    
    scroll_slider = sf::RectangleShape(slider_size);
    scroll_slider.setOrigin(scroll_slider.getGlobalBounds().width/2, scroll_slider.getGlobalBounds().height/2);
    scroll_slider.setPosition(slider_position);
    
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#update list position
        for (int i=0; i<cfg_list_size; i++) {
            cfg_entry_positions[i].x = (float) (window.getSize().x - 50.f)/2;
            cfg_entry_positions[i].y = 25.f+(50.f * i)-((slider_position.y - stop_bound)*50.f*cfg_list_size/(m_size.y-10.f));
            cfg_text_positions[i].y = 5.f+(50.f * i)-((slider_position.y - stop_bound)*50.f*cfg_list_size/(m_size.y-10.f));
            cfg_rect_list[i] = sf::RectangleShape(cfg_entry_size);
            cfg_rect_list[i].setOrigin(cfg_rect_list[i].getGlobalBounds().width/2, cfg_rect_list[i].getGlobalBounds().height/2);
            cfg_rect_list[i].setPosition(cfg_entry_positions[i]);
            m_texts[i].setPosition(cfg_text_positions[i]);
        }
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
    
    //perform updates for user mouse interactions
    //mouseScroll(event, window);
    //arrowScroll(event, window);
    mouseDrag(event, window);
    selectEntry(event, window);
    sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);
    
    bool mouseInscroll_bar = m_mousePosition.x >= scroll_bar.getPosition().x - scroll_bar.getGlobalBounds().width/2 && m_mousePosition.x <= scroll_bar.getPosition().x + scroll_bar.getGlobalBounds().width/2 && m_mousePosition.y >= scroll_bar.getPosition().y - scroll_bar.getGlobalBounds().height/2 && m_mousePosition.y <= scroll_bar.getPosition().y + scroll_bar.getGlobalBounds().height/2;
    
    bool mouseInup_button = m_mousePosition.x >= up_button.getPosition().x - up_button.getGlobalBounds().width/2 && m_mousePosition.x <= up_button.getPosition().x + up_button.getGlobalBounds().width/2 && m_mousePosition.y >= up_button.getPosition().y - up_button.getGlobalBounds().height/2 && m_mousePosition.y <= up_button.getPosition().y + up_button.getGlobalBounds().height/2;
    
    bool mouseIndown_button = m_mousePosition.x >= down_button.getPosition().x - down_button.getGlobalBounds().width/2 && m_mousePosition.x <= down_button.getPosition().x + down_button.getGlobalBounds().width/2 && m_mousePosition.y >= down_button.getPosition().y - down_button.getGlobalBounds().height/2 && m_mousePosition.y <= down_button.getPosition().y + down_button.getGlobalBounds().height/2;
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        //std::cout << "mx " << sf::Mouse::getPosition(window).x << " my " << sf::Mouse::getPosition(window).y << std::endl;
        if(mouseInscroll_bar){
            bar_state = mygui_test::state::clicked;
        }
        else{
            bar_state = mygui_test::state::normal;
        }
        if(mouseInup_button){
            upbutton_state = mygui_test::state::clicked;
            utriangle_state = mygui_test::state::clicked;
            if (slider_position.y > stop_bound) {
                slider_position.y  = slider_position.y - stepsize/100.f;// scroll up
            }
        }
        else{
            upbutton_state = mygui_test::state::normal;
            utriangle_state = mygui_test::state::normal;
        }
        if(mouseIndown_button){
            downbutton_state = mygui_test::state::clicked;
            dtriangle_state = mygui_test::state::clicked;
            if (slider_position.y < sbot_bound) {
                slider_position.y  = slider_position.y + stepsize/100.f;
            }
            // scroll down
        }
        else{
            downbutton_state = mygui_test::state::normal;
            dtriangle_state = mygui_test::state::normal;
        }
    }
    
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(mouseInscroll_bar){// && bar_state == mygui_test::state::clicked){
            bar_state = mygui_test::state::hovered;
        }
        else{
            bar_state = mygui_test::state::normal;
        }
        if(mouseInup_button){// && upbutton_state == mygui_test::state::clicked){
            upbutton_state = mygui_test::state::hovered;
            utriangle_state = mygui_test::state::hovered;
        }
        else{
            upbutton_state = mygui_test::state::normal;
            utriangle_state = mygui_test::state::normal;
        }
        if(mouseIndown_button){// && downbutton_state == mygui_test::state::clicked){
            downbutton_state = mygui_test::state::hovered;
            dtriangle_state = mygui_test::state::hovered;
        }
        else{
            downbutton_state = mygui_test::state::normal;
            dtriangle_state = mygui_test::state::normal;
        }
    }
    
    switch(bar_state)
    {
        case mygui_test::state::normal:
        {
            scroll_bar.setFillColor(m_bgNormal);
        }
            break;
            
        case mygui_test::state::hovered:
        {
            scroll_bar.setFillColor(m_bgHover);
        }
            break;
            
        case mygui_test::state::clicked:
        {
            scroll_bar.setFillColor(m_bgClicked);
        }
            break;
            
        case mygui_test::state::selected:
        {
            scroll_bar.setFillColor(m_bgSelected);
        }
            break;
         
        default:
            break;
    }
    
    switch(upbutton_state)
    {
        case mygui_test::state::normal:
        {
            up_button.setFillColor(m_bgNormal);
        }
            break;
            
        case mygui_test::state::hovered:
        {
            up_button.setFillColor(m_bgHover);
        }
            break;
            
        case mygui_test::state::clicked:
        {
            up_button.setFillColor(m_bgClicked);
        }
            break;
            
        case mygui_test::state::selected:
        {
            up_button.setFillColor(m_bgSelected);
        }
            break;
            
        default:
            break;
    }
    
    switch(downbutton_state)
    {
        case mygui_test::state::normal:
        {
            down_button.setFillColor(m_bgNormal);
        }
            break;
            
        case mygui_test::state::hovered:
        {
            down_button.setFillColor(m_bgHover);
        }
            break;
            
        case mygui_test::state::clicked:
        {
            down_button.setFillColor(m_bgClicked);
        }
            break;
            
        case mygui_test::state::selected:
        {
            down_button.setFillColor(m_bgSelected);
        }
            break;
            
        default:
            break;
    }
    
    switch(utriangle_state)
    {
        case mygui_test::state::normal:
        {
            up_triangle.setFillColor(am_bgNormal);
        }
            break;
            
        case mygui_test::state::hovered:
        {
            up_triangle.setFillColor(am_bgHover);
        }
            break;
            
        case mygui_test::state::clicked:
        {
            up_triangle.setFillColor(am_bgClicked);
        }
            break;
            
        case mygui_test::state::selected:
        {
            up_triangle.setFillColor(am_bgSelected);
        }
            break;
            
        default:
            break;
    }

    switch(dtriangle_state)
    {
        case mygui_test::state::normal:
        {
            down_triangle.setFillColor(am_bgNormal);
        }
            break;
            
        case mygui_test::state::hovered:
        {
            down_triangle.setFillColor(am_bgHover);
        }
            break;
            
        case mygui_test::state::clicked:
        {
            down_triangle.setFillColor(am_bgClicked);
        }
            break;
            
        case mygui_test::state::selected:
        {
            down_triangle.setFillColor(am_bgSelected);
        }
            break;
            
        default:
            break;
    }

    switch(slider_state)
    {
        case mygui_test::state::normal:
        {
            scroll_slider.setFillColor(am_bgNormal);
        }
            break;
            
        case mygui_test::state::hovered:
        {
            scroll_slider.setFillColor(am_bgHover);
        }
            break;
            
        case mygui_test::state::clicked:
        {
            scroll_slider.setFillColor(am_bgClicked);
        }
            break;
            
        case mygui_test::state::selected:
        {
            scroll_slider.setFillColor(am_bgSelected);
        }
            break;
            
        default:
            break;
    }
    
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#update scroll frame
    for (int j=0; j<cfg_list_size; j++) {
        if (j % 2 == 0 ) {
            //std::cout << "even: " << i << "\n";
            switch(cfg_entry_states[j])
            {
                case mygui_test::state::normal:
                {
                    cfg_rect_list[j].setFillColor(cfg1_bgNormal);
                    m_texts[j].setColor(cfg1_textNormal);
                }
                    break;
                    
                case mygui_test::state::hovered:
                {
                    cfg_rect_list[j].setFillColor(cfg1_bgHover);
                    m_texts[j].setColor(cfg1_textHover);
                }
                    break;
                    
                case mygui_test::state::clicked:
                {
                    cfg_rect_list[j].setFillColor(cfg1_bgClicked);
                    m_texts[j].setColor(cfg1_textClicked);
                }
                    break;
                    
                case mygui_test::state::selected:
                {
                    cfg_rect_list[j].setFillColor(cfg1_bgSelected);
                    m_texts[j].setColor(cfg1_textSelected);
                }
                    break;
                    
                default:
                    break;
            }
        }else{
            //std::cout << " odd: " << i << "\n";
            switch(cfg_entry_states[j])
            {
                case mygui_test::state::normal:
                {
                    cfg_rect_list[j].setFillColor(cfg2_bgNormal);
                    m_texts[j].setColor(cfg1_textNormal);
                }
                    break;
                    
                case mygui_test::state::hovered:
                {
                    cfg_rect_list[j].setFillColor(cfg2_bgHover);
                    m_texts[j].setColor(cfg1_textHover);
                }
                    break;
                    
                case mygui_test::state::clicked:
                {
                    cfg_rect_list[j].setFillColor(cfg2_bgClicked);
                    m_texts[j].setColor(cfg1_textClicked);
                }
                    break;
                    
                case mygui_test::state::selected:
                {
                    cfg_rect_list[j].setFillColor(cfg2_bgSelected);
                    m_texts[j].setColor(cfg1_textSelected);
                }
                    break;
                    
                default:
                    break;
            }
            
        }
    }
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
}

void mygui_test::scrollbar::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    switch(m_style)
    {
        case mygui_test::style::clean:
        {
            target.draw(scroll_bar, states);
            target.draw(up_button, states);
            target.draw(down_button, states);
            //#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            target.draw(up_triangle, states);
            target.draw(down_triangle, states);
            target.draw(scroll_slider, states);
            //#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#draw scrollframe
            for (int i=0; i<cfg_list_size; i++) {
                target.draw(cfg_rect_list[i], states);
                target.draw(m_texts[i], states);
            }
            //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
        }
            break;
            
        case mygui_test::style::alternate:
        {
            target.draw(scroll_bar, states);
            target.draw(up_button, states);
            target.draw(down_button, states);
            //#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            target.draw(up_triangle, states);
            target.draw(down_triangle, states);
            target.draw(scroll_slider, states);
            //#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
            //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#draw scrollframe
            for (int i=0; i<cfg_list_size; i++) {
                target.draw(cfg_rect_list[i], states);
                target.draw(m_texts[i], states);
            }
            //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
        }
            break;
            
        default:
            break;
    }
}

void mygui_test::scrollbar::mouseScroll(sf::Event& event, sf::RenderWindow& window){
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheel.delta == 1){
            //std::cout << "scroll d1  "<< event.mouseWheel.x << " " << event.mouseWheel.y << std::endl;
        }
        else if (event.mouseWheel.delta == 0){
            //std::cout << "scroll d0  "<< event.mouseWheel.x << " " << event.mouseWheel.y << std::endl;
            if (event.mouseWheel.x > 0) {
                if (slider_position.y > stop_bound) {
                    slider_position.y  -= stepsize/10.f;
                }
            }
            if (event.mouseWheel.x < 0) {
                if (slider_position.y < sbot_bound) {
                    slider_position.y  += stepsize/10.f;
                }
            }
        }
    }
}

void mygui_test::scrollbar::arrowScroll(sf::Event& event, sf::RenderWindow& window){
    if (event.key.code == sf::Keyboard::Up)
    {
        if (slider_position.y > stop_bound) {
            slider_position.y  -= stepsize/2.f;
        }
    }
    if (event.key.code == sf::Keyboard::Down)
    {
        if (slider_position.y < sbot_bound) {
            slider_position.y  += stepsize/2.f;
        }
    }
}

void mygui_test::scrollbar::mouseDrag(sf::Event& event, sf::RenderWindow& window){
    sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);
    
    bool mouseInslider = m_mousePosition.x >= scroll_slider.getPosition().x - scroll_slider.getGlobalBounds().width/2 && m_mousePosition.x <= scroll_slider.getPosition().x + scroll_slider.getGlobalBounds().width/2 && m_mousePosition.y >= scroll_slider.getPosition().y - scroll_slider.getGlobalBounds().height/2 && m_mousePosition.y <= scroll_slider.getPosition().y + scroll_slider.getGlobalBounds().height/2;
    
    bool mouseInscroll_bar = m_mousePosition.x >= scroll_bar.getPosition().x - scroll_bar.getGlobalBounds().width/2 && m_mousePosition.x <= scroll_bar.getPosition().x + scroll_bar.getGlobalBounds().width/2 && m_mousePosition.y >= scroll_bar.getPosition().y - scroll_bar.getGlobalBounds().height/2 && m_mousePosition.y <= scroll_bar.getPosition().y + scroll_bar.getGlobalBounds().height/2;
    
    switch(slider_state)
    {
        case mygui_test::state::normal:
        {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseInslider) {
                slider_state = mygui_test::state::hovered;
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseInslider && mouseInscroll_bar) {
                if (m_mousePosition.y < sbot_bound && m_mousePosition.y > stop_bound) {
                    slider_position.y = m_mousePosition.y;
                }else if (m_mousePosition.y > sbot_bound) {
                    slider_position.y = sbot_bound;
                }else if (m_mousePosition.y < stop_bound) {
                    slider_position.y = stop_bound;
                }
                slider_state = mygui_test::state::clicked;
            }
        }
            break;
            
        case mygui_test::state::hovered:
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseInslider)
            {
                slider_state = mygui_test::state::clicked;
            }
            if (!mouseInslider) {
                slider_state = mygui_test::state::normal;
            }
        }
            break;
            
        case mygui_test::state::clicked:
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (m_mousePosition.y != scrollbar_position.y) {
                    if (m_mousePosition.y < sbot_bound && m_mousePosition.y > stop_bound) {
                        slider_position.y = (float) m_mousePosition.y;
                    }else{
                        if (m_mousePosition.y > sbot_bound) {
                            slider_position.y = sbot_bound;
                        }
                        if (m_mousePosition.y < stop_bound) {
                            slider_position.y = stop_bound;
                        }
                    }
                }
            }
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (mouseInslider) {
                    slider_state = mygui_test::state::hovered;
                }else{
                    slider_state = mygui_test::state::normal;
                }
            }
        }
            break;
            
        case mygui_test::state::selected:
        {
            
        }
            break;
            
        default:
            break;
    }
    mouseDrag_position.x = m_mousePosition.x;
    mouseDrag_position.y = m_mousePosition.y;
}

void mygui_test::scrollbar::selectEntry(sf::Event& event, sf::RenderWindow& window){
    sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);
    
    for (int j=0; j<cfg_list_size; j++) {
        in_list_entries[j] = m_mousePosition.x >= cfg_rect_list[j].getPosition().x - cfg_rect_list[j].getGlobalBounds().width/2 && m_mousePosition.x <= cfg_rect_list[j].getPosition().x + cfg_rect_list[j].getGlobalBounds().width/2 && m_mousePosition.y >= cfg_rect_list[j].getPosition().y - cfg_rect_list[j].getGlobalBounds().height/2 && m_mousePosition.y <= cfg_rect_list[j].getPosition().y + cfg_rect_list[j].getGlobalBounds().height/2;
    }
    
    for (int k=0; k<cfg_list_size; k++) {
        switch (cfg_entry_states[k]){
            case mygui_test::state::normal:{
                if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && in_list_entries[k]) {
                    cfg_entry_states[k] = mygui_test::state::hovered;
                }
            }
                break;
            case mygui_test::state::hovered:{
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && in_list_entries[k])
                {
                    cfg_entry_states[k] = mygui_test::state::clicked;
                }
                if (!in_list_entries[k]) {
                    cfg_entry_states[k] = mygui_test::state::normal;
                }
            }
                break;
            case mygui_test::state::clicked:{
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    cfg_entry_states[k] = mygui_test::state::clicked;
                }
                if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (in_list_entries[k]) {
                        cfg_entry_states[k] = mygui_test::state::selected;
                        cfg_entry_selected = k;
                    }else{
                        cfg_entry_states[k] = mygui_test::state::normal;
                    }
                }
            }
                break;
            case mygui_test::state::selected:{
                if (cfg_entry_selected == k) {
                    cfg_entry_states[k] = mygui_test::state::selected;
                }else{
                    cfg_entry_states[k] = mygui_test::state::normal;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    cfg_entry_states[k] = mygui_test::state::normal;
                    cfg_entry_selected = -1;
                }
            }
                break;
            default:
                break;
        }
    }
}

void mygui_test::scrollbar::setCFileListSIZE(std::string pathprefix){
    std::string foldername = pathprefix + "sConfigFiles";
    const char* cfoldername = foldername.c_str();
    std::string filename = "";
    std::string line = "";
    int mfilecount = 0;
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
    struct dirent *de=NULL;
    DIR *d=NULL;
    d=opendir(cfoldername);
    if(d == NULL)
    {
        perror("Couldn't open directory");
        //std::cout << "Couldn't open directory\n";
        return(2);
    }
    // Loop while not NULL
    while((de = readdir(d))){
        //printf("open_dir: %s\n",de->d_name);
        std::string dnamestring = de->d_name;
        if (dnamestring == "." || dnamestring == "..") {
            //do nothing
        }else if(dnamestring.substr(dnamestring.size()-9, dnamestring.size()-1) == "_cfg_.txt"){
            mfilecount++;
        }
    }
    //std::cout << "filecount#: " << mfilecount << "\n";
    cfg_list_size = mfilecount;
    closedir(d);
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
}

void mygui_test::scrollbar::importConfigFiles(std::string pathprefix){
    std::string foldername = pathprefix + "sConfigFiles";
    const char* cfoldername = foldername.c_str();
    //std::string filename = "";
    std::string line = "";
    int mfilecount = 0;
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
    struct dirent *de=NULL;
    DIR *d=NULL;
    d=opendir(cfoldername);
    if(d == NULL)
    {
        perror("Couldn't open directory");
        //std::cout << "Couldn't open directory\n";
        return(2);
    }
    // Loop while not NULL
    while((de = readdir(d))){
        //printf("open_dir: %s\n",de->d_name);
        std::string dnamestring = de->d_name;
        if (dnamestring == "." || dnamestring == "..") {
            //do nothing
        }else if(dnamestring.substr(dnamestring.size()-9, dnamestring.size()-1) == "_cfg_.txt"){
            //filename = foldername + "/" + dnamestring;
            std::string displayconfigname = dnamestring.substr(0, dnamestring.size()-9);
            c_files_list[mfilecount] = displayconfigname;
            std::string testsarrayentry = c_files_list[mfilecount];
            //std::cout << "file\t" << testsarrayentry << " + _cfg_.txt" << "\n\n";
            mfilecount++;
        }
    }
    closedir(d);
    //_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#
}


int mygui_test::scrollbar::getSelected(){
    return cfg_entry_selected;
}

void mygui_test::scrollbar::resetSelected(){
    cfg_entry_selected = -1;
}

std::string mygui_test::scrollbar::getConfigFileName(int index){
    return c_files_list[index];
}
