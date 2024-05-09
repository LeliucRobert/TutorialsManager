//
// Created by Robi on 5/7/2024.
//

#ifndef OOP_A4_5_LELIUCROBERT_GUI_H
#define OOP_A4_5_LELIUCROBERT_GUI_H
#include <qwidget.h>
#include "Controller.h"
#include "SQL_Repository.h"
#include "HTML_Repository.h"
#include "CSV_Repository.h"
#include "Validator.h"
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QStackedWidget>
#include <qlistwidget.h>
#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QErrorMessage>

class CustomDialog;

class GUI : public QWidget{
    friend class CustomDialog;
private:
    QStackedWidget* stackedWidget;


    QComboBox *comboBox1;
    QComboBox *comboBox2;

    QListWidget* tutorialsWidget;
    QListWidget* watchListWidget;

    QPushButton* addButton;
    QPushButton* updateButton;
    QPushButton* deleteButton;
    QPushButton* backButton;

    QPushButton* browseWatchListButton;
    QPushButton* deleteFromWatchListButton;

    QListWidgetItem *selectedItem;

    QErrorMessage *errorMessageDialog;

    std::unique_ptr<Repository> repository;
    std::unique_ptr<Repository> fileRepository;
    std::unique_ptr<SQL_Repository> sqlRepository;
    std::unique_ptr<HTML_Repository> htmlRepository;
    std::unique_ptr<CSV_Repository> csvRepository;


    std::unique_ptr<Controller> controller;
    std::unique_ptr<Controller> watchListController;

public:
    GUI();
    void initialize();
    void createFirstPage();
    void createSecondPage();
    void createAdminPage();
    void createUserPage();
    void populateList();
    void populateWatchList();
    void onAddButtonAdmin();
    void onUpdateButtonAdmin();
    void onDeleteButtonAdmin();
    void onBrowseWatchListButton();
    void onDeleteFromWatchListButton();
};
class CustomDialog : public QDialog {

private:
    QStackedWidget* stackedWatchListWidget;

    QLineEdit *titleEdit;
    QLineEdit *presenterEdit;
    QSpinBox *durationEdit;
    QSpinBox *likesEdit;
    QLineEdit *linkEdit;
    GUI *parentGui;
    QPushButton* nextButton;
    QPushButton* likeButton;
    QPushButton* addToWatchlistButton;
    int watchListIndex;

public:
        explicit CustomDialog(GUI *parent = nullptr , const std::string& buttonText = "add");
        explicit CustomDialog(GUI *parent = nullptr , int val = 0);
        void addNewTutorial();
        void updateTutorial();
        void check_input(const std::string& data , Validator& validator);

};


#endif //OOP_A4_5_LELIUCROBERT_GUI_H
