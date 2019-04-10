
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
  //************************************************************************************
  //	LOCAL DATA
	AuthorizationIterator it = authorizationMap_.find(number);

  //************************************************************************************
  //	EXECUTABLE STATEMENTS
	if (authorizationMap_.find(number) == authorizationMap_.end()) {
		Transaction newTransaction(number, "***", gCurrentDate, gCurrentTime, false);
		transactionVector_.push_back(newTransaction);
		return false;
	}
	Authorization newAuthorization = it->second;
	Transaction newTransaction(number, newAuthorization.name_, gCurrentDate, gCurrentTime, true);
	transactionVector_.push_back(newTransaction);
  return true;
}

bool GateControl::AddAuthorization(CardNumber number, const string &name,
                                   const string &startTime,
                                   const string &endTime) {
  //************************************************************************************
  //	LOCAL DATA
  Authorization newAuthorization(number, name, startTime, endTime);

  //************************************************************************************
  //	EXECUTABLE STATEMENTS
	std::pair<std::map<CardNumber, Authorization>::iterator,bool> ret;
  ret = authorizationMap_.insert ( std::pair<CardNumber, Authorization>(number, newAuthorization) );
  return ret.second;
}

bool GateControl::ChangeAuthorization(CardNumber number, const string &name,
                                      const string &startTime,
                                      const string &endTime) {
  //************************************************************************************
  //	LOCAL DATA
	AuthorizationIterator it;
	Authorization newAuthorization(number, name, startTime, endTime);

  //************************************************************************************
  //	EXECUTABLE STATEMENTS
	it = authorizationMap_.find(number);
	if (it == authorizationMap_.end()) {
		return false;
	}
	it->second = newAuthorization;
  return true;
}

bool GateControl::DeleteAuthorization(CardNumber number) {
  //************************************************************************************
  //	LOCAL DATA

  //************************************************************************************
  //	EXECUTABLE STATEMENTS
	if (authorizationMap_.find(number) == authorizationMap_.end()) {
		return false;
	}
	authorizationMap_.erase(authorizationMap_.find(number));
  return true;
}

void GateControl::GetAllAuthorizations(
    AuthorizationVector &authorizationVector) {
  //************************************************************************************
  //	LOCAL DATA
  AuthorizationIterator it = authorizationMap_.begin();

  //************************************************************************************
  //	EXECUTABLE STATEMENTS

	authorizationVector = {}; // clear vector
	if (authorizationMap_.empty()) {
		return; // if map is empty, return
	}
	for (it = authorizationMap_.begin(); it != authorizationMap_.end(); ++it) {
		authorizationVector.push_back(it->second); // copy authorization
	}
  return;
}

void GateControl::GetAllTransactions(TransactionVector &transactionVector) {
  //************************************************************************************
  //	LOCAL DATA

  //************************************************************************************
  //	EXECUTABLE STATEMENTS
	transactionVector = {};
	if (transactionVector_.empty()) {
		return;
	}
	for (int i = 0; i < transactionVector_.size(); i++) {
		transactionVector.push_back(transactionVector_[i]);
	}
  return;
}

bool GateControl::GetCardAuthorization(CardNumber number,
                                       Authorization &authorization) {
  //************************************************************************************
  //	LOCAL DATA
	AuthorizationIterator it;

  //************************************************************************************
  //	EXECUTABLE STATEMENTS
	it = authorizationMap_.find(number);
	if (it == authorizationMap_.end()) {
		return false;
	}
	authorization = it->second;
  return true;
}

bool GateControl::GetCardTransactions(CardNumber number,
                                      TransactionVector &transactionVector) {
  //************************************************************************************
  //	LOCAL DATA

  //************************************************************************************
  //	EXECUTABLE STATEMENTS
	transactionVector = {};
	if (transactionVector_.empty()) {
		return false;
	}

	for (int i = 0; i < transactionVector_.size(); i++) {
		if (transactionVector_[i].number_ == number) {
			transactionVector.push_back(transactionVector_[i]);
		}
	}

	if (transactionVector.empty()) {
		return false;
	}

  return true;
}
