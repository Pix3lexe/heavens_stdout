#include "generator.h"

#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("God's Microphone");

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLineEdit *textField = new QLineEdit();
    textField->setReadOnly(true);
    layout->addWidget(textField);

    QPushButton *button = new QPushButton("Speak to me");
    layout->addWidget(button);

    Generator generator{};

    QObject::connect(
        button, &QPushButton::clicked, [&]() { textField->setText(generator.generate_sentence(Complexity::NORMAL)); });

    window.setLayout(layout);
    window.show();

    return app.exec();
}
