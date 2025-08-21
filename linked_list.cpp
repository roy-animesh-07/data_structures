#include<bits/stdc++.h>
using namespace std;

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
		void insertAtEnd(int data);
		void deleteFromEnd();
		void insertAtHead(int data);
		void deleteFromHead();
		bool isListEmpty();
		int nodesCount();
		bool isListSorted();
		void sortList();
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
	node *temp = this->head;
	head = head->next;
	if(temp) delete(temp);
}
void llist::printList() {
	node *temp = head;
	if(temp==nullptr) {
		cout<<"List is empty\n";
	}
	while(temp!=nullptr) {
		cout<<temp->data<<" ";
		temp = temp->next;
	}
	cout<<"\n";
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


int main()  {
	llist l1;
	for(int i = 0;i<20;i++) {
		int val = rand() %1000;
		l1.insertAtEnd(val);
	}

	l1.printList();

	cout<<l1.isListEmpty()<<"\n";
	cout<<l1.nodesCount()<<"\n";
	cout<<l1.isListSorted()<<"\n";


	l1.sortList();
	cout<<l1.isListSorted()<<"\n";
	l1.printList();
	return 0;
}