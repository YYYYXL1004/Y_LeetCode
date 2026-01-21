#include <iostream>
#include <vector>
using namespace std;

template<typename E> // E是一个万能的类型占位符

class MyArrayList() {
private:
    E* data;
    int size;  // 当前元素数量
    int cap;
    static const int INIT_CAP=1; // 初始容量

pubilc:
    MyArrayList() {
        this->data = new E[INIT_CAP];
        this->size = 0;
        this->cap = INIT_CAP;
    }
    MyArrayList(int intiCap) {
        this->data = new E[initCap];
        this->size = 0;
        this->cap = initCap;
    }
    // 增
    void addLast(E e) {
        if(size == cap) {
            resize(2 * cap); // 容量不够，扩容2倍
        }
        data[size] = e;
        size++;
    }

    void add(int index, E e) {
        if(index > cap) {
            return 0;
        }
        if(size==cap) {
            resize(2 * cap);
        }
        for(int i = size-1; i>=index; i--) {
            data[i+1] = data[i];
        } // 向后腾位置
        data[index] = e;
        size++; 
    }

    //删
    E removeLast() {
        if(size==0) {
            return 0;
        }
        if(size == cap / 4) { // 缩容，节省空间
            resize(cap / 2);
        }
        E deleteVal = data[size-1];
        data[size-1] = E(); // 最后一个元素置空，否则内存泄露
        size--;
        return deleteVal;
    }

    E remove(int index) {
        if(index >= size) {
            return 0;
        }   
        if(size == cap / 4) {
            resize(cap / 2);
        }
        E deleteVal = data[index];
        for(int i = size-1; i>=index; i--) {
            data[i-1] = data[i];
        }
        data[size-1] = E();
        size--;
        return deleteVal;
    }
    E removeFirst() {
        return remove(0); // 复用
    }

    // 查
    

}
int main() {

    return 0;
}