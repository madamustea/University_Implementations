#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab12OOP.h"
#include"Service.h"
class Lab12OOP : public QMainWindow
{
    Q_OBJECT

public:
    Lab12OOP(Service& service,QWidget *parent = Q_NULLPTR);
    void populate_list();
    int get_selectedIndex();
    void connectSignalsAndSlots();
    void deleteStatue();
    void addStatue();
    void updateStatue();
    void nextStatue();
    void populate_mylist();
    void saveStatue();
    void filterByMaterialAndAge();
    void open();
    void switchMode();

private:
    
    Ui::Lab12OOPClass ui;
    Service& service;
    std::string mode;
    

};
