#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->DeptId = dId;
}


void Manager::showInfo()
{
	cout << "ְ�����:" << this->m_ID
		<< "\tְ������:" << this->m_Name
		<<"\t��λ"<<this->getDeptName()
		<< " \t��λְ������ϰ彻��������,���·������Ա��" << endl;

}

string Manager::getDeptName()
{
	return string("����");
}