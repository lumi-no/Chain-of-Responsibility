#include <iostream>
#include <string>
#include <memory>


class Handler {
protected:
    std::shared_ptr<Handler> nextHandler_; 

public:
    virtual ~Handler() = default;

    
    void SetNext(std::shared_ptr<Handler> handler) {
        nextHandler_ = handler;
    }

   
    virtual void Handle(const std::string& request) const {
        if (nextHandler_) {
            nextHandler_->Handle(request);
        }
    }
};


class ConcreteHandler1 : public Handler {
public:
    void Handle(const std::string& request) const override {
        if (request == "Task1") {
            std::cout << "ConcreteHandler1 обробляє " << request << ".\n";
        }
        else if (nextHandler_) {
            std::cout << "ConcreteHandler1 передає запит далі.\n";
            nextHandler_->Handle(request);
        }
    }
};


class ConcreteHandler2 : public Handler {
public:
    void Handle(const std::string& request) const override {
        if (request == "Task2") {
            std::cout << "ConcreteHandler2 обробляє " << request << ".\n";
        }
        else if (nextHandler_) {
            std::cout << "ConcreteHandler2 передає запит далі.\n";
            nextHandler_->Handle(request);
        }
    }
};


class ConcreteHandler3 : public Handler {
public:
    void Handle(const std::string& request) const override {
        if (request == "Task3") {
            std::cout << "ConcreteHandler3 обробляє " << request << ".\n";
        }
        else {
            std::cout << "ConcreteHandler3: Запит не оброблено.\n";
        }
    }
};

void ClientCode(const std::shared_ptr<Handler>& handler, const std::string& request) {
    handler->Handle(request);
}

int main() {

    auto handler1 = std::make_shared<ConcreteHandler1>();
    auto handler2 = std::make_shared<ConcreteHandler2>();
    auto handler3 = std::make_shared<ConcreteHandler3>();

   
    handler1->SetNext(handler2);
    handler2->SetNext(handler3);

    std::cout << "Запит 'Task1':\n";
    ClientCode(handler1, "Task1");

    std::cout << "\nЗапит 'Task2':\n";
    ClientCode(handler1, "Task2");

    std::cout << "\nЗапит 'Task3':\n";
    ClientCode(handler1, "Task3");

    std::cout << "\nЗапит 'UnknownTask':\n";
    ClientCode(handler1, "UnknownTask");

    return 0;
}
