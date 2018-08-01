/*
* =========================================================================================
* Name        : listLib.h
* Author      : Duc Dung Nguyen
* Email       : nddung@hcmut.edu.vn
* Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
* Description : library for Assignment 1 - Data structures and Algorithms - Spring 2017
* =========================================================================================
*/

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
using namespace std;

class DSAException {
	int     _error;
	string  _text;
public:

	DSAException() : _error(0), _text("Success") {}
	DSAException(int err) : _error(err), _text("Unknown Error") {}
	DSAException(int err, const char* text) : _error(err), _text(text) {}

	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
	T data;
	L1Item<T> *pNext;
	L1Item() : pNext(NULL) {};
	L1Item(T &a) : data(a), pNext(NULL) {};
};

template <class T>
class L1List {
	L1Item<T>   *_pHead;// The head pointer of linked list
	size_t      _size;// number of elements in this list
public:
	L1List() : _pHead(NULL), _size(0) {}
	~L1List() {};
	int removeHead();
	void    clean();
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	T&  at(int i) {
		L1Item<T>   *p = _pHead;
		for (int j = 0; j < i; j++) {
			p = p->pNext;
		}
		return p->data;
	};
	T&      operator[](int i) {
		return at(i);
	}
	bool    find(T& a, int& idx) {
		L1Item<T>   *p = _pHead;
		if (_pHead == NULL) {
			idx = -1;
			return false;
		}
		idx = 0;
		while (p->pNext != NULL && p->data != a) {
			p = p->pNext;
			idx++;
		}

		if (p->data == a) {
			return true;
		}
		idx = -1;
		return false;
	};
	int     insert(int i, T& a) {
		if (i == 0) {
			return insertHead(a);
		}
		else {
			L1Item<T>   *p = _pHead;
			for (int j = 1; j < i; j++) {
				p = p->pNext;
			}
			if (p->pNext == NULL) return push_back(a);

			L1Item<T> *temp = new L1Item<T>(a);
			temp->pNext = p->pNext;
			p->pNext = temp;
		}
		_size++;
		return 0;
	};
	int     remove(int i) {
		if (i == 0) return removeHead();
		if (i >= _size - 1) return removeLast();
		L1Item<T>   *p = _pHead;
		for (int j = 1; j < i; j++) {
			p = p->pNext;
		}
		L1Item<T> *temp = p->pNext;
		p->pNext = temp->pNext;
		delete temp;
		_size--;
		return 0;

	};

	int     push_back(T& a);
	int     insertHead(T& a);
	int     removeLast();

	void reverse() {

		L1Item<T> *p = this->_pHead;
		if (p == NULL) return;
		L1Item<T> *pTemp = NULL;
		while (p != NULL) {
			L1Item<T> *pNew = new L1Item<T>(p->data);
			if (pTemp == NULL) pTemp = pNew;
			else {
				pNew->pNext = pTemp;
				pTemp = pNew;
			}
			p = p->pNext;
		}
		this->_pHead = pTemp;
	};
	void    traverse(void(*op)(T&)) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, void*), void* pParam) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data, pParam);
			p = p->pNext;
		}
	}

	void    traverse1(void(*op)(T&, void*, int &), void* pParam, int &a) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data, pParam, a);
			p = p->pNext;
		}
	}
};


/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
	if (_pHead == NULL) {
		_pHead = new L1Item<T>(a);
	}
	else {
		L1Item<T>   *p = _pHead;
		while (p->pNext) p = p->pNext;
		p->pNext = new L1Item<T>(a);
	}

	_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
	L1Item<T>   *p = new L1Item<T>(a);
	p->pNext = _pHead;
	_pHead = p;
	_size++;
	return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
	if (_pHead) {
		L1Item<T>* p = _pHead;
		_pHead = p->pNext;
		delete p;
		_size--;
		return 0;
	}
	return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
	if (_pHead) {
		if (_pHead->pNext) {
			L1Item<T>* prev = _pHead;
			L1Item<T>* pcur = prev->pNext;
			while (pcur->pNext) {
				prev = pcur;
				pcur = pcur->pNext;
			}
			delete pcur;
			prev->pNext = NULL;
		}
		else {
			delete _pHead;
			_pHead = NULL;
		}
		_size--;
		return 0;
	}
	return -1;
}


#endif //A01_LISTLIB_H

