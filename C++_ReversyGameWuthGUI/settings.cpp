#include "mainwindow.h"


Settings::Settings() : QWidget() {
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("Settings");
    back_btn = new QPushButton("Return in menu", this);
    start_btn = new QPushButton("Start game", this);
    QObject::connect(back_btn, &QPushButton::clicked, this, &Settings::settings_btns_slot);
    QObject::connect(start_btn, &QPushButton::clicked, this, &Settings::settings_btns_slot);
    turn_time_box = new QComboBox(this);
    QStringList turn_time_list = {"0", "1", "2", "3", "5", "7", "10"};
    turn_time_box->addItems(turn_time_list);
    turn_time_label = new QLabel("Minutes for game:", this);
    add_time_box = new QComboBox(this);
    QStringList add_time_list = {"0", "1", "2", "3", "5", "7", "10", "15"};
    add_time_box->addItems(add_time_list);
    add_time_label = new QLabel("Additional seconds:", this);
    field_size_box = new QComboBox(this);
    QStringList field_size_list = {"8", "10", "12"};
    field_size_box->addItems(field_size_list);
    field_size_label = new QLabel("Field size:", this);
    this->setFixedSize(1200, 800);
    draw_settings();
}

void Settings::draw_settings() {
    QFont font;
    font.setPointSize(16);
    QPalette background = palette();
    background.setColor(QPalette::Window, QColor(220, 220, 190));
    this->setPalette(background);
    turn_time_label->setFont(font);
    turn_time_label->setGeometry(300, 200, 200, 50);
    turn_time_box->setGeometry(300, 250, 150, 35);
    turn_time_box->setFont(font);
    back_btn->setGeometry(425, 400, 150, 50);
    back_btn->setFont(font);
    start_btn->setGeometry(625, 400, 150, 50);
    start_btn->setFont(font);
    add_time_label->setGeometry(487, 200, 200, 50);
    add_time_label->setFont(font);
    add_time_box->setGeometry(500, 250, 150, 35);
    add_time_box->setFont(font);
    field_size_label->setGeometry(730, 200, 200, 50);
    field_size_label->setFont(font);
    field_size_box->setGeometry(700, 250, 150, 35);
    field_size_box->setFont(font);
}

void Settings::settings_btns_slot() {
    std::string btn_text((((QPushButton*) sender())->text()).toStdString());
    if (btn_text == "Return in menu") {
        MainWindow *menu = new MainWindow;
        menu->show();
        this->close();
    }
    else if (btn_text == "Start game") {
        int field_size = field_size_box->currentText().toInt();
        int timer = turn_time_box->currentText().toInt();
        int timer_add = add_time_box->currentText().toInt();
        Field *field = new Field(field_size, timer * 60, timer_add);
        field->show();
        this->close();
    }
}

Settings::~Settings() {
    delete back_btn;
    delete start_btn;
    delete turn_time_box;
    delete add_time_box;
    delete field_size_box;
    delete turn_time_label;
    delete add_time_label;
    delete field_size_label;
}
