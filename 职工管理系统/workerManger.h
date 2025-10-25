#pragma once
#include<iostream>
#include"worker.h"
#include <fstream>
#define  FILENAME "empFile.txt"

using namespace std;


class workerManger
{
public:
	int m_EmpNum; //��¼�ļ��е���������
	worker** m_EmpArray;//Ա�������ָ��
	workerManger();
	//����ְ��
	void Add_Emp();
	void showMenu();
	//�����ļ�
	void save();
	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
	//ͳ������
	int get_EmpNum();
	//��ʼ������
	void init_Emp();
	//��ʾְ��
	void show_Emp();
	//ɾ��ְ��
	void Del_Emp();
	//�ж�ְ���Ƿ����
	int IsExist(int id);
	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void find_Emp();

	//ְ������
	void sort_Emp();
	//��պ���
	void Clean_File();
	void exitWorkerManger();
	~workerManger();
};