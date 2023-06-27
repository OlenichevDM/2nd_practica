#include <iostream>
using namespace std;

/*Класс Node представляет узел двусвязного списка*/
class Node {
public:
    int data;
    Node* prev;
    Node* next;

public:
    Node(int data) {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }
};

/*Класс LinkedList представляет собой реализацию двусвязного списка*/
class LinkedList {
public:
    Node* head;
    Node* tail;

public:
    /*Конструктор LinkedList является конструктором без параметров
    и инициализирует начальные значения указателей head и tail 
    списка значением NULL*/
    LinkedList() {
        head = tail = NULL;
    }

    /*Деструктор ~LinkedList освобождает память, выделенную под узлы списка,
    вызывая функцию clear()*/
    ~LinkedList() {
        clear();
    }

    /*Функция clear() очищает список, удаляя все его элементы*/
    void clear() {
        while (head != NULL) {
            pop_front();
        }
    }

    /*Функция push_front(int data) добавляет элемент в начало списка*/
    Node* push_front(int data) {
        Node* node = new Node(data);
        node->next = head;
        if (head != NULL) {
            head->prev = node;
        }
        if (tail == NULL) {
            tail = node;
        }
        head = node;

        return node;
    }

    /*Функция push_back(int data) добавляет элемент в конец списка*/
    Node* push_back(int data) {
        Node* node = new Node(data);
        node->prev = tail;
        if (tail != NULL) {
            tail->next = node;
        }
        if (head == NULL) {
            head = node;
        }
        tail = node;

        return node;
    }

    /*Функция pop_front() удаляет первый элемент списка*/
    void pop_front() {
        if (head == NULL) {
            return;
        }

        Node* node = head->next;
        if (node != NULL) {
            node->prev = NULL;
        }
        else
            tail = NULL;

        delete head;
        head = node;
    }

    /*Функция pop_back() удаляет последний элемент списка*/
    void pop_back() {
        if (tail == NULL) {
            return;
        }

        Node* node = tail->prev;
        if (node != NULL) {
            node->next = NULL;
        }
        else
            head = NULL;

        delete tail;
        tail = node;
    }

    /*Функция getAt(int index) возвращает указатель на узел списка по заданному индексу*/
    Node* getAt(int index) {
        Node* node = head;
        int n = 0;

        while (n != index) {
            if (node == NULL) {
                return node;
            }
            node = node->next;
            n++;
        }

        return node;
    }

    /*Функция insert(int index, int data) вставляет новый узел со значением data на заданную позицию в связном списке*/
    Node* insert(int index, int data) {
        Node* right = getAt(index);
        if (right == NULL) {
            return push_back(data);
        }

        Node* left = right->prev;
        if (left == NULL) {
            return push_front(data);
        }

        Node* node = new Node(data);

        node->prev = left;
        node->next = right;
        left->next = node;
        right->prev = node;

        return node;
    }

    /*Функция earse(int index) используется для удаления узла из связного списка по указанному индексу*/
    void earse(int index) {
        Node* node = getAt(index);
        if (node == NULL) {
            return;
        }
        if (node->prev == NULL) {
            pop_front();
            return;
        }
        if (node->next == NULL) {
            pop_back();
            return;
        }

        Node* left = node->prev;
        Node* right = node->next;
        left->next = right;
        right->prev = left;

        delete node;
    }

    /*Функция remove(int data) используется для удаления всех узлов в связном списке, которые содержат заданное значение data*/
    void remove(int data) {
        Node* node = head;

        while (node != NULL) {
            if (node->data == data) {
                if (node == head) {
                    pop_front();
                }
                else if (node == tail) {
                    pop_back();
                }
                else {
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                    delete node;
                }
                return;
            }
            node = node->next;
        }
    }

