//#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "logic.h"

//#include <QIcon>
//////////////////////////////////////////////////////////////////
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow()
    : QMainWindow(nullptr),
      Logic()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(1200, 800);
    start_btn = new QPushButton("Start", this);
    close_btn = new QPushButton("Exit", this);
    load_btn = new QPushButton("Load game", this);
    QObject::connect(close_btn, &QPushButton::clicked, this, &QApplication::quit);
    QObject::connect(start_btn, &QPushButton::clicked, this, &MainWindow::on_menu_btn_clicked);
    QObject::connect(load_btn, &QPushButton::clicked, this, &MainWindow::on_menu_btn_clicked);
    file_menu = menuBar()->addMenu("Menu");
    menu_bar_help = new QAction("Help", this);
    menu_bar_about = new QAction("About", this);
    menu_bar_quit = new QAction("Quit", this);
    file_menu->addAction(menu_bar_help);
    file_menu->addAction(menu_bar_about);
    file_menu->addAction(menu_bar_quit);
    QObject::connect(menu_bar_quit, &QAction::triggered, this, &QApplication::quit);
    QObject::connect(menu_bar_help, &QAction::triggered, this, &MainWindow::on_menu_bar_triggered);
    QObject::connect(menu_bar_about, &QAction::triggered, this, &MainWindow::on_menu_bar_triggered);
    screen_with_scroll.setParent(this);
    draw_main_menu();
    screen_with_scroll.setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow() {
    delete start_btn;
    delete close_btn;
    delete load_btn;
    delete menu_bar_help;
    delete menu_bar_about;
    delete menu_bar_quit;
    delete file_menu;
}

void MainWindow::draw_main_menu() {
    QPalette background = palette();
    background.setColor(QPalette::Window, QColor(220, 220, 190));
    this->setPalette(background);
    QPalette back = palette();
    back.setColor(QPalette::Window, QColor(230, 230, 220));
    screen_with_scroll.setPalette(back);
    QFont font;
    font.setPointSize(16);
    start_btn->setFont(font);
    load_btn->setFont(font);
    close_btn->setFont(font);
    start_btn->setGeometry(525, 180, 150, 80);
    load_btn->setGeometry(525, 280, 150, 80);
    close_btn->setGeometry(525, 380, 150, 80);
}

void MainWindow::on_menu_bar_triggered() {
    std::string sent_text((((QAction*) sender())->text()).toStdString());
    QFont font;
    font.setPointSize(15);
    QFile text_file((sent_text == "Help") ? "RULES" : "ABOUT");
    if (!text_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Can not open rules");
        return;
    }
    QTextStream in(&text_file);
    QString line;
    while (!in.atEnd()) {
        line = line + in.readLine() + '\n';
    }
    QScrollArea scroll_area(&screen_with_scroll);
    QDialog menu_bar_dialog;
    QLabel menu_bar_label(&menu_bar_dialog);
    menu_bar_label.setFont(font);
    menu_bar_label.setText(line);
    menu_bar_label.adjustSize();
    menu_bar_dialog.adjustSize();
    scroll_area.setWidget(&menu_bar_dialog);
    screen_with_scroll.setWindowTitle((sent_text == "Help") ? "Rules" : "About");
    scroll_area.setFixedWidth(651);
    scroll_area.setMinimumHeight(405);
    screen_with_scroll.setFixedSize(650, 400);
    screen_with_scroll.exec();
}


void MainWindow::slot_on_btn_with_remove_load_pushed() {
    QString btn_text = ((QPushButton*) sender())->text();
    if (btn_text == "Delete") {
        QFile save_file(QString("Saves/") + ((QPushButton*) sender())->accessibleName());
        save_file.remove();
        screen_with_scroll.close();
        return;
    }
    else if (btn_text == "Load") {
        Color *saved_field = nullptr;
        int saved_field_size = -1, saved_black_time = -1, saved_white_time = -1, saved_add_time = -1;
        Color saved_turn = none, saved_winner = none;
        bool saved_timeless = true;
        if(load_save(QString("Saves/") + ((QPushButton*) sender())->accessibleName(),
                      saved_field_size, saved_white_time, saved_black_time, saved_add_time,
                      saved_turn, saved_winner, &saved_field, saved_timeless)) {
            QMessageBox::warning(this, "Warning", "File was corrupted");
            screen_with_scroll.close();
            return;
        }
        Field *field = new Field(saved_field_size, saved_white_time, saved_black_time, saved_add_time,
                                 saved_turn, saved_winner, saved_field, saved_timeless);
        field->show();
        screen_with_scroll.close();
        this->close();
    }
}


void MainWindow::on_menu_btn_clicked() {
    std::string btn_text((((QPushButton*) sender())->text()).toStdString());
    QFont font;
    font.setPointSize(16);
    if (btn_text == "Start") {
        Settings *sett = new Settings();
        sett->show();
        this->close();
    }
    else if (btn_text == "Load game") {
        QScrollArea scroll_area_save(&screen_with_scroll);
        screen_with_scroll.setFixedSize(420, 600);
        scroll_area_save.setFixedSize(420, 600);
        QDialog screen_with_saves(&scroll_area_save);

        QDir dir(QString("Saves"));
        if (!dir.exists()) {
            dir.mkdir("Saves");
        }
        QFont font;
        font.setPointSize(16);
        QStringList list_of_saves = dir_files("Saves");
        QLabel *label_date_save = new QLabel[list_of_saves.size()];
        QPushButton *btn_list_with_load = new QPushButton[list_of_saves.size()];
        QPushButton *btn_list_with_delete = new QPushButton[list_of_saves.size()];
        for (int i = 0; i < list_of_saves.size(); i++) {
            btn_list_with_load[i].setParent(&screen_with_saves);
            btn_list_with_load[i].setText(QString("Load"));
            btn_list_with_load[i].setFont(font);
            btn_list_with_load[i].setAccessibleName(list_of_saves[i]);
            QObject::connect(&(btn_list_with_load[i]), &QPushButton::clicked,
                             this, &MainWindow::slot_on_btn_with_remove_load_pushed);
            btn_list_with_load[i].setGeometry(200, 100 * (i + 1), 80, 50);
            btn_list_with_delete[i].setParent(&screen_with_saves);
            btn_list_with_delete[i].setText(QString("Delete"));
            btn_list_with_delete[i].setFont(font);
            btn_list_with_delete[i].setAccessibleName(list_of_saves[i]);
            QObject::connect(&(btn_list_with_delete[i]), &QPushButton::clicked,
                             this, &MainWindow::slot_on_btn_with_remove_load_pushed);
            btn_list_with_delete[i].setGeometry(290, 100 * (i + 1), 80, 50);
            label_date_save[i].setParent(&screen_with_saves);
            label_date_save[i].setText(QFileInfo(QFile(QString("Saves/") +
                                                       list_of_saves[i])).birthTime().toString("dd.MM.yyyy hh:mm:ss"));
            label_date_save[i].setFont(font);
            label_date_save[i].setGeometry(10, 100 * (i + 1), 190, 50);
        }
        screen_with_saves.adjustSize();
        scroll_area_save.setWidget(&screen_with_saves);
        screen_with_scroll.adjustSize();
        screen_with_scroll.setWindowTitle("Saves");
        screen_with_scroll.exec();
        delete [] btn_list_with_load;
        delete [] btn_list_with_delete;
        delete [] label_date_save;
        this->raise();
        return;
    }
}
