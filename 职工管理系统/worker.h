#pragma once
#include<iostream>
using namespace std;

//����ְ���࣬��߾���ķ���ʹ�ü̳н��
class worker
{
public:
	virtual void showInfo();
	virtual string getDeptName();
public:
	string m_Name;
	int m_ID;
	int DeptId;//ְ�����ڲ������Ʊ��

};