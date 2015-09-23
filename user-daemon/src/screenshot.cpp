#include <stdio.h>
#include <QVariantHash>

#include "screenshot.h"

ScreenShot::ScreenShot(QObject *parent) :
    QObject(parent)
{
}

void ScreenShot::takeScreenShot()
{
    QString ssFilename = QString("%1/ss%2.png")
                            .arg(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation))
                            .arg(QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss-zzz"));

    QDBusMessage m = QDBusMessage::createMethodCall("org.nemomobile.lipstick",
                                                    "/org/nemomobile/lipstick/screenshot",
                                                    "",
                                                    "saveScreenshot" );

    QList<QVariant> args;
    args.append(ssFilename);
    m.setArguments(args);

    if (QDBusConnection::sessionBus().send(m))
        printf("tohkbd2-user: Screenshot success to %s\n", qPrintable(ssFilename));
    else
        printf("tohkbd2-user: Screenshot failed\n");

    notif.setAppName("TOHKBD");
    //: Notification shown after screenshot is taken
    //% "Screenshot saved"
    notif.setSummary(qtTrId("screenshot-saved"));
    notif.setPreviewSummary(qtTrId("screenshot-saved"));
    notif.setBody(ssFilename.split("/").last());
    notif.setPreviewBody(ssFilename.split("/").last());
    notif.setCategory("x-harbour.tohkbd2.screenshot");
    notif.setReplacesId(0);

    args.clear();
    args.append((QStringList() << ssFilename));

    notif.setRemoteAction(Notification::remoteAction("default",
                                                     QString(),
                                                     "com.jolla.gallery",
                                                     "/com/jolla/gallery/ui",
                                                     "com.jolla.gallery.ui",
                                                     "showImages",
                                                     args));

    notif.publish();

    printf("tohkbd2-user: Notification sent\n");
}


