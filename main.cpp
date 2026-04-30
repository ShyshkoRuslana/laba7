#include <iostream>
#include "SingleList.h"
#include "DoubleList.h"

using namespace std;
int main() {
        try {
            SingleList<int> s;
            s.push_back(10);
            s.push_back(2);
            s.push_front(0);
            s.insert_at(3, 5);
            cout << "Singly: " << s << "\n";
            cout << "s[3] = " << s[3] << "\n";
            cout << "find 1 at " << s.find(2) << "\n";
            s.remove_at(2);
            cout << "after remove: " << s << "\n";
            s.pop_front();
            s.pop_back();
            cout << "after pops: " << s << " size=" << s.size() << "\n";

            DoubleList<string> d;
            d.push_back("one");
            d.push_front("zero");
            d.push_back("two");
            d.insert_at(2, "middle");
            cout << "Doubly: " << d << "\n";
            cout << "d[2] = " << d[2] << "\n";
            cout << "find 'two' at " << d.find(string("two")) << "\n";
            d.remove_at(1);
            cout << "after remove: " << d << "\n";

            SingleList<int> e;
        }
        catch (const exception& ex) {
            cout << "Exception: " << ex.what() << "\n";
        }
        return 0;
}