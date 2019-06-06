//	INCLUDE FILES

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include "GateControl.hpp"

using namespace std;

//	PUBLIC DATA
extern string gCurrentDate;

extern string gCurrentTime;

// This function searches for the input cardNumber in the AuthorizationMap,
// if it is found, returns true. else returns false
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

  Transaction newTransaction(number, it->second.name_, gCurrentDate,
                             gCurrentTime, true);
  transactionVector_.push_back(newTransaction);
  return true;
}

// Adds authorization to the AuthorizationMap, returns true for a successful
// insertion and false if not
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

// Removes authorization from AuthorizationMap, returns true and removes
// element if element is in Map. Else returns false.
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

// Outputs all Authorizations to an AuthorizationVector
AuthorizationVector GateControl::GetAllAuthorizations() {

  //	EXECUTABLE STATEMENTS
  if (authorizationMap_.empty()) {
    throw std::range_error("AuthorizationMap is empty.");
  }
  AuthorizationVector allAuthorizations;
  for (const auto &it : authorizationMap_) {
    allAuthorizations.push_back(it.second); // copy authorization
  }
  return allAuthorizations;
}

// Outputs all transactions to a TransactionVector
TransactionVector GateControl::GetAllTransactions() {
  //	EXECUTABLE STATEMENTS
  if (transactionVector_.empty()) { // range check
    throw std::range_error("No transactions");
  }
  TransactionVector allTransactions;
  for (const auto &i : transactionVector_) {
    allTransactions.push_back(i);
  }
  return allTransactions;
}

// Searches AuthorizationMap for given card and returns the Authorization
// that cooresponds to the given card number.
Authorization GateControl::GetCardAuthorization(CardNumber number) {
  //	LOCAL DATA
  AuthorizationIterator it = authorizationMap_.find(number);

  //	EXECUTABLE STATEMENTS
  if (it == authorizationMap_.end()) {
    throw std::range_error("Card number not found.");
  }
  Authorization authorization = it->second;
  return authorization;
}

// Searches transactionVector for all transactions cooresponding to the given
// card number. Returns a vector of all relevant transactions
TransactionVector GateControl::GetCardTransactions(CardNumber number) {
  //	EXECUTABLE STATEMENTS
  if (transactionVector_.empty()) { // range check
    throw std::range_error("No transactions found");
  }
  TransactionVector transactionVector;
  for (const auto &i : transactionVector_) { // loop through
    if (i.number_ == number) {               // if key matches
      transactionVector.push_back(i);        // push_back
    }
  }

  return transactionVector;
}
