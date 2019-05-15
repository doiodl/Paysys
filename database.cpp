#include "database.h"

QJsonObject Shop::paySys_SSC(QJsonObject &pay){
    QJsonObject object{{"SSC", this->BanksEquireOn.value("Secret Service Code").toString()},{"name of shop",this->name,}};
    pay["SSC bank"] = object;
    return  pay;
}

bool bankAcquire::Check_fromShopPay(QJsonObject &pay){
    QString NameShop = pay.value("SSC bank").toObject().value("name of shop").toString();
    QString SSC = pay.value("SSC bank").toObject().value("SSC").toString();
    for(int i = 0; i < this->ConnectedShops.count();i++){
        if (this->ConnectedShops[i].toObject().value("shop's name").toString() == NameShop){
            if (this->ConnectedShops[i].toObject().value("SSC").toString() == SSC){
                qWarning() << "SSC совпал!";
                pay.remove("SSC bank");
                return true;
            }else{
                qWarning() << "SSC не совпал!";
                return false;
            }
        }else{
            if (i == ConnectedShops.count()-1){
                qWarning() << "Банк не обслуживает магазин!";
                return false;
            }
        }
    }
    return false;
}

QString bankAcquire::getCodeOfPaySys(QString cardnum,QString &NameOfSys){
    int paySysCode = (cardnum.mid(0, 1)).toInt();
    for (int i=0; i< this->ConnectedSystems.count();i++){
//        qWarning() << ConnectedSystems[i].toObject().value("Code").toString().toInt();
        if (ConnectedSystems[i].toObject().value("Code").toString().toInt() == paySysCode){
            NameOfSys = ConnectedSystems[i].toObject().value("name").toString();
            return ConnectedSystems[i].toObject().value("Code Access Bank Acquire").toString();
        }else{
            if (i == ConnectedSystems.count()-1){
                qWarning() << "Платежная система не подключена к банку Экваиру!";
                NameOfSys = "NaN";
                return "NaN";
            }
        }
    }
}

QString bankAcquire::setBArequest(QJsonObject &pay){
    QString NameOfPaySys;
    QString CABA = this->getCodeOfPaySys(pay.value("cardnumber").toString(),NameOfPaySys);
    if (CABA!="NaN"){
        QJsonObject object{{"name of bank",this->nameofBank}, {"CABA",CABA}};
        pay["BA Request"] = object;
        return NameOfPaySys;
    }else{
        return NameOfPaySys;
    }
}

bool paySistem::checkCABA(QJsonObject &pay, QString &nameOfBankE,paySistem* &paysys){
    QString nameBank = pay.value("BA Request").toObject().value("name of bank").toString();
    QString CABA = pay.value("BA Request").toObject().value("CABA").toString();
    for (int i=0; i<this->BankAcquire.count();i++){
        if (this->BankAcquire[i].toObject().value("name").toString() == nameBank){
            if (this->BankAcquire[i].toObject().value("CABA").toString() == CABA){
                qWarning() << "CABA совпал у Платежной системы и Банка Экваира";
                pay.remove("BA Request");
                nameOfBankE = this->setCOAPrequest(pay);
                if (nameOfBankE !="NaN"){
                    paysys = this;
                    return true;
                }else{
                  return false;
                }
            }else{
                qWarning() << "CABA не совпал у Платежной системы и Банка Экваира";
                return true;
            }
        }else{
            if (i == this->BankAcquire.count()-1){
                qWarning() << "Платежная система не поддерживает банк Экваир";
                return true;
            }
        }
    }

}


QString paySistem::setCOAPrequest(QJsonObject &pay){
    QString nameOfBankE;
    QString COAP = this->getCOAPfromPAY(pay.value("cardnumber").toString(), nameOfBankE);
    if (COAP!="NaN"){
        QJsonObject object{{"name of pay Sys",this->namesys}, {"COAP",COAP}};
        pay["PaySYS Request to Emitent"] = object;
        return nameOfBankE;
    }else{
        return nameOfBankE;
    }
}

bool BankEmitetList::check_COAP(QJsonObject &pay, QString nameOfBankE, BankEmitet* &b){
    for (int i = 0; i<this->banks.count();i++){
        if (banks[i]->nameofBank == nameOfBankE){
            return banks[i]->check_COAP_inBank(pay, b);
        }else{
            if (i == banks.count()-1){
                qWarning() << "Банка Эмитета нет в системе";
                return false;
            }
        }
    }
}


