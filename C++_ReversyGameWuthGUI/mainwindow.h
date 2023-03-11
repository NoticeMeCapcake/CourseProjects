#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTimer>
#include <QDialog>
#include <QScrollArea>
#include <iostream>
#include <QColor>
#include <QtCore>
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>


enum Color{
    none,
    white,
    black
};

class Logic
{
protected:
    QStringList dir_files(const QString path);  // Возвращает лист названий файлов в папке по переданному пути
    int write_save(const int field_size, const int black_turn_time, const int white_turn_time,
                    const int add_time, const Color turn, const Color winner,
                    const bool timeless, const Color *field);  // Записывает сохранение игры
    void make_a_move(const int width, const int x, const int y, const int field_size, int &black_turn_time,
                     int &white_turn_time, const int add_time, Color &turn,
                     const bool timeless, Color *field, Color &winner);  // Работает с полем и фишками на нём (реализация хода)
    int load_save(QString save_file_name, int &saved_field_size, int &saved_white_time, int &saved_black_time, int &saved_add_time,
                  Color &saved_turn, Color &saved_winner, Color **saved_field, bool &saved_timeless);
};


class MainWindow : public QMainWindow, public Logic
{
public:
    MainWindow();
    ~MainWindow();

private:
    QPushButton *start_btn, *close_btn, *load_btn;
    void draw_main_menu();
    void on_menu_btn_clicked();
    void on_menu_bar_triggered();
    QMenu *file_menu;
    QAction *menu_bar_help;
    QAction *menu_bar_about;
    QAction *menu_bar_quit;
    QString save_btn_text;
    void slot_on_btn_with_remove_load_pushed();
    QDialog screen_with_scroll;
};

class Field : public QWidget, public Logic
{
private:
    void paintEvent(QPaintEvent *);
    void field_btns_slot();
    int field_size, white_turn_time, black_turn_time, add_time;
    bool timeless;
    QPushButton *back_btn, *save_btn;
    Color *field;
    Color turn, winner;
    QTimer *game_timer;
    QLabel *gui_game_timer;
    void mousePressEvent(QMouseEvent * event);
    void timer_second_passed();
public:
    Field(const int f_size = 8, const int _turn_time = 0, const int _add_time = 0);
    Field(const int f_size, const int _white_turn_time, const int _black_turn_time, const int _add_time, const Color _turn,
          const Color _winner, Color *_field, const bool _timeless);
    ~Field();
};

class Settings : public QWidget
{
private:
    void settings_btns_slot();
    void draw_settings();
    QPushButton *back_btn, *start_btn;
    QComboBox *turn_time_box, *add_time_box, *field_size_box;
    QLabel *turn_time_label, *add_time_label, *field_size_label;

public:
    Settings();
    ~Settings();
};


#endif // MAINWINDOW_H
