#include "mainwindow.h"


QStringList Logic::dir_files(const QString path)
{

    QStringList file_list;
    QDir dir(path);
    if (dir.exists())
    {
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        dir.setSorting(QDir::Time);
        QFileInfoList list = dir.entryInfoList();

        for (int i = list.size() - 1; i >= 0; i--)
        {
            QFileInfo fileInfo = list.at(i);
            file_list.append(fileInfo.fileName());
        }
    }
    return file_list;
}

int Logic::write_save(const int field_size, const int black_turn_time, const int white_turn_time,
                const int add_time, const Color turn, const Color winner,
                const bool timeless, const Color *field)
{
    QDir dir(QString("Saves"));
    if (!dir.exists()) {
        dir.mkdir("Saves");
    }
    QStringList save_files_list = Logic::dir_files("Saves");
    QFile new_save_file(QString("Saves/Save") + QString::number(save_files_list.size() + 1));
    int i = 0;
    while (new_save_file.exists()) {
        i++;
        new_save_file.setFileName(QString("Saves/Save") + QString::number(save_files_list.size() + 1 + i));
    }
    if (!new_save_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return -1;
    }
    QTextStream file_out(&new_save_file);
    file_out << QString("f_size:") + QString::number(field_size) << '\n';
    file_out << QString("black_turn_time:") + QString::number(black_turn_time) << '\n';
    file_out << QString("white_turn_time:") + QString::number(white_turn_time) << '\n';
    file_out << QString("add_time:") + QString::number(add_time) << '\n';
    file_out << QString("whose_turn:") + QString::number((int) turn) << '\n';
    file_out << QString("winner:") + QString::number((int) winner) << '\n';
    file_out << QString("timeless:") + QString::number((int) timeless) << '\n';
    file_out << QString("field:");
    QString out;
    for (i = 0; i < field_size * field_size; i++) {
        if (i == field_size * field_size - 1) {
            out = QString::number((int) field[i]) + QString('\n');
        }
        else {
            out = QString::number((int) field[i]) + QString(',');
        }
        file_out << out;
    }
    return 0;
}

