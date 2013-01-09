#ifndef MENU_H
#define MENU_H

class subMenu;
class menuLeaf;

class menuItem {
    const prog_char *_label;
    menuItem *_parent;
    menuItem *_previous;
    menuItem *_next;
  public:
    menuItem(const prog_char *label);
    void get_label(char *buffer);
    void set_parent(menuItem *parent);
    void set_next(menuItem &next_item);
    void set_previous(menuItem &previous_item);
    virtual menuItem* get_first();
    menuItem* get_next();
    menuItem* get_previous();
    menuItem* get_parent();
    virtual menuItem* do_action();
    uint8_t count_next();
    uint8_t count_previous();
};

class menuLeaf : public menuItem {
  public:
    menuLeaf(const prog_char *label);
};

class subMenu : public menuItem {
    menuItem *_first;
    menuItem *_last;
  public:
    subMenu(const prog_char *label);
    virtual void append(menuItem &new_item);
    menuItem* get_first();
    menuItem* do_action();
};

class menuCore : public subMenu {
    display *_lcd;
    menuItem *_selected_item;
    uint8_t _last_move;
    uint8_t _last_lcd_row;
  public:
    menuCore();
    void append(menuItem &new_item);
    void attach_display(display &lcd);
    void print();
    void action(uint8_t move);
};

#endif
