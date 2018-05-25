#include <iostream>

using namespace std;

typedef struct Node {
	Node* parent;
	Node* left;
	Node* right;
	int value;
	int color;
}Node;

enum {black=100, red=200};
void insertNode(int n);
void makeRedBlackTree(int n);
Node* ruleFirst(Node* temp);
Node* ruleSecond(Node* temp);
Node* ruleThird(Node* temp);

Node* head=NULL;

int main()
{
	for (int i = 0; i < 6; i++)
	{
		int temp;
		scanf("%d", &temp);
		insertNode(temp);
		makeRedBlackTree(temp);
	}
}

Node* ruleFirst(Node* temp)
{
	if (temp->parent->parent != NULL)
	{
		if (temp->parent->parent->right != temp->parent && temp->parent->parent->right!=NULL)   //삼촌이 오른쪽에 있을 경우
		{
			if (temp->parent->parent->right->color == red)
			{
				temp->parent->color = black;
				temp->parent->parent->right->color = black;
				temp->parent->parent->color = red;
				return temp->parent->parent;
			}
			else
			{
				return NULL;
			}
		}
		else if (temp->parent->parent->left != temp->parent && temp->parent->parent->left!=NULL)// 삼촌이 왼쪽에 있을 경우
		{
			if (temp->parent->parent->left->color == red)
			{
				temp->parent->color = black;
				temp->parent->parent->left->color = black;
				temp->parent->parent->color = red;
				return temp->parent->parent;
			}
			else
			{
				return NULL;
			}
		}
	}
	return NULL;
}

Node* ruleSecond(Node* temp)
{
	if (temp->parent->parent != NULL)
	{
		if (temp->parent->parent->right != temp->parent || temp->parent->parent->right == NULL)   //삼촌이 오른쪽에 있을 경우
		{
			if (temp->parent->parent->right == NULL || temp->parent->parent->right->color == black)
			{
				if (temp->parent->right == temp)
				{
					Node* temp1 = temp->parent->parent;
					Node* temp2 = temp->parent;
					temp1->left = temp;
					if (temp->left != NULL)  //왼쪽 자식이 있는 경우
					{
						temp2->right = temp->left;
						temp->left = temp2;
					}
					else
					{
						temp2->right = NULL;
						temp->left = temp2;
					}

					return ruleThird(temp2);
				}
			}
			else
			{
				return NULL;
			}
		}
		else if (temp->parent->parent->left != temp->parent || temp->parent->parent->left == NULL)// 삼촌이 왼쪽에 있을 경우
		{
			if (temp->parent->parent->left == NULL || temp->parent->parent->left->color == black)
			{
				if (temp->parent->right == temp)
				{
					Node* temp1 = temp->parent->parent;
					Node* temp2 = temp->parent;
					temp1->right = temp;
					if (temp->left != NULL)  //왼쪽 자식이 있는 경우
					{
						temp2->right = temp->left;
						temp->left = temp2;
					}
					else
					{
						temp2->right = NULL;
						temp->left = temp2;
					}

					return ruleThird(temp2);
				}
			}
			else
			{
				return NULL;
			}
		}
	}
	return NULL;
}
Node* ruleThird(Node* temp)
{
	if (temp->parent->parent != NULL)
	{
		if (temp->parent->parent->right == NULL || temp->parent->parent->right != temp->parent)   //삼촌이 오른쪽에 있을 경우
		{
			if (temp->parent->parent->right == NULL || temp->parent->parent->right->color == black)
			{
				if (temp->parent->left == temp)
				{
					temp->parent->color = black;
					temp->parent->parent->color = red;
					Node* temp1 = temp->parent;
					Node* temp2 = temp->parent->parent;
					if (temp1->right != NULL)
					{
						temp2->left = temp1->right;
						temp1->right = temp2;
					}
					else
					{
						temp2->left = NULL;
						temp1->right = temp2;
					}
					return temp1;
				}
			}
			else
			{
				return NULL;
			}
		}
		else if (temp->parent->parent->left != temp->parent || temp->parent->parent->left == NULL)// 삼촌이 왼쪽에 있을 경우
		{
			if (temp->parent->parent->left == NULL||temp->parent->parent->left->color == black)
			{
				if (temp->parent->left == temp)
				{
					temp->parent->color = black;
					temp->parent->parent->color = red;
					Node* temp1 = temp->parent;
					Node* temp2 = temp->parent->parent;
					if (temp1->right != NULL)
					{
						temp2->left = temp1->right;
						temp1->right = temp2;
					}
					else
					{
						temp2->left = NULL;
						temp1->right = temp2;
					}
					return temp1;
				}
			}
			else
			{
				return NULL;
			}
		}
	}
	return NULL;
}
void makeRedBlackTree(int n)
{
	Node* temp=head;  //search를 위한 초기화

	while (true)
	{
		if (n < temp->value)
		{
			temp = temp->left;
		}
		else if (n > temp->value)
		{
			temp = temp->right;
		}
		else
		{
			break;
		}
	}

	while (temp != head)
	{
		Node* result = ruleFirst(temp);
		if (result != NULL)
		{
			temp = result;
		}
		else
		{
			result = ruleSecond(temp);
			if (result != NULL)
			{
				temp = result;
			}
			else
			{
				result = ruleThird(temp);
				if (result != NULL)
				{
					temp = result;
				}
			}
		}
		if (temp->parent == head)
		{
			break;
		}
	}
	if (head->color == red)
	{
		head->color = black;
	}
}



void insertNode(int n)      //노드 삽입하는 함수
{
	Node* temp = head;
	if (head == NULL)
	{
		Node* element = (Node*)malloc(sizeof(Node));
		element->parent = NULL;
		element->right = NULL;
		element->left = NULL;
		element->value = n;
		element->color = black;
		head = element;
	}

	while (temp!=NULL)
	{
		if (temp->value > n)
		{
			if (temp->left == NULL)
			{
				Node* element = (Node*)malloc(sizeof(Node));
				element->color = red;
				element->right = element->left = NULL;
				element->parent = temp;
				element->value = n;

				temp->left = element;
				cout << temp->value << " 의 자식 " << n << endl;
				break;
			}
			else
			{
				temp = temp->left;
			}
		}
		else
		{
			if (temp->right == NULL)
			{
				Node* element = (Node*)malloc(sizeof(Node));
				element->color = red;
				element->right = element->left = NULL;
				element->parent = temp;
				element->value = n;

				temp->right = element;
				cout << temp->value << " 의 자식 " << n << endl;
				break;
			}
			else
			{
				temp = temp->right;
			}
		}
	}
}

