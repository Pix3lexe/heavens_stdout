#include "heavens_stdout.h"

HeavensStdout::HeavensStdout(QWidget *parent) : QMainWindow(parent)
{
    mUi.setupUi(this);
    connect(mUi.talkButton, &QPushButton::clicked, this, &HeavensStdout::onTalkButtonClicked);
}

void HeavensStdout::onTalkButtonClicked()
{
    mUi.godLineEdit->setText(mGenerator.generate_sentence(Complexity::NORMAL));
}
