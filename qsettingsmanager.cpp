#include "qsettingsmanager.h"
#include "stylesheetgenerator.h"

#include <QSettings>
#include <QCoreApplication>

QSettingsManager::QSettingsManager()
    : settings(QString("%1/%2").arg(QCoreApplication::applicationDirPath(),"StopwatchSettings.ini"), QSettings::Format::IniFormat)
    , SettingsForHotkeyGroup{
          "Hotkeys/ToggleOnOff",
          "Hotkeys/Reset",
          "Hotkeys/BringToForeground"}
    , SettingsForStopwatchGroup{
          "Stopwatch/Font",
          "Stopwatch/FontColor",
          "Stopwatch/Background"}

{
    setValue("Application", "Version", "0.3-alpha");
}

void QSettingsManager::setValue(QString groupName, QString valueName, QString value)
{
    settings.setValue(QString("%1/%2").arg(groupName, valueName), value);
}

void QSettingsManager::setValue(SettingsForStopwatchGroupIndex e, QString value)
{
    settings.setValue(QString("%1").arg(SettingsForStopwatchGroup[e]), value);
}

void QSettingsManager::setValue(SettingsForHotkeyGroupIndex e, QString value)
{
    settings.setValue(QString("%1").arg(SettingsForHotkeyGroup[e]), value);
}

const QVariant QSettingsManager::getValue(enum SettingsForHotkeyGroupIndex e)
{
    return settings.value(SettingsForHotkeyGroup[e], false);
}

const QVariant QSettingsManager::getValue(enum SettingsForStopwatchGroupIndex e)
{
    return settings.value(SettingsForStopwatchGroup[e], false);
}

const QVariant QSettingsManager::getValue(QString groupName, QString valueName)
{
    return settings.value(QString("%1/%2").arg(groupName, valueName),false);
}

QString QSettingsManager::FetchStopwatchFontColor()
{
    QVariant val = getValue(FontColor);

    if (val == false) return StylesheetGenerator::DefaultFontHexColor;
    else return val.toString();
}

QString QSettingsManager::FetchStopwatchFont()
{
    QVariant val = getValue(Font);

    if (val == false) return StylesheetGenerator::DefaultFont.toString();
    else return val.toString();
}
