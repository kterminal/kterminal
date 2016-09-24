/*
  Copyright (C) 2008-2009 by Eike Hein <hein@kde.org>
  Copyright (C) 2009 by Juan Carlos Torres <carlosdgtorres@gmail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of
  the License or (at your option) version 3 or any later version
  accepted by the membership of KDE e.V. (or its successor appro-
  ved by the membership of KDE e.V.), which shall act as a proxy
  defined in Section 14 of version 3 of the license.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see http://www.gnu.org/licenses/.
*/


#include "sessionstack.h"
//#include "settings.h"

#include <KMessageBox>
#include <KLocalizedString>

#include <QtDBus/QtDBus>


SessionStack::SessionStack(QWidget* parent, QWidget *window) : QTabWidget(parent)
{
    m_window = window;
    QDBusConnection::sessionBus().registerObject("/kterminal/sessions", this, QDBusConnection::ExportScriptableSlots);
    setTabPosition(QTabWidget::South);
    m_activeSessionId = -1;
}

SessionStack::~SessionStack() {
}

void SessionStack::horizontal_split_current_terminal() {
  Splitter *current_spliter = (Splitter*)currentWidget();
  std::cout << "Split current terminal horizontally (TopBottom)" << std::endl;
  current_spliter->session()->splitTopBottom();
}

void SessionStack::vertical_split_current_terminal() {
  Splitter *current_spliter = (Splitter*)currentWidget();
  std::cout << "Split current terminal vertically (LeftRight)" << std::endl;
  current_spliter->session()->splitLeftRight();
}

void SessionStack::auto_select_last_session() {
  Session *session = m_sessions.values().last();
  raiseSession(session->id());
}

int SessionStack::addSession(Session::SessionType type)
{
    Session* session = new Session(type, this);
    connect(session, SIGNAL(titleChanged(int,QString)), this, SIGNAL(titleChanged(int,QString)));
    connect(session, SIGNAL(terminalManuallyActivated(Terminal*)), this, SLOT(handleManualTerminalActivation(Terminal*)));
    connect(session, SIGNAL(activityDetected(Terminal*)), m_window, SLOT(handleTerminalActivity(Terminal*)));
    connect(session, SIGNAL(silenceDetected(Terminal*)), m_window, SLOT(handleTerminalSilence(Terminal*)));
    connect(session, SIGNAL(destroyed(int)), this, SLOT(cleanup(int)));

    m_sessions.insert(session->id(), session);

    QString tab_label = QString("Shell (") + QString::number(session->id(), 16) + ")";
    addTab(session->widget(), tab_label);

    emit sessionAdded(session->id());

    raiseSession(session->id());

    return session->id();
}

int SessionStack::addSessionTwoHorizontal()
{
    return addSession(Session::TwoHorizontal);
}

int SessionStack::addSessionTwoVertical()
{
    return addSession(Session::TwoVertical);
}

int SessionStack::addSessionQuad()
{
    return addSession(Session::Quad);
}

void SessionStack::raiseSession(int sessionId)
{
    if (sessionId == -1 || !m_sessions.contains(sessionId)) return;
    Session* session = m_sessions.value(sessionId);

    if (m_activeSessionId != -1 && m_sessions.contains(m_activeSessionId))
    {
        Session* oldActiveSession = m_sessions.value(m_activeSessionId);

        disconnect(oldActiveSession, SLOT(closeTerminal()));
        disconnect(oldActiveSession, SLOT(focusPreviousTerminal()));
        disconnect(oldActiveSession, SLOT(focusNextTerminal()));
        disconnect(oldActiveSession, SLOT(manageProfiles()));
        disconnect(oldActiveSession, SIGNAL(titleChanged(QString)),
            this, SIGNAL(activeTitleChanged(QString)));

        oldActiveSession->reconnectMonitorActivitySignals();
    }

    m_activeSessionId = sessionId;

    setCurrentWidget(session->widget());

    if (session->widget()->focusWidget())
        session->widget()->focusWidget()->setFocus();

    session->focusNextTerminal();

    connect(this, SIGNAL(closeTerminal()), session, SLOT(closeTerminal()));
    connect(this, SIGNAL(previousTerminal()), session, SLOT(focusPreviousTerminal()));
    connect(this, SIGNAL(nextTerminal()), session, SLOT(focusNextTerminal()));
    connect(this, SIGNAL(manageProfiles()), session, SLOT(manageProfiles()));
    connect(session, SIGNAL(titleChanged(QString)), this, SIGNAL(activeTitleChanged(QString)));

    emit sessionRaised(sessionId);

    emit activeTitleChanged(session->title());
}

void SessionStack::removeSession(int sessionId)
{
    if (sessionId == -1) sessionId = m_activeSessionId;
    if (sessionId == -1) return;
    if (!m_sessions.contains(sessionId)) return;

    m_sessions.value(sessionId)->deleteLater();
}

