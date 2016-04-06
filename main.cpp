#include "Fraction.cpp"

// Print array of fractions
void printList(int n, Fraction f[]) {
	cout<<"\n List of "<<n<<" fractions";
	for (int i=int_zero; i<n; i++) {
		cout<<"\n";
		f[i].printFraction();
	}
	cout<<"\n";
}

// Program header printed at beginning
void printStart() {
	cout<<"\n *********************************************";
	cout<<"\n * Project 1:  Implementing a fraction class *";
	cout<<"\n ********************************************* \n";
}

// Display options for user
int printOptions() {
	cout<<"\n Main menu options";
	cout<<"\n 1. Load list of commands from data file and compute operations";
	cout<<"\n 2. Manually enter command and compute";
	cout<<"\n 3. Load array of fractions from data file";
	cout<<"\n 4. Manually enter array of fractions";
	cout<<"\n 5. Calculate SUM of array";
	cout<<"\n 6. SORT the array";
	cout<<"\n 7. Calculate MEAN of array";
	cout<<"\n 8. Calculate MEDIAN of array";
	cout<<"\n 9. Calculate MODE of array";
	cout<<"\n Enter option (1-9): ";
	int entry;
	cin >> entry;
	return entry;
}

// Prompt user for the data file name
string requestFile() {
	string filename;
	cout<<"\n Enter data file: ";
	cin >> filename;
	return filename;
}

// Execute command (with integer arguments)
void execute(int opRef, int param[]) {
	Fraction f1(param[int_zero],param[1]);
	Fraction f2(param[2],param[3]);
	Fraction f3(param[int_zero],param[1],param[2]);
	Fraction f4(param[3],param[4],param[5]);
	switch(opRef) {
		case ADD:
			f1.add(&f2);
			break;
		case XADD:
			f1.xadd(&f2);
			break;
		case SUB:
			f1.sub(&f2);
			break;
		case MUL:
			f1.mul(&f2);
			break;
		case DIV:
			f1.div(&f2);
			break;
		case XDIV:
			f1.xdiv(&f2);
			break;
		case REC:
			f1.rec();
			break;
		case RED:
			f1.printReduction();
			f1.red();
			f1.printResult();
			break;
		case MIX:
			f1.printMix();
			f1.mix();
			f1.printMixedNumber();
			break;
		case UNM:
			f3.unm();
			break;
		case AMIX:
			f3.amix(&f4);
			break;
		case LESS:
			f1.less(&f2);
			break;
		default:
			cout<<"\n Error: Command not recognized \n";
	}
}

// Execute command (with float argument)
void execute(float decParam) {
	Fraction f;
	f.d2f(decParam);
}

// Lookup operation reference
int lookupOp(string operation) {
	string op[] = {"ADD","XADD","SUB","MUL","DIV","XDIV","REC","RED","D2F","MIX","UNM","AMIX","LESS"};

	for (int i=int_zero; i<13; i++) {
		if (operation == op[i]) return i;
	}
	return -1;
}

// Lookup number of parameters
int lookupParam(int opRef) {
	switch(opRef) {
		case ADD:
		case XADD:
		case SUB:
		case MUL:
		case DIV:
		case XDIV:
		case LESS:
			return 4;
			break;
		case REC:
		case RED:
		case MIX:
			return 2;
			break;
		case D2F:
			return 1;
			break;
		case UNM:
			return 3;
			break;
		case AMIX:
			return 6;
			break;
		default:
			cout<<"Error: Command not recognized \n";
			return 0;
	}
}

// Option #5:
// Input: an integer N and a list of N fractions
// Output: sum of the fractions
Fraction SUM(int n, Fraction f[]) {
	Fraction accumulator = f[int_zero];
	for (int i=1; i<n; i++) {
		accumulator = accumulator.add(&f[i]);
	}

	// Display the SUM as both fraction and mixed number
	cout<<"\n SUM of "<<n<<" items in array ";
	accumulator.printResult();
	accumulator.mix();
	accumulator.printResult();
	cout<<"\n";
	return accumulator;
}

// Option #6:
// Input: an integer N and a list of N fractions
// Output: list of fractions sorted in increasing order
void *SORT(int n, Fraction f[]) {
	cout<<"\n Sorting list... \n";
	Fraction temp = f[int_zero];
	for (int i=n; i>2; i--) {
		for (int j=1; j<i; j++) {
			if (f[j].less(&f[j-1])) {
				temp = f[j-1];
				f[j-1] = f[j];
				f[j] = temp;
			}
		}
	}
	printList(n,f);
}

// Option #7:
// Input: an integer N and a list of N fractions
// Output: number of fractions and their average
Fraction MEAN(int n, Fraction f[]) {
	Fraction result = SUM(n,f);

	// Convert SUM to improper fraction before calculating MEAN
	result.unm();
	Fraction divisor(n,1);
	result = result.div(&divisor);

	// Display the MEAN as both fraction and mixed number
	cout<<"\n MEAN of "<<n<<" items in array ";
	result.printResult();
	result.mix();
	if (result.number != 0) result.printResult();
	cout<<"\n";
	return result;
}

