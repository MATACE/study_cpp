#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include <iostream>
#include <memory>

using namespace std;

namespace memento {

class EditorMemento {
public:
    EditorMemento() = delete;
    explicit EditorMemento(const string& content)
        : content_(content) {}
    string GetContent() const {return content_;}
    virtual ~EditorMemento() = default;
private:
    string content_;
};

class Editor {
    using save_state = shared_ptr<EditorMemento>;
public:
    Editor() = default;
    virtual ~Editor() = default;
    void Write(string content) {
        content_ = content;
    }
    save_state Save() {
        return make_shared<EditorMemento>(content_);
    }
    void ResState(save_state& save) {
        content_  = save->GetContent();
    }
    string GetContent() const {return content_;}

private:
    string content_;
};

}

#endif // MEMENTO_HPP