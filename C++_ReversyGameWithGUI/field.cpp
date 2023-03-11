#include "mainwindow.h"


Field::Field(const int f_size, const int _turn_time, const int _add_time)
    : QWidget(),
      Logic::Logic()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(1200, 800);
    this->setWindowTitle("Field");
    field_size = f_size;
    white_turn_time = _turn_time;
    black_turn_time = _turn_time;
    add_time = _add_time;
    winner = none;
    turn = black;
    field = new Color[field_size * field_size];
    for (int i = 0; i < field_size * field_size; i++) {
        field[i] = none;
        if (i == field_size * (field_size / 2 - 1) + (field_size / 2 - 1) ||
                i == field_size * (field_size / 2 ) + (field_size / 2)) {
            field[i] = black;
        }
        if (i == field_size * (field_size / 2 - 1) + (field_size / 2) ||
                i == field_size * (field_size / 2) + (field_size / 2 - 1)) {
            field[i] = white;
        }
    }
    if (field_size > 8) {
        field[field_size * (field_size / 2 - 1) + (field_size / 2)] = black;
        field[field_size * (field_size / 2 ) + (field_size / 2)] = white;
    }
    if (_turn_time == 0) timeless = true;
    else timeless = false;
    QFont font;
    font.setPointSize(16);
    back_btn = new QPushButton("Return in menu", this);
    back_btn->setFont(font);
    save_btn = new QPushButton("Save game", this);
    save_btn->setFont(font);
    QObject::connect(back_btn, &QPushButton::clicked, this, &Field::field_btns_slot);
    QObject::connect(save_btn, &QPushButton::clicked, this, &Field::field_btns_slot);
    back_btn->setGeometry(40, 50, 150, 50);
    save_btn->setGeometry(40, 100, 150, 50);
    if (!timeless) {
        gui_game_timer = new QLabel(this);
        gui_game_timer->setGeometry(1000, 100, 200, 80);
        gui_game_timer->setFont(font);
        gui_game_timer->setText(QString("Remaining time:\n") + QString::number(_turn_time / 60) +
                                QString(":") + QString::number(_turn_time % 60));
        game_timer = new QTimer(this);
        game_timer->start(1000);
        QObject::connect(game_timer, &QTimer::timeout, this, &Field::timer_second_passed);
    }
}

Field::Field(const int f_size, const int _white_turn_time, const int _black_turn_time, const int _add_time, const Color _turn,
             const Color _winner, Color *_field, const bool _timeless)
    : QWidget(),
      Logic()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(1200, 800);
    this->setWindowTitle("Field");
    field_size = f_size;
    white_turn_time = _white_turn_time;
    black_turn_time = _black_turn_time;
    add_time = _add_time;
    turn = _turn;
    winner = _winner;
    field = _field;
    timeless = _timeless;
    QFont font;
    font.setPointSize(16);
    back_btn = new QPushButton("Return in menu", this);
    back_btn->setFont(font);
    save_btn = new QPushButton("Save game", this);
    save_btn->setFont(font);
    QObject::connect(back_btn, &QPushButton::clicked, this, &Field::field_btns_slot);
    QObject::connect(save_btn, &QPushButton::clicked, this, &Field::field_btns_slot);
    back_btn->setGeometry(40, 50, 150, 50);
    save_btn->setGeometry(40, 100, 150, 50);
    if (!timeless) {
        gui_game_timer = new QLabel(this);
        gui_game_timer->setGeometry(1000, 100, 200, 80);
        gui_game_timer->setFont(font);
        game_timer = new QTimer(this);
        if (turn == white) {
            gui_game_timer->setText(QString("Remaining time:\n") + QString::number(white_turn_time / 60) +
                                QString(":") + QString::number(white_turn_time % 60));
            game_timer->start(1000);
            QObject::connect(game_timer, &QTimer::timeout, this, &Field::timer_second_passed);
        }
        else if (turn == black) {
            gui_game_timer->setText(QString("Remaining time:\n") + QString::number(black_turn_time / 60) +
                                QString(":") + QString::number(black_turn_time % 60));
            game_timer->start(1000);
            QObject::connect(game_timer, &QTimer::timeout, this, &Field::timer_second_passed);
        }
        else {
            gui_game_timer->setText(QString("Remaining time:\n") + QString::number(0) +
                                QString(":") + QString::number(0));
        }
    }
}

void Field::timer_second_passed() {
    int turn_time = 0;
    if (turn == white) {
        turn_time = --white_turn_time;
        if (turn_time == 0) {
            turn = none;
            winner = black;
            game_timer->stop();
            this->repaint();
        }
    }
    else if (turn == black) {
        turn_time = --black_turn_time;
        if (turn_time == 0) {
            turn = none;
            winner = white;
            game_timer->stop();
            this->repaint();
        }
    }
    else {
        game_timer->stop();
        return;
    }
    gui_game_timer->setText(QString("Remaining time:\n") + QString::number(turn_time / 60) +
                            QString(":") + QString::number(turn_time % 60));
}

