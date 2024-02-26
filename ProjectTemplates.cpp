#include <iostream>
#include <string>

const int MAX_ITEMS = 10; // Global constant for the maximum number of items

template <typename T>
class EntertainmentCollection {
private:
    T* items[MAX_ITEMS];
    int numItems;

public:
    EntertainmentCollection() : numItems(0) {
        for (int i = 0; i < MAX_ITEMS; ++i) {
            items[i] = nullptr;
        }
    }

    void add(T* item) {
        if (numItems < MAX_ITEMS) {
            items[numItems++] = item;
            std::cout << "Item added: " << item->getTitle() << std::endl;
        }
        else {
            throw FullCollection();
        }
    }

    T* remove() {
        if (numItems > 0) {
            T* removedItem = items[--numItems];
            items[numItems] = nullptr;
            std::cout << "Item removed: " << removedItem->getTitle() << std::endl;
            return removedItem;
        }
        else {
            throw EmptyCollection();
        }
    }

    int getNumItems() const {
        return numItems;
    }

    class FullCollection {}; // Exception class for full collection
    class EmptyCollection {}; // Exception class for empty collection
};

template <typename T>
class Item {
public:
    std::string title;

    Item(const std::string& t) : title(t) {}

    std::string getTitle() const {
        return title;
    }
};

int main() {
    EntertainmentCollection<Item<std::string>> collection;

    while (true) {
        std::cout << "Press 1 to add an item to the collection." << std::endl;
        std::cout << "Press 2 to remove an item from the collection." << std::endl;
        std::cout << "Press 3 to see how many items are currently in the collection." << std::endl;
        std::cout << "Press 4 to quit." << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string title;
            std::cout << "Enter the item title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            Item<std::string>* newItem = new Item<std::string>(title);
            try {
                collection.add(newItem);
            }
            catch (const EntertainmentCollection<Item<std::string>>::FullCollection&) {
                std::cerr << "Error! Collection is full. Cannot add more items." << std::endl;
            }
            break;
        }
        case 2: {
            try {
                Item<std::string>* removedItem = collection.remove();
                delete removedItem; // Frees the memory of the removed item
            }
            catch (const EntertainmentCollection<Item<std::string>>::EmptyCollection&) {
                std::cerr << "Error! Collection is empty. Cannot remove an item." << std::endl;
            }
            break;
        }
        case 3:
            std::cout << "Number of items in the collection: " << collection.getNumItems() << std::endl;
            break;
        case 4:
            return 0;
        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }

    return 0;
}
