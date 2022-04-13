#include <iostream>
#include <stdlib.h>
#include "fifteen.h"

Fifteen::Fifteen(QObject *parent):
    QAbstractListModel(parent) {
    for (int i = 1; i < 17; i++) m_numbers.append(i);
}

int Fifteen::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_numbers.size();
}

QVariant Fifteen::data(const QModelIndex &index, int role) const {
    //std::cout << "data from " << index.row() << ' ' << std::endl;
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
        case Number:
            return m_numbers.at(index.row());
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> Fifteen::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Number] = "number";
    return roles;
}

void Fifteen::move(int index) {
    if(index > 0 && m_numbers.at(index-1) == 16) {  //left
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index - 1);
        m_numbers.move(index, index-1);
        endMoveRows();
    } else if(index < 15 && m_numbers.at(index+1) == 16) { //right
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index + 2);
        m_numbers.move(index, index+1);
        endMoveRows();
    } else if(index > 3 && m_numbers.at(index-4) == 16) {   //up
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index-4);
        m_numbers.swapItemsAt(index, index-4);
        endMoveRows();
        beginMoveRows(QModelIndex(), index-3, index-3, QModelIndex(), index+1);
        endMoveRows();
    } else if(index < 12 && m_numbers.at(index+4) == 16) {  //down
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index+5);
        m_numbers.swapItemsAt(index, index+4);
        endMoveRows();
        beginMoveRows(QModelIndex(), index+3, index+3, QModelIndex(), index);
        endMoveRows();
    }
    if (m_numbers.at(15) == 16) {
        for (int i = 0; i < 15; i++) {
            if (m_numbers.at(i) > m_numbers.at(i+1)) {
                return;
            }
        }
        emit win();
    }
}

/*
void Fifteen::move(int index) {
    if(index == 15) {  //left
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index - 1);
        endMoveRows();
    } else if(index == 10 ) { //right
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index + 2);
        endMoveRows();
    } else if(index == 14 ) {
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index-4);
        endMoveRows();
        beginMoveRows(QModelIndex(), index-3, index-3, QModelIndex(), index+1);
        endMoveRows();
    } else if(index == 11 ) {
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index+5);
        endMoveRows();
        beginMoveRows(QModelIndex(), index+3, index+3, QModelIndex(), index);
        endMoveRows();
    }
}
*/

void Fifteen::mixNumbers() {
    do {
        for (int i = 15; i >= 0; i -= 1) {
          int j = rand() % (i + 1);
          m_numbers.swapItemsAt(i, j);
        }
    } while(checkLoss());
    emit reloadModel();
    std::cout << *this << std::endl;
}

bool Fifteen::checkLoss() {
    int sum = 0;
    int nullNumber;
    for (int n = 0; n < 15; n++) {
        if (m_numbers.at(n) > m_numbers.at(n+1)) {
            sum++;
        }
        if (m_numbers.at(n) == 16) nullNumber = n;
    }
    int loss = sum + nullNumber/4;
    return loss%2;
}


std::ostream& operator<< (std::ostream &out, const Fifteen &fifteen) {
    for (int i = 0; i < fifteen.m_numbers.size(); ++i) {
        out << fifteen.m_numbers.at(i) << ' ';
    }
    return out;
}

