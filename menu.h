#ifndef MENU_H
#define MENU_H

class subMenu;
class menuLeaf;
class menuCore;

PROGMEM const prog_char yes_sel[]   = "> YES <";
PROGMEM const prog_char yes_unsel[] = "  YES";
PROGMEM const prog_char no_sel[]    = "> NO  <";
PROGMEM const prog_char no_unsel[]  = "  NO";

typedef void (*callback_function)(void);

class menuItem {
  public:
    menuItem(const prog_char *label);
    virtual void get_label(char *buffer);
    void set_parent(menuItem *parent);
    void set_next(menuItem &next_item);
    void set_previous(menuItem &previous_item);
    void set_root_menu(menuCore *root_menu);
    virtual menuItem* get_first();
    menuItem* get_next();
    menuItem* get_previous();
    menuItem* get_parent();
    menuCore* get_root_menu();
    virtual menuItem* do_action();
    uint8_t count_next();
    uint8_t count_previous();
  private:
    const prog_char *_label;
    menuItem *_parent;
    menuItem *_previous;
    menuItem *_next;
    menuCore *_root_menu;
};

class menuLeaf : public menuItem {
  public:
    menuLeaf(const prog_char *label);
};

class menuRun : public menuLeaf {
  public:
    menuRun(const prog_char *label,callback_function f);
    virtual menuItem* do_action();
  private:
    callback_function _f;
};

class menuDialog : public menuLeaf {
  public:
    menuDialog(const prog_char *label, const prog_char *question);
    virtual display* get_display();
    virtual void get_question(char *buffer);
  private:
    const prog_char *_question;
};

class enterNumberItem : public menuDialog {
  public:
    enterNumberItem(const prog_char *label,
                    const prog_char *question,
                    int *variable);
    virtual menuItem* do_action();
  private:
    const prog_char *_question;
    int *_variable;
};

class yesNoItem : public menuDialog {
  public:
    yesNoItem(const prog_char *label,
              const prog_char *question,
              uint8_t *variable);
    virtual menuItem* do_action();
  private:
    const prog_char *_question;
    uint8_t *_variable;
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

class menuCore : public subMenu {
  public:
    menuCore();
    void append(menuItem &new_item);
    void attach_display(display &lcd);
    virtual display *get_display();
    void print();
    void action(uint8_t move);
  private:
    display *_lcd;
    menuItem *_selected_item;
    uint8_t _last_move;
    uint8_t _last_lcd_row;
};

#endif
