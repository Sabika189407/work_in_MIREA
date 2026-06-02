#include <tuple>
#include <iostream>

struct Node {
    double value;
    Node* next;
	Node* previous;
};

Node* start_find(Node* head, Node* turtle)
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

std::pair<Node*, size_t> floyd_algorythm(Node* head)
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
				return {start_find(head, turtle), measure(turtle, hare)};
			}
		}
		return {nullptr, 0};
}
int main(){
    Node* nodes[5];
    nodes[4] = new Node{5, nullptr};
    nodes[3] = new Node{4, nodes[4]};
    nodes[2] = new Node{3, nodes[3]};
    nodes[1] = new Node{2, nodes[2]};
    nodes[0] = new Node{1, nodes[1]};
    nodes[4]->next = nodes[2];
    std::pair<Node*, size_t> result = floyd_algorythm(nodes[0]);
    if (result.first)
    {
            std::cout << "The length of cycle " << result.second << " in node\'" << result.first->value << "\'" << std::endl;
    }
    else
    {
            std::cout << "Cycle was not found" << std::endl;
    }
    for (size_t i = 0; i < 5; i++)
    {
        delete nodes[i];
    }
}