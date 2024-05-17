#include "./myFile.hpp"

namespace Model
{
    MyFile::MyFile(const QString &name, long long int size, const QString &path, QObject *parent)
        : File(path, name, size, parent), path{path}
    {
    }
} // namespace Model
