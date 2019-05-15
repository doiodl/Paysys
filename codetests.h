//#ifndef DATABASE_H
//#define DATABASE_H
//#include "QString"
//#include "QObject"
//#include <QDebug>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QFile>
//#include <QJsonArray>
//#include <QVector>
//#endif // DATABASE_H

//namespace Ui {
//class Card; // peoples card
//class paySistem; // like visa master
//class worldSistemes; // system of paysystems
//class BankEmitet; //bank who give me card
//class BankAcquire ; // who get money
//class Shop; // shop
//}
//QJsonArray initialisation_cards(QString filename){
//    QString val;
//    QFile file;
//    file.setFileName(filename);
//    file.open(QIODevice::ReadOnly | QIODevice::Text);
//    val = file.readAll();
//    file.close();
//    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
//    QJsonObject sett2 = d.object();
//    QJsonValue value = sett2.value(QString("card"));
//    QJsonArray item = value.toArray();
//    return item;

//};
//class Card: public QObject
//{
//public:
//    QString cardHolder;
//    QString cardNumber;
//    QString CVC;
//    QString MMYY;
//    QString balance;
//    Card(){
//        cardHolder="";
//        cardNumber="";
//        CVC="";
//        MMYY="";
//        balance="";
//    }
//    Card( Card &other){ //constuct copy
//        this->CVC= other.CVC;
//        this->MMYY=other.MMYY;
//        this->balance=other.balance;
//        this->cardHolder=other.cardHolder;
//        this->cardNumber=other.cardNumber;
//    }
//    Card & operator = (Card &other){ //constuct inni
//        this->CVC= other.CVC;
//        this->MMYY=other.MMYY;
//        this->balance=other.balance;
//        this->cardHolder=other.cardHolder;
//        this->cardNumber=other.cardNumber;
//        return *this;
//    }
//    ~Card(){
//    }
//};

//class paySistem: public QObject
//{
//private:
//    QString Code;
//    QVector <QVector<QString>> banksWhichApp = {{"Bank A", "21" }, {"Bank B", "23"}};
//    int lencards;
//public:
//    double procent;
//    double balance;
//    QString *cardsNum;
//    QString namesys;
//    paySistem(){
//         qDebug() << "d";
//    }
//    paySistem(QString name){
//        namesys =  name;
//        balance = 0;
//        if (namesys == "visa"){
//            procent = 0.001;
//            Code = "4";
//            QJsonArray item = initialisation_cards("/Users/timurzajnullin/myPay/cardVisa.json");
//            lencards = item.count();
//            cardsNum = new QString[lencards];
//            for (int i=0; i < item.count(); i++){
//                cardsNum[i] = item[i].toObject().value("cardNumber").toString();
//              }
//        } else if (namesys == "mastercard"){
//            procent = 0.002;
//            Code = "5";
//            QJsonArray item = initialisation_cards("/Users/timurzajnullin/myPay/cardMaster.json");
//            lencards = item.count();
//            cardsNum = new QString[lencards];
//            for (int i=0; i < item.count(); i++){
//                cardsNum[i] = item[i].toObject().value("cardNumber").toString();
//              }
//        }else {
//            qDebug() << "non name system";
//        }

//    }
//    bool checkBanks(QString nameOfBank,QString &nameOfbankEmitet){
//        QVector <QVector<QString>> banksCodificate = {{"Bank A", "2" }, {"Bank B", "3"}};
//        for (int i = 0; i < banksCodificate.length(); i++ ){
//            if (nameOfBank.mid(1, 1) == banksCodificate[i][1]){
//                nameOfbankEmitet = banksCodificate[i][0];
//                return true;
//            }
//        }
//        return false;
//    }
//    void BalanceUpPaySys(QString str){
//        int paySysCode = str.toDouble();
//        balance = balance + paySysCode*procent;
//    }
//    void toCreatePod(QJsonObject &myPay){
//        if (this->namesys == "visa"){
//            myPay["paySys"] = "visa";
//            QString cod = "100";
//            myPay["codeFromPay"] = QString::fromLatin1(cod.toLatin1().toHex());
//        }else if (this->namesys == "mastercard"){
//            myPay["paySys"] = "mastercard";
//            QString cod = "101";
//            myPay["codeFromPay"] = QString::fromLatin1(cod.toLatin1().toHex());
//        }

