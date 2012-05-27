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

#include "DirectedGraphView.h"
#include "ui_DirectedGraphView.h"

#include <QGraphVizView.h>

#include "DirectedGraphScene.h"
#include "DirectedGraphNode.h"
#include "DirectedGraphNodeDialog.h"

namespace Plugins {
namespace DirectedGraphView {

DirectedGraphView::DirectedGraphView(const QByteArray &content, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirectedGraphView),
    m_Scene(NULL),
    m_View(NULL)
{
    ui->setupUi(this);

    m_Scene = new DirectedGraphScene(QString(content));
    m_View = new QGraphVizView(m_Scene, this);
    m_Scene->setParent(m_View);

    setWindowTitle(tr("Directed Graph View"));

    ui->verticalLayout->insertWidget(0, m_View);

    connect(m_Scene, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));
}

DirectedGraphView::~DirectedGraphView()
{
    delete ui;
}

QGraphVizView *DirectedGraphView::view()
{
    return m_View;
}

void DirectedGraphView::on_txtFilter_textChanged(const QString &filter)
{
    QRegExp rx = QRegExp(filter, Qt::CaseInsensitive, QRegExp::RegExp2);
    foreach(QGraphVizNode *gvNode, m_Scene->getNodes()) {
        if(DirectedGraphNode *node = dynamic_cast<DirectedGraphNode *>(gvNode)) {
            if(rx.indexIn(node->label()) >= 0) {
                node->setSelected(true);
            } else {
                node->setSelected(false);
            }
        }
    }
}

void DirectedGraphView::selectionChanged()
{
    if(m_Scene->selectedItems().count() == 1) {
        if(DirectedGraphNode *node = dynamic_cast<DirectedGraphNode *>(m_Scene->selectedItems().at(0))) {
            DirectedGraphNodeDialog *dlg = new DirectedGraphNodeDialog(this);
            dlg->setNode(node);
            dlg->exec();
        }
    }
}


} // namespace DirectedGraphView
} // namespace Plugins
