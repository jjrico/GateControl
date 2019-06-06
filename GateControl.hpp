#pragma once

#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef uint32_t CardNumber;

typedef uint32_t GateNumber;

// Authorization sruct used to create a vector of those allowed inside the gate
struct Authorization {
  Authorization() {}

  Authorization(CardNumber number, const string &name, const string &startTime,
                const string &endTime)
      : number_(number), name_(name), startTime_(startTime), endTime_(endTime) {
  }

  CardNumber number_; // Cardnumber

  string name_; // Employee name

  string startTime_; // Beginning of access window

  string endTime_; // End of access window
};

typedef map<CardNumber, Authorization> AuthorizationMap;
typedef AuthorizationMap::iterator AuthorizationIterator;

typedef vector<Authorization> AuthorizationVector;

struct Transaction {
  Transaction() {}

  Transaction(CardNumber number, const string &name, const string &date,
              const string &time, bool accessAllowed)
      : number_(number), name_(name), date_(date), time_(time),
        accessAllowed_(accessAllowed) {}

  CardNumber number_;

  string name_;

  string date_;

  string time_;

  bool accessAllowed_;
};

typedef vector<Transaction> TransactionVector;

class GateControl {
private:
  AuthorizationMap authorizationMap_;

  TransactionVector transactionVector_;

public:
  bool AccessAllowed(CardNumber number);

  bool AddAuthorization(CardNumber number, const string &name,
                        const string &startTime, const string &endTime);

  bool ChangeAuthorization(CardNumber number, const string &name,
                           const string &startTime, const string &endTime);

  bool DeleteAuthorization(CardNumber number);

  AuthorizationVector GetAllAuthorizations();

  TransactionVector GetAllTransactions();

  Authorization GetCardAuthorization(CardNumber number);

  TransactionVector GetCardTransactions(CardNumber number);
};
