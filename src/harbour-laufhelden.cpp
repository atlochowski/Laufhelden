/*
 * Copyright (C) 2017 Jens Drescher, Germany
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QtQml>
#include <QGuiApplication>
#include <QQuickView>
#include <sailfishapp.h>
#include "trackrecorder.h"
#include "historymodel.h"
#include "trackloader.h"
#include "settings.h"
#include "bluetoothconnection.h"
#include "bluetoothdata.h"
#include "logwriter.h"
#include "plotwidget.h"
#include "light.h"
#include "pebblemanagercomm.h"
#include "pebblewatchcomm.h"
#include "timeformatter.h"
#include "o2/src/o2.h"

QByteArray encryptDecrypt(QByteArray toEncrypt) {
    char key = 'K';
    QByteArray output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt.at(i) ^key;

    return output;
}

int main(int argc, char *argv[]) {
    QGuiApplication *app = SailfishApp::application(argc, argv);

    app->setApplicationName("Laufhelden");
    app->setApplicationVersion(QString(APP_VERSION));

    qDebug()<<app->applicationName()<<" version "<<app->applicationVersion();

    qmlRegisterType<TrackRecorder>("harbour.laufhelden", 1, 0, "TrackRecorder");
    qmlRegisterType<HistoryModel>("harbour.laufhelden", 1, 0, "HistoryModel");
    qmlRegisterType<TrackLoader>("harbour.laufhelden", 1, 0, "TrackLoader");
    qmlRegisterType<Settings>("harbour.laufhelden", 1, 0, "Settings");
    qmlRegisterType<BluetoothConnection,1>("harbour.laufhelden", 1, 0, "BluetoothConnection");
    qmlRegisterType<BluetoothData,1>("harbour.laufhelden", 1, 0, "BluetoothData");
    qmlRegisterType<LogWriter,1>("harbour.laufhelden", 1, 0, "LogWriter");
    qmlRegisterType<PlotWidget,1>("harbour.laufhelden", 1, 0, "PlotWidget");
    qmlRegisterType<Light,1>("harbour.laufhelden", 1, 0, "Light");
    qmlRegisterType<TimeFormatter,1>("harbour.laufhelden", 1, 0, "TimeFormatter");
    qmlRegisterType<PebbleManagerComm,1>("harbour.laufhelden", 1, 0, "PebbleManagerComm");
    qmlRegisterType<PebbleWatchComm,1>("harbour.laufhelden", 1, 0, "PebbleWatchComm");
    qmlRegisterType<O2>("com.pipacs.o2", 1, 0, "O2");

    QQuickView *view = SailfishApp::createView();
    view->rootContext()->setContextProperty("appVersion", app->applicationVersion());
    view->rootContext()->setContextProperty("STRAVA_CLIENT_SECRET", encryptDecrypt("}{s{--z*.x{y{ss///x/x){*xz{(|yy/{syr-/})"));
    view->rootContext()->setContextProperty("STRAVA_CLIENT_ID", "13707");

    view->setSource(SailfishApp::pathTo("qml/harbour-laufhelden.qml"));
    view->showFullScreen();

    return app->exec();
}

