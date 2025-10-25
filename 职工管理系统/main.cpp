#include<iostream>
using namespace std;
#include"workerManger.h"
#include"boss.h"
#include"manager.h"
#include"employee.h"
#include"worker.h"


void test()
{
	worker* worker = NULL;
	worker = new Employee(1, "张三", 1);
	worker->showInfo();
	delete worker;

	worker = new Employee(2, "李四", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "王五", 3);
	worker->showInfo();
	delete worker;
}

int main()
{
	//test();
	workerManger wm;
	wm.showMenu();
	int choice = 0;
	cout << "请输入你的选择：" << endl;
	cin >> choice;
	switch (choice)
	{
	case 0:
		wm.exitWorkerManger();
		break;
	case 1:
		wm.Add_Emp();
		break;
	case 2:
		wm.show_Emp();
		break;
	case 3:
	{
		wm.Del_Emp();
		break;
	}
	case 4:
		wm.Mod_Emp();
		break;
	case 5:
		wm.find_Emp();
		break;
	case 6:
		wm.sort_Emp();
		break;
	case 7:
		wm.Clean_File();
		break;
	default:
		system("cls");
		break;
	}
	return 0;
}