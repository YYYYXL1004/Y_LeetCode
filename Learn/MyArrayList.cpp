#include <iostream>
#include <vector>
using namespace std;

template<typename E> // E是一个万能的类型占位符

class MyArrayList {
private:
    E* data;
    int size;  // 当前元素数量
    int cap;
    static const int INIT_CAP=1; // 初始容量

public:
    MyArrayList() {
        this->data = new E[INIT_CAP];
        this->size = 0;
        this->cap = INIT_CAP;
    }
    MyArrayList(int initCap) {
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
            return;  
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
    void addFirst(E e) {
        add(0, e);
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
        for(int i = index; i < size - 1; i++) {  // 修复: 从index向后遍历
            data[i] = data[i+1];  // 修复: 将后面的元素向前移动
        }
        data[size-1] = E();
        size--;
        return deleteVal;
    }
    E removeFirst() {
        return remove(0); // 复用
    }

    // 查
    E get(int index) {
        if(index >= size) {
            return 0;
        }
        return data[index];
    }

    // 改
    E set(int index, E element) {
        if(index >= size) {
            return 0;
        }
        E oldVal = data[index];
        data[index] = element;
        return oldVal;
    }

    // 工具方法
    int getSize() {
        return size;
    }
    
    void resize(int newCap) {
        E* temp = new E[newCap];
        for (int i = 0; i < size; i++) {
            temp[i] = data[i];
        }

        // 释放原数组内存
        delete[] data;

        data = temp;
        cap = newCap;
    }

    ~MyArrayList() {
        delete[] data;
    }
};

int main() {
    MyArrayList<int> arr(3);
    for(int i=0; i<5; i++) {
        arr.addLast(i);
    } // 0 1 2 3 4

    arr.remove(4); // 0 1 2 3
    arr.add(1, 9); // 0 9 1 2 3
    arr.addFirst(100); // 100 0 9 1 2 3

    int val = arr.removeLast(); // 100 0 9 1 2

    for(int i=0;i < arr.getSize(); i++) {
        cout<< arr.get(i) <<endl;
    }
    return 0;
}