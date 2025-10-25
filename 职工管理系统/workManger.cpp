#include"workerManger.h"
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"


	workerManger::workerManger()
	{
		//文件不存在
		ifstream ifs;
		ifs.open(FILENAME, ios::in);
		if (!ifs.is_open())
		{
			cout << "文件不存在" << endl;
			this->m_EmpNum = 0;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;	
			ifs.close();
			return;
		}

		//文件存在并且为空
		char ch;
		ifs >> ch;
		if (ifs.eof())
		{
			cout << "文件存在并且为空" << endl;
			this->m_EmpNum = 0;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
			ifs.close();
			return;
		}
		int num = this->get_EmpNum();
		cout << "职工个数为：" << num << endl;
		this->m_EmpNum = num;
	    //创建职工数创建数组
		this->m_EmpArray = new worker * [this->m_EmpNum];
		//初始化职工
		init_Emp();
		//测试代码
		for (int i = 0; i < m_EmpNum; i++)
		{
			cout << "职工号：" << this->m_EmpArray[i]->m_ID
				<< "职工名称：" << this->m_EmpArray[i]->m_Name
				<< "部门编号：" << this->m_EmpArray[i]->DeptId << endl;
		}
	}
	
	void workerManger::showMenu()
	{
		cout << "********************************************" << endl;
		cout << "*********  欢迎使用职工管理系统！ **********" << endl;
		cout << "*************  0.退出管理程序  *************" << endl;
		cout << "*************  1.增加职工信息  *************" << endl;
		cout << "*************  2.显示职工信息  *************" << endl;
		cout << "*************  3.删除离职职工  *************" << endl;
		cout << "*************  4.修改职工信息  *************" << endl;
		cout << "*************  5.查找职工信息  *************" << endl;
		cout << "*************  6.按照编号排序  *************" << endl;
		cout << "*************  7.清空所有文档  *************" << endl;
		cout << "********************************************" << endl;
	}
	void workerManger::exitWorkerManger()
	{
		cout << "欢迎下次使用" << endl;
		system("pause");
		exit(0);
	}

	void workerManger::Add_Emp()
	{
		cout << "请输入增加职工数量： " << endl;

		int addNum = 0;
		cin >> addNum;

		if (addNum > 0)
		{
			//计算新空间大小
			int newSize = this->m_EmpNum + addNum;

			//开辟新空间
			worker** newSpace = new worker * [newSize];

			//将原空间下内容存放到新空间下
			if (this->m_EmpArray != NULL)
			{
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					newSpace[i] = this->m_EmpArray[i];
				}
			}

			//输入新数据
			for (int i = 0; i < addNum; i++)
			{
				int id;
				string name;
				int dSelect;

				cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
				cin >> id;


				cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
				cin >> name;


				cout << "请选择该职工的岗位：" << endl;
				cout << "1、普通职工" << endl;
				cout << "2、经理" << endl;
				cout << "3、老板" << endl;
				cin >> dSelect;


				worker* worker = NULL;
				switch (dSelect)
				{
				case 1: //普通员工
					worker = new Employee(id, name, 1);
					break;
				case 2: //经理
					worker = new Manager(id, name, 2);
					break;
				case 3:  //老板
					worker = new Boss(id, name, 3);
					break;
				default:
					break;
				}


				newSpace[this->m_EmpNum + i] = worker;
			}

			//释放原有空间
			delete[] this->m_EmpArray;

			//更改新空间的指向
			this->m_EmpArray = newSpace;

			//更新新的个数
			this->m_EmpNum = newSize;

			//更改职工标志
			this->m_FileIsEmpty = false;

			this->save();
			//提示信息
			cout << "成功添加" << addNum << "名新职工！" << endl;
		}
		else
		{
			cout << "输入有误" << endl;
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
			//记录人数
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
			//根据不同的部门id创建不同对象
			if (dId == 1)// 1普通员工
			{
				worker = new Employee(id, name, dId);
			}
			else if (dId = 2)//2经理
			{
				worker = new Manager(id, name, dId);
			}
			else//总裁
			{
				worker = new Boss(id, name, dId);
			}
			//存放在数组中
			this->m_EmpArray[index] = worker;
			index++;
		}
	}

	//显示职工;
	void workerManger::show_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "文件不存在或记录为空!" << endl;
		}
		else
		{
			for (int i = 0; i < m_EmpNum; i++)
			{
				//利用多态接口调用
				this->m_EmpArray[i]->showInfo();
			}

		}
		system("pause");
		system("cls");
	}

	//删除职工
	void workerManger::Del_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "文件不存在或已删除" << endl;
		}
		else
		{
			cout << "请输入需要删除的职工" << endl;
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
				cout << "该职工已经删除" << endl;
			}
			else
			{
				cout << "职工不存在或已删除" << endl;
			}
		}
		system("pause");
		system("cls");
	}

	//判断职工是否存在
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

	//修改职工
	void workerManger::Mod_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "文件不存在" << endl;
		}
		else
		{
			cout << "请输入需要修改的职工编号" << endl;
			int id = 0;
			cin >> id;
			if (this->IsExist(id) != -1)
			{
				//先删除当前职工再重新赋值
				delete this->m_EmpArray[id];
				
				//赋值
				int newId=0;
				string newName=" ";
				int dSelect=0;
				
				cout << "查到：" << id << "号职工，请输入新职工号:" << endl;
				cin >> newId;
				cout << "请输入新姓名" << endl;
				cin >> newName;
				cout << "请输入岗位" << endl;
				cout << "1.普通职工" << endl;
				cout << "2.经理" << endl;
				cout << "3.老板" << endl;
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
				//更改数据
				this->m_EmpArray[id] = worker;
				cout << "修改成功" << endl;
				//保存文件
				this->save();
			}
			else
			{

				cout << "职工不存在" << endl;
			}
		}
	}

	//查找职工
	void workerManger::find_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "文件不存在" << endl;

		}
		else
		{
			cout << "请输入你要选择的查询方式" << endl;
			cout << "1.按职工编号查找" << endl;
			cout << "2.按职工姓名查找" << endl;
			int select = 0;
			cin >> select;
			if (select == 1)
			{
				int id;
				cout << "请输入职工编号" << endl;
				cin >> id;
				
				int ret = IsExist(id);
				if (ret != -1)
				{
					cout << "查找成功！该职工信息如下" << endl;
					this->m_EmpArray[ret]->showInfo();
				}
				else
				{
					cout << "查找失败，查无此人" << endl;
				}
			}
			else if (select == 2)
			{
				string name;
				cout << "请输入查找的姓名" << endl;
				cin >> name;
				
				bool flag = false;
				for (int i = 0; i < m_EmpNum; i++)
				{
					if (m_EmpArray[i]->m_Name == name)
					{
						cout << "查找成功，职工编号为："
							<< m_EmpArray[i]->m_ID
							<< "号的信息如下：" << endl;
						flag = true;
						this->m_EmpArray[i]->showInfo();
					}
				}
				if (flag== false)
				{
					cout << "查找失败，查无此人" << endl;
				}
			}
			else
			{
				cout << "输入选项有误" << endl;
			}
		}
		system("pause");
		system("cls");
	}

	void workerManger::sort_Emp()
	{
		if (this->m_FileIsEmpty)
		{
			cout << "文件不存在" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			cout << "请确定排序方式" << endl;
			cout << "1、按职工号进行升序" << endl;
			cout << "2.按职工号进行降序" << endl;
			int select;
			cin >> select;
			for (int i = 0; i< m_EmpNum; i++)
			{
				int minOrMax = i;
				for (int j = i + 1; j < m_EmpNum; j++)
				{
					if (select == 1)//升序
					{
						if (m_EmpArray[minOrMax]->m_ID > m_EmpArray[j]->m_ID)
						{
							minOrMax = j;
						}
					}
					else//降序
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
			cout << "排序成功，排序后结果为：" << endl;
			this->save();
			this->show_Emp();
			
		}
	}

	void workerManger::Clean_File()
	{
		cout << "确认清空" << endl;
		cout << "1.确认" << endl;
		cout << "2.返回" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//ios::trunc模式，如果存在删除文件并重新创建
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
		cout << "清空成功" << endl;
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