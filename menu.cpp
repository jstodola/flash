#include <Arduino.h>
#include <avr/pgmspace.h>
#include "common.h"
#include "display.h"
#include "menu.h"
#include "button.h"

extern buttonsReader buttons_reader;
extern char buffer[];

// menuItem
menuItem::menuItem(const prog_char *label) {
    _label = label;
    _parent = 0;
    _previous = 0;
    _next = 0;
    _root_menu = 0;
}

void menuItem::get_label(char *buffer) {
    strcpy_P(buffer, _label);
}

void menuItem::set_parent(menuItem *parent) {
    _parent = parent;
}

void menuItem::set_next(menuItem &next_item) {
    _next = &next_item;
}

void menuItem::set_previous(menuItem &previous_item) {
    _previous = &previous_item;
}

void menuItem::set_root_menu(menuCore *root_menu) {
    _root_menu = root_menu;
}

menuItem* menuItem::get_first() {
    return this;
}

menuItem* menuItem::get_next() {
    return _next;
}

menuItem* menuItem::get_previous() {
    return _previous;
}

menuItem* menuItem::get_parent() {
    return _parent;
}

menuCore* menuItem::get_root_menu() {
    return _root_menu;
}

menuItem* menuItem::do_action() {
    return 0;
}

uint8_t menuItem::count_next() {
    menuItem *next = this;
    uint8_t count = 0;

    while( (next = next->get_next()) ) {
        count++;
    }
    return count;
}

uint8_t menuItem::count_previous() {
    menuItem *previous = this;
    uint8_t count = 0;

    while( (previous = previous->get_previous()) ) {
        count++;
    }
    return count;
}

// menuLeaf
menuLeaf::menuLeaf(const prog_char *label) : menuItem(label) {
}

// menuRun
menuRun::menuRun(const prog_char *label, callback_function f) : menuLeaf(label) {
    _f = f;
}

menuItem* menuRun::do_action() {
    _f();
    return 0;
}

// menuDialog
menuDialog::menuDialog(const prog_char *label, const prog_char *question) : menuLeaf(label) {
    _question = question;
}

display* menuDialog::get_display() {
    menuItem *tmp;
    display *lcd;
    
    // first we need to find lcd - go up through menu items
    tmp = this;
    while(tmp->get_parent()) {
        tmp = tmp->get_parent();
    }
    // items in root menu don't have parrents, but knows root menu item with lcd
    lcd = tmp->get_root_menu()->get_display();
    
    return lcd;
}

void menuDialog::get_question(char *buffer) {
    strcpy_P(buffer, _question);
}

// enterNumberItem
enterNumberItem::enterNumberItem(const prog_char *label,
                                 const prog_char *question,
                                 int *variable,
                                 callback_function_int f) : menuDialog(label, question) {
    _variable = variable;
    _f = f;
}

menuItem* enterNumberItem::do_action() {
    display *lcd;
    int value;
    uint8_t button;

    lcd = get_display();
    get_question(buffer);
    value = *_variable;

    do {
        lcd->clear();
        lcd->print(buffer);
        
        lcd->setCursor(0, 2);
        lcd->print(value);
        
        // wait for some useful key
        do{
            button = buttons_reader.read();
        } while(button == IDLE);

        if(button == UP) {
            value++;
        } else if(button == DOWN) {
            value--;
            if(value < 0) {
                value = 0;
            }
        }
        if(_f) {
            _f(value);
        }

    } while(button == UP || button == DOWN);
    
    // if not "cancel", save value
    if(button != LEFT) {
        *_variable = value;
    }

    return 0;
}

// yesNoItem
yesNoItem::yesNoItem(const prog_char *label,
                     const prog_char *question,
                     uint8_t *variable) : menuDialog(label, question) {
    _variable = variable;
}

menuItem* yesNoItem::do_action() {
    display *lcd;
    uint8_t value;
    uint8_t button;

    lcd = get_display();
    value = *_variable;

    do {
        lcd->clear();
        get_question(buffer);
        lcd->print(buffer);
        
        if(value) {
            strcpy_P(buffer, yes_sel);
        } else {
            strcpy_P(buffer, yes_unsel);
        }
        lcd->setCursor(0, 2);
        lcd->print(buffer);
 
        if(value) {
            strcpy_P(buffer, no_unsel);
        } else {
            strcpy_P(buffer, no_sel);
        }
        lcd->setCursor(0, 3);
        lcd->print(buffer);
        
        // wait for some useful key
        do{
            button = buttons_reader.read();
        } while(button == IDLE);

        if(button == UP) {
            value = 1;
        } else if(button == DOWN) {
            value = 0;
        }

    } while(button == UP || button == DOWN);
    
    // if not "cancel", save value
    if(button != LEFT) {
        *_variable = value;
    }

    return 0;
}

// radioItem
radioItem::radioItem(const prog_char *label, uint8_t *variable, uint8_t value) : menuItem(label) {
    _variable = variable;
    _value = value;
}

