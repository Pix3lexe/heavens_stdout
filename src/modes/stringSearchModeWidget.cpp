#include "stringSearchModeWidget.h"

StringSearchModeWidget::StringSearchModeWidget(QWidget *parent) : QWidget(parent)
{
    mUi.setupUi(this);

    connect(
        mUi.stringSearchLineEdit,
        &QLineEdit::returnPressed,
        this,
        &StringSearchModeWidget::onStringSearchLineEditReturnPressed);
}

void StringSearchModeWidget::onStringSearchLineEditReturnPressed()
{
    mUi.godTextBrowserSearchMode->clear();
    QString searchString = mUi.stringSearchLineEdit->text();
    mUi.stringSearchLineEdit->clear();
    auto        res         = mGenerator.searchString(searchString);
    QString     returnedStr = res.first;
    std::size_t foundInd    = res.second;
    mUi.godTextBrowserSearchMode->setText(returnedStr);
    mUi.stringSearchLineEdit->setText(QString("Found after %1 letters").arg(res.second));
}