bool BankEmitet::check_COAP_inBank(QJsonObject &pay, BankEmitet* &b){
    QString nameofPaySys = pay.value("PaySYS Request to Emitent").toObject().value("name of pay Sys").toString();
    QString COAP = pay.value("PaySYS Request to Emitent").toObject().value("COAP").toString();
    for (int i = 0; i<this->PaySystemsWithWorks.count();i++){
        if(nameofPaySys == PaySystemsWithWorks[i].toObject().value("name").toString()){
            if(COAP == PaySystemsWithWorks[i].toObject().value("COAP").toString()){
                qWarning() << "Имя и COAP в банке Эмитете совпал с запросом от платежной системе";
                b = this;
                return true;
            }else{
                qWarning() << "COAP не совпал у Банка Эмитета и запроса";
                return false;
            }
        }else{
            if( i == PaySystemsWithWorks.count()-1){
                qWarning() << "Банк Эмитет не работает с платежной системой!";
                return false;
            }
        }
    }
}


bool BankEmitet::check_card(QJsonObject &pay){
    QString cardnumber = pay["cardnumber"].toString(); // проверка карты на наличие денег!
    for (int i = 0; i < this->lencards; i++){
        if (this->cards[i].cardNumber == cardnumber ){ // проверяем карты по базе на совпадение номера карты
            if (this->cards[i].CVC == pay["CVC"].toString()){
                if (this->cards[i].cardHolder == pay["cardholder"].toString()){
                    if (this->cards[i].MMYY == pay["MMYY"].toString()){
                        if (this->cards[i].balance.toDouble() > pay["paybalance"].toString().toDouble()){
                            double dif = this->cards[i].balance.toDouble() - pay["paybalance"].toString().toDouble();
                            this->cards[i].balance = QString::number(dif); // списали деньги
                            return true;
                        }else{
                            qWarning() << "Не достаточно денег!";
                            return false;
                        }

                    }else {
                        qWarning() << "Не совпадает MMYY";
                        return false;
                    }

                }else{
                    qWarning() << "Не совпадает cardholder";
                    return false;
                }
            }else {
                qWarning() << "Не совпадает CVC";
                return false;
            }

        }else {
            if (i== this->lencards - 1){
                qWarning() << "Такой карточки нет в системе!";
                return false;
            }

        }
    }
}

QString paySistem::getCOAPfromPAY(QString cardnum,QString &nameOfBankE){
    int bankCode = (cardnum.mid(1, 1)).toInt();
    for(int i=0; i < this->BankEmitets.count();i++){
        if (this->BankEmitets[i].toObject().value("Codificator of Bank").toString().toInt() == bankCode){
            nameOfBankE = BankEmitets[i].toObject().value("name").toString();
            return BankEmitets[i].toObject().value("Code of access pay").toString();
        }else{
            if ( i == BankEmitets.count()-1){
                nameOfBankE =  "NaN";
                return "NaN";
            }
        }
    }
}
bool worldSistemes::checkCABAInPS(QJsonObject &myPay, QString NameOfPaySys,QString &nameOfBankE,paySistem* &paysys){
    for ( int i = 0; i<this->kd.count();i++){
        if (this->kd[i]->namesys == NameOfPaySys){
            return this->kd[i]->checkCABA(myPay,nameOfBankE,paysys);
        }else{
            if (i == this->kd.count()-1 ){
                qWarning() << "Не к одной платежной системе не подошел CABA";
                return false;
            }
        }
    }
}

bool EcoSystemOf::checkPayBack(QJsonObject &myPay, BankEmitet* &bankEmitet,paySistem* &paysys){
    this->SHOP->paySys_SSC(myPay);
    if(this->BankB->Check_fromShopPay(myPay)){
         QString NameOfPaySys = this->BankB->setBArequest(myPay);
         if (NameOfPaySys!="NaN"){
             QString nameOfBankE;
             if(this->worldsys->checkCABAInPS(myPay,NameOfPaySys,nameOfBankE,paysys)){
                 if(this->BanksE->check_COAP(myPay,nameOfBankE,bankEmitet)){
                     if(bankEmitet->check_card(myPay)){
                         return true;
                     }
                 }
             }
         }
    }
    return false;
}

bool EcoSystemOf::getPayAll(QJsonObject &myPay){
    BankEmitet *bankEmitet;
    paySistem *paysys;
    if (this->checkPayBack(myPay,bankEmitet,paysys)){
            qWarning()<< " Все проверки прошли";
            bankEmitet->balanceUp(myPay["paybalance"].toString());
            paysys->BalanceUpPaySys(myPay["paybalance"].toString());
            this->BankB->balanceUp(myPay["paybalance"].toString(),bankEmitet->procent,paysys->procent);
            this->SHOP->BalanceUp(this->BankB->procent,myPay["paybalance"].toString());
            qWarning() << this->SHOP->balance;
            qWarning() << this->BankB->balance;
            qWarning() << bankEmitet->balance;
            qWarning() << paysys->balance;
            return true;
    }else{
        return false;
    }
}

