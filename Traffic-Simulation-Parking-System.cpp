#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

struct CarNode {
string plate;
CarNode* left;
CarNode* right;

CarNode(string p) {
plate = p;
left = NULL;
right = NULL;
}
};

CarNode* root = NULL; 


CarNode* insertCar(CarNode* node, string plate) {
if (node == NULL) {
return new CarNode(plate);
}
if (plate < node->plate) {
node->left = insertCar(node->left, plate);
}  if (plate > node->plate) {
node->right = insertCar(node->right, plate);
}
return node;

}

bool searchCar(CarNode* node, string plate) {
if (node == NULL) {
return false;
}
if (node->plate == plate) {
return true;
}
if (plate < node->plate) {
return searchCar(node->left, plate);
} else {
return searchCar(node->right, plate);
}
}
queue<string> signalQueue; 
stack<string> parkingLot; 
void carArrives() {
string plate;
cout << "Enter car plate number: ";
cin >> plate;
signalQueue.push(plate);
cout << "Car " << plate << " is now waiting at the signal.\n";
}

void greenLight() {
if (signalQueue.empty()) {
cout << "No cars waiting at the signal.\n";
return;
}
string plate = signalQueue.front();
signalQueue.pop();
cout << "Car " << plate << " passed the signal.\n";
}

void parkCar() {
if (signalQueue.empty()) {
cout << "No car at the signal to park.\n";
return;
}
string plate = signalQueue.front();
signalQueue.pop();
if (searchCar(root, plate)){
	cout<<"Error: Car with plate number"<<" "<<plate<<" is already parked. Duplicate plate number are not allowed\n.";
	return ;
}

parkingLot.push(plate);
root = insertCar(root, plate);

cout << "Car " << plate << " has been parked.\n";
}

void leaveParking() {
if (parkingLot.empty()) {
cout << "Parking lot is empty.\n";
return;
}
string plate = parkingLot.top();
parkingLot.pop();
cout << "Car " << plate << " has left the parking lot.\n";
}

void searchCarMenu() {
string plate;
cout << "Enter plate number to search: ";
cin >> plate;

if (searchCar(root, plate)) {
cout << "Car " << plate << " was found in parking records.\n";
} else {
cout << "Car " << plate << " not found.\n";
}
}

void viewQueue() {
if (signalQueue.empty()) {
cout << "No cars waiting.\n";
return;
}

queue<string> temp = signalQueue; 
cout << "Cars waiting at signal: ";
while (!temp.empty()) {
cout << temp.front() << " ";
temp.pop();
}
cout << endl;
}

void viewParking() {
if (parkingLot.empty()) {
cout << "Parking lot is empty.\n";
return;
}

stack<string> temp = parkingLot; 
cout << "Cars in parking lot (top to bottom): ";
while (!temp.empty()) {
cout << temp.top() << " ";
temp.pop();
}
cout << endl;
}

int main() {
int choice;

do {
cout << "\n===== TRAFFIC SIMULATION =====\n";
cout << "1. Car arrives (join signal queue)\n";
cout << "2. Green light (next car passes)\n";
cout << "3. Park a car\n";
cout << "4. Car leaves parking\n";
cout << "5. Search car by plate number\n";
cout << "6. View cars waiting at signal\n";
cout << "7. View cars in parking lot\n";
cout << "8. Exit\n";
cout << "Enter choice: ";
cin >> choice;

switch (choice) {
case 1:
carArrives();
break;
case 2:
greenLight();
break;
case 3:
parkCar();
break;
case 4:
leaveParking();
break;
case 5:
searchCarMenu();
break;
case 6:
viewQueue();
break;
case 7:
viewParking();
break;
case 8:
cout << "Exiting program. Bye!\n";
break;
default:
cout << "Invalid choice, try again.\n";
}

} while (choice != 8);

return 0;
}
