#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "listmodel.h"
#include "filterproxymodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //Create and populate list model instance
    CustomListModel listModel;
    listModel.addData("Isaac Newton", "isaac@gamail.com");
    listModel.addData("Alexander Graham Bell", "Alexander@gmail.com");
    listModel.addData("Leonhard Euler", "euler@gmail.com");
    listModel.addData("Nikola Tesla", "tesla@gmail.com");
    listModel.addData("Charles-Augustin de Coulomb", "Coulomb@gmail.com");
    listModel.addData("Andre-Marie Ampere", "ampere@hotmail.com");
    listModel.addData("Michael Faraday", "faraday@gmail.com");
    listModel.addData("Blaise Pascal", "blaise@hotmail.com");
    listModel.addData("Anders Celsius", "Celsius@yahoo.com");
    listModel.addData("James Watt", "AA@latinchat.com");


    //Create filter model
    FilterProxyModel filterModel;
    filterModel.setSourceModel(&listModel);


//    filterModel.setFilterRole(CustomListModel::NameRole); // this is dinamically done from qml
//    filterModel.setSortRole(CustomListModel::EmailRole); // this is dinamically done from qml


    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("filterModel", &filterModel);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
