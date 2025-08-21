#include<iostream>
class node {
	public:
		int data;
		node *next;
		node () {
			data = 0;
			next = nullptr;
		}
		node(int data) {
			this->data = data;
			next = nullptr;
		}
};
class llist {
		node *head;

		//helper functions
		node* merge(node* left, node* right);
		node* getMiddle(node* head);
		node* mergeSort(node* head);
	public:
		llist() {
			head = nullptr;
		}
		llist(int data) {
			head = new node(data);
		}
		~llist() {
			node* temp;
			while (head) {
				temp = head;
				head = head->next;
				delete temp;
			}
		}
		void insertAtEnd(int data);
		void deleteFromEnd();
		void insertAtHead(int data);
		void deleteFromHead();
		bool isListEmpty();
		int nodesCount();
		bool isListSorted();
		void sortList();
		bool isNodePresent(int data);
		void insertAfterInodes(int data,int i);
		void deleteAfterInodes(int i);
		void reverseList();
		void printList();
};
node* llist::merge(node* left, node* right){
	if(!left) return right;
	if(!right) return left;

	node *res = nullptr;
	if(left->data<=right->data) {
		res = left;
		res->next = merge(left->next,right);
	}
	else{
		res = right;
		res->next = merge(left,right->next);
	}
	return res;

}
node* llist::getMiddle(node* head){
	if(!head) return head;
	node *slow = head,*fast = head->next;
	while(fast != nullptr && fast->next!=nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}
node* llist::mergeSort(node* head){
	if(head==nullptr || head->next==nullptr) return head;
	node *mid = getMiddle(head);
	node *midNext = mid->next;
	//break the list
	mid->next = nullptr;
	node *lef = mergeSort(head);
	node *rig = mergeSort(midNext);

	return merge(lef,rig);
}
void llist::insertAtEnd(int data) {
	node *temp = this->head;
	node *newnode = new node(data);
	if(head==nullptr) {
		head = newnode;
		return;
	}
	while(temp->next!=nullptr) {
		temp = temp->next;
	}
	
	temp->next = newnode;
}
void llist::deleteFromEnd() {
	if (!head) return; 
    if (!head->next) { 
        delete head;
        head = nullptr;
        return;
    }
	node *temp = this->head;
	node *prev = nullptr;
	while(temp->next!=nullptr) {
		prev = temp;
		temp = temp->next;
	}
	if(prev) {
		prev->next = nullptr;
	}
	delete(temp);
}
void llist::insertAtHead(int data) {
	node *temp = head;
	node *newnode = new node(data);
	newnode->next = head;
	this->head = newnode;
}
void llist::deleteFromHead() {
	if (!head) return; 
    if (!head->next) { 
        delete head;
        head = nullptr;
        return;
    }
	node *temp = this->head;
	head = head->next;
	if(temp) delete(temp);
}
void llist::printList() {
	node *temp = head;
	if(temp==nullptr) {
		std::cout<<"List is empty\n";
	}
	while(temp!=nullptr) {
		std::cout<<temp->data<<" ";
		temp = temp->next;
	}
	std::cout<<"\n";
}
bool llist::isListEmpty() {
	if(head==nullptr) return 1;
	else return 0;
}
int llist::nodesCount() {
	node *temp = head;
	int numberOfNodes = 0;
	while(temp!=nullptr) {
		numberOfNodes++;
		temp = temp->next;
	}
	return numberOfNodes;
}
bool llist::isListSorted() {
	node *temp = head;
	if(isListEmpty()) {
		return 1;
	}
	bool ch = 1;
	int prev = head->data;
	temp = temp->next;
	while(temp!=nullptr && ch) {
		if(prev<=temp->data) {
			prev = temp->data;
		}
		else{
			ch = 0;
			break;
		}
		temp = temp->next;
	}
	return ch;
}
void llist::sortList() {
	head = mergeSort(this->head);
}
bool llist::isNodePresent(int data) {
	node *temp = head;
	bool ch = false;
	while(temp!=nullptr) {
		if(temp->data==data) {
			ch=true;
			break;
		}
		temp = temp->next;
	}
	return ch;
}
void llist::insertAfterInodes(int data,int i) {
	node *temp = head;
	if(nodesCount()<i ) {
		std::cout<<"Insertion Failed list has less than i nodes\n";
	}
	else{
		node *prev = head;
		while(i--) {
			prev = temp;
			temp = temp->next;
		}
		node *newnode = new node(data);
		prev->next = newnode;
		newnode->next = temp;
	}
}
void llist::deleteAfterInodes(int i) {
	node *temp = head;
	if(nodesCount()<i ) {
		std::cout<<"Deletion Failed list has less than i nodes\n";
	}
	else{
		node *prev = head;
		while(i--) {
			prev = temp;
			temp = temp->next;
		}
		prev->next = temp->next;
		delete(temp);
	}
}
void llist::reverseList() {
	if(head==nullptr || head->next==nullptr) return;
	node *prev = nullptr;
	node *curr = head;
	node *nex = head->next;
	while(curr!=nullptr) {
		curr->next = prev;
		prev = curr;
		curr = nex;
		if(nex)
			nex = nex->next;
	}
	head = prev;
}
int main()  {

	llist l1;
	for(int i = 0;i<5;i++) {
		int val = rand() %1000;
		l1.insertAtEnd(val);
	}

	l1.printList();

	std::cout<<l1.isListEmpty()<<"\n";
	std::cout<<l1.nodesCount()<<"\n";
	std::cout<<l1.isListSorted()<<"\n";


	l1.sortList();
	std::cout<<l1.isListSorted()<<"\n";
	l1.printList();
	l1.reverseList();
	l1.deleteAfterInodes(2);
	l1.insertAfterInodes(5,2);
	std::cout<<l1.isNodePresent(776)<<"\n";
	l1.printList();
	return 0;
}