uint8_t radioItem::is_selected() {
    if(*_variable == _value) {
        return 1;
    } else {
        return 0;
    }
}

void radioItem::get_label(char *buffer) {
    buffer[0] = ' ';
    if(is_selected()) {
        buffer[0] = '*';
    }
    menuItem::get_label(buffer + 1) ;
}

menuItem* radioItem::do_action() {
    *_variable = _value;
    return 0;
}

// checkItem
checkItem::checkItem(const prog_char *label, uint8_t *variable, uint8_t value) : radioItem(label, variable, value){
}

uint8_t checkItem::is_selected() {
    if(*_variable & _value) {
        return 1;
    } else {
        return 0;
    }
}

menuItem* checkItem::do_action() {
    *_variable = *_variable ^ _value; // toggle
    return 0;
}

// subMenu
subMenu::subMenu(const prog_char *label) : menuItem(label) {
    _first = 0;
    _last = 0;
}

void subMenu::append(menuItem &new_item) {
    new_item.set_parent(this);
    // empty list of items
    if(_last == 0) {
        _first = &new_item;
        _last = &new_item;
    } else {
        new_item.set_previous(*_last);
        _last->set_next(new_item);
        _last = &new_item;
    }
}

menuItem* subMenu::get_first() {
    return _first;
}

menuItem* subMenu::do_action() {
    return get_first();
}

// menuCore
void menuCore::append(menuItem &new_item) {
    subMenu::append(new_item);
    // items in root menu don't have parent
    new_item.set_parent(0);
    // but know root menu
    new_item.set_root_menu(this);
}

menuCore::menuCore() : subMenu(0){
    _selected_item = 0;
    _last_move = IDLE;
    _last_lcd_row = 0;
    _lcd = 0;
}

void menuCore::attach_display(display &lcd) {
    _lcd = &lcd;
}

display* menuCore::get_display() {
    return _lcd;
}

void menuCore::action(uint8_t move) {
    
    menuItem *new_selected = 0;

    _last_move = move;

    if(_selected_item == 0) {
        _selected_item = get_first();
    } else {
        switch (move) {
            case DOWN:
                new_selected = _selected_item->get_next();
                break;
             case UP:
                new_selected = _selected_item->get_previous();
                break;
             case LEFT:
                new_selected = _selected_item->get_parent();
                break;
             case OK:
             case RIGHT:
                new_selected = _selected_item->do_action();
                break;
        }

        if(new_selected) {
            this->_selected_item = new_selected;
        }
    }
    print();
}

void menuCore::print() {
    menuItem* tmp;
    uint8_t lcd_rows;
    uint8_t previous_items;
    uint8_t next_items;
    uint8_t lcd_row;
    uint8_t i;
    uint8_t remaining;

    // print only if lcd is attached
    if(_lcd == 0) {
        return;
    }

    // no selected_item? select the first one in menu
    if(_selected_item == 0) {
        _selected_item = get_first();
    }

    // find ideal place for selected item on lcd
    previous_items = _selected_item->count_previous();
    next_items = _selected_item->count_next();
    lcd_rows = _lcd->get_rows();
    
    //all items fit on lcd
    if(previous_items + next_items + 1 <= lcd_rows) {
        lcd_row = previous_items;
    } else if(previous_items == 0) { // first item selected
        lcd_row = 0;
    } else if(next_items == 0) {     // last item selected
        lcd_row = lcd_rows - 1;
    } else if(_last_move == DOWN) {
        lcd_row = lcd_rows - 2;
        if(lcd_row - _last_lcd_row > 1) { // too big skip
            lcd_row = _last_lcd_row + 1;  // skip only one row
        }
    } else if(_last_move == UP) {
        lcd_row = 1;
        if(_last_lcd_row - lcd_row > 1) {
            lcd_row = _last_lcd_row - 1;
        }
    } else {    // unknown position
        lcd_row = (lcd_rows * previous_items + 1) / (previous_items + next_items + 1);
    }
    
    _lcd->clear();

    // display items before the current
    tmp = _selected_item->get_previous();
    for(i = lcd_row; i; i--) {
        tmp->get_label(buffer);
        _lcd->setCursor(0, i - 1);
        _lcd->print(" ");
        _lcd->print(buffer);
        tmp = tmp->get_previous();
    }

    // display the current item
    _lcd->setCursor(0, lcd_row);
    _lcd->print("*");
    _selected_item->get_label(buffer);
    _lcd->print(buffer);

    // display next items
    remaining = (next_items < lcd_rows - lcd_row - 1) ? next_items : lcd_rows - lcd_row - 1;  // minimal
    tmp = _selected_item->get_next();
    for(i = 0; i < remaining; i++) {
        tmp->get_label(buffer);
        _lcd->setCursor(0, i + lcd_row + 1);
        _lcd->print(" ");
        _lcd->print(buffer);
        tmp = tmp->get_next();
    }

    _last_lcd_row = lcd_row; 

}
