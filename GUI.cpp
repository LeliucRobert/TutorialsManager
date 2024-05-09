//
// Created by Robi on 5/7/2024.
//


#include <iostream>
#include <mysql.h>
#include <QListWidget>
#include "GUI.h"
#include "SQL_Repository.h"
#include "HTML_Repository.h"
#include "CSV_Repository.h"
#include "Exceptions.h"
#include "Validator.h"
#include <QErrorMessage>

GUI::GUI(){

    stackedWidget = new QStackedWidget {this};
    errorMessageDialog = new QErrorMessage(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);

    setWindowTitle("C++ Tutorials Manager");
    setMinimumSize(300 , 200);

    createFirstPage();
    createSecondPage();

}



void GUI::initialize() {
    this->stackedWidget->setCurrentIndex(1);
    QString selectedText1 = comboBox1->currentText();
    QString selectedText2 = comboBox2->currentText();

    if (selectedText1.toStdString() == "MySQL") {
        MYSQL *conn;
        conn = mysql_init(NULL);
        this->sqlRepository = std::make_unique<SQL_Repository>(conn);

        if (selectedText2.toStdString() == "TXT") {
            this->repository = std::make_unique<Repository>("watchlist.txt" , "noread");
            this->watchListController = std::make_unique<Controller>(*repository);
            this->controller = std::make_unique<Controller>(*sqlRepository);
        } else if (selectedText2.toStdString() == "HTML") {
            this->htmlRepository = std::make_unique<HTML_Repository>("database.html");
            this->watchListController = std::make_unique<Controller>(*htmlRepository);
            this->controller = std::make_unique<Controller>(*sqlRepository);
        } else if (selectedText2.toStdString() == "CSV") {
            this->csvRepository = std::make_unique<CSV_Repository>("database.csv");
            this->watchListController = std::make_unique<Controller>(*csvRepository);
            this->controller = std::make_unique<Controller>(*sqlRepository);
        }
    }
    else if (selectedText1.toStdString() == "txt File"){
        this->fileRepository = std::make_unique<Repository>("database.txt", "read");

        if (selectedText2.toStdString() == "TXT") {
            this->repository = std::make_unique<Repository>("watchlist.txt" , "noread");
            this->watchListController = std::make_unique<Controller>(*repository);
            this->controller = std::make_unique<Controller>(*fileRepository);
        } else if (selectedText2.toStdString() == "HTML") {
            this->htmlRepository = std::make_unique<HTML_Repository>("database.html");
            this->watchListController = std::make_unique<Controller>(*htmlRepository);
            this->controller = std::make_unique<Controller>(*fileRepository);
        } else if (selectedText2.toStdString() == "CSV") {
            this->csvRepository = std::make_unique<CSV_Repository>("database.csv");
            this->watchListController = std::make_unique<Controller>(*csvRepository);
            this->controller = std::make_unique<Controller>(*fileRepository);
        }

    }

    createAdminPage();
    createUserPage();
}

void GUI::createFirstPage() {
    QWidget* mainWidget = new QWidget;
    mainWidget->setMinimumSize(300 , 200);

    QVBoxLayout* VBoxLayout = new QVBoxLayout {mainWidget};

    QFormLayout *upperLayout = new QFormLayout;

    QLabel *label1 = new QLabel ("Database type: ");
    comboBox1 = new QComboBox;
    comboBox1->addItems(QStringList() << "txt File" << "MySQL");

    QLabel *label2 = new QLabel ("Watchlist storage type: ");
    comboBox2 = new QComboBox;
    comboBox2->addItems(QStringList() << "TXT" << "CSV" << "HTML");

    upperLayout->addRow(label1 , comboBox1);
    upperLayout->addRow(label2 , comboBox2);

    VBoxLayout->addLayout(upperLayout);

    QPushButton* nextButton = new QPushButton {"Next"};
    nextButton->setMinimumWidth(100);
    VBoxLayout->addWidget(nextButton , 0 , Qt::AlignCenter);

    connect(nextButton , &QPushButton::clicked, this , &GUI::initialize);

    stackedWidget->addWidget(mainWidget);



}