void Logic::make_a_move(const int width, const int x, const int y, const int field_size, int &black_turn_time,
                 int &white_turn_time, const int add_time, Color &turn,
                 const bool timeless, Color *field, Color &winner)
{
    bool correct_place = false;

    if (x < 230 + width || y < 20 + width || x > 230 + (field_size + 1) * width ||
            y > 20 + (field_size + 1) * width || turn == none) {
        return;
    }
    int row = (x - 230 - width) / width;
    int col = (y - 25 - width) / width;

    if (field[col * field_size + row] != none) {
        return;
    }

    for (int i = 0; i < 9; i++) {
        if (((col - 1 + i / 3) * field_size + (row - 1 + i % 3) < 0) ||
           ((col - 1 + i / 3) * field_size + (row - 1 + i % 3) > field_size * field_size - 1) ||
                i == 4) {
            continue;
        }
        if (field[(col - 1 + i / 3) * field_size + (row - 1 + i % 3)] != turn &&
                field[(col - 1 + i / 3) * field_size + (row - 1 + i % 3)] != none) {

            int pos = (col - 1 + i / 3) * field_size + (row - 1 + i % 3);
            int delta = pos - (col * field_size + row);

            if ((i == 0 || i == 6 || i == 3)
                    && pos % field_size != (col * field_size + row) % field_size - 1) {
                continue;
            }
            else if ((i == 2 || i == 8 || i == 5)
                    && pos % field_size != (col * field_size + row) % field_size + 1) {
                continue;
            }
            while (1) {
                if (pos + delta > field_size * field_size - 1 || pos + delta < 0) {
                    break;
                }

                if (field[pos + delta] == turn) {
                    if ((i == 0 || i == 6 || i == 3)
                            && (pos + delta) % field_size != pos % field_size - 1) {
                        break;
                    }
                    else if ((i == 2 || i == 8 || i == 5)
                            && (pos + delta) % field_size != pos % field_size + 1) {
                        break;
                    }
                    correct_place = true;
                    pos += delta;
                    while (pos != (col - 1 + i / 3) * field_size + (row - 1 + i % 3)) {
                        pos -= delta;
                        field[pos] = turn;
                    }
                    break;
                }
                else if (field[pos + delta] != turn && field[pos + delta] != none) {
                    if ((i == 0 || i == 6 || i == 3)
                            && (pos + delta) % field_size != pos % field_size - 1) {
                        break;
                    }
                    else if ((i == 2 || i == 8 || i == 5)
                            && (pos + delta) % field_size != pos % field_size + 1) {
                        break;
                    }
                    pos += delta;
                    continue;
                }
                else if (field[pos + delta] == none) {
                    break;
                }
                break;
            }
        }
    }
    if (!correct_place) {
        return;
    }

    if (!timeless) {
        if (turn == black) {
            black_turn_time += add_time;
        }
        else if (turn == white) {
            white_turn_time += add_time;
        }
    }
    field[col * field_size + row] = turn;

    correct_place = false;
    int white_counter = 0, black_counter = 0;
    for (int k = 0; k < 2; k++) {
        if (turn == black) {
            turn = white;
        }
        else if (turn == white) {
            turn = black;
        }
        for (int j = 0; j < field_size * field_size; j++) {
            if (field[j] == turn) {
                if (field[j] == black) {
                    black_counter++;
                }
                else {
                    white_counter++;
                }
                for (int i = 0; i < 9; i++) {
                    col = j / field_size;
                    row = j % field_size;
                    if (((col - 1 + i / 3) * field_size + (row - 1 + i % 3) < 0) ||
                    ((col - 1 + i / 3) * field_size + (row - 1 + i % 3) > field_size * field_size - 1) ||
                     i == 4) {
                        continue;
                    }
                    if (field[(col - 1 + i / 3) * field_size + (row - 1 + i % 3)] != turn &&
                    field[(col - 1 + i / 3) * field_size + (row - 1 + i % 3)] != none) {
                        int pos = (col - 1 + i / 3) * field_size + (row - 1 + i % 3);
                        int delta = pos - (col * field_size + row);
                        if ((i == 0 || i == 6 || i == 3)
                            && pos % field_size != (col * field_size + row) % field_size - 1) {
                            continue;
                        }
                        else if ((i == 2 || i == 8 || i == 5)
                        && pos % field_size != (col * field_size + row) % field_size + 1) {
                            continue;
                        }
                        while (1) {
                            if (pos + delta > field_size * field_size - 1 || pos + delta < 0) {
                                break;
                            }

                            if (field[pos + delta] == turn) {
                                break;
                            }
                            else if (field[pos + delta] != turn && field[pos + delta] != none) {
                                if ((i == 0 || i == 6 || i == 3)
                                        && (pos + delta) % field_size != pos % field_size - 1) {
                                    break;
                                }
                                else if ((i == 2 || i == 8 || i == 5)
                                        && (pos + delta) % field_size != pos % field_size + 1) {
                                    break;
                                }
                                pos += delta;
                                continue;
                            }
                            else if (field[pos + delta] == none) {
                                if ((i == 0 || i == 6 || i == 3)
                                        && (pos + delta) % field_size != pos % field_size - 1) {
                                    break;
                                }
                                else if ((i == 2 || i == 8 || i == 5)
                                        && (pos + delta) % field_size != pos % field_size + 1) {
                                    break;
                                }
                                correct_place = true;
                                break;
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (correct_place) {
            break;
        }
    }

    if (!correct_place) {
        if (black_counter > white_counter) {
            winner = black;
        }
        else if(white_counter > black_counter) {
            winner = white;
        }
        else {
            winner = none;
        }
        turn = none;
    }
}

int Logic::load_save(QString save_file_name, int &saved_field_size, int &saved_white_time,
                     int &saved_black_time, int &saved_add_time,
                     Color &saved_turn, Color &saved_winner, Color **saved_field, bool &saved_timeless) {
    QFile save_file(save_file_name);
    if (!save_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return -1;
    }
    *saved_field = nullptr;
    saved_field_size = -1;
    saved_black_time = -1;
    saved_white_time = -1;
    saved_add_time = -1;
    saved_turn = none;
    saved_winner = none;
    saved_timeless = true;
    bool converted = false;
    QTextStream save_file_stream(&save_file);
    bool flags[8];
    for (int i = 0; i < 8; i++) {
        flags[i] = false;
    }
    while (!save_file_stream.atEnd()) {
        converted = false;
        QString line = save_file_stream.readLine();
        QStringList list_with_saved_game_info = line.split(':');
        if (list_with_saved_game_info.size() != 2 && list_with_saved_game_info.size() != 0) {
            if (*saved_field != nullptr) {
                delete [] *saved_field;
            }
            return -1;
        }
        if (list_with_saved_game_info[0].contains("black_turn_time")) {
            saved_black_time = list_with_saved_game_info[1].toInt(&converted, 10);
            if (!converted || saved_black_time < 0 || saved_black_time > 600 || flags[0]) {
                if (*saved_field != nullptr) {
                    delete [] *saved_field;
                }
                return -1;
            }
            flags[0] = true;
        }
        else if (list_with_saved_game_info[0].contains("white_turn_time")) {
            saved_white_time = list_with_saved_game_info[1].toInt(&converted, 10);
            if (!converted || saved_white_time < 0 || saved_white_time > 600 || flags[1]) {
                if (*saved_field != nullptr) {
                    delete [] *saved_field;
                }
                return -1;
            }
            flags[1] = true;
        }
        else if (list_with_saved_game_info[0].contains("add_time")) {
            saved_add_time = list_with_saved_game_info[1].toInt(&converted, 10);
            if (!converted || saved_add_time < 0 || saved_add_time > 15 || flags[2]) {
                if (*saved_field != nullptr) {
                    delete [] *saved_field;
                }
                return -1;
            }
            flags[2] = true;
        }
        else if (list_with_saved_game_info[0].contains("whose_turn")) {
            saved_turn = (Color) list_with_saved_game_info[1].toInt(&converted, 10);
            if (!converted || (saved_turn > (Color) 2 && saved_turn < (Color) 0) || flags[3]) {
                if (*saved_field != nullptr) {
                    delete [] *saved_field;
                }
                return -1;
            }
            flags[3] = true;
        }
        else if (list_with_saved_game_info[0].contains("winner")) {
            saved_winner = (Color) list_with_saved_game_info[1].toInt(&converted, 10);
            if (!converted || (saved_winner > (Color) 2 && saved_winner < (Color) 0) || flags[4]) {
                if (*saved_field != nullptr) {
                    delete [] *saved_field;
                }
                return -1;
            }
            flags[4] = true;
        }
        else if (list_with_saved_game_info[0].contains("field")) {
            QStringList field_list = list_with_saved_game_info[1].split(',');
            *saved_field = new Color[field_list.size()];
            for (int i = 0; i < field_list.size(); i++) {
                converted = false;
                (*saved_field)[i] = (Color) field_list[i].toInt(&converted, 10);
                if (!converted || ((*saved_field)[i] > (Color) 2 && (*saved_field)[i] < (Color) 0) || flags[5]) {
                    if (*saved_field != nullptr) {
                        delete [] *saved_field;
                    }
                    return -1;
                }

            }
            flags[5] = true;
        }
        else if (list_with_saved_game_info[0].contains("f_size")) {
            saved_field_size = list_with_saved_game_info[1].toInt(&converted, 10);
            if (!converted || saved_field_size < 0 || flags[6]) {
                if (*saved_field != nullptr) {
                    delete [] *saved_field;
                }
                return -1;
            }
            flags[6] = true;
        }
        else if (list_with_saved_game_info[0].contains("timeless")) {
            saved_timeless = (bool) list_with_saved_game_info[1].toInt(&converted, 10);
            if (!converted || flags[7]) {
                if (*saved_field != nullptr) {
                    delete [] *saved_field;
                }
                return -1;
            }
            flags[7] = true;
        }
    }
    for (int i = 0; i < 8; i++) {
        if (!(flags[i])) {
            if (*saved_field != nullptr) {
                delete [] *saved_field;
            }
            return -1;
        }
    }
    if ((saved_field_size != 8 && saved_field_size != 10 && saved_field_size != 12) ||
            saved_black_time < 0 || saved_white_time < 0 ||
            saved_add_time < 0 || *saved_field == nullptr ||
            ((saved_black_time != 0 || saved_white_time != 0) && saved_timeless) ||
            (saved_turn == none && saved_winner == none) || (saved_turn && saved_winner) ||
            (saved_black_time == 0 && saved_white_time == 0 && !saved_timeless)) {
        if (*saved_field != nullptr) {
            delete [] *saved_field;
        }
        return -1;
    }
    return 0;
}
