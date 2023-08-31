#include<iostream>
#include<fstream>
#include<string>
#include <cassert>
using namespace std;
template <typename T>
struct Data {
    T score; //スコア
    string username; //ユーザー名

    Data(T score, const string& username) : score(score), username(username) {}//スコアとユーザー名のコンストラクタ
};
template <typename T>
class DoublyLinkedList {
private:
    template<typename L>
    struct Node {
        Node* prev; //前のノードへのポインタ
        Node* next; //次のノードへのポインタ
        Data<L> data; //成績データ

        Node(L score, const string& username) : prev(nullptr), next(nullptr), data(score, username) {}//ノード構造体のコンストラクタ
    };
    Node<T> *head;//ノードへのポインタ
    size_t size;//データ数の取得
public:
    Node<T> *getHead()const {
        return head;
    }
    size_t getSize() const {
        return size;
    }
    DoublyLinkedList() : head(nullptr),/* tail(nullptr)*/ size(0) {}//DoublyLinkedListのコンストラクタ
    class ConstIterator {
    private:
        typename DoublyLinkedList::template Node<T>* current;//現在のノード
        ConstIterator(Node* node) : current(node) {} //currentのコンストラクタ
        const Data<T>& operator*() const {
            assert(current != nullptr);
            return current->data;//イテレータの指す要素の取得
        }

        ConstIterator& operator++() {
            assert(current != nullptr);
            if (current) {
                current = current->next;//リストの末尾に一つ進める
            }
            return *this;
        }

        ConstIterator& operator--() {
            assert(current != nullptr);
            if (current) {
                current = current->prev;//リストの先頭に一つ進める
            }
            return *this;
        }
        ConstIterator& operator=(const ConstIterator& other) {
            if (this != &other) {
                current = other.current;//代入
            }
            return *this;
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current;//同一か比較
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;//異なるか比較
        }
        friend class DoublyLinkedList;
    };
    ConstIterator begin() const {
        return ConstIterator(head);//コンストイテレータの先頭を返す
    }

    ConstIterator end() const {
        return ConstIterator(head);//コンストイテレータの末尾を返す 
    }
    class Iterator :public ConstIterator {
    private:
        Node* current;
        Iterator(Node* node) :ConstIterator(node), current(node) {
            current = node;//currentにnodeを代入
        }

        Data<T>& operator*() {
            return current->data;//非const版の取得
        }
        operator ConstIterator() const {
            return ConstIterator(current);
        }
        friend class DoublyLinkedList;
    };
    Iterator begin() {
        return Iterator(head);//イテレータの先頭を返す
    }

    Iterator end() {
        return Iterator(head);//イテレータの末尾を返す
    }

    void insert(Iterator position, T score, const string& username) {
        typename Node<T>::template Node<T>* newNode = new typename Node<T>::template Node<T>(score, username);
        if (position == begin()) {
            if (head == nullptr) { // 空のリストの場合
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
            if (head == nullptr) { // 空のリストの場合
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
            if (size == 1) { //サイズが1の場合
                head = nullptr;
            }
            else {
                Node* nextNode = position.current->next;//ノードを一つ後に
                nextNode->prev = position.current->prev;//ノードをひとつ前に
                position.current->prev->next = nextNode;
                if (position.current == head) {
                    head = nextNode;
                }
                delete position.current;
            }
        }
        else {
            Node* prevNode = position.current->prev;//ひとつ前に
            Node* nextNode = position.current->next;//一つ後に
            prevNode->next = nextNode;//prevNodeをnextNodeに
            nextNode->prev = prevNode;//NextnodeをprevNodeに
            delete position.current;
        }
        size--;
    }
    void Constremove(ConstIterator position) {
        if (position == begin()) {
            if (size == 1) { //サイズが1の場合
                head = nullptr;
            }
            else {
                Node* nextNode = position.current->next;//ノードを一つ後に
                nextNode->prev = position.current->prev;//ノードをひとつ前に
                position.current->prev->next = nextNode;
                if (position.current == head) {
                    head = nextNode;
                }
                delete position.current;
            }
        }
        else {
            Node* prevNode = position.current->prev;//ひとつ前に
            Node* nextNode = position.current->next;//一つ後に
            prevNode->next = nextNode;//prevNodeをnextNodeに
            nextNode->prev = prevNode;//NextnodeをprevNodeに
            delete position.current;
        }
        size--;
    }

};