void Field::mousePressEvent(QMouseEvent* mousePressEventArgs) {
    if (mousePressEventArgs->button() != Qt::MouseButton::LeftButton) {
            return;
    }
    int width = 72 - 5 * (field_size - 8);
    int x = mousePressEventArgs->position().x();
    int y = mousePressEventArgs->position().y();
    if (x < 230 + width || y < 20 + width || x > 230 + (field_size + 1) * width ||
            y > 20 + (field_size + 1) * width || turn == none) {
        return;
    }
    make_a_move(width, x, y, field_size, black_turn_time, white_turn_time,
                add_time, turn, timeless, field, winner);
    if (!timeless) {
        int turn_time = 0;
        if (turn == black) {
            turn_time = black_turn_time;
        }
        else if (turn == white) {
            turn_time = white_turn_time;
        }
        else {
            game_timer->stop();
        }
        gui_game_timer->setText(QString("Remaining time:\n") + QString::number(turn_time / 60) +
                                QString(":") + QString::number(turn_time % 60));
    }
    this->repaint();
}

void Field::paintEvent(QPaintEvent *paintEventArgs) {
    Q_UNUSED(paintEventArgs)
    int width = 72 - 5 * (field_size - 8);
    QPalette background = palette();
    background.setColor(QPalette::Window, QColor(220, 220, 190));
    this->setPalette(background);
    int counter_white = 0, counter_black = 0;
    QPainter painter;
    QFont font;
    painter.begin(this);
    font.setPointSize(16);
    painter.setFont(font);
    painter.setPen(QPen(QBrush(QColor(0, 0, 0)), 3));
    painter.setBrush(QBrush(QColor::fromRgb(200, 200, 215)));
    painter.drawRect(230, 25, (field_size + 2) * width, (field_size + 2) * width);
    for (int i = 0; i < field_size * field_size; i++) {
        painter.setBrush(QBrush(QColor::fromRgb(200, 200, 215)));
        if ((i / field_size + i % field_size) % 2 != 0) {
            painter.setBrush(QBrush(QColor::fromRgb(100, 100, 107)));
        }
        painter.drawRect(230 + width + (i % (field_size) * width),
                         25 + width + (i / (field_size) * width),
                         width, width);
        if (i / field_size == 0) {
            QString border_alpha(QChar(i % field_size + 'A'));
            painter.drawText(230 + width + (i % field_size * width),
                         25,
                         width, width, Qt::AlignCenter, border_alpha);
        }
        if (i % field_size == 0) {
            QString border_num(QString::number(field_size - i / field_size));
            painter.drawText(230,
                         25 + width + (i / field_size * width),
                         width, width, Qt::AlignCenter, border_num);
        }
        if (i / field_size == field_size - 1) {
            QString border_alpha(QChar(i % field_size + 'A'));
            painter.drawText(230 + width + (i % field_size * width),
                         25 + ((i / field_size + 2) * width),
                         width, width, Qt::AlignCenter, border_alpha);
        }
        if (i % field_size == field_size - 1) {
            QString border_num(QString::number(field_size - i / field_size));
            painter.drawText(230 + ((i % field_size + 2) * width),
                         25 + width + (i / field_size * width),
                         width, width, Qt::AlignCenter, border_num);
        }
        if (field[i] == white) {
            counter_white++;
            painter.setBrush(QBrush(QColor::fromRgb(250, 250, 250)));
            painter.drawEllipse(230 + width + (i % (field_size) * width) + 7,
                                25 + width + (i / (field_size) * width) + 7,
                                width - 14, width - 14);
        }
        else if (field[i] == black) {
            counter_black++;
            painter.setBrush(QBrush(QColor::fromRgb(5, 5, 5)));
            painter.drawEllipse(230 + width + (i % (field_size) * width) + 7,
                                25 + width + (i / (field_size) * width) + 7,
                                width - 14, width - 14);
        }
    }
    painter.drawText(30, 160, 170, 50, Qt::AlignCenter, QString("BLACK: ") +
                     QString::number(counter_black));
    painter.drawText(30, 230, 170, 50, Qt::AlignCenter, QString("WHITE: ") +
                     QString::number(counter_white));
    if (turn == white) {
        painter.drawText(500, 2, 200, 20, Qt::AlignCenter, QString("WHITE\'S TURN"));
    }
    else if (turn == black) {
        painter.drawText(500, 2, 200, 20, Qt::AlignCenter, QString("BLACK\'S TURN"));
    }
    else {
        if (winner == black) {
            painter.drawText(500, 2, 200, 20, Qt::AlignCenter, QString("BLACK IS WINNER"));
        }
        else if (winner == white) {
            painter.drawText(500, 2, 200, 20, Qt::AlignCenter, QString("WHITE IS WINNER"));
        }
        else {
            painter.drawText(500, 2, 200, 20, Qt::AlignCenter, QString("DRAW"));
        }
    }
    painter.end();
}

void Field::field_btns_slot() {
    std::string btn_text((((QPushButton*) sender())->text()).toStdString());
    if (btn_text == "Return in menu") {
        MainWindow *menu = new MainWindow;
        menu->show();
        this->close();
    }
    else if (btn_text == "Save game") {
        if (write_save(field_size, black_turn_time, white_turn_time,
                        add_time, turn, winner, timeless, field)) {
            QMessageBox::warning(this, "Warning", "Can not save the game");
        }
    }
}

Field::~Field() {
    delete back_btn;
    delete save_btn;
    if (!timeless) {
        delete game_timer;
        delete gui_game_timer;
    }
    delete [] field;
}
