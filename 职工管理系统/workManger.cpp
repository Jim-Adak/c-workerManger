#include"workerManger.h"
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"


	workerManger::workerManger()
	{
		//�ļ�������
		ifstream ifs;
		ifs.open(FILENAME, ios::in);
		if (!ifs.is_open())
		{
			cout << "�ļ�������" << endl;
			this->m_EmpNum = 0;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;	
			ifs.close();
			return;
		}

		//�ļ����ڲ���Ϊ��
		char ch;
		ifs >> ch;
		if (ifs.eof())
		{
			cout << "�ļ����ڲ���Ϊ��" << endl;
			this->m_EmpNum = 0;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
			ifs.close();
			return;
		}
		int num = this->get_EmpNum();
		cout << "ְ������Ϊ��" << num << endl;
		this->m_EmpNum = num;
	    //����ְ������������
		this->m_EmpArray = new worker * [this->m_EmpNum];
		//��ʼ��ְ��
		init_Emp();
		//���Դ���
		for (int i = 0; i < m_EmpNum; i++)
		{
			cout << "ְ���ţ�" << this->m_EmpArray[i]->m_ID
				<< "ְ�����ƣ�" << this->m_EmpArray[i]->m_Name
				<< "���ű�ţ�" << this->m_EmpArray[i]->DeptId << endl;
		}
	}
	
	void workerManger::showMenu()
	{
		cout << "********************************************" << endl;
		cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
		cout << "*************  0.�˳��������  *************" << endl;
		cout << "*************  1.����ְ����Ϣ  *************" << endl;
		cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
		cout << "*************  3.ɾ����ְְ��  *************" << endl;
		cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
		cout << "*************  5.����ְ����Ϣ  *************" << endl;
		cout << "*************  6.���ձ������  *************" << endl;
		cout << "*************  7.��������ĵ�  *************" << endl;
		cout << "********************************************" << endl;
	}
	void workerManger::exitWorkerManger()
	{
		cout << "��ӭ�´�ʹ��" << endl;
		system("pause");
		exit(0);
	}

	void workerManger::Add_Emp()
	{
		cout << "����������ְ�������� " << endl;

		int addNum = 0;
		cin >> addNum;

		if (addNum > 0)
		{
			//�����¿ռ��С
			int newSize = this->m_EmpNum + addNum;

			//�����¿ռ�
			worker** newSpace = new worker * [newSize];

			//��ԭ�ռ������ݴ�ŵ��¿ռ���
			if (this->m_EmpArray != NULL)
			{
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					newSpace[i] = this->m_EmpArray[i];
				}
			}

			//����������
			for (int i = 0; i < addNum; i++)
			{
				int id;
				string name;
				int dSelect;

				cout << "������� " << i + 1 << " ����ְ����ţ�" << endl;
				cin >> id;


				cout << "������� " << i + 1 << " ����ְ��������" << endl;
				cin >> name;


				cout << "��ѡ���ְ���ĸ�λ��" << endl;
				cout << "1����ְͨ��" << endl;
				cout << "2������" << endl;
				cout << "3���ϰ�" << endl;
				cin >> dSelect;


				worker* worker = NULL;
				switch (dSelect)
				{
				case 1: //��ͨԱ��
					worker = new Employee(id, name, 1);
					break;
				case 2: //����
					worker = new Manager(id, name, 2);
					break;
				case 3:  //�ϰ�
					worker = new Boss(id, name, 3);
					break;
				default:
					break;
				}


				newSpace[this->m_EmpNum + i] = worker;
			}

			//�ͷ�ԭ�пռ�
			delete[] this->m_EmpArray;

			//�����¿ռ��ָ��
			this->m_EmpArray = newSpace;

			//�����µĸ���
			this->m_EmpNum = newSize;

			//����ְ����־
			this->m_FileIsEmpty = false;

			this->save();
			//��ʾ��Ϣ
			cout << "�ɹ����" << addNum << "����ְ����" << endl;
		}
		else
		{
			cout << "��������" << endl;
		}

		system("pause");
		system("cls");
	}

	void workerManger::save()
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::out);

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			ofs << this->m_EmpArray[i]->m_ID << " "
				<< this->m_EmpArray[i]->m_Name << " "
				<< this->m_EmpArray[i]->DeptId << endl;
		}
		ofs.close();
	}

	int workerManger::get_EmpNum()
	{
		ifstream ifs;
		ifs.open(FILENAME, ios::in);
		int id;
		string name;
		int dId;
		int num = 0;

		while (ifs >> id && ifs >> name && ifs >> dId)
		{
			//��¼����
			num++;
		}
		ifs.close();

		return num;
	}

	void workerManger::init_Emp()
	{
		ifstream ifs;
		ifs.open(FILENAME, ios::in);
		int id;
		string name;
		int dId;
		int index = 0;
		while (ifs >> id && ifs >> name && ifs >> dId)
		{
			worker* worker = NULL;
			//���ݲ�ͬ�Ĳ���id������ͬ����
			if (dId == 1)// 1��ͨԱ��
			{
				worker = new Employee(id, name, dId);
			}
			else if (dId = 2)//2����
			{
				worker = new Manager(id, name, dId);
			}
			else//�ܲ�
			{
				worker = new Boss(id, name, dId);
			}
			//�����������
			this->m_EmpArray[index] = worker;
			index++;
		}
	}

	//��ʾְ��;
	void workerManger::show_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "�ļ������ڻ��¼Ϊ��!" << endl;
		}
		else
		{
			for (int i = 0; i < m_EmpNum; i++)
			{
				//���ö�̬�ӿڵ���
				this->m_EmpArray[i]->showInfo();
			}

		}
		system("pause");
		system("cls");
	}

	//ɾ��ְ��
	void workerManger::Del_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "�ļ������ڻ���ɾ��" << endl;
		}
		else
		{
			cout << "��������Ҫɾ����ְ��" << endl;
			int index = 0;
			cin >> index;
			if (index!=-1)
			{
				for (int i = index; i < this->m_EmpNum - 1; i++)
				{
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
					
				}
				this->m_EmpNum--;
				this->save();
				cout << "��ְ���Ѿ�ɾ��" << endl;
			}
			else
			{
				cout << "ְ�������ڻ���ɾ��" << endl;
			}
		}
		system("pause");
		system("cls");
	}

	//�ж�ְ���Ƿ����
	int workerManger::IsExist(int id)
	{
		int index = -1;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i]->m_ID == id)
			{
				index = i;
			}

			return index;
		}
	}

	//�޸�ְ��
	void workerManger::Mod_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "�ļ�������" << endl;
		}
		else
		{
			cout << "��������Ҫ�޸ĵ�ְ�����" << endl;
			int id = 0;
			cin >> id;
			if (this->IsExist(id) != -1)
			{
				//��ɾ����ǰְ�������¸�ֵ
				delete this->m_EmpArray[id];
				
				//��ֵ
				int newId=0;
				string newName=" ";
				int dSelect=0;
				
				cout << "�鵽��" << id << "��ְ������������ְ����:" << endl;
				cin >> newId;
				cout << "������������" << endl;
				cin >> newName;
				cout << "�������λ" << endl;
				cout << "1.��ְͨ��" << endl;
				cout << "2.����" << endl;
				cout << "3.�ϰ�" << endl;
				cin >> dSelect;

				worker* worker = NULL;
				switch (dSelect)
				{
				case 1:
					worker = new Employee(newId, newName, dSelect);
					break;
				case 2:
					worker = new Manager(newId, newName, dSelect);
					break;
				case 3:
					worker = new Boss(newId, newName, dSelect);
					break;
				}
				//��������
				this->m_EmpArray[id] = worker;
				cout << "�޸ĳɹ�" << endl;
				//�����ļ�
				this->save();
			}
			else
			{

				cout << "ְ��������" << endl;
			}
		}
	}

	//����ְ��
	void workerManger::find_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "�ļ�������" << endl;

		}
		else
		{
			cout << "��������Ҫѡ��Ĳ�ѯ��ʽ" << endl;
			cout << "1.��ְ����Ų���" << endl;
			cout << "2.��ְ����������" << endl;
			int select = 0;
			cin >> select;
			if (select == 1)
			{
				int id;
				cout << "������ְ�����" << endl;
				cin >> id;
				
				int ret = IsExist(id);
				if (ret != -1)
				{
					cout << "���ҳɹ�����ְ����Ϣ����" << endl;
					this->m_EmpArray[ret]->showInfo();
				}
				else
				{
					cout << "����ʧ�ܣ����޴���" << endl;
				}
			}
			else if (select == 2)
			{
				string name;
				cout << "��������ҵ�����" << endl;
				cin >> name;
				
				bool flag = false;
				for (int i = 0; i < m_EmpNum; i++)
				{
					if (m_EmpArray[i]->m_Name == name)
					{
						cout << "���ҳɹ���ְ�����Ϊ��"
							<< m_EmpArray[i]->m_ID
							<< "�ŵ���Ϣ���£�" << endl;
						flag = true;
						this->m_EmpArray[i]->showInfo();
					}
				}
				if (flag== false)
				{
					cout << "����ʧ�ܣ����޴���" << endl;
				}
			}
			else
			{
				cout << "����ѡ������" << endl;
			}
		}
		system("pause");
		system("cls");
	}

	void workerManger::sort_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "�ļ�������" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			cout << "��ȷ������ʽ" << endl;
			cout << "1����ְ���Ž�������" << endl;
			cout << "2.��ְ���Ž��н���" << endl;
			int select;
			cin >> select;
			for (int i = 0; i< m_EmpNum; i++)
			{
				int minOrMax = i;
				for (int j = i + 1; j < m_EmpNum; j++)
				{
					if (select == 1)//����
					{
						if (m_EmpArray[minOrMax]->m_ID > m_EmpArray[j]->m_ID)
						{
							minOrMax = j;
						}
					}
					else//����
					{
						if (m_EmpArray[minOrMax]->m_ID < m_EmpArray[j]->m_ID)
						{
							minOrMax = j;
						}
					}
				}
				if (i != minOrMax)
				{
					worker* temp = m_EmpArray[i];
					m_EmpArray[i] = m_EmpArray[minOrMax];
					m_EmpArray[minOrMax] = temp;
				}

			}
			cout << "����ɹ����������Ϊ��" << endl;
			this->save();
			this->show_Emp();
			
		}
	}

	void workerManger::Clean_File()
	{
		cout << "ȷ�����" << endl;
		cout << "1.ȷ��" << endl;
		cout << "2.����" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//ios::truncģʽ���������ɾ���ļ������´���
			ofstream ofs(FILENAME, ios::trunc);
			ofs.close();

			if (this->m_EmpArray != NULL)
			{
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i] != NULL)
					{
						delete this->m_EmpArray[i];
					}
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
		system("pause");
		system("cls");
	}

	

	workerManger::~workerManger()
	{
		if (this->m_EmpArray != NULL)
		{
			delete[] this->m_EmpArray;
		}
	}