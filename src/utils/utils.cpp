#include "./utils.hpp"
#include <iomanip>
#include <sstream>
#include <QApplication>
#include <QDesktopServices>
#include <QNetworkInterface>
#include <QClipboard>
#include <QUrl>
#include <QDir>
#include <QFileInfo>
#include "appConfig.hpp"

Utils::Utils(QObject *parent)
    : QObject(parent)
{
}

QStringList Utils::getLocalIPv4Addresses()
{
    QStringList addresses;
    for (auto &&interface : QNetworkInterface::allInterfaces())
    {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            for (auto &&address : interface.addressEntries())
            {
                if (address.ip().protocol() == QAbstractSocket::IPv4Protocol)
                {
                    addresses.append(address.ip().toString());
                }
            }
        }
    }
    return addresses;
}

bool Utils::isLocalAddress(const QString &address)
{
    QStringList addresses = getLocalIPv4Addresses();
    for (auto &&localAddress : addresses)
    {
        if (localAddress == address)
        {
            return true;
        }
    }
    return false;
}

bool Utils::isIPv4Address(const QString &address)
{
    QHostAddress hostAddress(address);
    return hostAddress.protocol() == QAbstractSocket::IPv4Protocol;
}

constexpr const double KB = 1024.0;
constexpr const double MB = KB * 1024.0;
constexpr const double GB = MB * 1024.0;

QString Utils::getReadableSize(long long int size)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1);
    if (size < KB)
    {
        ss << size << "B";
    }
    else if (size < MB)
    {
        ss << size / KB << "KB";
    }
    else if (size < GB)
    {
        ss << size / MB << "MB";
    }
    else
    {
        ss << size / GB << "GB";
    }
    return QString::fromStdString(ss.str());
}

void Utils::copyToClipboard(const QString &text)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void Utils::openMyGithubPage()
{
    QDesktopServices::openUrl(QUrl(ORGANIZATION_DOMAIN));
}

void Utils::openThisProjectPage()
{
    QDesktopServices::openUrl(QUrl(PROJECT_DOMAIN));
}

void Utils::openThisProjectIssuesPage()
{
    QDesktopServices::openUrl(QUrl(PROJECT_ISSUES_DOMAIN));
}

void Utils::openFileDirectory(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if (fileInfo.exists())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absolutePath()));
    }
}

std::tuple<QString, QString> Utils::getExclusiveFilePath(const QString &dirPath, const QString &fileName)
{
    const QDir dir(dirPath);
    const QString filePath = dir.filePath(fileName);
    const QFileInfo fileInfo(filePath);

    if (fileInfo.exists())
    {
        int index = 1;
        while (true)
        {
            QString newFileName;
            if (fileInfo.suffix().isEmpty())
            {
                newFileName = fileInfo.baseName() + "(" + QString::number(index) + ")";
            }
            else
            {
                newFileName = fileInfo.baseName() + "(" + QString::number(index) + ")." + fileInfo.suffix();
            }

            const QString newFilePath = dir.filePath(newFileName);
            const QFileInfo newFileInfo(newFilePath);
            if (!newFileInfo.exists())
            {
                return {newFileName, newFilePath};
            }
            index++;
        }
    }
    return {fileName, filePath};
}