//    }
//    //~paySistem();
//};

//class worldSistemes: public QObject
//{
//private:
//    paySistem Visa;
//    paySistem Mastercard;
//public:
//    QList<paySistem*> kd;
//    worldSistemes():Visa("visa"),Mastercard("mastercard"){
//        qWarning() << &(this->Visa);
//        kd.append(&(this->Visa));
//        kd.append(&(this->Mastercard));
//    }

//};



//class bankAcquire: public QObject
//{
//private:

//    QString plugPaySys[2] = {"visa","mastercard"};
//public:
//    double balance = 0;
//    double procent = 0.02;
//    QString nameofBank = "Bank B";
//    bool checkPays(QString name, QString &nameOfSys){
//        QString tmp;
//        int paySysCode = (name.mid(0, 1)).toInt();
//        if (paySysCode == 4){
//            tmp = "visa";
//            nameOfSys = tmp;
//        } else if (paySysCode == 5){
//            tmp = "mastercard";
//            nameOfSys = tmp;
//        }else {
//             qDebug() << "PaySys not exist";
//             return false;
//        }
//        for (int i=0; i < plugPaySys->length(); i++){
//            if (plugPaySys[i] == tmp){
//                return true;
//            }
//        }
//        return false;
//    }
//    void balanceUp(QString str, double procentEm,double paySys){
//        int paySysCode = str.toDouble();
//        balance = balance + paySysCode*(procent-procentEm-paySys);
//    }


//};

//class BankEmitet: public QObject{
//private:

//    Card *cards;
//    int lencards;

//    bool checkPaySysCode(QJsonObject pay);
//    bool checkMoneyOnCard(QJsonObject pay);
//public:
//    double procent = 0.017;
//    double balance = 0;
//    QString nameofBank = "Bank A";
//    BankEmitet(){
//          QJsonArray item = initialisation_cards("/Users/timurzajnullin/myPay/test.json");
//          lencards = item.count();
//          cards = new Card[lencards];
//          for (int i=0; i < item.count(); i++){
//              cards[i].CVC = item[i].toObject().value("CVC").toString();
//              cards[i].cardNumber = item[i].toObject().value("cardNumber").toString();
//              cards[i].cardHolder= item[i].toObject().value("cardHolder").toString();
//              cards[i].MMYY =item[i].toObject().value("MM/YY").toString();
//              cards[i].balance = item[i].toObject().value("balance").toString();

//            }
//          }
//    void balanceUp(QString str){
//        int paySysCode = str.toInt(); // деньги в запросе!
//        balance = balance + paySysCode*procent;
//    }
//    bool dataOfRequest(QJsonObject pay);


//};
//bool BankEmitet::checkPaySysCode(QJsonObject pay){
//    QString codeFromPay = pay["codeFromPay"].toString() ;
//    QString hex =  QString::fromLatin1(QByteArray::fromHex(codeFromPay.toLatin1()));
//    if (pay["paySys"].toString() == "visa"){
//        if (hex == "100"){
//            return  true;
//        }else{
//            return false;
//        }
//    }else if (pay["paySys"].toString() == "mastercard"){
//        if (hex == "101"){
//            return  true;
//        }else{
//            return false;
//        }
//    }else {
//        qWarning() << "Система не поддерживается в банке на проверке системы!";
//        return false;
//    }
//}

//bool BankEmitet::checkMoneyOnCard(QJsonObject pay){
//    QString cardnumber = pay["cardnumber"].toString(); // проверка карты на наличие денег!
//    for (int i = 0; i < this->lencards; i++){
//        if (this->cards[i].cardNumber == cardnumber ){ // проверяем карты по базе на совпадение номера карты
//            if (this->cards[i].CVC == pay["CVC"].toString()){
//                if (this->cards[i].cardHolder == pay["cardholder"].toString()){
//                    if (this->cards[i].MMYY == pay["MMYY"].toString()){
//                        if (this->cards[i].balance.toDouble() > pay["paybalance"].toString().toDouble()){
//                            this->balanceUp(pay["paybalance"].toString()); // банк взял комиссию с платежа
//                            double dif = this->cards[i].balance.toDouble() - pay["paybalance"].toString().toDouble();
//                            this->cards[i].balance = QString::number(dif); // списали деньги
//                            return true;
//                        }else{
//                            qWarning() << "Не достаточно денег!";
//                            return false;
//                        }

