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


#ifndef SESSIONSTACK_H
#define SESSIONSTACK_H


#include "session.h"


#include <QHash>
#include <QStackedWidget>


class Session;

class SessionStack : public QStackedWidget
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.konsplit")

    public:
        explicit SessionStack(QWidget* parent, QWidget* window);
        ~SessionStack();

    public slots:
        Q_SCRIPTABLE int addSession(Session::SessionType type = Session::Single);
        Q_SCRIPTABLE int addSessionTwoHorizontal();
        Q_SCRIPTABLE int addSessionTwoVertical();
        Q_SCRIPTABLE int addSessionQuad();

        Q_SCRIPTABLE void raiseSession(int sessionId);
        Q_SCRIPTABLE void shutdown();
        Q_SCRIPTABLE void removeSession(int sessionId);
        Q_SCRIPTABLE void removeTerminal(int terminalId);

        Q_SCRIPTABLE int splitSessionLeftRight(int sessionId);
        Q_SCRIPTABLE int splitSessionTopBottom(int sessionId);
        Q_SCRIPTABLE int splitTerminalLeftRight(int terminalId);
        Q_SCRIPTABLE int splitTerminalTopBottom(int terminalId);

        Q_SCRIPTABLE int tryGrowTerminalRight(int terminalId, uint pixels = 10);
        Q_SCRIPTABLE int tryGrowTerminalLeft(int terminalId, uint pixels = 10);
        Q_SCRIPTABLE int tryGrowTerminalTop(int terminalId, uint pixels = 10);
        Q_SCRIPTABLE int tryGrowTerminalBottom(int terminalId, uint pixels = 10);

        Q_SCRIPTABLE int activeSessionId() { return m_activeSessionId; }
        Q_SCRIPTABLE int activeTerminalId();

        Q_SCRIPTABLE int sessionIdForTerminalId(int terminalId);

        Q_SCRIPTABLE void runCommand(const QString& command);
        Q_SCRIPTABLE void runCommandInTerminal(int terminalId, const QString& command);


    signals:
        void sessionAdded(int sessionId, const QString& title = 0);
        void sessionRaised(int sessionId);
        void sessionRemoved(int sessionId);

        void activeTitleChanged(const QString& title);
        void titleChanged(int sessionId, const QString& title);

        void closeTerminal();

        void previousTerminal();
        void nextTerminal();

        void manageProfiles();

        void removeTerminalHighlight();


    private slots:
        void handleManualTerminalActivation(Terminal*);

        void cleanup(int sessionId);


    private:
        int m_activeSessionId;
        QWidget *m_window;
        QHash<int, Session*> m_sessions;
};

#endif
