/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "glwidget.h"
#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    currentGlWidget = new GLWidget;
    connect(currentGlWidget, &GLWidget::clicked,
                        this, &Window::setCurrentGlWidget);

    mainLayout->setRowStretch(0, 0);
    mainLayout->setRowStretch(1, 1);
    mainLayout->setSpacing(0);
    m_label = new QLabel();
    m_label->setMinimumHeight(28);
    mainLayout->addWidget(m_label, 0, 0);
    mainLayout->addWidget(currentGlWidget, 1, 0);
    setLayout(mainLayout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Window::rotateOneStep);
    timer->start(2);

    setWindowTitle(tr("Textures"));
    m_isCklicked = false;
}

void Window::mousePressEvent(QMouseEvent *event)
{
    QString text = m_label->text();
    emit sig_clicked(text);
  //  m_isCklicked = !m_isCklicked;
//    QString style;
//    if(m_isCklicked)
//    {
//        style = "border-radius: 1px;border:1px solid black;background:#ffc6ff; color: rgb(18, 18, 18);font-size: 25px;";
//    }
//    else
//    {
//        style = "border-radius: 1px;border:1px solid black;background:#ffffff; color: rgb(18, 18, 18);font-size: 25px;";
//    }
    //    this->setStyleSheet(style);
}

void Window::setInfo(const QString &info)
{
    m_label->setText(info);
}

QString Window::getInfo() const
{
    return m_label->text();
}

void Window::setStyleColor(const QString &styleSheet, bool value)
{
    this->setStyleSheet(styleSheet);
    if(value)
    {
        currentGlWidget->setClearColor(Qt::red);
    }
    else
    {
        currentGlWidget->setClearColor(Qt::black);
    }

}

void Window::setCurrentGlWidget()
{
    currentGlWidget = qobject_cast<GLWidget *>(sender());
    QString text = m_label->text();
    emit sig_clicked(text);
    qDebug()<<"Window emit sig_clicked";
}

void Window::rotateOneStep()
{
    if (currentGlWidget)
        currentGlWidget->rotateBy(+2 * 16, +2 * 16, -1 * 16);
}