void GUI::createSecondPage() {
    QWidget* mainWidget = new QWidget;
    mainWidget->setMinimumSize(300 , 200);

    QVBoxLayout* VBoxLayout = new QVBoxLayout {mainWidget};

    QPushButton* userMode = new QPushButton {"User Mode"};
    QPushButton* adminMode = new QPushButton {"Administrator Mode"};

    VBoxLayout->addWidget(adminMode);
    VBoxLayout->addWidget(userMode);


    connect(adminMode , &QPushButton::clicked, this ,[this]() {
        stackedWidget->setCurrentIndex(2);
    });
    connect(userMode , &QPushButton::clicked, this ,[this]() {
        stackedWidget->setCurrentIndex(3);
    });
    stackedWidget->addWidget(mainWidget);



}

void GUI::createAdminPage() {

    QWidget* mainWidget = new QWidget;

    QHBoxLayout* mainLayout = new QHBoxLayout{mainWidget };
    this->tutorialsWidget = new QListWidget{};
    mainLayout->addWidget(this->tutorialsWidget);

    QVBoxLayout* rightLayout = new QVBoxLayout{};



    this->addButton = new QPushButton{ "Add" };
    this->updateButton = new QPushButton{ "Update" };
    this->deleteButton = new QPushButton{ "Delete" };
    this->backButton = new QPushButton{ "Back" };


    rightLayout->addWidget(this->addButton);
    rightLayout->addWidget(this->updateButton);
    rightLayout->addWidget(this->deleteButton);
    rightLayout->addWidget(this->backButton);

    mainLayout->addLayout(rightLayout);
    populateList();

    connect(this->addButton , &QPushButton::clicked, this , &GUI::onAddButtonAdmin);
    connect(this->updateButton , &QPushButton::clicked, this , &GUI::onUpdateButtonAdmin);
    connect(this->deleteButton , &QPushButton::clicked, this , &GUI::onDeleteButtonAdmin);
    connect(this->backButton , &QPushButton::clicked, this , [this]() {
        stackedWidget->setCurrentIndex(1);
    });


    stackedWidget->addWidget(mainWidget);

}

void GUI::populateList()
{
    this->tutorialsWidget->clear();

    for (auto s : this->controller->get_tutorials())
    {
        this->tutorialsWidget->addItem(QString::fromStdString("Title: " + s.get_title() +  " Link: " + s.get_link()));

        /*QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s.getName() + " " + s.getCaptain() + " " + s.getType())};
        QFont font{ "Verdana", 20, 10 };
        item->setFont(font);
        this->spaceshipListWidget->addItem(item);*/
    }
}

void GUI::populateWatchList() {
    this->watchListWidget->clear();
    std::vector<Tutorial> tutorials = this->watchListController->get_tutorials();
    std::cout << 1;
    for (auto s : tutorials)
    {
        this->watchListWidget->addItem(QString::fromStdString("Title: " + s.get_title() +  " Link: " + s.get_link()));

        /*QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s.getName() + " " + s.getCaptain() + " " + s.getType())};
        QFont font{ "Verdana", 20, 10 };
        item->setFont(font);
        this->spaceshipListWidget->addItem(item);*/
    }
}

void GUI::onAddButtonAdmin() {
    CustomDialog dialog(this , "Add new Tutorial");
    int result = dialog.exec();
}

void GUI::onUpdateButtonAdmin() {
    selectedItem = tutorialsWidget->currentItem();
    if (selectedItem){
        CustomDialog dialog(this , "Update Tutorial");
        int result = dialog.exec();
    }
    else
        this->errorMessageDialog->showMessage("No tutorial selected!");

}

