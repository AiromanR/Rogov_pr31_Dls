// Rogov_pr31_Dls.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

struct EventSystem {
    struct Node {

        union Handlers {
            void(*simpleHandler)();
            void(*messageHandler)(std::string*);
        };
        Handlers Handler;

        std::string* messages;
        Node* next;

        Node(void(*handler)()) : messages(nullptr), next(nullptr) {
            Handler.simpleHandler = handler;
        }
        Node(void(*handler)(std::string*), std::string* msgs) : messages(msgs), next(nullptr) {
            Handler.messageHandler = handler;
        }
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    void registerHandler(void(*handler)()) {
        Node* node = new Node(handler);

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

    void registerHandler(void(*handler)(std::string*), std::string* messages) {
        Node* node = new Node(handler, messages);

        if (head == nullptr) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    void triggerEvent() {
        for (Node* i = head; i != nullptr; i = i->next) {
            if (i->messages) {
                i->Handler.messageHandler(i->messages);
            }
            else {
                i->Handler.simpleHandler();
            }
        }
    }
};

void onUserLogin() {
    std::cout << "Пользователь вошел в систему\n";
}

void onUserLogout() {
    std::cout << "Пользователь вышел из системы\n";
}

void onError() {
    std::cout << "Произошла ошибка!\n";
}

void onError(std::string* messages) {
    std::cout << "Произошла ошибка:";
    for (int i = 0; messages[i] != ""; i++) {
        if (i != 0) std::cout << ", \"" << messages[i] << "\"";
        else std::cout << " \"" << messages[i] << "\"";
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    EventSystem system;

    system.registerHandler(&onUserLogin);
    system.registerHandler(&onUserLogout);
    system.registerHandler(&onUserLogout);
    system.registerHandler(&onError);


    std::string error1[] = { "Неверный пароль", "" };
    system.registerHandler(&onError, error1);

    std::string error2[] = { "Соединение разорвано", "Таймаут", "" };
    system.registerHandler(&onError, error2);

    std::string error3[] = { "Неверный пароль", "Двааааааааа", "Триииииииииии", "" };
    system.registerHandler(&onError, error3);

    std::string error4[] = { "11111111111111", "222222222222", "33333333333333", "444444444444" , "" };
    system.registerHandler(&onError, error4);

    system.triggerEvent();
}