void SessionStack::removeTerminal(int terminalId)
{
    int sessionId = sessionIdForTerminalId(terminalId);

    if (terminalId == -1)
    {
        if (m_activeSessionId == -1) return;
        if (!m_sessions.contains(m_activeSessionId)) return;

        if (m_sessions.value(m_activeSessionId)->closable())
            m_sessions.value(m_activeSessionId)->closeTerminal();
    }
    else
    {
        if (m_sessions.value(sessionId)->closable())
            m_sessions.value(sessionId)->closeTerminal(terminalId);
    }
}

void SessionStack::cleanup(int sessionId)
{
    if (sessionId == m_activeSessionId) m_activeSessionId = -1;

    m_sessions.remove(sessionId);

    emit sessionRemoved(sessionId);
    if (m_sessions.empty()) {
      qApp->exit();
    } else {
      auto_select_last_session();
    }
}

int SessionStack::activeTerminalId()
{
    if (!m_sessions.contains(m_activeSessionId)) return -1;

    return m_sessions.value(m_activeSessionId)->activeTerminalId();
}

int SessionStack::sessionIdForTerminalId(int terminalId)
{
    int sessionId = -1;

    QHashIterator<int, Session*> it(m_sessions);

    while (it.hasNext())
    {
        it.next();

        if (it.value()->hasTerminal(terminalId))
        {
            sessionId = it.key();

            break;
        }
    }

    return sessionId;
}

void SessionStack::runCommand(const QString& command)
{
    if (m_activeSessionId == -1) return;
    if (!m_sessions.contains(m_activeSessionId)) return;

    m_sessions.value(m_activeSessionId)->runCommand(command);
}

void SessionStack::runCommandInTerminal(int terminalId, const QString& command)
{
    QHashIterator<int, Session*> it(m_sessions);

    while (it.hasNext())
    {
        it.next();

        it.value()->runCommand(command, terminalId);
    }
}

int SessionStack::splitSessionLeftRight(int sessionId)
{
    if (sessionId == -1) return -1;
    if (!m_sessions.contains(sessionId)) return -1;

    return m_sessions.value(sessionId)->splitLeftRight();
}

int SessionStack::splitSessionTopBottom(int sessionId)
{
    if (sessionId == -1) return -1;
    if (!m_sessions.contains(sessionId)) return -1;

    return m_sessions.value(sessionId)->splitTopBottom();
}

int SessionStack::splitTerminalLeftRight(int terminalId)
{
    int sessionId = sessionIdForTerminalId(terminalId);

    if (sessionId == -1) return -1;

    return m_sessions.value(sessionId)->splitLeftRight(terminalId);
}

int SessionStack::splitTerminalTopBottom(int terminalId)
{
    int sessionId = sessionIdForTerminalId(terminalId);

    if (sessionId == -1) return -1;

    return m_sessions.value(sessionId)->splitTopBottom(terminalId);
}

int SessionStack::tryGrowTerminalRight(int terminalId, uint pixels)
{
    int sessionId = sessionIdForTerminalId(terminalId);

    if (sessionId == -1) return -1;

    return m_sessions.value(sessionId)->tryGrowTerminal(terminalId, Session::Right, pixels);
}

int SessionStack::tryGrowTerminalLeft(int terminalId, uint pixels)
{
    int sessionId = sessionIdForTerminalId(terminalId);

    if (sessionId == -1) return -1;

    return m_sessions.value(sessionId)->tryGrowTerminal(terminalId, Session::Left, pixels);
}

int SessionStack::tryGrowTerminalTop(int terminalId, uint pixels)
{
    int sessionId = sessionIdForTerminalId(terminalId);

    if (sessionId == -1) return -1;

    return m_sessions.value(sessionId)->tryGrowTerminal(terminalId, Session::Up, pixels);
}

int SessionStack::tryGrowTerminalBottom(int terminalId, uint pixels)
{
    int sessionId = sessionIdForTerminalId(terminalId);

    if (sessionId == -1) return -1;

    return m_sessions.value(sessionId)->tryGrowTerminal(terminalId, Session::Down, pixels);
}

void SessionStack::handleManualTerminalActivation(Terminal* terminal)
{
    //if (!Settings::terminalHighlightOnManualActivation())
    //    return;

    Session* session = qobject_cast<Session*>(QObject::sender());

    ///if (session->terminalCount() > 1)
    ///    m_visualEventOverlay->highlightTerminal(terminal, false);
}

///bool SessionStack::queryClose(int sessionId, QueryCloseType type)
///{
///    if (!m_sessions.contains(sessionId)) return false;
///
///    if (!m_sessions.value(sessionId)->closable())
///    {
///        QString closeQuestionIntro = i18nc("@info", "<warning>You have locked this session to prevent accidental closing of terminals.</warning>");
///        QString closeQuestion;
///
///        if (type == QueryCloseSession)
///            closeQuestion = i18nc("@info", "Are you sure you want to close this session?");
///        else if (type == QueryCloseTerminal)
///            closeQuestion = i18nc("@info", "Are you sure you want to close this terminal?");
///
///        int result = KMessageBox::warningContinueCancel(this,
///            closeQuestionIntro + "<br/><br/>" + closeQuestion,
///            i18nc("@title:window", "Really Close?"), KStandardGuiItem::close(), KStandardGuiItem::cancel());
///
///        if (result != KMessageBox::Continue)
///            return false;
///    }
///
///    return true;
///}
