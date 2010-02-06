/*
    Copyright (C) 2009 Andres Cabrera
    mantaraya36@gmail.com

    This file is part of QuteCsound.

    QuteCsound is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    QuteCsound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/

#include "inspector.h"

#include <QtCore>

Inspector::Inspector(QWidget *parent)
  : QDockWidget(parent)
{
  setWindowTitle(tr("Inspector"));
  m_treeWidget = new QTreeWidget(this);
  m_treeWidget->setHeaderLabel(tr("Inspector"));
  m_treeWidget->show();
  setWidget(m_treeWidget);
  connect(m_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
          this, SLOT(itemActivated(QTreeWidgetItem*,int)));
//  connect(m_treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
//          this, SLOT(itemActivated(QTreeWidgetItem*,int)));
}


Inspector::~Inspector()
{
  delete m_treeWidget;
}

void Inspector::parseText(const QString &text)
{
//  qDebug() << "Inspector:parseText";
  m_treeWidget->clear();
  TreeItem *opcodeItem = new TreeItem(m_treeWidget, QStringList(tr("Opcodes")));
  opcodeItem->setLine(-1);
  TreeItem *instrItem = new TreeItem(m_treeWidget, QStringList(tr("Instruments")));
  instrItem->setLine(-1);
  TreeItem *ftableItem = new TreeItem(m_treeWidget, QStringList(tr("F-tables")));
  ftableItem->setLine(-1);
  TreeItem *scoreItem = new TreeItem(m_treeWidget, QStringList(tr("Score")));
  scoreItem->setLine(-1);
  TreeItem *currentInstrument = 0;
  QStringList lines = text.split(QRegExp("[\n\r]"));
  for (int i = 0; i< lines.size(); i++) {
    if (lines[i].trimmed().startsWith("instr")) {
      QString text = lines[i].mid(lines[i].indexOf("instr") + 6);
      QStringList columnslist(QString("instr %1").arg(text).simplified());
      TreeItem *newItem = new TreeItem(instrItem, columnslist);
      newItem->setLine(i + 1);
      currentInstrument = newItem;
    }
    else if (lines[i].trimmed().startsWith("opcode")) {
      QString text = lines[i].trimmed();
      QStringList columnslist(text.simplified());
      TreeItem *newItem = new TreeItem(opcodeItem, columnslist);
      newItem->setLine(i + 1);
    }
    else if (lines[i].trimmed().contains(QRegExp("^f\\s*\\d")) ||
        lines[i].trimmed().contains(QRegExp("^[\\w]*[\\s]*ftgen"))) {
      QString text = lines[i].trimmed();
      QStringList columnslist(text.simplified());
      TreeItem *newItem = new TreeItem(ftableItem, columnslist);
      newItem->setLine(i + 1);
    }
    else if (lines[i].trimmed().contains(QRegExp("^s\\s*\\b")) ||
        lines[i].trimmed().contains(QRegExp("^m\\s*\\b"))) {
      QString text = lines[i].trimmed();
      QStringList columnslist(text.simplified());
      TreeItem *newItem = new TreeItem(scoreItem, columnslist);
      newItem->setLine(i + 1);
    }
    else if (lines[i].trimmed().contains(QRegExp("\\w+:"))) {
      QString text = lines[i].trimmed();
      QStringList columnslist(text.simplified());
      if (currentInstrument != 0) {
        TreeItem *newItem = new TreeItem(currentInstrument, columnslist);
        newItem->setLine(i + 1);
      }
    }
  }
  m_treeWidget->expandItem(opcodeItem);
  m_treeWidget->expandItem(instrItem);
  m_treeWidget->expandItem(ftableItem);
  m_treeWidget->expandItem(scoreItem);
}

void Inspector::focusInEvent (QFocusEvent * event)
{
  QWidget::focusInEvent(event);
//  parseText();
}

void Inspector::closeEvent(QCloseEvent * /*event*/)
{
  emit Close(false);
}

void Inspector::itemActivated(QTreeWidgetItem * item, int column)
{
  int line = static_cast<TreeItem *>(item)->getLine();
  if (line >= 0) {
    emit jumpToLine(line);
  }
}
