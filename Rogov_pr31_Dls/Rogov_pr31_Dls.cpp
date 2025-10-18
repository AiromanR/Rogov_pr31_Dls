// Rogov_pr31_Dls.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

struct EventSystem {
    struct Node {
        void(*data)();
        Node* next;

        Node(void(*value)()) : data(value), next(nullptr) {};
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    void registerHandler(EventSystem& system, void(*handler)()) {
        Node* node = new Node(*handler);

        if (head == nullptr) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
        tail = node;
    }
    void triggerEvent(const EventSystem& system) {
        for (Node* i = head; i != nullptr; i = i->next) {
            i->data();
        }
    }
};
void handler(std::string message) {
    std::cout << message << std::endl;
}
void onUserLogin() {
    std::cout << "Пользователь вошел в систему\n";
}
void onUserLogout() {
    std::cout << "Пользователь вышел из системы\n";
}
void onError() {
    std::cout << "Произошла ошибка\n";
}
int main()
{
    setlocale(LC_ALL, "Russian");
    EventSystem system;

    system.registerHandler(system, &onUserLogin);
    system.registerHandler(system, &onUserLogout);
    system.registerHandler(system, &onUserLogout);
    system.registerHandler(system, &onError);
    system.registerHandler(system, &onError);
    system.registerHandler(system, &onError);
    system.registerHandler(system, &onError);

    system.triggerEvent(system);
}
