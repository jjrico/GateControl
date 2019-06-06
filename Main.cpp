#include <iomanip>
#include <iostream>

#include "GateControl.hpp"

std::string gCurrentDate;

std::string gCurrentTime;

int main(int argc, char *const argv[]) {
	// Local Data

  GateControl gateControl;
  AuthorizationVector jVector;
  TransactionVector tVector;
  Authorization authorization;
  CardNumber card_number;
  std::string name, start, end;
  char choice;
  bool display = true;

  std::cout << "Welcome to GateControl! Please choose an option: " << std::endl;

  do {
    std::cout << std::endl;
    std::cout << "[N] New Transaction" << std::endl;
    std::cout << "[E] New Authorization" << std::endl;
    std::cout << "[R] Remove Authorization" << std::endl;
    std::cout << "[C] Change Authorization" << std::endl;
    std::cout << "[A] View Authorizations" << std::endl;
    std::cout << "[G] Get Card Authorization" << std::endl;
    std::cout << "[T] View All Transactions" << std::endl;
    std::cout << "[V] View Card Transtactions" << std::endl;
    std::cout << "[X] Exit" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;

    // ignore the newline char that follows the user input for choice, but
    // also check for multiple character input
    std::getline(std::cin, name);
    if (name.length() > 0) {
      choice = ' '; // set to invalid "choice"
    }

    switch (choice) {
    case 'N': // Attempt to open the gate with input card number
    case 'n':
      std::cout << "\nPlease enter card number: ";
      std::cin >> card_number;
      if (gateControl.AccessAllowed(card_number)) {
        std::cout << "Access granted!" << std::endl;
      } else {
        std::cout << "Access denied." << std::endl;
      }
      break;
    case 'E':	// Add new authorization
    case 'e':
      std::cout << "\nPlease enter card number: ";
      std::cin >> card_number;
      cin.ignore(); // ignore new line character
      std::cout << "Please enter name: ";
      std::getline(std::cin, name);
      std::cout << "Please enter start of access time (HHMM 24 HR format): ";
      std::cin >> start;
      std::cout << "Please enter end of access time: ";
      std::cin >> end;
      if (gateControl.AddAuthorization(card_number, name, start, end)) {
        std::cout << "\nAuthorization added!" << std::endl;
      } else {
        std::cout << "\nAuthorization already in database." << std::endl;
      }
      break;
    case 'R':	// Remove Authorization
    case 'r':
      std::cout << "\nPlease enter card number: ";
      std::cin >> card_number;
      if (gateControl.DeleteAuthorization(card_number)) {
        std::cout << "\nAuthorization deleted!" << std::endl;
      } else {
        std::cout << "\nAuthorization not found." << std::endl;
      }
      break;
    case 'C':	// Change Authorization
    case 'c':
      std::cout << "\nPlease enter card number: ";
      std::cin >> card_number;
      cin.ignore();
      std::cout << "Please enter name: ";
      std::getline(std::cin, name);
      std::cout << "Please enter start of access time (HHMM 24 HR format): ";
      std::cin >> start;
      std::cout << "Please enter end of access time: ";
      std::cin >> end;
      if (gateControl.ChangeAuthorization(card_number, name, start, end)) {
        std::cout << "\nAuthorization changed!" << std::endl;
      } else {
        std::cout << "\nCard number not found." << std::endl;
      }
      break;
    case 'A':	// List all authorizations in a formatted table
    case 'a':
      jVector = gateControl.GetAllAuthorizations();
      std::cout << "\nAuthorizations:" << std::endl;
      std::cout << std::left << std::setw(15) << "Name:"
                << "Card number:" << std::endl;
      for (const auto &i : jVector) {
        std::cout << std::left << std::setw(15) << i.name_;
        std::cout << i.number_ << std::endl;
      }
      std::cout << std::endl;
      break;
    case 'G':	// View authorization information pertaining to a certain card
    case 'g':
      std::cout << "\nPlease enter card number: ";
      std::cin >> card_number;
      // This function will throw an excpetion if card number is not found
      // No need for an if else statement.
      authorization = gateControl.GetCardAuthorization(card_number);
      std::cout << std::left << std::setw(15)
                << "Card Number: " << authorization.number_ << std::endl;
      std::cout << std::left << std::setw(15) << "Name: " << authorization.name_
                << std::endl;
      std::cout << std::left << std::setw(15)
                << "Start time: " << authorization.startTime_ << std::endl;
      std::cout << std::left << std::setw(15)
                << "End time: " << authorization.endTime_ << std::endl;
      break;
    case 'T': // List all transactions in a formatted table
    case 't':
      tVector = gateControl.GetAllTransactions();
      std::cout << std::endl;
      std::cout << std::left << std::setw(15) << "Card Number" << std::left
                << std::setw(15) << "Name" << std::left << std::setw(15)
                << "Access Allowed" << std::endl;
      for (const auto &i : tVector) {
        std::cout << std::left << std::setw(15) << i.number_ << std::left
                  << std::setw(15) << i.name_;
        if (i.accessAllowed_) {
          std::cout << std::left << std::setw(15) << "Yes" << std::endl;
        } else {
          std::cout << std::left << std::setw(15) << "No" << std::endl;
        }
      }
      std::cout << std::endl;
      break;
    case 'V':	// List all transactions attempted by a card number
    case 'v':
      std::cout << "\nPlease enter card number: ";
      std::cin >> card_number;
      tVector = gateControl.GetCardTransactions(card_number);
      std::cout << std::left << std::setw(15) << "Card Number" << std::left
                << std::setw(15) << "Name" << std::left << std::setw(15)
                << "Access Allowed" << std::endl;
      for (const auto &i : tVector) {
        std::cout << std::left << std::setw(15) << i.number_ << std::left
                  << std::setw(15) << i.name_;
        if (i.accessAllowed_) {
          std::cout << std::left << std::setw(15) << "Yes" << std::endl;
        } else {
          std::cout << std::left << std::setw(15) << "No" << std::endl;
        }
      }
      std::cout << std::endl;
      break;
    case 'X': // Exit
    case 'x':
      display = false;
      break;
    default:
      std::cout << "\nInvalid choice. Please try again.\n";
      break;
    }
  } while (display);

  std::cout << "\nThanks for using GateControl!" << std::endl;

  return (0);
}
