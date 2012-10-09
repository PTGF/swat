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

#include "STATScene.h"
#include "STATNode.h"

#include <QDebug>

namespace Plugins {
namespace DirectedGraph {

STATNode::STATNode(node_t *node, STATScene *scene, QGraphicsItem *parent) :
    DirectedGraphNode(node, scene, parent),
    m_Scene(scene)
{
}

QString STATNode::functionName()
{
    return m_Scene->nodeInfo(nodeId(), STATScene::NodeInfoType_FunctionName).toString();
}

quint64 STATNode::programCounter()
{
    return m_Scene->nodeInfo(nodeId(), STATScene::NodeInfoType_ProgramCounter).toULongLong();
}

QString STATNode::sourceFile()
{
    return m_Scene->nodeInfo(nodeId(), STATScene::NodeInfoType_SourceFile).toString();
}

quint32 STATNode::sourceLine()
{
    return m_Scene->nodeInfo(nodeId(), STATScene::NodeInfoType_SourceLine).toUInt();
}

QString STATNode::iter()
{
    return m_Scene->nodeInfo(nodeId(), STATScene::NodeInfoType_IterString).toString();
}

QString STATNode::processCount()
{
    return m_Scene->edgeInfo(nodeId(), STATScene::EdgeInfoType_ProcessCount).toString();
}

QStringList STATNode::processList()
{
    return m_Scene->edgeInfo(nodeId(), STATScene::EdgeInfoType_ProcessList).toStringList();
}

void STATNode::showToolTip(const QPoint &pos, QWidget *w, const QRect &rect)
{
    QStringList toolTips;
    toolTips << QApplication::tr("Function:      %1").arg(this->functionName());

    if(this->processList().count() > 8) {
        toolTips << QApplication::tr("<br />Process Count: %1").arg(this->processCount());
    } else {
        toolTips << QApplication::tr("<br />Process Count: %1").arg(this->processCount());
        toolTips << QApplication::tr("Process List:  %1").arg(this->processList().join(", "));
    }

    if(!sourceFile().isEmpty()) {
        toolTips << QApplication::tr("<br />Source File:   %1").arg(this->sourceFile());
        toolTips << QApplication::tr("Source Line:   %1").arg(this->sourceLine());
    }

    QToolTip::showText(pos, QString("<pre>%1</pre>").arg(toolTips.join("<br />")), w, rect);
}


} // namespace DirectedGraph
} // namespace Plugins
