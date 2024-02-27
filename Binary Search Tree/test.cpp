#include <algorithm>
#include <cassert>

template <typename T>
struct Node {
    T v;
    Node *child, *sibling, *parent;

    Node(const T &val) : v(val), child(nullptr), sibling(nullptr), parent(nullptr) {}
    Node(T &&val) : v(std::move(val)), child(nullptr), sibling(nullptr), parent(nullptr) {}
};

template <typename T, typename Cmp=std::less<T>>
class PairingHeap {

    using Node = Node<T>;

    private:

        Node *root_;
        size_t size_;
        Cmp cmp;

        void swap(Node *&x, Node *&y) {
            Node *temp = x;
            x = y;
            y = temp;
        }

        Node* meld(Node *x, Node *y) {
            if (!x) return y;
            if (!y) return x;
            // The compare function should return true when "smaller" on the
            // left hand side.
            if (cmp(y->v, x->v)) swap(x, y);
            if (x->child) x->child->parent = y;
            y->sibling = x->child;
            y->parent = x;
            x->child = y;
            return x;
        }

        Node* merge(Node *x) {
            if (!x) return nullptr;
            x->parent = nullptr;
            if (!(x->sibling)) return x;

            Node *y = x->sibling, *c = y->sibling;
            y->parent = nullptr;
            x->sibling = nullptr;
            y->sibling = nullptr;

            return meld(merge(c), meld(x, y));

        }

        Node* decrease(Node *root, Node *x, T v) {
            x->v = v;
            if (x == root) return x;
            if (x->parent->child == x) x->parent->child = x->sibling;
            else x->parent->sibling = x->sibling;
            if (x->sibling) x->sibling->parent = x->parent;
            x->sibling = nullptr;
            x->parent = nullptr;
            return meld(root, x);
        }

        Node* pop(Node *x) {
            Node *t = merge(x->child);
            // If remove the "delete" line, the memory that holds the
            // original x is not release, we can still access the v stored
            // at that memory or else we will just get some garbage value after deleting
            delete x;
            return t;
        }

    public:
        PairingHeap() : size_(0), root_(nullptr) {};

        PairingHeap(Cmp cmp) : cmp(cmp), size_(0), root_(nullptr) {
        }

        void meld(PairingHeap other) {
            root_ = meld(root_, other.root_);
            size_ += other.size_;
        }

        void meld(Node *other) {
            root_ = meld(root_, other);
            size_++;
        }

        void decrease(Node *x, T v) {
            root_ = decrease(root_, x, v);
        }

        T pop() {
            assert(size_ && "The heap is empty...");
            T t = root_->v;
            root_ = pop(root_);
            size_--;
            return t;

        }

        [[nodiscard]] bool empty() {
            return size_;
        }

        [[nodiscard]] size_t size() const {
            return size;
        }

        [[nodiscard]] T top() const {
            return root_->v;
        }
};

int main() {
//    using T = std::pair<int, std::string>;
//    auto f = [](std::pair<int, std::string> &a, std::pair<int, std::string> &b) {return a.second < b.second;};
//    PairingHeap<T, decltype(f)> heap(f);
//    Node<T> *p = new Node(std::make_pair(5, std::string("Oscar")));
//    heap.meld(p);

//    p = new Node(6);
//    heap.meld(p);
//    p = new Node(std::make_pair(3, std::string("Cindy")));
//    heap.meld(p);
//    p = new Node(std::make_pair(4, std::string("Batman")));
//    heap.meld(p);
//    p = new Node(7);
//    heap.meld(p);
//    p = new Node(8);
//    heap.meld(p);
//    std::random_device rd;
    std::mt19937 gen(21);
    std::uniform_int_distribution<> rand(1, 100);
    using T = int;

    PairingHeap<T> p, q, h;

    for (int i = 0; i < 5; i++) {

        Node<T> *t = new Node(rand(gen));
        p.meld(t);
        p.decrease(t, i);
        t = new Node(rand(gen));
        q.meld(t);
    }
    p.meld(q);
    std::cout << p.pop() << std::endl;
    std::cout << p.pop() << std::endl;
    std::cout << p.pop() << std::endl;
    std::cout << p.pop() << std::endl;
    std::cout << p.pop() << std::endl;
    std::cout << p.pop() << std::endl;
    std::cout << p.pop() << std::endl;
    std::cout << p.pop() << std::endl;
    std::cout << p.pop() << std::endl;
    std::cout << p.pop() << std::endl;
//    std::cout << p.pop() << std::endl;


//    Node<T> *t = new Node(2);
//    p.meld(t);
//    t = new Node(7);
//    p.meld(t);
//    t = new Node(6);
//    Node<T> *f = t;
//    h.meld(t);
//    t = new Node(9);
//    h.meld(t);
//    p.meld(h);
//    t = new Node(4);
//    q.meld(t);
//    t = new Node(5);
//    q.meld(t);
//    p.meld(q);
//    p.decrease(f, 1);
////    p.pop();
//    std::cout << p.pop() << std::endl;
//    std::cout << p.pop() << std::endl;
//    std::cout << p.pop() << std::endl;
//    std::cout << p.pop() << std::endl;
//    std::cout << p.pop() << std::endl;
//    std::cout << p.pop() << std::endl;
}

