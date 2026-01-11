#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "excelhandler.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QCoreApplication::setOrganizationName("Enstein Robots and Automations Pvt Limited");
  QCoreApplication::setApplicationName("Enstein Stock Manager");
  QCoreApplication::setApplicationVersion("1.0.0");

  qmlRegisterType<ExcelHandler>("ExcelHandler", 1, 0, "ExcelHandler");

  QQmlApplicationEngine engine;
  engine.loadFromModule("Enstein", "Main");

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
