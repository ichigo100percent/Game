#include <iostream>
#include <memory>

// 추상 제품 1: 버튼
class Button {
public:
    virtual ~Button() = default;
    virtual void paint() const = 0;
};

// 추상 제품 2: 체크박스
class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void paint() const = 0;
};

// 구체적 제품 1A: 윈도우 스타일 버튼
class WindowsButton : public Button {
public:
    void paint() const override {
        std::cout << "Windows Button\n";
    }
};

// 구체적 제품 1B: 맥 스타일 버튼
class MacButton : public Button {
public:
    void paint() const override {
        std::cout << "Mac Button\n";
    }
};

// 구체적 제품 2A: 윈도우 스타일 체크박스
class WindowsCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "Windows Checkbox\n";
    }
};

// 구체적 제품 2B: 맥 스타일 체크박스
class MacCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "Mac Checkbox\n";
    }
};

// 추상 팩토리: GUI 팩토리
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
};

// 구체적 팩토리: 윈도우 스타일 GUI 팩토리
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<WindowsCheckbox>();
    }
};

// 구체적 팩토리: 맥 스타일 GUI 팩토리
class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};

// 클라이언트: GUI 애플리케이션
class Application {
private:
    std::unique_ptr<GUIFactory> factory;

public:
    Application(std::unique_ptr<GUIFactory> factory) : factory(std::move(factory)) {}

    void paint() {
        auto button = factory->createButton();
        auto checkbox = factory->createCheckbox();

        button->paint();
        checkbox->paint();
    }
};

// 클라이언트 코드
int main() {
    std::unique_ptr<GUIFactory> factory;

    // 윈도우 스타일 GUI 사용
    factory = std::make_unique<WindowsFactory>();
    Application appWindows(std::move(factory));
    appWindows.paint();

    // 맥 스타일 GUI 사용
    factory = std::make_unique<MacFactory>();
    Application appMac(std::move(factory));
    appMac.paint();

    return 0;
}