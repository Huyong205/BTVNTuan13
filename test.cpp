#include<bits/stdc++.h>
using namespace std;

struct Product{
	string name;
	int qty;
	int price;
	Product* next;
};

struct QueueProduct{
	Product* front;
	Product* rear;
};


struct Customer{
	QueueProduct head;
	Customer* next;
};

void initQueueProduct(QueueProduct& head){
	head.front = NULL;
	head.rear = NULL;
}

void enQueueProduct(QueueProduct& head, Product a){
	Product* newNode = new Product;
	newNode->name = a.name;
	newNode->qty = a.qty;
	newNode->price = a.price;
	newNode->next = NULL;
	if(head.rear == NULL){
		head.front = head.rear = newNode;	
	}
	else{
		head.rear->next = newNode;
		head.rear = newNode;
	}
}

void deQueueProduct(QueueProduct& head){
  if (head.front == NULL){
    return;
  }
  Product* tmp = head.front;
  head.front = head.front->next;
  if (head.front == NULL){
    head.rear = NULL;
  }
  delete tmp;
}

int calculateTotalRevenue(QueueProduct& head){
  int total = 0;
  while (head.front != NULL) {
    total += head.front->price * head.front->qty;
    deQueueProduct(head);
  }
  return total;
}

struct QueueCustomer{
	Customer* front;
	Customer* rear;
};

void initQueueCustomer(QueueCustomer& head){
	head.front = head.rear = NULL;
}

void enQueueCustomer(QueueCustomer& headC, Customer a){
	Customer* newNode = new Customer;
	newNode->head = a.head;
	newNode->next = NULL;
	if(headC.rear == NULL){
		headC.front = headC.rear = newNode;	
	}
	else{
		headC.rear->next = newNode;
		headC.rear = newNode;
	}
}

void deQueueCustomer(QueueCustomer& head){
  if (head.front == NULL){
    return;
  }
  Customer* tmp = head.front;
  head.front = head.front->next;
  if (head.front == NULL){
    head.rear = NULL;
  }
  delete tmp;
}

int thanhToan(QueueCustomer& head){
	int total = 0;
	while(head.front != NULL){
		total += calculateTotalRevenue(head.front->head);
		deQueueCustomer(head);
	}
	return total;
}

int soSPA(QueueCustomer head){
	int cnt = 0;
	Customer* tmp = head.front;
	while(tmp != NULL){
		Product* tmp2 = tmp->head.front;
		while(tmp2 != NULL){
			if(tmp2->name == "A") cnt += tmp2->qty;
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return cnt;
}

void print(QueueProduct head){
	while(head.front != NULL){
		cout << head.front->name << ' ';
		head.front = head.front->next;
	}
}

int main(){
	Product a{"A", 2, 1};
	Product b{"B", 1, 1};
	Product c{"C", 1, 1};
	Product d{"D", 1, 1};
	QueueCustomer head;
	initQueueCustomer(head);
	
	Customer x;
	initQueueProduct(x.head);
	enQueueProduct(x.head, a);
	enQueueProduct(x.head, b);
	enQueueProduct(x.head, c);
	enQueueProduct(x.head, d);
	
	Customer y;
	initQueueProduct(y.head);
	enQueueProduct(y.head, a);
	enQueueProduct(y.head, b);
	enQueueProduct(y.head, c);
	enQueueProduct(y.head, d);
	
	enQueueCustomer(head, x);
	enQueueCustomer(head, y);
	
	cout << "So san pham A: " << soSPA(head) << endl;
	cout << thanhToan(head);
}
