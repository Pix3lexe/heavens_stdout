#include "stringSearchModeWidget.h"

#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

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
    mUi.godTextBrowserSearchMode->setText("Searching in gods messages...");

    auto watcher = new QFutureWatcher<std::pair<QString, std::size_t>>(this);

    connect(
        watcher,
        &QFutureWatcher<std::pair<QString, std::size_t>>::finished,
        this,
        [=, this]()
        {
            auto res = watcher->result();
            mUi.godTextBrowserSearchMode->setText(res.first);
            mUi.stringSearchLineEdit->setText(QString("Found after %1 letters").arg(res.second));
            watcher->deleteLater();
        });

    QFuture<std::pair<QString, std::size_t>> future =
        QtConcurrent::run([=, this]() { return mGenerator.searchString(searchString); });

    watcher->setFuture(future);
}
