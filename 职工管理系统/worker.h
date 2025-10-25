#pragma once
#include<iostream>
using namespace std;

//创建职工类，后边具体的分类使用继承解决
class worker
{
public:
	virtual void showInfo();
	virtual string getDeptName();
public:
	string m_Name;
	int m_ID;
	int DeptId;//职工所在部门名称编号

};