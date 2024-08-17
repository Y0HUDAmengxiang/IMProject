#include <Windows.h>
#include <iostream>
#include "MySQL/CMySql.h"
#include "CKernel.h"

using namespace std;


int main() {
	CKernel Ck;
	if (!Ck.startServer()) {
		cout << "start server fail" << endl;
	}

	while (true) {
		Sleep(10000);
		cout << "server is running" << endl;
	}
	return 0;
}