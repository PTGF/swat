/*!
   \file
   \author Dane Gardner <dane.gardner@gmail.com>
   \version

   \section LICENSE
   This file is part of the StackWalker Analysis Tool (SWAT)
   Copyright (C) 2012-2012 Argo Navis Technologies, LLC
   Copyright (C) 2012-2012 University of Wisconsin

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

#ifndef PLUGINS_SWAT_WELCOMEDATA_H
#define PLUGINS_SWAT_WELCOMEDATA_H

#include <QtCore>
#include <QtXml>

#include <Welcome/IWelcomeData.h>

using namespace Plugins::Welcome;

namespace Plugins {
namespace SWAT {

class WelcomeData : public QObject, public IWelcomeData
{
    Q_OBJECT
    Q_INTERFACES(Plugins::Welcome::IWelcomeData)

public:
    WelcomeData(QObject *parent = 0);

    /* BEGIN IWelcomeData */
    bool initialize();
    QList<Link> actions();
    QList<Link> recent();
    QList<Link> tutorials();
    QList<Link> examples();
    QList<Link> support();
    QStringList tipsAndTricks();
    QList<QUrl> latestNewsRss();
    QList<QWidget *> additionalTabs();
    /* END IWelcomeData */

protected:
    QList<Link> createUrlLinks(const QString &elementName);
    Link createUrlLink(const QDomElement &link);

private:
    QDomDocument m_WelcomeData;

};

} // namespace SWAT
} // namespace Plugins

#endif // PLUGINS_SWAT_WELCOMEDATA_H
