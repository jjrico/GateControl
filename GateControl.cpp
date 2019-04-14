//	INCLUDE FILES

#include <iostream>
#include <map>
#include <vector>

#include "GateControl.hpp"

using namespace std;

//	PUBLIC DATA
extern string gCurrentDate;

extern string gCurrentTime;

bool GateControl::AccessAllowed(CardNumber number) {

  //	LOCAL DATA
  AuthorizationIterator it = authorizationMap_.find(number);

  //	EXECUTABLE STATEMENTS
  // if element is not in map, find() returns end() element
  if (it == authorizationMap_.end()) {
    // create new transaction using *** for name and false for access
    Transaction newTransaction(number, "***", gCurrentDate, gCurrentTime,
                               false);
    transactionVector_.push_back(newTransaction);
    return false;
  }
  // iterator -> authorization . name
  Transaction newTransaction(number, it->second.name_, gCurrentDate,
                             gCurrentTime, true);
  transactionVector_.push_back(newTransaction);
  return true;
}

bool GateControl::AddAuthorization(CardNumber number, const string &name,
                                   const string &startTime,
                                   const string &endTime) {
  //	LOCAL DATA
  Authorization newAuthorization(number, name, startTime, endTime);

  //	EXECUTABLE STATEMENTS
  // insert() returns a pair. An iterator to the inserted element, and a
  // boolean which indicates whether insertion was successful
  std::pair<std::map<CardNumber, Authorization>::iterator, bool> ret;
  ret = authorizationMap_.insert(
      std::pair<CardNumber, Authorization>(number, newAuthorization));
  // return second item of pair returned by insert()
  return ret.second;
}

bool GateControl::ChangeAuthorization(CardNumber number, const string &name,
                                      const string &startTime,
                                      const string &endTime) {
  //	LOCAL DATA
  AuthorizationIterator it = authorizationMap_.find(number);

  //	EXECUTABLE STATEMENTS
  if (it == authorizationMap_.end()) {
    return false;
  }
  authorizationMap_[number] = {number, name, startTime, endTime};
  return true;
}

bool GateControl::DeleteAuthorization(CardNumber number) {
  //	NO LOCAL DATA NEEDED

  //	EXECUTABLE STATEMENTS
  if (authorizationMap_.find(number) == authorizationMap_.end()) {
    return false;
  }
  // find() returns iterator so it can be used as input for erase()
  authorizationMap_.erase(authorizationMap_.find(number));
  return true;
}

void GateControl::GetAllAuthorizations(
    AuthorizationVector &authorizationVector) {
  //	EXECUTABLE STATEMENTS

  authorizationVector = {}; // clear vector
  if (authorizationMap_.empty()) {
    return; // if map is empty, return
  }
  for (const auto & it : authorizationMap_) {
    authorizationVector.push_back(it.second); // copy authorization
  }
  return;
}

void GateControl::GetAllTransactions(TransactionVector &transactionVector) {
  //	EXECUTABLE STATEMENTS
  transactionVector = {};           // clear output vector
  if (transactionVector_.empty()) { // range check
    return;
  }
  for (const auto & i : transactionVector_) {
    transactionVector.push_back(i);
  }
  return;
}

bool GateControl::GetCardAuthorization(CardNumber number,
                                       Authorization &authorization) {
  //	LOCAL DATA
  AuthorizationIterator it = authorizationMap_.find(number);

  //	EXECUTABLE STATEMENTS
  if (it == authorizationMap_.end()) {
    return false;
  }
  authorization = it->second;
  return true;
}

bool GateControl::GetCardTransactions(CardNumber number,
                                      TransactionVector &transactionVector) {
  //	EXECUTABLE STATEMENTS
  transactionVector = {};           // clear vector
  if (transactionVector_.empty()) { // range check
    return false;
  }

  for (const auto & i : transactionVector_) {   // loop through
    if (i.number_ == number) {        // if key matches
      transactionVector.push_back(i); // push_back
    }
  }

  return true;
}
