#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_normal_clicked()
{
    ui->using_2->setText("using: Normal Search...");
}

void MainWindow::on_binary_clicked()
{
     ui->using_2->setText("using: Binary Search...");
}

void MainWindow::on_generate_clicked()
{
    QString size= ui->lineEdit_size->text();
    ui->datasetSize->setText("The Dataset size is: " + size);
    size1 = size.toInt();
    ui->arrayList->clear();
    if(arr != NULL)
        delete[] arr;
    arr = new int[size1];
    for (int i = 0; i < size1; i++)
    {
        int val = rand()%100;
        for(int j=0;j<i;j++)
            if(val==arr[j])
            {
                val = rand()%100;
                j=0;
            }
        arr[i]= val;
        ui->arrayList->addItem(QString::number(arr[i]));
    }
}

void MainWindow::merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;


    int L[n1], R[n2];

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];


    int i = 0;
    int j = 0;
    int k = l;

     while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {	arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MainWindow::mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


void MainWindow::on_merge_clicked()
{
    ui->arrayList->clear();
    ui->sortingUsing->setText("Sorting using merge sort");
    ui->array->setText("Array is sorted");
    std :: chrono :: steady_clock :: time_point now = std :: chrono:: steady_clock :: now ();
    mergeSort(arr, 0, size1-1);
    std ::chrono :: steady_clock :: time_point then = std :: chrono :: steady_clock :: now ();
    this -> sortTime = std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(then - now ).count();

    for (int i = 0; i < size1; i++)
    {
        ui->arrayList->addItem(QString::number(arr[i]));
    }
}

void MainWindow::on_stl_clicked()
{
    ui->arrayList->clear();
    ui->sortingUsing->setText("Sorting using quick sort");
    ui->array->setText("Array is sorted");
    std :: chrono :: steady_clock :: time_point now = std :: chrono:: steady_clock :: now ();
    std::sort(arr, arr+size1);
    std ::chrono :: steady_clock :: time_point then = std :: chrono :: steady_clock :: now ();
    this -> sortTime = std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(then - now ).count();

    for (int i = 0; i < size1; i++)
    {
        ui->arrayList->addItem(QString::number(arr[i]));
    }
}

int MainWindow::BinarySearch(int arr[], int val, int start,int end)
{
    if(start>end)
        return -1;
    int mid = (start+end)/2;
    if(arr[mid] == val)
        return mid;
    else if(val>arr[mid])
        return BinarySearch(arr,val,mid+1,end);
    else
        return BinarySearch(arr,val,start,mid-1);
}

int MainWindow::normal_search (int arr[], int size, int key)
{
    if (size == 0) {
            return -1;
        }
        else if (arr[size - 1] == key) {
            // Return the found key.
            return arr[size - 1];
        }
        else {
            int ans = normal_search(arr, size - 1, key);
            return ans;
        }
}

void MainWindow::on_find_clicked()
{
    QString searchType = ui->using_2->text();


 QMessageBox msgBox;
    if (searchType == "using: Normal Search...")
    {
        QString key =ui->lineEdit_find->text(); // get the specified number and store it in key
        int key1 = key.toInt();
        QString size= ui->lineEdit_size->text();
        int size1 = size.toInt();
        std :: chrono :: steady_clock :: time_point now = std :: chrono:: steady_clock :: now ();
        int ans = normal_search(arr, size1 , key1);
        std ::chrono :: steady_clock :: time_point then = std :: chrono :: steady_clock :: now ();
        this -> sortTime += std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(then - now ).count();

        if (ans == -1)
        {
                msgBox.setText(key+ " was not found, and time taken= " + QString :: number (sortTime)+" Nanoseconds");

         }
            else
        {
            msgBox.setText(key+ " was found, and time taken = " + QString :: number (sortTime)+" Nanoseconds");

            }
        msgBox.exec();
    }

    else if (searchType == "using: Binary Search...")
    {
        QString key =ui->lineEdit_find->text(); // get the specified number and store it in key
        int key1 = key.toInt();
        QString size2= ui->lineEdit_size->text();
        int size3 = size2.toInt();
        std :: chrono :: steady_clock :: time_point now = std :: chrono:: steady_clock :: now ();
        int index = BinarySearch(arr,key1,0,size3-1);
        std ::chrono :: steady_clock :: time_point then = std :: chrono :: steady_clock :: now ();
       this -> sortTime += std :: chrono :: duration_cast<std :: chrono :: nanoseconds>(then - now ).count();

        if(index == -1)
            msgBox.setText(key+ " was not found, and time taken = "+ QString :: number (sortTime)+" Nanoseconds");
        else
            msgBox.setText(key+" was found, and time taken = " + QString :: number (sortTime)+" Nanoseconds");
    }
    msgBox.exec();
    sortTime =0;
}

