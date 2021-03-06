//////////////////////////////////////////////////////////////////////
// chatdialog.cpp: implementation of the CChatDialog class.
//
//
// History:
//	2015-02-21  Initial creation MSW
//////////////////////////////////////////////////////////////////////

//==========================================================================================
// + + +   This Software is released under the "Simplified BSD License"  + + +
//Copyright 2010 Moe Wheatley. All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification, are
//permitted provided that the following conditions are met:
//
//   1. Redistributions of source code must retain the above copyright notice, this list of
//	  conditions and the following disclaimer.
//
//   2. Redistributions in binary form must reproduce the above copyright notice, this list
//	  of conditions and the following disclaimer in the documentation and/or other materials
//	  provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY Moe Wheatley ``AS IS'' AND ANY EXPRESS OR IMPLIED
//WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Moe Wheatley OR
//CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//The views and conclusions contained in the software and documentation are those of the
//authors and should not be interpreted as representing official policies, either expressed
//or implied, of Moe Wheatley.
//==========================================================================================
#include "chatdialog.h"
#include <qdebug.h>
#include "ui_chatdialog.h"

CChatDialog* g_pChatDialog = NULL;		//pointer to this class is global so everybody can access


CChatDialog::CChatDialog(QWidget *parent, Qt::WindowFlags f) :
	QDialog(parent,f),
	ui(new Ui::CChatDialog)
{
	ui->setupUi(this);
	m_pSdrInterface = NULL;
	connect(this, SIGNAL(SendChatData(quint8) ), this,  SLOT( GotChatData(quint8) ) );
	connect(this, SIGNAL(SendChatStr(QString) ), this,  SLOT( GotChatStr(QString) ) );
//	ui->plainTextEditRx->setCenterOnScroll(true);
	ui->plainTextEditRx->setReadOnly(true);
	ui->plainTextEditRx->setTextInteractionFlags(Qt::NoTextInteraction);
	setWindowTitle("PSK/FSK Text");
	ui->comboBoxPskMode->addItem("BPSK31");
	ui->comboBoxPskMode->addItem("BPSK63");
}

CChatDialog::~CChatDialog()
{
	delete ui;
}

void CChatDialog::GotChatData(quint8 ch)
{
QChar qch(ch);
QString str(qch);
	if('\b' == ch)
	{	//if backspace then delete previous character
		QTextCursor c = ui->plainTextEditRx->textCursor();
		c.deletePreviousChar();
		ui->plainTextEditRx->setTextCursor(c);
	}
	else
	{
		ui->plainTextEditRx->insertPlainText(str);
	}
	ui->plainTextEditRx->ensureCursorVisible();
}

void CChatDialog::GotChatStr(QString str)
{
	ui->plainTextEditRx->insertPlainText(str+"\n");
	ui->plainTextEditRx->ensureCursorVisible();
}


void CChatDialog::OnPskModeChanged(int index)
{
qDebug()<<"Mode="<<index;
	if(m_pSdrInterface)
		m_pSdrInterface->SetPskMode(index);
}

void CChatDialog::OnClear()
{
	ui->plainTextEditRx->clear();
}


