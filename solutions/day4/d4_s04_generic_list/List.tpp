
template<class T>
List<T>::List():
	first(NULL), last(NULL), currentSize(0)
{}

template<class T>
List<T>::~List() {
	// just delete first element while list is not empty
	while (currentSize > 0) {
		deleteFirst();
	}
}

template<class T>
List<T>::List(const List<T>& other):
	first(NULL), last(NULL), currentSize(0)
{
	for (ListItem<T> *item = other.first; item != NULL; item = item->getNext()) {
		appendElement(item->getContent());
	}
}

template<class T>
void List<T>::appendElement(const T& i) {
	ListItem<T> *item = new ListItem<T>(last, NULL, i);
	last = item;
	// if size WAS 0, set first item to newly created item
	if (currentSize++ == 0) {
		first = item;
	}
}

template<class T>
void List<T>::prependElement(const T& i) {
	ListItem<T> *item = new ListItem<T>(NULL, first, i);
	first = item;
	// if size WAS 0, set last item to newly created item
	if (currentSize++ == 0) {
		last = item;
	}
}

template<class T>
void List<T>::insertElementAt(const T& i, int pos) {
	if (pos <= 0) {
		prependElement(i);
	}
	if (pos >= getSize()) {
		appendElement(i);
	}
	else {
		ListItem<T>* p = first;
		// iterate over elements
		while (pos-- > 0) {
			p = p->getNext();
		}
		new ListItem<T>(p->getPrevious(), p, i);
		++currentSize;
	}
}

template<class T>
int List<T>::getSize() const {
	return currentSize;
}

template<class T>
T& List<T>::getNthElement(int n) {
	ListItem<T>* p = first;
	// iterate over elements
	while (n-- > 0) {
		p = p->getNext();
	}
	return p->getContent();
}

template<class T>
T& List<T>::getFirst() {
	return first->getContent();
}

template<class T>
T& List<T>::getLast() {
	return last->getContent();
}

template<class T>
void List<T>::deleteFirst() {
	if (first) {
		ListItem<T> *next = first->getNext();
		delete first; // delete first element
		first = next; // and the current first element to next of first element before
		// do not forget to reset last element if list is empty
		if (next == NULL) {
			last = NULL;
		}
		--currentSize;
	}
}

template<class T>
void List<T>::deleteLast() {
	if (last) {
		ListItem<T> *prev = last->getPrevious();
		delete last; // delete last element
		last = prev; // and the current last element to previous of last element before
		// do not forget to reset first element if list is empty
		if (last == NULL) {
			first = NULL;
		}
		--currentSize;
	}
}

/** delete element at given position. delete first/last if pos outside of range */
template<class T>
void List<T>::deleteAt(int pos) {
	if (pos <= 0) {
		return deleteFirst();
	}
	else if (pos >= currentSize - 1) {
		return deleteLast();
	}
	else {
		ListItem<T>* p = first;
		// iterate over elements
		while (pos-- > 0) {
			p = p->getNext();
		}
		delete p;
		--currentSize;
	}
}

template<class T>
ListIterator<T> List<T>::begin() {
	return ListIterator<T>(this, first);
}

template<class T>
ListIterator<T> List<T>::end() {
	return ListIterator<T>(this, NULL);
}

template<class T>
std::ostream& operator<<(std::ostream& out, List<T>& list) {
	out << "[";
	ListIterator<T> iter = list.begin();
	if (iter != list.end()) {
		out << *iter++;
		while (iter != list.end()) {
			out << ", " << *iter++;
		}
	}
	out << "]";
	return out;
}