    /*Функция printList() используется для печати содержимого связного списка*/
    void printList() {
        Node* node = head;
        while (node != NULL) {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }

    /*Функция swap принимает два индекса index1 и index2. Сначала она находит узлы списка, соответствующие этим индексам, 
    с помощью функции getAt. Затем происходит обмен ссылками между узлами и обновление ссылок соседних узлов*/
    void swap(int index1, int index2) {
        if (index1 == index2) { // Проверяется, являются ли индексы одинаковыми. Если да, то обмен не требуется
            return;
        }

        Node* node1 = getAt(index1); // Получаем указатель на узел списка с индексом index1
        Node* node2 = getAt(index2); // Получаем указатель на узел списка с индексом index2

        if (node1 == NULL || node2 == NULL) { // Проверяем, что оба узла существуют. Если хотя бы один из них отсутствует, то обмен не может быть выполнен, и функция завершается
            return;
        }

        /*Сохраняются указатели на соседние узлы для node1 и node2*/
        Node* prev1 = node1->prev;
        Node* next1 = node1->next;
        Node* prev2 = node2->prev;
        Node* next2 = node2->next;

        if (prev1 != NULL) { // Проверяется, существует ли предыдущий узел для node1. Если да, то выполняется обновление связи, чтобы предыдущий узел указывал на node2
            prev1->next = node2;
        }
        else { // Если предыдущего узла нет, то head обновляется, чтобы указывать на node2
            head = node2;
        }

        if (next1 != NULL) { // Проверяется, существует ли следующий узел для node1. Если да, то выполняется обновление связи, чтобы следующий узел указывал на node2
            next1->prev = node2;
        }
        else { // Если следующего узла нет, то tail обновляется, чтобы указывать на node2
            tail = node2;
        }

        if (prev2 != NULL) { // Проверяется, существует ли предыдущий узел для node2. Если да, то выполняется обновление связи, чтобы предыдущий узел указывал на node1
            prev2->next = node1;
        }
        else { // Если предыдущего узла нет, то head обновляется, чтобы указывать на node1
            head = node1;
        }

        if (next2 != NULL) { // Проверяется, существует ли следующий узел для node2. Если да, то выполняется обновление связи, чтобы следующий узел указывал на node1
            next2->prev = node1;
        }
        else { // Если следующего узла нет, то tail обновляется, чтобы указывать на node1
            tail = node1;
        }

        /*Обмениваем значения узлов node1 и node2*/
        node1->prev = prev2;
        node1->next = next2;
        node2->prev = prev1;
        node2->next = next1;
    }

};

int main()
{
    setlocale(LC_ALL, "rus"); // устанавливает локаль программы на русскую, чтобы поддерживать русский язык ввода-вывода

    LinkedList lst; // создает объект класса LinkedList с именем lst

    int choice;
    bool exit = false;

    while (!exit) {
        cout << "Выберите операцию:" << endl;
        cout << "1. Создание списка с вводом элементов с клавиатуры" << endl;
        cout << "3. Удалить первый элемент списка" << endl;
        cout << "4. Удалить последний элемент списка" << endl;
        cout << "5. Вывести список" << endl;
        cout << "6. Очистить список" << endl;
        cout << "7. Удалить элемент по значению" << endl;
        cout << "8. Удалить элемент по номеру" << endl;
        cout << "9. Выполнить перестановку двух элементов списка" << endl;
        cout << "10. Добавить элемент в определенную позицию" << endl;
        cout << "11. Добавить элемент в начало списка" << endl;
        cout << "12. Добавить элемент в конец списка" << endl;
        cout << "13. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        /*switch (choice) является конструкцией, которая позволяет выполнить
        различные действия в зависимости от значения переменной choice. Здесь choice представляет выбор операции,
        сделанный пользователем в меню. Код внутри блока switch содержит несколько case, каждый из которых соответствует
        определенной операции. Когда значение choice совпадает с значением в каком-либо case,
        код выполняет соответствующие действия внутри этого case. Если ни одно из значений choice не совпадает с case,
        выполнение переходит к блоку default, который определяет действия при неправильном выборе.*/
        switch (choice) {
        case 11: {
            system("cls");
            int data;
            cout << "Введите элемент для добавления в начало списка: ";
            cin >> data;
            lst.push_front(data);
            cout << "Элемент успешно добавлен в начало списка." << endl << endl;
            continue;;
        }
        case 12: {
            system("cls");
            int data;
            cout << "Введите элемент для добавления в конец списка: ";
            cin >> data;
            lst.push_back(data);
            cout << "Элемент успешно добавлен в конец списка." << endl << endl;
            continue;;
        }
        case 3: {
            system("cls");
            lst.pop_front();
            cout << "Первый элемент списка успешно удален." << endl << endl;
            continue;;
        }
        case 4: {
            system("cls");
            lst.pop_back();
            cout << "Последний элемент списка успешно удален." << endl << endl;
            continue;;
        }
        case 5: {
            system("cls");
            cout << "Список: ";
            lst.printList();
            cout << endl;
            continue;;
        }
        case 6: {
            system("cls");
            lst.clear();
            cout << "Список успешно очищен." << endl << endl;
            continue;;
        }
        case 7: {
            system("cls");
            int data;
            cout << "Введите значение элемента для удаления: ";
            cin >> data;
            lst.remove(data);
            cout << "Элемент успешно удален." << endl << endl;
            continue;;
        }
        case 8: {
            system("cls");
            int index;
            cout << "Введите номер элемента для удаления: ";
            cin >> index;
            lst.earse(index);
            cout << "Элемент успешно удален." << endl << endl;
            continue;;
        }
        case 9: {
            system("cls");
            int index1, index2;
            cout << "Введите индекс первого элемента для перестановки: ";
            cin >> index1;
            cout << "Введите индекс второго элемента для перестановки: ";
            cin >> index2;
            lst.swap(index1, index2);
            cout << "Элементы успешно переставлены." << endl << endl;
            continue;
        }
        case 10: {
            system("cls");
            int index, data;
            cout << "Введите номер позиции для вставки элемента: ";
            cin >> index;
            cout << "Введите значение элемента: ";
            cin >> data;
            lst.insert(index, data);
            cout << "Элемент успешно добавлен в позицию " << index << "." << endl << endl;
            continue;;
        }
        case 1: {
            system("cls");
            int size;
            cout << "Введите количество элементов списка: ";
            cin >> size;
            cout << endl;

            cout << "Введите элементы списка: " << endl;
            for (int i = 0; i < size; i++) {
                int data;
                cout << "Элемент " << i + 1 << ": ";
                cin >> data;
                lst.push_back(data);
            }

            cout << "Односвязный список успешно создан." << endl << endl;
            continue;
        }
        case 13: {
            exit = true;
            break;
        }
        default: {
            cout << "Неверный выбор. Попробуйте снова." << endl << endl;
            break;
        }
        }
    }

    cout << endl << endl << endl << endl << endl;

    return 0;
}
