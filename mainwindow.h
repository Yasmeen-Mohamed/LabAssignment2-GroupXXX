#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mergeSort(int arr[], int l, int r);
    void merge(int arr[], int l, int m, int r);
    int normal_search(int arr[], int n, int m);
    int BinarySearch(int arr[], int v, int s, int e);

private slots:
    void on_normal_clicked();

    void on_binary_clicked();

    void on_generate_clicked();

    void on_merge_clicked();

    void on_stl_clicked();

    void on_find_clicked();

private:
    Ui::MainWindow *ui;
    int *arr = NULL;
    int size1;
    int sortTime;
};
#endif // MAINWINDOW_H
