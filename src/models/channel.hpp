#pragma once

#include <QObject>
#include <QList>
#include <QUrl>
#include "models/file.hpp"
#include "models/myFile.hpp"

namespace Model
{
    class Channel : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(Type type READ getType WRITE setType CONSTANT)
        Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString address READ getAddress WRITE setAddress NOTIFY addressChanged)
        Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)
        Q_PROPERTY(bool webEnabled READ getWebEnabled WRITE setWebEnabled NOTIFY webEnabledChanged)
        Q_PROPERTY(int wsPort READ getWsPort WRITE setWsPort)
        Q_PROPERTY(int webServerPort READ getWebServerPort WRITE setWebServerPort)

    public:
        enum class Type
        {
            Server,
            Client
        };
        Q_ENUM(Type)

    public:
        explicit Channel(QObject *parent = nullptr);
        ~Channel() = default;

        Type getType() const;
        void setType(Type type);
        const QString &getName() const;
        void setName(const QString &name);
        const QString &getAddress() const;
        void setAddress(const QString &address);
        int getPort() const;
        void setPort(int port);
        bool getWebEnabled() const;
        void setWebEnabled(bool enabled);
        int getWsPort() const;
        void setWsPort(int port);
        int getWebServerPort() const;
        void setWebServerPort(int port);

    signals:
        void nameChanged(const QString &name);
        void addressChanged(const QString &address);
        void portChanged(int port);
        void webEnabledChanged(bool enabled);

    private:
        Type channelType;
        QString channelName;
        QString channelAddress;
        int channelPort;
        bool webEnabled;
        int wsPort;
        int webServerPort;
    };

    inline Channel::Type Channel::getType() const
    {
        return channelType;
    }

    inline const QString &Channel::getName() const
    {
        return channelName;
    }

    inline const QString &Channel::getAddress() const
    {
        return channelAddress;
    }

    inline int Channel::getPort() const
    {
        return channelPort;
    }

    inline bool Channel::getWebEnabled() const
    {
        return webEnabled;
    }

    inline int Channel::getWsPort() const
    {
        return wsPort;
    }

    inline int Channel::getWebServerPort() const
    {
        return webServerPort;
    }
} // namespace Model
