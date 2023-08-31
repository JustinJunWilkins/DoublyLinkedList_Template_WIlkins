#include<iostream>
#include<fstream>
#include<string>
#include <cassert>
using namespace std;
template <typename T>
struct Data {
    T score; //�X�R�A
    string username; //���[�U�[��

    Data(T score, const string& username) : score(score), username(username) {}//�X�R�A�ƃ��[�U�[���̃R���X�g���N�^
};
template <typename T>
class DoublyLinkedList {
private:
    template<typename L>
    struct Node {
        Node* prev; //�O�̃m�[�h�ւ̃|�C���^
        Node* next; //���̃m�[�h�ւ̃|�C���^
        Data<L> data; //���уf�[�^

        Node(L score, const string& username) : prev(nullptr), next(nullptr), data(score, username) {}//�m�[�h�\���̂̃R���X�g���N�^
    };
    Node<T> *head;//�m�[�h�ւ̃|�C���^
    size_t size;//�f�[�^���̎擾
public:
    Node<T> *getHead()const {
        return head;
    }
    size_t getSize() const {
        return size;
    }
    DoublyLinkedList() : head(nullptr),/* tail(nullptr)*/ size(0) {}//DoublyLinkedList�̃R���X�g���N�^
    class ConstIterator {
    private:
        typename DoublyLinkedList::template Node<T>* current;//���݂̃m�[�h
        ConstIterator(Node* node) : current(node) {} //current�̃R���X�g���N�^
        const Data<T>& operator*() const {
            assert(current != nullptr);
            return current->data;//�C�e���[�^�̎w���v�f�̎擾
        }

        ConstIterator& operator++() {
            assert(current != nullptr);
            if (current) {
                current = current->next;//���X�g�̖����Ɉ�i�߂�
            }
            return *this;
        }

        ConstIterator& operator--() {
            assert(current != nullptr);
            if (current) {
                current = current->prev;//���X�g�̐擪�Ɉ�i�߂�
            }
            return *this;
        }
        ConstIterator& operator=(const ConstIterator& other) {
            if (this != &other) {
                current = other.current;//���
            }
            return *this;
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current;//���ꂩ��r
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;//�قȂ邩��r
        }
        friend class DoublyLinkedList;
    };
    ConstIterator begin() const {
        return ConstIterator(head);//�R���X�g�C�e���[�^�̐擪��Ԃ�
    }

    ConstIterator end() const {
        return ConstIterator(head);//�R���X�g�C�e���[�^�̖�����Ԃ� 
    }
    class Iterator :public ConstIterator {
    private:
        Node* current;
        Iterator(Node* node) :ConstIterator(node), current(node) {
            current = node;//current��node����
        }

        Data<T>& operator*() {
            return current->data;//��const�ł̎擾
        }
        operator ConstIterator() const {
            return ConstIterator(current);
        }
        friend class DoublyLinkedList;
    };
    Iterator begin() {
        return Iterator(head);//�C�e���[�^�̐擪��Ԃ�
    }

    Iterator end() {
        return Iterator(head);//�C�e���[�^�̖�����Ԃ�
    }

    void insert(Iterator position, T score, const string& username) {
        typename Node<T>::template Node<T>* newNode = new typename Node<T>::template Node<T>(score, username);
        if (position == begin()) {
            if (head == nullptr) { // ��̃��X�g�̏ꍇ
                head = newNode;
                newNode->prev = newNode->next = newNode;
            }
            else {
                newNode->next = head;
                newNode->prev = head->prev;
                head->prev->next = newNode;
                head->prev = newNode;
                if (position.current == head) {
                    head = newNode;
                }
            }
        }
        else if (position == end()) {

        }
        else {
            Node* prevNode = position.current->prev;
            newNode->prev = prevNode;
            newNode->next = position.current;
            prevNode->next = newNode;
            position.current->prev = newNode;
        }
        size++;
    }

    void Constinsert(ConstIterator position, int const score, const string& username) {
        typename Node<T>::template Node<T>* newNode = new typename Node<T>::template Node<T>(score, username);
        if (position == begin()) {
            if (head == nullptr) { // ��̃��X�g�̏ꍇ
                head = newNode;
                newNode->prev = newNode->next = newNode;
            }
            else {
                newNode->next = head;
                newNode->prev = head->prev;
                head->prev->next = newNode;
                head->prev = newNode;
                if (position.current == head) {
                    head = newNode;
                }
            }
        }
        else if (position == end()) {

        }
        else {
            Node* prevNode = position.current->prev;
            newNode->prev = prevNode;
            newNode->next = position.current;
            prevNode->next = newNode;
            position.current->prev = newNode;
        }
        size++;
    }
    void remove(Iterator position) {
        if (position == begin()) {
            if (size == 1) { //�T�C�Y��1�̏ꍇ
                head = nullptr;
            }
            else {
                Node* nextNode = position.current->next;//�m�[�h������
                nextNode->prev = position.current->prev;//�m�[�h���ЂƂO��
                position.current->prev->next = nextNode;
                if (position.current == head) {
                    head = nextNode;
                }
                delete position.current;
            }
        }
        else {
            Node* prevNode = position.current->prev;//�ЂƂO��
            Node* nextNode = position.current->next;//����
            prevNode->next = nextNode;//prevNode��nextNode��
            nextNode->prev = prevNode;//Nextnode��prevNode��
            delete position.current;
        }
        size--;
    }
    void Constremove(ConstIterator position) {
        if (position == begin()) {
            if (size == 1) { //�T�C�Y��1�̏ꍇ
                head = nullptr;
            }
            else {
                Node* nextNode = position.current->next;//�m�[�h������
                nextNode->prev = position.current->prev;//�m�[�h���ЂƂO��
                position.current->prev->next = nextNode;
                if (position.current == head) {
                    head = nextNode;
                }
                delete position.current;
            }
        }
        else {
            Node* prevNode = position.current->prev;//�ЂƂO��
            Node* nextNode = position.current->next;//����
            prevNode->next = nextNode;//prevNode��nextNode��
            nextNode->prev = prevNode;//Nextnode��prevNode��
            delete position.current;
        }
        size--;
    }

};