void GUI::onDeleteButtonAdmin() {
    selectedItem = tutorialsWidget->currentItem();
    if (selectedItem){
        QString itemText = selectedItem->text();
        QString link = itemText.mid(itemText.indexOf("www."));
        this->controller->delete_controller(link.toStdString());
        this->populateList();
    }
    else
        this->errorMessageDialog->showMessage("No tutorial selected!");

}

CustomDialog::CustomDialog(GUI *parent, const std::string &buttonText)  : QDialog(parent) , parentGui(parent){
    QString qButtonText = QString::fromStdString(buttonText);

    setWindowTitle("Custom Dialog");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QFormLayout *upperLayout = new QFormLayout();

    titleEdit = new QLineEdit(this);
    upperLayout->addRow(new QLabel("Title:"), titleEdit);


    presenterEdit = new QLineEdit(this);
    upperLayout->addRow(new QLabel("Presenter:"), presenterEdit);

    durationEdit = new QSpinBox(this);
    durationEdit->setRange(0, 10000);
    durationEdit->setSuffix(" min");
    upperLayout->addRow(new QLabel("Duration:"), durationEdit);

    likesEdit = new QSpinBox(this);
    likesEdit->setRange(0, 1000000);
    upperLayout->addRow(new QLabel("Likes:"), likesEdit);


    linkEdit = new QLineEdit(this);
    upperLayout->addRow(new QLabel("Link:"), linkEdit);

    QPushButton *addButton = new QPushButton(qButtonText, this);


    layout->addLayout(upperLayout);
    layout->addWidget(addButton);

    if (buttonText == "Add new Tutorial")
        connect(addButton , &QPushButton::clicked, this , &CustomDialog::addNewTutorial);
    else if (buttonText == "Update Tutorial")
        connect(addButton, &QPushButton::clicked, this, &CustomDialog::updateTutorial);

    }

void CustomDialog::addNewTutorial() {
    try{
        QString title = this->titleEdit->text();
        QString presenter = this->presenterEdit->text();
        QString link = this->linkEdit->text();
        int duration = this->durationEdit->value();
        int likes = this->likesEdit->value();

        NumberValidator number_validator;
        LinkValidator link_validator;

        check_input(std::to_string(likes) , number_validator);
        check_input(link.toStdString() , link_validator);

        this->parentGui->controller->add_controller(title.toStdString() , presenter.toStdString() , duration, likes , link.toStdString());
        this->parentGui->populateList();

        close();
    }
    catch(std::exception& e){
        this->parentGui->errorMessageDialog->showMessage(e.what());

    }
}

void CustomDialog::updateTutorial() {
    try{
        QString itemText = this->parentGui->selectedItem->text();
        QString oldLink = itemText.mid(itemText.indexOf("www."));

        QString title = this->titleEdit->text();
        QString presenter = this->presenterEdit->text();
        QString link = this->linkEdit->text();
        int duration = this->durationEdit->value();
        int likes = this->likesEdit->value();

        NumberValidator number_validator;
        LinkValidator link_validator;

        check_input(std::to_string(likes) , number_validator);
        check_input(link.toStdString() , link_validator);

        this->parentGui->controller->update_controller(oldLink.toStdString() ,title.toStdString() , presenter.toStdString() , duration, likes , link.toStdString());
        this->parentGui->populateList();

        close();
    }
    catch(std::exception& e){
        this->parentGui->errorMessageDialog->showMessage(e.what());
    }
}

void CustomDialog::check_input(const std::string& data , Validator& validator) {
    if (validator.validate(data) == 1)
        return;
    throw InputException("Invalid input!\n\n");
}

