#pragma once

#include <QDirIterator>
#include <QString>
#include <QDebug>

namespace utility
{
    static void printResources()
    {
        QDirIterator it(":/", QDirIterator::Subdirectories);

        while (it.hasNext())
        {
            QString resourceFile = it.next();
            qDebug() << "Resource File:" << resourceFile;
        }
    }
}