#include <tuple>
#include <iostream>

struct Node {
    double val;
    Node* next;
	Node* prev;
};

Node* findStart(Node* head, Node* turtle)
{
	while (head != turtle)
    {
		head = head->next;
		turtle = turtle->next;
	}
	return head;
}

size_t measure(Node* turtle, Node* hare)
{
	size_t count = 0;
	while (hare)
    {
		hare = hare->next;
		++count;
		if (hare == turtle)
        {
            return count;
        }
	}
	return 0;
}

std::pair<Node*, size_t> floyd(Node* head)
{
		Node* turtle = head;
		Node* hare = head;
		while (hare && turtle)
        {
			turtle = turtle->next;
			if (hare->next)
            {
                hare = hare->next->next;
            }
			else
            {
                hare = nullptr;
            }
			if (hare && (hare == turtle))
            {
				return {findStart(head, turtle), measure(turtle, hare)};
			}
		}
		return {nullptr, 0};
}

int main() {

}