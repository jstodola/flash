#ifndef MENU_H
#define MENU_H

class subMenu;
class menuLeaf;

class menuItem {
  public:
    menuItem(const prog_char *label);
    virtual void get_label(char *buffer);
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
  private:
    const prog_char *_label;
    menuItem *_parent;
    menuItem *_previous;
    menuItem *_next;
};

class menuLeaf : public menuItem {
  public:
    menuLeaf(const prog_char *label);
};

class radioItem : public menuItem {
  friend class checkItem;
  public:
    radioItem(const prog_char *label, uint8_t *variable, uint8_t value);
    virtual void get_label(char *buffer);
    virtual menuItem* do_action();
  private:
    virtual uint8_t is_selected();
    uint8_t *_variable;
    uint8_t _value;
};

class checkItem : public radioItem {
  public:
    checkItem(const prog_char *label, uint8_t *variable, uint8_t value);
    virtual menuItem* do_action();
  private:
    virtual uint8_t is_selected();
};

class subMenu : public menuItem {
  public:
    subMenu(const prog_char *label);
    virtual void append(menuItem &new_item);
    virtual menuItem* get_first();
    virtual menuItem* do_action();
  private:
    menuItem *_first;
    menuItem *_last;
};

class menuCore : public subMenu {
  public:
    menuCore();
    void append(menuItem &new_item);
    void attach_display(display &lcd);
    void print();
    void action(uint8_t move);
  private:
    display *_lcd;
    menuItem *_selected_item;
    uint8_t _last_move;
    uint8_t _last_lcd_row;
};

#endif
