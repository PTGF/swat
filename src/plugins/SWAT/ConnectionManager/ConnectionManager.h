/*!
   \file
   \author Dane Gardner <dane.gardner@gmail.com>
   \version

   \section LICENSE
   This file is part of the Parallel Tools GUI Framework (PTGF)
   Copyright (C) 2010-2011 Argo Navis Technologies, LLC

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by the
   Free Software Foundation; either version 2.1 of the License, or (at your
   option) any later version.

   This library is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
   for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this library; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

   \section DESCRIPTION

 */

#ifndef PLUGINS_SWAT_CONNECTIONMANAGER_H
#define PLUGINS_SWAT_CONNECTIONMANAGER_H

#include <QtCore>

#include "ConnectionManagerLibrary.h"

namespace Plugins {
namespace SWAT {

class IAdapter;

class CONNECTIONMANAGER_EXPORT ConnectionManager : public QObject
{
    Q_OBJECT
public:
    static ConnectionManager &instance();
    bool initialize(QStringList &args, QString *err);
    void shutdown();

    static IAdapter *currentAdapter();

signals:
    void CurrentAdapterChanged(IAdapter *from, IAdapter *to);

public slots:

protected:
    explicit ConnectionManager(QObject *parent = 0);
    ~ConnectionManager();
    void readSettings();
    void writeSettings();

protected slots:
    void pluginObjectRegistered(QObject *);


private:
    IAdapter *m_CurrentAdapter;

};

} // namespace SWAT
} // namespace Plugins

#endif // PLUGINS_SWAT_CONNECTIONMANAGER_H
