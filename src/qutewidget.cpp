/***************************************************************************
 *   Copyright (C) 2008 by Andres Cabrera                                  *
 *   mantaraya36@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/
#include "qutewidget.h"

#include <QSlider>

QuteWidget::QuteWidget(QWidget *parent, widgetType type):
    QWidget(parent), m_type(type)
{
  this->setGeometry(QRect(5, 5, 20, 200));
  m_widget = new QSlider(this);

  propertiesAct = new QAction(/*QIcon(":/images/gtk-new.png"),*/ tr("&Properties"), this);
  propertiesAct->setShortcut(tr("Alt+P"));
  propertiesAct->setStatusTip(tr("Open widget properties"));
  connect(propertiesAct, SIGNAL(triggered()), this, SLOT(openProperties()));
}


QuteWidget::~QuteWidget()
{
}

void QuteWidget::setWidgetLine(QString line)
{
  m_line = line;
}

void QuteWidget::setChannelName(QString name)
{
  m_name = name;
  m_widget->setObjectName(name);
//   qDebug("QuteWidget::setChannelName %s", m_name.toStdString().c_str());
}

void QuteWidget::setWidgetGeometry(int x, int y, int w, int h)
{
  setWidgetGeometry(QRect(x,y,w,h));
}

void QuteWidget::setWidgetGeometry(QRect rect)
{
  this->setGeometry(rect);
  m_widget->setMinimumSize(rect.width(), rect.height());
}

void QuteWidget::setRange(int min, int max)
{
  qDebug("QuteWidget::setRange not implemented for widget type");
}

void QuteWidget::setValue(double value)
{
  qDebug("QuteWidget::setValue not implemented for widget type");
}

void QuteWidget::setResolution(double resolution)
{
  switch (m_type) {
//     case QUTE_SLIDER:
//       ((QSlider *)m_widget)->setValue(min,max);
//       break;
    default:
      qDebug("QuteWidget::setResolution not implemented for widget type");
  }
}

void QuteWidget::setChecked(bool checked)
{
  switch (m_type) {
//     case QUTE_SLIDER:
//       break;
    default:
      qDebug("QuteWidget::setChecked not implemented for widget type");
  }
}

void QuteWidget::setText(QString text)
{
  switch (m_type) {
//     case QUTE_SLIDER:
//       break;
    default:
      qDebug("QuteWidget::setText not implemented for widget type");
  }
}

QString QuteWidget::getChannelName()
{
  return m_name;
}

QString QuteWidget::getWidgetLine()
{
  return m_line;
}

double QuteWidget::getValue()
{
  switch (m_type) {
//     case QUTE_SLIDER:
// 
//       break;
    default:
      qDebug("QuteWidget::getValue not implemented for widget type");
      return 0.0;
  }
}

void QuteWidget::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu menu(this);
  menu.addAction(propertiesAct);
//   menu.addAction(copyAct);
//   menu.addAction(pasteAct);
  menu.exec(event->globalPos());
//   qDebug("menu");
}

void QuteWidget::openProperties()
{
  QDialog dialog(this);
  dialog.resize(300, 300);
  dialog.setModal(true);
  QGridLayout *layout = new QGridLayout(&dialog);
  QLabel *label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("X =");
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 0, 0, Qt::AlignCenter);
  QSpinBox *spinBox = new QSpinBox(&dialog);
  spinBox->setValue(this->x());
  layout->addWidget(spinBox, 0, 1, Qt::AlignCenter);
  label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("Y =");
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 0, 2, Qt::AlignCenter);
  spinBox = new QSpinBox(&dialog);
  spinBox->setValue(this->y());
  layout->addWidget(spinBox, 0, 3, Qt::AlignCenter);
  label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("Width =");
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 1, 0, Qt::AlignCenter);
  spinBox = new QSpinBox(&dialog);
  spinBox->setValue(this->width());
  layout->addWidget(spinBox, 1, 1, Qt::AlignCenter);
  label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("Height =");
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 1, 2, Qt::AlignCenter);
  spinBox = new QSpinBox(&dialog);
  spinBox->setValue(this->height());
  layout->addWidget(spinBox, 1, 3, Qt::AlignCenter);
  label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("Min =");
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 2, 0, Qt::AlignCenter);
  label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText(QString::number(m_min,'f', 6));
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 2,1, Qt::AlignCenter);
  label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("Max =");
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 2, 2, Qt::AlignCenter);
  label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText(QString::number(m_max,'f', 6));
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 2,3, Qt::AlignCenter);
  label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("Channel name =");
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 3, 0, Qt::AlignCenter);
  label = new QLabel(&dialog);
  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText(getChannelName());
  label->setAlignment(Qt::AlignRight);
  layout->addWidget(label, 3, 1, Qt::AlignCenter);
  QPushButton *cancelButton = new QPushButton(tr("Cancel"));
  layout->addWidget(cancelButton, 4, 2, Qt::AlignCenter);
  QPushButton *acceptButton = new QPushButton(tr("Ok"));
  layout->addWidget(acceptButton, 4, 3, Qt::AlignCenter);

  connect(acceptButton, SIGNAL(released()), &dialog, SLOT(accept()));
  connect(&dialog, SIGNAL(accepted()), this, SLOT(applyProperties()));
  connect(cancelButton, SIGNAL(released()), &dialog, SLOT(close()));
  dialog.exec();
}

void QuteWidget::applyProperties()
{
  qDebug("QuteWidget::applyProperties() Not implemented yet.");
}
