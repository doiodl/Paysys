#ifndef DATABASE_H
#define DATABASE_H
#include "QString"
#include "QObject"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QVector>
#include <iterator>

#endif // DATABASE_H

namespace Ui {
class Card; // peoples card
class paySistem; // like visa master
class worldSistemes; // system of paysystems
class BankEmitet; //bank who give me card
class BankAcquire ; // who get money
class Shop; // shop
}

class Card: public QObject
{
public:
    QString cardHolder;
    QString cardNumber;
    QString CVC;
    QString MMYY;
    QString balance;
    Card(){
        cardHolder="";
        cardNumber="";
        CVC="";
        MMYY="";
        balance="";
    }
    ~Card(){
    }
};
class paySistem_abst: public QObject
{
protected:
public:
    virtual void BalanceUpPaySys(QString str)=0;
};
class paySistem: public paySistem_abst
{
private:
public:
    QString Code;
    QJsonArray BankEmitets;
    QJsonArray BankAcquire;
    double procent;
    double balance;
    QJsonArray CardsNumber;
    QString namesys;
    QString COAP; //Code of access pay
    paySistem(){}
    paySistem(QString name, QString procent, QString codificator, QString balance, QString COAP, QJsonArray BanksEmitets, QJsonArray BankAcquire, QJsonArray IC ){
        this->namesys = name;
        this->procent = procent.toDouble();
        this->balance = balance.toDouble();
        this->Code = codificator;
        this->COAP = COAP;
        this->BankAcquire = BankAcquire;
        this->BankEmitets = BanksEmitets;
        this->CardsNumber = IC;
    }

    void BalanceUpPaySys(QString str) override{
        int paySysCode = str.toDouble();
        balance = balance + paySysCode*procent;
    }
    // патерны проектирования

    bool checkCABA(QJsonObject &pay,QString &nameOfBankE,paySistem* &paysys);
    QString setCOAPrequest(QJsonObject &pay);
    QString getCOAPfromPAY(QString cardnum,QString &nameOfBankE);
//    ~paySistem();
};
// abstract класс от него  наследовать платежную систему.
// отсоеднить
//
class worldSistemes: public QObject
{
private:
public:
    QList<paySistem*> kd;
    worldSistemes(){}
    worldSistemes(QJsonArray m){
        QJsonArray::Iterator iterator = m.begin();
        for (int i= 0; i < m.count(); i++) {
            QString name = iterator->toObject().value("name").toString();
            QString procent = iterator->toObject().value("procent").toString();
            QString codificator = iterator->toObject().value("codificator").toString();
            QString balance = iterator->toObject().value("balance").toString();
            QString COAP = iterator->toObject().value("Code of access PaySystem").toString();
            QJsonArray BanksEmitets = iterator->toObject().value("Banks Emitets with work").toArray();
            QJsonArray BankAcquire = iterator->toObject().value("Banks Aquire with work").toArray();
            QJsonArray IC = iterator->toObject().value("Issued cards").toArray();
            paySistem *k = new paySistem(name,procent,codificator,balance,COAP,BanksEmitets,BankAcquire,IC);
            kd.append(k);
            iterator++;
          }
    }

    bool checkCABAInPS(QJsonObject &myPay, QString NameOfPaySys, QString &nameOfBankE,paySistem* &paysys);
};

class bankAcquire: public QObject
{
private:
public:
    double balance;
    double procent;
    QString nameofBank;
    QJsonArray ConnectedSystems;
    QJsonArray ConnectedShops;
    bankAcquire(QJsonObject item){
        nameofBank = item.value("name").toString();
        balance = item.value("balance").toString().toDouble();
        procent = item.value("procent").toString().toDouble();
        ConnectedSystems = item.value("ConnectedSystems").toArray();
        ConnectedShops = item.value("ConnectedShops").toArray();

    }
    void balanceUp(QString str, double procentEm,double paySys){
        int paySysCode = str.toDouble();
        balance = balance + paySysCode*(procent-procentEm-paySys);
    }