// Option #8:
// Input: an integer N and a list of N fractions
// Output: median of the fractions
void MEDIAN(int n, Fraction f[]) {
	// Make sure list is sorted first
	SORT(n,f);

	// If N is odd
	if ((n % 2) == 1) {
		cout<<"\n MEDIAN of "<<n<<" items in array ";
		f[n/2].red();
		f[n/2].printResult();
	}

	// If N is even
	else {
		Fraction f1[] = {f[n/2-1],f[n/2]};
		f1[0].unm();
		f1[0].printResult();
		f1[1].unm();
		f1[1].printResult();
		f1[0] = MEAN(2,f1);
		cout<<"\n MEDIAN of "<<n<<" items in array ";
		f1[0].mix();
		f1[0].printResult();
	}
	cout<<"\n";
}

// Option #9:
// Input: an integer N and a list of N fractions
// Output: mode of the fractions
Fraction *MODE(int n, Fraction f[], Fraction modes[]) {
	// Make sure list is sorted first
	SORT(n,f);

	// Create array of most frequently occurring fractions
	int counter = int_zero;
	int max = int_zero;
	int numOfModes = int_zero;
	Fraction diff;
	for (int i=1; i<n; i++) {
		diff = f[i].sub(&f[i-1]);
		if (diff.numerator == int_zero) counter++;
		else {
			if (counter > max) {
				max = counter;
				numOfModes = 1;
				modes[int_zero] = f[i-1];
			}
			else if (counter == max) {
				modes[numOfModes] = f[i-1];
				numOfModes++;
			}
			counter = int_zero;
		}
	}
	cout<<"\n List of MODEs from list \n";
	printList(numOfModes,modes);
	return modes;
}

// Option #1: Execute list of commands from data file
void executeList(string filename) {
	cout << "\n Loading commands from "<<filename<<" \n";

	// Convert filename from string to char[]
	char *c = new char[filename.size()+1];
	strcpy(c, filename.c_str());
	ifstream myfile(c);

	// Operation and arguments
	string operation;
	float decParam;
	int param[6];
	int opRef,numOfParams;

	// Read values from data file
	while (myfile >> operation) {
		opRef = lookupOp(operation);
		numOfParams = lookupParam(opRef);
		if (numOfParams == 1) {
			myfile >> decParam;
			execute(decParam);
		}
		else {
			for (int i=int_zero; i<numOfParams; i++) myfile >> param[i];
			execute(opRef,param);
		}
	}
	cout<<"\n";
}

// Option #2: User manually enters a single command
void inputCommand() {
	cout<<"\n Enter command: ";

	// Operation and arguments
	string operation;
	cin >> operation;
	float decParam;
	int param[6];
	int opRef = lookupOp(operation);
	int numOfParams = lookupParam(opRef);

	// Read values from console
	cout<<"Enter arguments: ";
	for (int i=0; i<numOfParams; i++) {
		if (numOfParams == 1) cin >> decParam;
		else cin >> param[i];
	}
	if (numOfParams > 1) execute(opRef,param);
	else if (numOfParams == 1) execute(decParam);
	else cout<<" No operation performed \n";
}

// Option #3: Load array of fractions from data file
int loadArray(string filename, Fraction f[]) {
	cout << "\n Loading array of fractions from "<<filename<<" \n";

	// Convert filename from string to char[]
	char *c = new char[filename.size()+1];
	strcpy(c, filename.c_str());
	ifstream myfile(c);
	int num,den;
	int n = 0;

	// Read values from data file
	while (myfile >> num) {
		myfile >> den;
		f[n].setValues(num,den);
		n++;
	}
	cout<<"\n";
	printList(n,f);
	return n;
}

// Option #4: User manually inputs list of fractions
int inputList(Fraction f[]) {
	cout<<"\n Enter zero for denominator when finished \n";
	int num,den;
	cout<<"1. Numerator: ";
	cin >> num;
	cout<<"1. Denominator: ";
	cin >> den;
	f[int_zero].setValues(num,den);
	int n = 1;
	while ((den != int_zero) && (n < 100)) {
		cout<<(n+1)<<". Numerator: ";
		cin >> num;
		cout<<(n+1)<<". Denominator: ";
		cin >> den;
		if (den == 0) n--;
		else f[n].setValues(num,den);
		n++;
	}
	return n;
}

int main() {
	printStart();

	// Display menu options to the user
	int option = printOptions();

	// Allow up to 100 fractions in the list
	Fraction f[100];

	// If list is full and all fractions are unique, every fraction is a mode
	Fraction modes[100];

	// Number of fractions in list
	int N;

	// Data file name
	string filename;

	// Run program until user enters 0
	while ((option > int_zero) && (option <= 9)) {
	    switch(option) {
		case 1: filename = requestFile();
			executeList(filename);
			break;
		case 2:	inputCommand();
			break;
		case 3: filename = requestFile();
			N = loadArray(filename,f);
			break;
		case 4: N = inputList(f);
			break;
		case 5:	SUM(N,f);
			break;
		case 6:	SORT(N,f);
			break;
		case 7: MEAN(N,f);
			break;
		case 8: MEDIAN(N,f);
			break;
		case 9: MODE(N,f,modes);
			break;
		default:
			cout<<"\n Code should never get here";
	    };

		// Remind user of menu options
		option = printOptions();
	}
}