//                    }else {
//                        qWarning() << "Не совпадает MMYY";
//                        return false;
//                    }

//                }else{
//                    qWarning() << "Не совпадает cardholder";
//                    return false;
//                }
//            }else {
//                qWarning() << "Не совпадает CVC";
//                return false;
//            }

//        }else {
//            qWarning() << "Такой карточки нет в системе!";
//            return false;
//        }
//    }
//}

//bool BankEmitet::dataOfRequest(QJsonObject pay){
//    if (pay["type"].toString() == "pay"){
//        // проверить если откуда платеж, виза или мастер кард! потом проверить по кодификатору
//        // если код совпал то проверить наличие денег, если норм то тру
//        // отправить сумму - процент за межбанковскую комиссию и пополнить свой счет
//        //
//        if (this->checkPaySysCode(pay)){
//               return this->checkMoneyOnCard(pay);
//        }else {
//            qWarning() << "НЕ совпадает система и ее код! ";
//            return false;
//        }

//    } else{
//        qWarning() << "nothing";
//        return false;
//    }
//}
//class Shop: public QObject{
//private:

//public:
//    double balance = 0;
//    QString BanksEquireOn = "Bank B";
//    bool checkMoneyInBank(QString name,QString name2);
//    void BalanceUp(double procent, QString money){
//        balance += (money.toDouble())*(1-procent);
//    }
//};

//bool Shop::checkMoneyInBank(QString name, QString name2){
//    if (name == name2){
//        return true;
//    } else{
//    qWarning() << "the Acquire bank named " + BanksEquireOn + " is not available";
//    return false;
//    }
//}

//class EcoSystemOf: public QObject{

//public:
//    BankEmitet bankA;
//    Shop Magnit;
//    bankAcquire bankB;
//    worldSistemes PayEveryWhere;
//    QList<BankEmitet*> banksEmitet;
//    EcoSystemOf(): bankA() {
//    banksEmitet.append(&(this->bankA));
//    }
//    bool checkPayBack(QJsonObject myPay);

//};

//bool EcoSystemOf::checkPayBack(QJsonObject myPay){
//    QString str = myPay["cardnumber"].toString(); // номер карточки пользователя
//    if (this->Magnit.checkMoneyInBank(this->Magnit.BanksEquireOn,this->bankB.nameofBank)){
//        QString nameOfSys;
//        if (this->bankB.checkPays(str, nameOfSys)){ // проверили какой платежной системе принадлежит карточка, подключены ли мы к ней + вернули названия системы
//            for (int i = 0 ; i < 2; i++){
//                if (this->PayEveryWhere.kd[i]->namesys == nameOfSys){ // сравниваем имена систем, с той что определили
//                    this->PayEveryWhere.kd[i]->toCreatePod(myPay);
//                    QString nameOfbankEmitet; // получим именка банка, если он подключен к платежной системе
//                    if (this->PayEveryWhere.kd[i]->checkBanks(str,nameOfbankEmitet)){// в той системе проверяем подключен ли банк или нет
//                        for (int p = 0; p < 1; p++){
//                            if (this->banksEmitet[p]->nameofBank == nameOfbankEmitet){// проверили наличие банка эмитета в системе
//                               if (this->banksEmitet[p]->dataOfRequest(myPay)){
//                                    this->PayEveryWhere.kd[i]->BalanceUpPaySys(myPay["paybalance"].toString());
//                                    this->bankB.balanceUp(myPay["paybalance"].toString(),this->banksEmitet[p]->procent,this->PayEveryWhere.kd[i]->procent);
//                                    this->Magnit.BalanceUp(this->bankB.procent,myPay["paybalance"].toString());
//                               }else{
//                                return false; // zapros ne proshel
//                               }
//                                // доделать функцию проверки данных и все
//                            }else{
//                                qWarning() << "Bank Emitet не включен!";
//                                return false;
//                            }
//                        }
//                    }else{
//                        qWarning() << nameOfbankEmitet;
//                        qWarning() << "Bank Emitet не подключен!";
//                        return false;
//                    }
//                break;
//                }else{
//                    qWarning() << this->PayEveryWhere.kd[i]->namesys;
//                    qWarning() << "Такой  nen системы нет!";
//                    return false;
//                }

//            }
//        }else{
//             return false;
//        }

//    }
//    else{
//        return true;
//    }
//}






