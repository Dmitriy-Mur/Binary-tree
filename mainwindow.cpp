#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

#include "BinaryTree.h"
#include "Tree.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QGraphicsScene* scene = CreateScene(nullptr);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() {
    delete ui;
}

void preOrderTreeSceneCreate(Tree* tree, QGraphicsScene* Scene, int ell_r, int lvlH, int lvlW, int lvlH_delt, int lvlW_delt, bool left, Tree* to_paint) {
    if (tree == nullptr) {
        return;
    }
    int cur_lvlW_delt;
    if (left) {
        if (lvlW_delt < 25) {
            cur_lvlW_delt = lvlW_delt + 50;
            lvlW_delt = 25;
        } else {
            cur_lvlW_delt = lvlW_delt + 50;
        }
    } else {
        if(lvlW_delt < 25){
            cur_lvlW_delt = lvlW_delt * -1 - 50;
            lvlW_delt = 25;
        } else {
            cur_lvlW_delt = (lvlW_delt + 50) * -1;
        }
    }
    if (tree->parent != nullptr) {
        QGraphicsLineItem *edge = Scene->addLine(lvlW, lvlH, lvlW + cur_lvlW_delt,lvlH - lvlH_delt);
        QPen PenEdge(Qt::black);  //edges color
        PenEdge.setWidth(4);
        PenEdge.setDashPattern({5, 2});
        edge->setPen(PenEdge);
    }
    preOrderTreeSceneCreate(tree->left, Scene, ell_r, lvlH + lvlH_delt, lvlW - lvlW_delt, lvlH_delt, lvlW_delt - 50, true, to_paint);
    preOrderTreeSceneCreate(tree->right, Scene, ell_r, lvlH + lvlH_delt, lvlW + lvlW_delt, lvlH_delt, lvlW_delt - 50, false, to_paint);
    QGraphicsEllipseItem *ELL = Scene->addEllipse(lvlW - ell_r/2, lvlH - ell_r/2, ell_r, ell_r);
    QPen penELL(Qt::black);
    penELL.setWidth(2);
    QBrush brushELL(QColor(211, 211, 211));
    if (to_paint != nullptr) {
        if (to_paint->data == tree->data) {
            brushELL = QBrush(QColor(255, 0, 0));
        }
    }
    ELL->setPen(penELL);
    ELL->setBrush(brushELL);
    int text_delt = std::to_string(tree->data).size();
    QGraphicsTextItem *text = Scene->addText(QString::number(tree->data));
    text->setDefaultTextColor(Qt::black);
    text->setFont(QFont("Arial", 12));
    text->setPos(lvlW - 5 - 4 * text_delt, lvlH - 12);
}

QGraphicsScene* MainWindow::CreateScene(Tree* to_paint) {
    int ell_r = 40;
    int lvlH = 0;
    int lvlW = 0;
    int lvlH_delt = 80;
    int lvlW_delt = 120;
    QGraphicsScene* new_Scene = new QGraphicsScene;
    preOrderTreeSceneCreate(binaryTree.root, new_Scene, ell_r, lvlH, lvlW, lvlH_delt, lvlW_delt, false, to_paint);
    return new_Scene;
}

void preOrderQStringCreate(Tree* tree, QString* qString) {
    if (tree == nullptr) {
        return;
    }
    *qString += QString::number(tree->data);
    *qString += " ";
    preOrderQStringCreate(tree->left, qString);
    preOrderQStringCreate(tree->right, qString);
}

void simOrderQStringCreate(Tree* tree, QString* qString) {
    if (tree == nullptr) {
        return;
    }
    simOrderQStringCreate(tree->left, qString);
    *qString += QString::number(tree->data);
    *qString += " ";
    simOrderQStringCreate(tree->right, qString);
}

void postOrderQStringCreate(Tree* tree, QString* qString) {
    if (tree == nullptr) {
        return;
    }
    postOrderQStringCreate(tree->left, qString);
    postOrderQStringCreate(tree->right, qString);
    *qString += QString::number(tree->data);
    *qString += " ";
}

void MainWindow::clear_status() {
    ui->search_status_label->setText("");
    ui->Order_result_textBrowser->setText("");
}

void MainWindow::on_insert_btn_clicked() {
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status();
    int to_add = ui->inser_textEdit->toPlainText().toInt();
    if (binaryTree.root == nullptr) {
        binaryTree.root = new Tree(to_add);
    } else {
        binaryTree.insert(to_add);
    }
    ui->inser_textEdit->setText("");
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    ui->graphicsView->setScene(new_Scene);
    if (prev_scene) {
        delete prev_scene;
    };
}

void MainWindow::on_search_btn_clicked() {
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status();
    Tree* found = binaryTree.find(ui->search_textEdit->toPlainText().toInt());
    QGraphicsScene *new_Scene;
    if (found != nullptr) {
        //ui->search_status_label->setText("Элемент найден");
        new_Scene = CreateScene(found);
    } else {
        //ui->search_status_label->setText("Элемент не найден");
        new_Scene = CreateScene(nullptr);
    }
    ui->search_textEdit->setText("");
    ui->graphicsView->setScene(new_Scene);
    if (prev_scene) {
        delete prev_scene;
    };
}


void MainWindow::on_del_btn_clicked() {
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status();
    int to_del = ui->del_textEdit->toPlainText().toInt();
    bool isErase = binaryTree.erase(to_del);
    ui->del_textEdit->setText("");
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    ui->graphicsView->setScene(new_Scene);
    if (prev_scene) {
        delete prev_scene;
    };
}

void MainWindow::on_pushButton_clicked() {
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status();
    binaryTree.balance();
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    ui->graphicsView->setScene(new_Scene);
    if (prev_scene) {
        delete prev_scene;
    };
}

void MainWindow::on_preOrder_btn_clicked() {
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status();
    QString restult;
    preOrderQStringCreate(binaryTree.root, &restult);
    ui->Order_result_textBrowser->setText(restult);
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    ui->graphicsView->setScene(new_Scene);
    if (prev_scene) {
        delete prev_scene;
    };
}

void MainWindow::on_del_tree_btn_clicked() {
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status();
    binaryTree.clear();
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    ui->graphicsView->setScene(new_Scene);
    if (prev_scene) {
        delete prev_scene;
    };
}

void MainWindow::on_simOrder_btn_clicked() {
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status();
    QString result;
    simOrderQStringCreate(binaryTree.root, &result);
    ui->Order_result_textBrowser->setText(result);
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    ui->graphicsView->setScene(new_Scene);
    if (prev_scene) {
        delete prev_scene;
    };
}

void MainWindow::on_postOrder_btn_clicked() {
    QGraphicsScene *prev_scene = ui->graphicsView->scene();
    clear_status();
    QString result;
    postOrderQStringCreate(binaryTree.root, &result);
    ui->Order_result_textBrowser->setText(result);
    QGraphicsScene *new_Scene = CreateScene(nullptr);
    ui->graphicsView->setScene(new_Scene);
    if (prev_scene) {
        delete prev_scene;
    };
}
