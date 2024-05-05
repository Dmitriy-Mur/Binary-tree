#include <QMainWindow>
#include <QGraphicsScene>
#include "BinaryTree.h"
#include "Tree.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_insert_btn_clicked();
    void on_search_btn_clicked();
    void on_del_btn_clicked();
    void on_pushButton_clicked();
    void on_preOrder_btn_clicked();
    void on_del_tree_btn_clicked();
    void on_simOrder_btn_clicked();
    void on_postOrder_btn_clicked();
private:
    Ui::MainWindow *ui;
    BinaryTree binaryTree;
    QGraphicsScene* CreateScene(Tree*);
    void clear_status();
};

