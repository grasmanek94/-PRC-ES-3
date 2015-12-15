void BubbleSort(Key* head) {
	bool done = false;
	
	Key* prev = NULL;
	Key* curr = NULL;
	Key* temp = NULL;
	
	while (!done) { //each iteration through the whole list
		done = true;
		curr = prev = head;
		while (curr->getNext() != NULL) {
			if (curr->getText() > curr->getNext()->getText()) {
				done = false;
				// do swap
				temp = curr->getNext();
				curr->setNext(curr->getNext()->getNext());
				temp->setNext(curr);
				if (curr == head) {
					head = prev = temp;
				} else {
					prev->setNext(temp);
				}
				curr = temp;
			}
			prev = curr;
			curr = curr->getNext();
		}
	}
	//std::cout << "new head: " << head->getText() << std::endl;
	//std::cout << "nexttext: " << head->getNext()->getText() << std::endl;
}