CustomDialog::CustomDialog(GUI *parent , int val) : QDialog(parent) , parentGui(parent){
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->watchListIndex = 0;

    this->stackedWatchListWidget = new QStackedWidget(this);
    mainLayout->addWidget(this->stackedWatchListWidget);

    std::vector<Tutorial> tutorials = this->parentGui->controller->get_tutorials();

    for (auto it:  tutorials) {

        QLabel *label = new QLabel(QString::fromStdString("Title: " + it.get_title() + " | Presenter: " + it.get_presenter()), this);
        label->setAlignment(Qt::AlignCenter);
        stackedWatchListWidget->addWidget(label);
    }


    this->likeButton = new QPushButton("Like", this);
    this->addToWatchlistButton = new QPushButton("Add to Watchlist", this);
    this->nextButton = new QPushButton("Next", this);



    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(this->likeButton);
    buttonLayout->addWidget(this->addToWatchlistButton);
    buttonLayout->addWidget(this->nextButton);

    mainLayout->addLayout(buttonLayout);


    connect(this->nextButton, &QPushButton::clicked, this, [this]() {
        if (stackedWatchListWidget->count() > 0) {
            this->watchListIndex = (this->watchListIndex + 1) % stackedWatchListWidget->count();
            stackedWatchListWidget->setCurrentIndex(this->watchListIndex);
        }
    });
    connect(this->addToWatchlistButton, &QPushButton::clicked, this, [this]() {
        try {
            std::vector<Tutorial> tutorials = this->parentGui->controller->get_tutorials();
            this->parentGui->watchListController->add_controller(tutorials[this->watchListIndex].get_title(),
                                                                 tutorials[this->watchListIndex].get_presenter(),
                                                                 tutorials[this->watchListIndex].get_duration(),
                                                                 tutorials[this->watchListIndex].get_likes(),
                                                                 tutorials[this->watchListIndex].get_link());
        }
        catch(std::exception& e){
            this->parentGui->errorMessageDialog->showMessage(e.what());
        }
    });
    connect(this->likeButton, &QPushButton::clicked, this, [this]() {
        std::vector<Tutorial> tutorials = this->parentGui->controller->get_tutorials();
        this->parentGui->controller->update_controller(tutorials[this->watchListIndex].get_link(), tutorials[this->watchListIndex].get_title(), tutorials[this->watchListIndex].get_presenter()
                , tutorials[this->watchListIndex].get_duration(), tutorials[this->watchListIndex].get_likes() + 1, tutorials[this->watchListIndex].get_link());

    });
}

void GUI::createUserPage() {

    QWidget* mainWidget = new QWidget;

    QHBoxLayout* mainLayout = new QHBoxLayout{mainWidget };
    this->watchListWidget = new QListWidget{};
    mainLayout->addWidget(this->watchListWidget);

    QVBoxLayout* rightLayout = new QVBoxLayout{};


    this->browseWatchListButton = new QPushButton{ "Browse tutorials" };
    this->deleteFromWatchListButton = new QPushButton{ "Delete Tutorial from Watchlist" };
    this->backButton = new QPushButton{ "Back" };


    rightLayout->addWidget(this->browseWatchListButton);
    rightLayout->addWidget(this->deleteFromWatchListButton);
    rightLayout->addWidget(this->backButton);


    mainLayout->addLayout(rightLayout);

    connect(this->browseWatchListButton , &QPushButton::clicked, this , &GUI::onBrowseWatchListButton);
    connect(this->deleteFromWatchListButton , &QPushButton::clicked, this , &GUI::onDeleteFromWatchListButton);
    connect(this->backButton , &QPushButton::clicked, this , [this]() {
        stackedWidget->setCurrentIndex(1);
    });


    stackedWidget->addWidget(mainWidget);

}

void GUI::onBrowseWatchListButton() {
    CustomDialog dialog(this , 0);
    int result = dialog.exec();
    this->populateWatchList();
}

void GUI::onDeleteFromWatchListButton() {
    selectedItem = watchListWidget->currentItem();
    if (selectedItem){
        QString itemText = selectedItem->text();
        QString link = itemText.mid(itemText.indexOf("www."));
        this->watchListController->delete_controller(link.toStdString());
        this->populateWatchList();
    }
    else
        this->errorMessageDialog->showMessage("No tutorial selected!");

}


