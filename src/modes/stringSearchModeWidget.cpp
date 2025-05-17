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

    auto watcher = new QFutureWatcher<std::tuple<QString, int, std::size_t>>(this);

    connect(
        watcher,
        &QFutureWatcher<std::tuple<QString, int, std::size_t>>::finished,
        this,
        [=, this]()
        {
            auto [context, localIndex, globalIndex] = watcher->result();
            QString before =
                context.left(localIndex); // or res.second if you want to exclude the matched character itself
            QString match = context.mid(localIndex, searchString.length());
            QString after = context.mid(localIndex + searchString.length());

            QString displayText =
                QString("%1<span style=\"color: red; font-weight: bold;\">%2</span>%3").arg(before, match, after);
            mUi.godTextBrowserSearchMode->setHtml(displayText);

            mUi.stringSearchLineEdit->setText(QString("Found after %1 letters").arg(globalIndex));
            watcher->deleteLater();
        });

    QFuture<std::tuple<QString, int, std::size_t>> future =
        QtConcurrent::run([=, this]() { return mGenerator.searchString(searchString); });

    watcher->setFuture(future);
}
