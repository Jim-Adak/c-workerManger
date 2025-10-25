#pragma once
#include<iostream>
#include"worker.h"
#include <fstream>
#define  FILENAME "empFile.txt"

using namespace std;


class workerManger
{
public:
	int m_EmpNum; //记录文件中的人数个数
	worker** m_EmpArray;//员工数组的指针
	workerManger();
	//增加职工
	void Add_Emp();
	void showMenu();
	//保存文件
	void save();
	//标志文件是否为空
	bool m_FileIsEmpty;
	//统计人数
	int get_EmpNum();
	//初始化数组
	void init_Emp();
	//显示职工
	void show_Emp();
	//删除职工
	void Del_Emp();
	//判断职工是否存在
	int IsExist(int id);
	//修改职工
	void Mod_Emp();

	//查找职工
	void find_Emp();

	//职工排序
	void sort_Emp();
	//清空函数
	void Clean_File();
	void exitWorkerManger();
	~workerManger();
};