    bool Check_fromShopPay(QJsonObject &pay);
    QString getCodeOfPaySys(QString cardnum,QString &NameOfSys);
    QString setBArequest(QJsonObject &pay);
};

class BankEmitet: public QObject{
private:
    int lencards;
    bool checkPaySysCode(QJsonObject pay);
    bool checkMoneyOnCard(QJsonObject pay);
public:
    Card *cards;
    double procent;
    double balance;
    QString nameofBank;
    QJsonArray PaySystemsWithWorks;
    BankEmitet(QJsonObject item) {
        nameofBank = item.value("name").toString();
        balance = item.value("balance").toString().toDouble();
        procent = item.value("procent").toString().toDouble();
        lencards = item.value("cards").toArray().count();
        cards = new Card [lencards];
        for (int i= 0; i < lencards; i++) {
            cards[i].CVC = item.value("cards").toArray()[i].toObject().value("CVC").toString();//iterator->toObject().value("CVC").toString();
            cards[i].cardNumber = item.value("cards").toArray()[i].toObject().value("cardNumber").toString();//iterator->toObject().value("cardNumber").toString();
            cards[i].cardHolder= item.value("cards").toArray()[i].toObject().value("cardHolder").toString();//iterator->toObject().value("cardHolder").toString();
            cards[i].MMYY = item.value("cards").toArray()[i].toObject().value("MM/YY").toString();//iterator->toObject().value("MM/YY").toString();
            cards[i].balance = item.value("cards").toArray()[i].toObject().value("balance").toString();//iterator->toObject().value("balance").toString();
          }
        PaySystemsWithWorks = item.value("Pay Systems with works").toArray();
    }
    void balanceUp(QString str){
        int paySysCode = str.toInt(); // деньги в запросе!
        balance = balance + paySysCode*procent;
    }
    bool check_COAP_inBank(QJsonObject &pay,BankEmitet* &b);
    bool check_card(QJsonObject &pay);
    ~BankEmitet(){
        delete [] cards;
    }
};

class BankEmitetList:public QObject{
public:
    QList<BankEmitet *> banks;
    BankEmitetList(QJsonArray m){
        QJsonArray::Iterator iterator = m.begin();
        for (int i= 0; i < m.count(); i++) {
            BankEmitet *k = new BankEmitet(m[i].toObject());
            banks.append(k);
            //iterator++;
    }
    }

    bool check_COAP(QJsonObject &pay, QString nameOfBankeE, BankEmitet* &b);

};


class Shop: public QObject{
private:
public:
    double balance;
    QJsonObject BanksEquireOn;
    QString name;
    Shop(QJsonObject item){
        balance = item.value("balance").toDouble();
        name = item.value("name").toString();
        BanksEquireOn = item.value("bankAcquireOn").toObject();
    }
    void BalanceUp(double procent, QString money){
        balance += (money.toDouble())*(1-procent);
    }

    QJsonObject paySys_SSC(QJsonObject &pay);

};


class EcoSystemOf: public QObject{
public:
    worldSistemes *worldsys;
    Shop *SHOP;
    bankAcquire *BankB;
    BankEmitetList *BanksE;
 EcoSystemOf(){ QString filename = "/Users/timurzajnullin/myPay/EcoSysAll.json";
    QString val;
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("worldpaySystems"));
    QJsonArray item = value.toArray();

    worldsys = new worldSistemes(item);

    SHOP = new Shop(sett2.value("Shop").toObject());

    BankB = new bankAcquire(sett2.value("bankAcquire").toObject());

    BanksE = new BankEmitetList(sett2.value("BankEmitets").toArray());
    }

    bool checkPayBack(QJsonObject &myPay,BankEmitet* &bankEmitet,paySistem* &paysys);
    bool getPayAll(QJsonObject &myPay);
};

