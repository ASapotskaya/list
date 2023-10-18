#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <io.h>
#include <exception>
using namespace std;

enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}

struct Node
{
	int data;
	Node* next;//адрес следующего элемента
};

class myList
{
	Node* Head = nullptr;
	Node* Tail = nullptr;
	int count = 0;
public:

	//конструктор по умолчанию дублирует начальное состояние полей
	myList()
	{
		Head = Tail = nullptr;
		count = 0;
	}

	~myList()
	{
		while (count != 0)
		{
			getElementFromHead();
		}
	}

	//метод для удаления элемента с головы списка
	int getElementFromHead()
	{
		if (Head != nullptr)
		{
			Node* dell = Head;
			Head = Head->next;//перебросили голову на следующий элемент
			int temp = dell->data;
			delete dell;
			count--;
			//если элемент, который мы удаляем был последним в списке
			if (count == 0)
			{
				Head = Tail = nullptr;
			}
			if (count == 1)//если после удаления остался только один элемент
			{
				Tail = Head;
			}
			return temp;
		}
	}
	//метод для добавления объекта в хвост списка
	void addElement(int data)
	{
		//создаём динамический объект
		Node* newelement = new Node;
		newelement->data = data;

		//если это первый добавляемый в список элемент - то он и голова и хвост
		if (Head == nullptr)
		{
			Head = Tail = newelement;
		}
		//если это не первый элемент - нам нужно добавить его после хвоста 
		//и перебросить указатель хвоста на него
		else
		{
			//за хвостом стоит новый элемент
			Tail->next = newelement;
			Tail = newelement;//этот элемент яввляется хвостом
		}
		count++;
		Tail->next = nullptr;//за хвостовым элементом никого нет
	}
	//показ всего списка
	void printList()
	{
		//если список не пуст
		if (Head != nullptr)
		{
			Node* move = Head;//заппоминаем адрес головы
			while (move != nullptr)
			{
				cout << move->data << "\n";
				//перепрыгиваем на следующий элемент
				move = move->next;
			}
		}
		else
		{
			throw exception("list is empty");
		}
	}

	//добавить в голову
	void addElementtoHead(int a_data)
	{
		if (Head == nullptr)
		{
			addElement(a_data);
		}
		else
		{
			//создаем новый элемент
			Node* newelement = new Node;
			newelement->data = a_data;
			// записываем указатель на следующий элемпент(старая голова)
			newelement->next = Head;
			// Головой назначаем новый элемент
			Head = newelement;
			count++;
		}
	}
	//удалить с позиции
	void eraseFromPos(int position)
	{
		if (position == 0)
		{
			getElementFromHead();
		}
		else
		{
			Node* position_befor_dell;
			Node* dell;
			//адрес головы
			position_befor_dell = Head;
			for (size_t i = 0; i < position - 1; i++)
			{
				position_befor_dell = position_befor_dell->next;
			}
			cout << "!!!! " << position_befor_dell->data << endl;
			dell = position_befor_dell->next;
			if (dell->next == nullptr)//если элемент. который мы удаляем это хвост
			{
				position_befor_dell->next = nullptr;
				Tail = position_befor_dell;
			}
			else
			{
				position_befor_dell = position_befor_dell->next->next;
			}
			cout << "dell " << dell->data << endl;
			delete dell;

			count--;
		}
		if (count == 0)
		{
			Head = Tail = nullptr;
		}
		if (count == 1)//если после удаления остался только один элемент
		{
			Tail = Head;
		}

	}




	//перегрузить []
	int operator[](int index)
	{
		Node* temp;
		temp = Head;
		for (size_t i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		return temp->data;
		//обработать ситуацию. если позиция за границами списка
	}

	//ДЗ
	//перегрузить ! - инвертировать список

	
	//получить элемент с позиции
	int GetElement(int number)const
	{
			Node* newelement = new Node;
			newelement->data = number;
			if (count == 0)
			{
				throw exception("List is empty");
			}
		//проверка порядкового номера в списке
		if (number > 0 && number <= count)
		{
			//если указан номер первого узла, вернем голову
			if (number == 1)return Head->data;
			//если указан номер последнего узла вернем хвост
			if (number == count)return Tail->data;
			//указатель на элемент списка для перемещения, помещаем голову
			Node* temp = Head;
			for (size_t i = 1; i < number; i++)//чтобы найти адрес 3 узла нужно дойти до второго
			{
				temp = temp->next; // переходим к следущему
			}
			return temp->data;//возвращаем адрес из поля next узла перед искомым (из 2 если ищем 3)
		}
		
	}
	//добавить на позицию

	void addToPosition(int position, int arg)
	{

		//создаем новый элемент(выделяем память)
		Node* New = new Node;  //проверка выделения памяти
		//заполняем узел данными
		New->data = arg;
		if (position >= 0 || position >= count - 1)
		{

			//если добавляем узел в начало списка
			if (!position)
			{
				addElementtoHead(arg);
			}
			else //иначе добавление узла после указанного
			{

				Node* Pos = new Node;
				Pos = Head;
				for (size_t i = 1; i < position; i++)
				{
					Pos = Pos->next;

				}

				New->next = Pos->next; //новый элемент указывает на тот элемент,на который йказывал элемент, после которого добавляется новы элеемент
				Pos->next = New; //узел после которого добавляется новый узел указывает на новый как следущий за собой
				if (Pos == Tail)Tail = New; //если добавляем узел после последнего узла, то новый узел станет хвостом
			}
			count++;
		}
	}
};
void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	myList list;
	for (size_t i = 0; i < 5; i++)
	{
		list.addElement(rand() % 45);
	}
	list.printList();
	cout << "getElement = " << list.getElementFromHead() << "\n";
	cout << "getElement = " << list.getElementFromHead() << "\n";
	cout << "getElement = " << list.getElementFromHead() << "\n";
	cout << "getElement = " << list.getElementFromHead() << "\n";
	cout << "\nLIST\n";
	list.printList();
	list.addElement(rand() % 45);
	cout << "\nLIST\n";
	list.printList();
	cout << "getElement = " << list.getElementFromHead() << "\n";
	cout << "getElement = " << list.getElementFromHead() << "\n";
	cout << "\nLIST\n";
	list.addElementtoHead(100);
	list.addElementtoHead(200);
	list.addElementtoHead(400);
	/*try
	{
		list.printList();
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}
	*/
	list.addToPosition(3, 3);
	list.printList();
	/*try
	{
		cout << "Addtoposition = " << list.addToPosition(10,5)  << "\n";
		cout << "Addtoposition = " <<  << "\n";
		cout << "Addtoposition = " <<  << "\n";
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}*/
}